#include <iostream>
#include <bitset>
#include <string>
#include <sstream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <vector>
#include <openssl/rsa.h>
#include <openssl/pem.h>
// ----------------------------------------------------------------------------
// Generate a public-private key pair and save to files
RSA* generateKeyPair(const char* publicKeyFile, const char* privateKeyFile) {
    RSA *keypair = RSA_new();
    BIGNUM *e = BN_new();
    BN_set_word(e, 65537);

    RSA_generate_key_ex(keypair, 2048, e, NULL);
    FILE *publicKey = fopen(publicKeyFile, "w");
    PEM_write_RSAPublicKey(publicKey, keypair);
    fclose(publicKey);

    FILE *privateKey = fopen(privateKeyFile, "w");
    PEM_write_RSAPrivateKey(privateKey, keypair, NULL, NULL, 0, NULL, NULL);
    fclose(privateKey);

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
    FILE *privateKey = fopen(privateKeyFile, "r");
    PEM_read_RSAPrivateKey(privateKey, &keypair, NULL, NULL);
    fclose(privateKey);
    return keypair;
}
// ----------------------------------------------------------------------------
// Encrypt data using public key
std::string rsa_encrypt(const std::string &plaintext, RSA *rsa_key) {
    int rsa_size = RSA_size(rsa_key);
    std::vector<unsigned char> ciphertext(rsa_size);

    int len = RSA_public_encrypt(plaintext.size(), reinterpret_cast<const unsigned char *>(plaintext.data()),
                                 ciphertext.data(), rsa_key, RSA_PKCS1_PADDING);

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
                                  plaintext.data(), rsa_key, RSA_PKCS1_PADDING);

    if (len < 0) {
        std::cerr << "Decryption failed" << std::endl;
        return "";
    }

    return std::string(reinterpret_cast<const char *>(plaintext.data()), len);
}

// ----------------------------------------------------------------------------
int main(int, char**) {
    const char* publicKeyFile = "public_key.pem";
    const char* privateKeyFile = "private_key.pem";
    // RSA* keypair = generateKeyPair(publicKeyFile, privateKeyFile);

    // Load public key
    RSA *public_key = loadPublicKey(publicKeyFile);
    // Load private key
    RSA *private_key = loadPrivateKey(privateKeyFile);

    // // Load public key
    // FILE *public_key_file = fopen("public_key.pem", "rb");
    // RSA *public_key = PEM_read_RSA_PUBKEY(public_key_file, nullptr, nullptr, nullptr);
    // fclose(public_key_file);

    // // Load private key
    // FILE *private_key_file = fopen("private_key.pem", "rb");
    // RSA *private_key = PEM_read_RSAPrivateKey(private_key_file, nullptr, nullptr, nullptr);
    // fclose(private_key_file);

     // Encrypt and decrypt a message
    std::string message = "12345678";
    std::string encrypted = rsa_encrypt(message, public_key);
    std::string decrypted = rsa_decrypt(encrypted, private_key);

    std::cout << "Original message: " << message << std::endl;
    std::cout << "Encrypted message: " << encrypted << std::endl;
    std::cout << "Decrypted message: " << decrypted << std::endl;

    // Free resources
    RSA_free(public_key);
    RSA_free(private_key);
    return 0;
}
