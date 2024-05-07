#include <iostream>
#include <string>
#include <unordered_map>
#include <chrono>
#include <openssl/md5.h>
#include <openssl/sha.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>

std::string generateRandomString(int length) {
    const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    std::string random_string;
    srand(time(nullptr)); // Seed the random number generator
    for (int i = 0; i < length; ++i) {
        random_string += alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    return random_string;
}

long long processMD5(const std::string& input) {
    unsigned char digest[MD5_DIGEST_LENGTH];
    auto start = std::chrono::high_resolution_clock::now();
    long long iterations = 0;
    auto end = start + std::chrono::seconds(5); // Loop for 5 seconds
    while (std::chrono::high_resolution_clock::now() < end) {
        MD5((const unsigned char*)input.c_str(), input.length(), digest);
        ++iterations;
    }
    return iterations;
}

long long processSHA1(const std::string& input) {
    unsigned char digest[SHA_DIGEST_LENGTH];
    auto start = std::chrono::high_resolution_clock::now();
    long long iterations = 0;
    auto end = start + std::chrono::seconds(5); // Loop for 5 seconds
    while (std::chrono::high_resolution_clock::now() < end) {
        SHA1((const unsigned char*)input.c_str(), input.length(), digest);
        ++iterations;
    }
    return iterations;
}

long long processSHA256(const std::string& input) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    auto start = std::chrono::high_resolution_clock::now();
    long long iterations = 0;
    auto end = start + std::chrono::seconds(5); // Loop for 5 seconds
    while (std::chrono::high_resolution_clock::now() < end) {
        SHA256((const unsigned char*)input.c_str(), input.length(), digest);
        ++iterations;
    }
    return iterations;
}

int main(int argc, char *argv[]) {
    std::string splash = "██████  ██████  ███████ ███    ██  ██████ ██   ██\n██   ██ ██   ██ ██      ████   ██ ██      ██   ██\n██████  ██████  █████   ██ ██  ██ ██      ███████\n██   ██ ██   ██ ██      ██  ██ ██ ██      ██   ██\n██   ██ ██████  ███████ ██   ████  ██████ ██   ██\n";
    std::cout << splash;

    std::unordered_map<std::string, std::string> args;
    for (int i = 1; i < argc; ++i) { // Parse command line arguments
        std::string arg = argv[i];
        size_t pos = arg.find('=');
        if (pos != std::string::npos) {
            std::string key = arg.substr(0, pos);
            std::string value = arg.substr(pos + 1);
            args[key] = value;
        }
    }

    // Set default values
    int blocksize = 128; // The count of blocks, each block is 1024.

    // Check if --blocksize is provided and update the value
    if (args.find("--blocksize") != args.end()) {
        try {
            blocksize = std::stoi(args["--blocksize"]);
        } catch (const std::invalid_argument& e) {
            std::cerr << "Invalid blocksize value: " << args["--blocksize"] << std::endl;
            return 1;
        }
    }

    int score = 0;
    
    std::string plaintext = generateRandomString(blocksize * 1024);
    std::cout << "String generated, starting benchmark now." << std::endl;

    // Benchmark MD5
    std::cout << "MD5: ";
    long long md5_iterations = processMD5(plaintext);
    std::cout << md5_iterations << std::endl;
    score = score + md5_iterations;

    // Benchmark SHA1
    std::cout << "SHA1: ";
    long long sha1_iterations = processSHA1(plaintext);
    std::cout << sha1_iterations << std::endl;
    score = score + sha1_iterations;

    // Benchmark SHA256
    std::cout << "SHA256: ";
    long long sha256_iterations = processSHA256(plaintext);
    std::cout << sha256_iterations << std::endl;
    score = score + sha256_iterations;

    std::cout << "Total Score: " << score << std::endl;

    return 0;
}