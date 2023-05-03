#include <iostream>
#include <bitset>
#include <string>
#include <sstream>
#include <fstream>
#include <cstring>
#include <openssl/des.h>
#include <iomanip>

std::string des_encrypt(const std::string& key, const std::string& message);
std::string des_decrypt(const std::string& key, const std::string& encrypted_message);

std::string des_encrypt(const std::string& key, const std::string& message) {
    DES_cblock key_des;
    DES_key_schedule key_schedule;
    std::string encrypted_message;
    const_DES_cblock iv = {0};

    // Convert the key to a DES key
    memset(key_des, 0, 8);
    memcpy(key_des, key.c_str(), std::min<size_t>(key.size(), 8));
    DES_set_key_checked(&key_des, &key_schedule);

    // Encrypt the message using DES
    size_t message_length = message.size();
    size_t encrypted_message_length = ((message_length + 7) / 8) * 8;
    unsigned char* encrypted_message_buffer = new unsigned char[encrypted_message_length];
    memset(encrypted_message_buffer, 0, encrypted_message_length);
    DES_ncbc_encrypt(reinterpret_cast<const unsigned char*>(message.c_str()),
                     encrypted_message_buffer, message_length, &key_schedule, &iv, DES_ENCRYPT);

    // Convert the encrypted message to a string
    std::stringstream ss;
    for (size_t i = 0; i < encrypted_message_length; ++i) {
        ss << std::hex << std::setfill('0') << std::setw(2) << static_cast<int>(encrypted_message_buffer[i]);
    }
    encrypted_message = ss.str();

    delete[] encrypted_message_buffer;

    return encrypted_message;
}



std::string des_decrypt(const std::string& key, const std::string& encrypted_message) {
    DES_cblock key_des;
    DES_key_schedule key_schedule;
    std::string decrypted_message;
    const_DES_cblock iv = {0};

    // Convert the key to a DES key
    memset(key_des, 0, 8);
    memcpy(key_des, key.c_str(), std::min<size_t>(key.size(), 8));
    DES_set_key_checked(&key_des, &key_schedule);

    // Convert the encrypted message from a hex string to bytes
    std::string encrypted_message_bytes;
    std::istringstream ss(encrypted_message);
    while (true) {
        int byte;
        ss >> std::hex >> byte;
        if (ss.eof()) {
            break;
        }
        encrypted_message_bytes += static_cast<char>(byte);
    }

    // Decrypt the message using DES
    size_t encrypted_message_length = encrypted_message_bytes.size();
    unsigned char* decrypted_message_buffer = new unsigned char[encrypted_message_length];
    memset(decrypted_message_buffer, 0, encrypted_message_length);
    DES_ncbc_encrypt(reinterpret_cast<const unsigned char*>(encrypted_message_bytes.c_str()),
                     decrypted_message_buffer, encrypted_message_length, &key_schedule, &iv, DES_DECRYPT);

    // Convert the decrypted message to a string
    decrypted_message = std::string(reinterpret_cast<char*>(decrypted_message_buffer));

    delete[] decrypted_message_buffer;

    return decrypted_message;
}


int main(int, char**) {
    //std::string key = "abcdefgh";
    //std::string message = "12345678";
    // result = 21C60DA534248BCE

    std::string key = "secretkey";
    std::string message = "hello world";
    std::string encrypted_message = des_encrypt(key, message);
    std::cout << "Encrypted message: " << encrypted_message << std::endl;

    std::string decrypted_message = des_decrypt(key, encrypted_message);
    std::cout << "Decrypted message: " << decrypted_message << std::endl;

    return 0;
}
