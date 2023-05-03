#include <iostream>
#include <string>
#include <openssl/sha.h>
#include <iomanip>
std::string sha1(const std::string& message);
std::string sha1(const std::string& message) {
    std::string digest;

    // Calculate the SHA-1 hash
    unsigned char hash[SHA_DIGEST_LENGTH];
    SHA1(reinterpret_cast<const unsigned char*>(message.c_str()), message.length(), hash);

    // Convert the hash digest to a string
    char hex_hash[SHA_DIGEST_LENGTH * 2 + 1];
    for (size_t i = 0; i < SHA_DIGEST_LENGTH; ++i) {
        snprintf(hex_hash + (i * 2), 3, "%02x", hash[i]);
    }
    digest = hex_hash;

    return digest;
}
// ----------------------------------------------------------------------------
int main(int, char**) {
    std::string message = "12345678";
    std::string hash = sha1(message);
    std::cout << "SHA-1 hash: " << hash << std::endl;
    return 0;
}
