#include <iomanip>
#include <iostream>
#include <string>
#include <cryptopp/rsa.h>
#include <cryptopp/osrng.h>
#include <cryptopp/base64.h>
#include <cryptopp/files.h>

using namespace CryptoPP;

std::string rsa_encrypt(const std::string& plaintext, const RSA::PublicKey& publicKey)
{
    AutoSeededRandomPool rng;
    std::string ciphertext;

    RSAES_OAEP_SHA_Encryptor encryptor(publicKey);
    StringSource ss1(plaintext, true,
                     new PK_EncryptorFilter(rng, encryptor,
                                            new StringSink(ciphertext)));

    return ciphertext;
}

std::string rsa_decrypt(const std::string& ciphertext, const RSA::PrivateKey& privateKey)
{
    AutoSeededRandomPool rng;
    std::string recovered;

    RSAES_OAEP_SHA_Decryptor decryptor(privateKey);
    StringSource ss2(ciphertext, true,
                     new PK_DecryptorFilter(rng, decryptor,
                                            new StringSink(recovered)));

    return recovered;
}

int main()
{
    // Generate a key pair
    AutoSeededRandomPool rng;
    InvertibleRSAFunction params;
    params.GenerateRandomWithKeySize(rng, 2048);

    RSA::PrivateKey privateKey(params);
    RSA::PublicKey publicKey(params);

    // Save the keys to files
    FileSink pubFile("public_key.der", true);
    publicKey.Save(pubFile);
    FileSink privFile("private_key.der", true);
    privateKey.Save(privFile);

    // Encrypt and decrypt a message
    std::string message = "12345678";
    std::string encrypted = rsa_encrypt(message, publicKey);
    std::string decrypted = rsa_decrypt(encrypted, privateKey);

    std::cout << "Original message: " << message << std::endl;

    std::string encoded;
    StringSource(encrypted, true, new Base64Encoder(new StringSink(encoded)));
    std::cout << "Encrypted message: " << encoded << std::endl;
    std::cout << "Decrypted message: " << decrypted << std::endl;

    return 0;
}
