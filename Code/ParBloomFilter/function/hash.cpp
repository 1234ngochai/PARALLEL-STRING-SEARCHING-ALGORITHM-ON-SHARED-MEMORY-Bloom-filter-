#include "hash.h"
#include <array>
#include <sstream>
#include <cstring>
#include <cstdio>

#define FNV_32_PRIME 0x01000193
#define FNV_32_OFFSET_BASIS 0x811c9dc5


// hasing the string into a number
uint32_t fnv_1a_hash(const char* input, uint32_t seed) {
    uint32_t hash = FNV_32_OFFSET_BASIS ^ seed;
    size_t length = strlen(input);
    for (size_t i = 0; i < length; i++) {
        hash ^= (uint32_t)input[i];
        hash *= FNV_32_PRIME;
    }
    return hash;
}


// hashing the string into another string 
std::string simple_sha256(const std::string& input) {
    const uint64_t prime1 = 73856093;
    const uint64_t prime2 = 19349669;
    const uint64_t prime3 = 83492791;
    const uint64_t prime4 = 15485863;
    const uint64_t prime5 = 49979687;

    std::array<uint64_t, 4> hash = {0};  
    uint64_t temp_hash1 = 0;
    uint64_t temp_hash2 = 0;

    for(size_t i = 0; i < input.size(); ++i) {
        char c = input[i];
        temp_hash1 = (temp_hash1 ^ (c * prime4)) * prime1;
        temp_hash1 ^= (temp_hash1 << 5) + (temp_hash1 >> 3) + c * prime2;
        temp_hash1 = (temp_hash1 + (temp_hash1 << 3)) ^ (temp_hash1 >> 11) * prime3;

        temp_hash2 = (temp_hash2 ^ (c * prime5)) * prime2;
        temp_hash2 ^= (temp_hash2 << 7) + (temp_hash2 >> 5) + c * prime3;
        temp_hash2 = (temp_hash2 + (temp_hash2 << 4)) ^ (temp_hash2 >> 13) * prime1;

        hash[i % 4] ^= temp_hash1 ^ temp_hash2;
    }

    std::ostringstream oss;
    for(uint64_t val : hash) {
        oss << std::hex << val;
    }

    return oss.str();
}

uint32_t recycleHash(const std::string& input, int k) {
    std::string temp = input;
    for (int i = 0; i < k; ++i) {
        temp = simple_sha256(temp);
    }

    // Now convert the hashed string to a number using fnv_1a_hash
    return fnv_1a_hash(temp.c_str(), 0);  // 0 is the seed value
}
