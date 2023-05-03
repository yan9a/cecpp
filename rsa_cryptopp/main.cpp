#include <iostream>
#include <string>
#include <cryptopp/cryptlib.h>
#include <cryptopp/des.h>
#include <cryptopp/hex.h>
#include <cryptopp/modes.h>
#include <iomanip>

std::string des_encrypt(const std::string& key, const std::string& message);
std::string des_decrypt(const std::string& key, const std::string& encrypted_message);


std::string des_encrypt(const std::string& key, const std::string& message) {
    std::string encrypted_message;

    // Convert the key to a Crypto++ key
    CryptoPP::SecByteBlock key_des(CryptoPP::DES::DEFAULT_KEYLENGTH);
    memset(key_des, 0, CryptoPP::DES::DEFAULT_KEYLENGTH);
    memcpy(key_des, key.c_str(), std::min<size_t>(key.size(), CryptoPP::DES::DEFAULT_KEYLENGTH));

    // Encrypt the message using DES
    std::string cipher;
    CryptoPP::ECB_Mode<CryptoPP::DES>::Encryption encryptor(key_des, CryptoPP::DES::DEFAULT_KEYLENGTH);
    CryptoPP::StringSource(message, true, new CryptoPP::StreamTransformationFilter(encryptor, new CryptoPP::StringSink(cipher)));

    // Convert the encrypted message to a hex string
    CryptoPP::HexEncoder encoder;
    encoder.Attach(new CryptoPP::StringSink(encrypted_message));
    encoder.Put(reinterpret_cast<const unsigned char*>(cipher.c_str()), cipher.size());
    encoder.MessageEnd();

    return encrypted_message;
}

std::string des_decrypt(const std::string& key, const std::string& encrypted_message) {
    std::string decrypted_message;

    // Convert the key to a Crypto++ key
    CryptoPP::SecByteBlock key_des(CryptoPP::DES::DEFAULT_KEYLENGTH);
    memset(key_des, 0, CryptoPP::DES::DEFAULT_KEYLENGTH);
    memcpy(key_des, key.c_str(), std::min<size_t>(key.size(), CryptoPP::DES::DEFAULT_KEYLENGTH));

    // Convert the encrypted message from a hex string to bytes
    std::string cipher;
    CryptoPP::StringSource(encrypted_message, true, new CryptoPP::HexDecoder(new CryptoPP::StringSink(cipher)));

    // Decrypt the message using DES
    std::string decrypted;
    CryptoPP::ECB_Mode<CryptoPP::DES>::Decryption decryptor(key_des, CryptoPP::DES::DEFAULT_KEYLENGTH);
    CryptoPP::StringSource(cipher, true, new CryptoPP::StreamTransformationFilter(decryptor, new CryptoPP::StringSink(decrypted)));

    // Convert the decrypted message to a string
    decrypted_message = decrypted;

    return decrypted_message;
}


int main(int, char**) {
    std::string key = "abcdefgh";
    std::string message = "12345678";
    // result = 21C60DA534248BCE
    std::string encrypted_message = des_encrypt(key, message);
    std::cout << "Encrypted message: " << encrypted_message << std::endl;

    std::string decrypted_message = des_decrypt(key, encrypted_message);
    std::cout << "Decrypted message: " << decrypted_message << std::endl;

    return 0;
}
