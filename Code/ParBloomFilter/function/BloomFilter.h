#include <vector>
#include <cmath>
#include "hash.h"

class BloomFilter {
public:
    BloomFilter(double p, int n);

    // void insert(const std::string& key);
    bool query(const std::string& key) const;
    void insert(const std::vector<uint32_t>& hashValues);
    std::vector<std::vector<std::vector<uint32_t>>> precomputeAllHashValues(const std::vector<std::vector<std::string>>& ppWordListArray);

private:
    std::vector<bool> bit_array;
    int m; // Size of the bit array
    int k; // Number of hash functions
    int n; // Number of expected elements to insert

    uint32_t recycleHash(const std::string& input, int seed, int k) const;
    int nearestPrime(int num) const;
};
