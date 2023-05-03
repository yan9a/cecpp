#include <iostream>
#include <string>
#include <cryptopp/cryptlib.h>
#include <cryptopp/sha.h>
#include <cryptopp/hex.h>
#include <iomanip>

std::string sha1(const std::string& message);

std::string sha1(const std::string& message) {
    std::string digest;

    // Calculate the SHA-1 hash
    CryptoPP::SHA1 hash;
    CryptoPP::StringSource(message, true, new CryptoPP::HashFilter(hash, new CryptoPP::HexEncoder(new CryptoPP::StringSink(digest), false)));

    return digest;
}

int main(int, char**) {
    std::string message = "12345678";
    std::string hash = sha1(message);
    std::cout << "SHA-1 hash: " << hash << std::endl;
    return 0;
}
