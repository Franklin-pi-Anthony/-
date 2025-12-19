#include <iostream>
#include <fstream>
#include <sstream>
#include <openssl/md5.h>
#include <openssl/sha.h>
#include <cctype>

// Function to convert bytes to hex string
std::string bytesToHexString(const unsigned char* bytes, size_t length) {
    std::ostringstream oss;
    for (size_t i = 0; i < length; ++i) {
        oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(bytes[i]);
    }
    return oss.str();
}

// Function to calculate MD5 hash
std::string calculateMD5(const std::string& filePath) {
    unsigned char md5[MD5_DIGEST_LENGTH];
    MD5_CTX md5Ctx;
    std::ifstream file(filePath, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Failed to open file");
    }

    MD5_Init(&md5Ctx);
    std::vector<char> buffer(1024);
    while (file.read(buffer.data(), buffer.size()) || file.gcount() > 0) {
        MD5_Update(&md5Ctx, buffer.data(), file.gcount());
    }
    MD5_Final(md5, &md5Ctx);

    return bytesToHexString(md5, MD5_DIGEST_LENGTH);
}

// Function to calculate SHA-1 hash
std::string calculateSHA1(const std::string& filePath) {
    unsigned char sha1[SHA_DIGEST_LENGTH];
    SHA_CTX sha1Ctx;
    std::ifstream file(filePath, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Failed to open file");
    }

    SHA1_Init(&sha1Ctx);
    std::vector<char> buffer(1024);
    while (file.read(buffer.data(), buffer.size()) || file.gcount() > 0) {
        SHA1_Update(&sha1Ctx, buffer.data(), file.gcount());
    }
    SHA1_Final(sha1, &sha1Ctx);

    return bytesToHexString(sha1, SHA_DIGEST_LENGTH);
}

// Function to calculate SHA-256 hash
std::string calculateSHA256(const std::string& filePath) {
    unsigned char sha256[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256Ctx;
    std::ifstream file(filePath, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Failed to open file");
    }

    SHA256_Init(&sha256Ctx);
    std::vector<char> buffer(1024);
    while (file.read(buffer.data(), buffer.size()) || file.gcount() > 0) {
        SHA256_Update(&sha256Ctx, buffer.data(), file.gcount());
    }
    SHA256_Final(sha256, &sha256Ctx);

    return bytesToHexString(sha256, SHA256_DIGEST_LENGTH);
}

// Function to calculate SHA-512 hash
std::string calculateSHA512(const std::string& filePath) {
    unsigned char sha512[SHA512_DIGEST_LENGTH];
    SHA512_CTX sha512Ctx;
    std::ifstream file(filePath, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Failed to open file");
    }

    SHA512_Init(&sha512Ctx);
    std::vector<char> buffer(1024);
    while (file.read(buffer.data(), buffer.size()) || file.gcount() > 0) {
        SHA512_Update(&sha512Ctx, buffer.data(), file.gcount());
    }
    SHA512_Final(sha512, &sha512Ctx);

    return bytesToHexString(sha512, SHA512_DIGEST_LENGTH);
}

// Function to convert string to lower case
std::string toLowerCase(const std::string& str) {
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), [](unsigned char c){ return std::tolower(c); });
    return lowerStr;
}

int main() {
    std::string filePath;
    std::string md5Str, sha1Str, sha256Str, sha512Str;
    std::string inputStr;

    // Get file path from user
    std::cout << "Enter the absolute file path: ";
    std::cin >> filePath;

    try {
        // Calculate hashes
        md5Str = calculateMD5(filePath);
        sha1Str = calculateSHA1(filePath);
        sha256Str = calculateSHA256(filePath);
        sha512Str = calculateSHA512(filePath);

        // Print hashes
        std::cout << "MD5:    " << md5Str << std::endl;
        std::cout << "SHA-1:  " << sha1Str << std::endl;
        std::cout << "SHA-256:" << sha256Str << std::endl;
        std::cout << "SHA-512:" << sha512Str << std::endl;

        // Get input string from user
        std::cout << "Enter a string to validate: ";
        std::cin >> inputStr;

        // Convert both input string and hash strings to lower case for case-insensitive comparison
        inputStr = toLowerCase(inputStr);
        md5Str = toLowerCase(md5Str);
        sha1Str = toLowerCase(sha1Str);
        sha256Str = toLowerCase(sha256Str);
        sha512Str = toLowerCase(sha512Str);

        // Validate input string
        if (inputStr == md5Str || inputStr == sha1Str || inputStr == sha256Str || inputStr == sha512Str) {
            std::cout << "valid" << std::endl;
        } else {
            std::cout << "invalid" << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}