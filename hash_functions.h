#ifndef HASH_FUNCTIONS_H
#define HASH_FUNCTIONS_H

#include <string>

// SHA-256 hash fonksiyonu
std::string sha256(const std::string& data);

// RIPEMD-160 hash fonksiyonu
std::string ripemd160(const std::string& data);

#endif // HASH_FUNCTIONS_H
