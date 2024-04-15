#ifndef HASH_H
#define HASH_H

#include <string>
#include <cstdint>

std::string simple_sha256(const std::string& input);
uint32_t fnv_1a_hash(const char* input, uint32_t seed);
uint32_t recycleHash(const std::string& input, int k);

#endif // HASH_H
