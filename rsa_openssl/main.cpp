#include <iostream>
#include <bitset>
#include <string>
#include <sstream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <vector>
#include <openssl/bio.h>
#include <openssl/pem.h>
#include <openssl/rsa.h>
#include <openssl/bn.h>
#include <algorithm>
using namespace std;
#define TARGET_RSA_LEN 1984 
// ----------------------------------------------------------------------------
std::string str_hex2byte(std::string str)
{
	string bstr;
	str.erase(remove_if(str.begin(), str.end(), [](char ch) {
		return !(
			(ch >= '0' && ch <= '9') ||
			(ch >= 'A' && ch <= 'Z') ||
			(ch >= 'a' && ch <= 'z')); }), str.end());
	int n = str.length();
	for (int i = 0; i < n; i += 2) 
		bstr += ((char)stoi(str.substr(i, 2), NULL, 16));
	return bstr;
}

std::string str_byte2hex(std::string bstr)
{
    unsigned char u;
    std::stringstream ss;
    for (auto c: bstr) {
        u = (unsigned char)(c);
        ss << std::hex << std::setfill('0') << std::setw(2) << static_cast<int>(u);
    }
    return ss.str();
}
// ----------------------------------------------------------------------------
// Generate a public-private key pair and save to files
RSA* generateKeyPair(const char* publicKeyFile, const char* privateKeyFile) {
    RSA *keypair = RSA_new();
    BIGNUM *e = BN_new();
    BN_set_word(e, 3);

    int keyLength = TARGET_RSA_LEN; // 2048
    RSA_generate_key_ex(keypair, keyLength, e, NULL);
    FILE *publicKey = fopen(publicKeyFile, "w");
    PEM_write_RSAPublicKey(publicKey, keypair);
    fclose(publicKey);

    FILE *bigN = fopen(privateKeyFile, "w");
    PEM_write_RSAPrivateKey(bigN, keypair, NULL, NULL, 0, NULL, NULL);
    fclose(bigN);

    BN_free(e);
    return keypair;
}

// Load public key from file
RSA* loadPublicKey(const char* publicKeyFile) {
    RSA *keypair = RSA_new();
    FILE *publicKey = fopen(publicKeyFile, "r");
    PEM_read_RSAPublicKey(publicKey, &keypair, NULL, NULL);
    fclose(publicKey);
    return keypair;
}

// Load private key from file
RSA* loadPrivateKey(const char* privateKeyFile) {
    RSA *keypair = RSA_new();
    FILE *bigN = fopen(privateKeyFile, "r");
    PEM_read_RSAPrivateKey(bigN, &keypair, NULL, NULL);
    fclose(bigN);
    return keypair;
}
// ----------------------------------------------------------------------------
// Encrypt data using public key
std::string rsa_encrypt(const std::string &plaintext, RSA *rsa_key) {
    int rsa_size = RSA_size(rsa_key);
    std::vector<unsigned char> ciphertext(rsa_size);

    int len = RSA_public_encrypt(plaintext.size(), reinterpret_cast<const unsigned char *>(plaintext.data()),
                                 ciphertext.data(), rsa_key, RSA_NO_PADDING); 
                                 //ciphertext.data(), rsa_key, RSA_PKCS1_PADDING);

    if (len < 0) {
        std::cerr << "Encryption failed" << std::endl;
        return "";
    }

    return std::string(reinterpret_cast<const char *>(ciphertext.data()), len);
}

// Decrypt data using private key
std::string rsa_decrypt(const std::string &ciphertext, RSA *rsa_key) {
    int rsa_size = RSA_size(rsa_key);
    std::vector<unsigned char> plaintext(rsa_size);

    int len = RSA_private_decrypt(ciphertext.size(), reinterpret_cast<const unsigned char *>(ciphertext.data()),
                                  plaintext.data(), rsa_key, RSA_NO_PADDING);

    if (len < 0) {
        std::cerr << "Decryption failed" << std::endl;
        return "";
    }

    return std::string(reinterpret_cast<const char *>(plaintext.data()), len);
}

string bn2str(BIGNUM* bigN)
{
    // Convert BIGNUM to binary representation
    size_t bnSize = BN_num_bytes(bigN);
    unsigned char bnStr[bnSize];
    BN_bn2bin(bigN, bnStr);
    string bnString((char*)bnStr,bnSize);   
    return bnString;
}

// ----------------------------------------------------------------------------
int main(int, char**) {
    const char* publicKeyFile = "public_key.pem";
    const char* privateKeyFile = "private_key.pem";
    std::string encrypted;
    std::string decrypted;
    std::string message = "12345678";
    message.resize(TARGET_RSA_LEN/8, '\0');
    std::cout << "Original message: " << message << std::endl;
    // ----------------------------------------------------------------------------
    // KEY GENERATION (uncomment the following line to generate  key files)
    RSA* keypair = generateKeyPair(publicKeyFile, privateKeyFile);


    // ----------------------------------------------------------------------------
    // GET KEY FROM FILES
    // Load public key
    RSA *public_key = loadPublicKey(publicKeyFile);
    // Load private key
    RSA *private_key = loadPrivateKey(privateKeyFile);

     // Encrypt and decrypt a message
    encrypted = rsa_encrypt(message, public_key);
    decrypted = rsa_decrypt(encrypted, private_key);
    std::cout << "Encrypted message: " << str_byte2hex(encrypted) << std::endl;
    std::cout << "Decrypted message: " << decrypted << std::endl;

    // ----------------------------------------------------------------------------
    // GET KEY FROM BIGNUM
    // Obtain the key components as BIGNUM
    BIGNUM* bn_d = BN_dup(RSA_get0_d(private_key));
    BIGNUM* bn_e = BN_dup(RSA_get0_e(private_key));
    BIGNUM* bn_n = BN_dup(RSA_get0_n(private_key));


    RSA *public_key2 = RSA_new();
    RSA_set0_key(public_key2,bn_n,bn_e,NULL);
    RSA *private_key2 = RSA_new();
    RSA_set0_key(private_key2,bn_n,bn_e,bn_d);    

    encrypted = rsa_encrypt(message, public_key2);
    decrypted = rsa_decrypt(encrypted, private_key2);

    std::cout << "Encrypted message2: " << str_byte2hex(encrypted) << std::endl;
    std::cout << "Decrypted message2: " << decrypted << std::endl;

    // RSA_free(public_key2);
    // RSA_free(private_key2);

    // ----------------------------------------------------------------------------
    // GET KEY FROM BINARY STRING 

    string dstr = bn2str(bn_d);
    string estr = bn2str(bn_e);
    string nstr = bn2str(bn_n);
    std::cout << "RSA d (Len "<< dstr.length() <<"): " << str_byte2hex(dstr) << std::endl;
    std::cout << "RSA e (Len "<< estr.length() <<"): " << str_byte2hex(estr) << std::endl;
    std::cout << "RSA n (Len "<< nstr.length() <<"): " << str_byte2hex(nstr) << std::endl;

    BIGNUM* bn_d3 = BN_new();
    BIGNUM* bn_e3 = BN_new();
    BIGNUM* bn_n3 = BN_new();
    if (BN_bin2bn((const unsigned char*)dstr.c_str(), dstr.length(), bn_d3) == NULL){
        printf("Failed to convert modulus or exponent");
        return 1;
    }
    if (BN_bin2bn((const unsigned char*)estr.c_str(), estr.length(), bn_e3) == NULL){
        printf("Failed to convert modulus or exponent");
        return 1;
    }
    if (BN_bin2bn((const unsigned char*)nstr.c_str(), nstr.length(), bn_n3) == NULL){
        printf("Failed to convert modulus or exponent");
        return 1;
    }


    RSA *public_key3 = RSA_new();
    RSA_set0_key(public_key3,bn_n3,bn_e3,NULL);
    RSA *private_key3 = RSA_new();
    RSA_set0_key(private_key3,bn_n3,bn_e3,bn_d3);    

    encrypted = rsa_encrypt(message, public_key3);
    decrypted = rsa_decrypt(encrypted, private_key3);

    std::cout << "Encrypted message3: " << str_byte2hex(encrypted) << std::endl;
    std::cout << "Decrypted message3: " << decrypted << std::endl;

    // RSA_free(public_key3);
    // RSA_free(private_key3);
    // ----------------------------------------------------------------------------
    // Clean up resources
    BN_free(bn_d);
    BN_free(bn_e);
    BN_free(bn_n);
    //------------------------
    // Free resources
    RSA_free(public_key);
    RSA_free(private_key);

    return 0;
}
