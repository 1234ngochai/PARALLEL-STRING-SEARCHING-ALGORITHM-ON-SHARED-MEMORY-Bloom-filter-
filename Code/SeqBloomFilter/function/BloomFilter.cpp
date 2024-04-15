#include "BloomFilter.h"
#include "hash.h"
#include <cmath>
#include <omp.h>
BloomFilter::BloomFilter(double p, int n)
    : n(n) 
{
    // Calculate m and k based on the formulas
    m = static_cast<int>(ceil((-n * log(p)) / (log(2) * log(2))));
    m = nearestPrime(m);
    k = static_cast<int>(ceil((m / n) * log(2)));
    
    // Initialize the bit array
    bit_array = std::vector<bool>(m, false);
}


//inserting the value
void BloomFilter::insert(const std::vector<uint32_t>& hashValues) {
    for(const auto& hashValue : hashValues) {
        bit_array[hashValue % m] = true;
    }
}


// querying the value
bool BloomFilter::query(const std::string& key) const {
    for(int i = 0; i < k; ++i) {
        uint32_t hashValue = recycleHash(key, i, k);
        if(!bit_array[hashValue % m]) {
            return false;
        }
    }
    return true;
}

// hash the value over and over by k time using hash funciton 
uint32_t BloomFilter::recycleHash(const std::string& input, int seed, int k) const {
    std::string temp_input = input;
    for (int i = 0; i < k; ++i) {
        temp_input = simple_sha256(temp_input);
    }
    return fnv_1a_hash(temp_input.c_str(), seed);
}

// precomputer all the value
std::vector<std::vector<std::vector<uint32_t>>> BloomFilter::precomputeAllHashValues(const std::vector<std::vector<std::string>>& ppWordListArray) {
    std::vector<std::vector<std::vector<uint32_t>>> allHashValues(ppWordListArray.size());

    for(std::size_t i = 0; i < ppWordListArray.size(); ++i) {
        allHashValues[i].resize(ppWordListArray[i].size(), std::vector<uint32_t>(k));
        for(std::size_t j = 0; j < ppWordListArray[i].size(); ++j) {
            for(int l = 0; l < k; ++l) {
                allHashValues[i][j][l] = recycleHash(ppWordListArray[i][j], l, k);
            }
        }
    }

    return allHashValues;
}


//finding the nearestPrime for array
int BloomFilter::nearestPrime(int num) const {
    if (num <= 2)
        return 2;

    auto isPrime = [](int n) {
        if (n < 2) return false;
        if (n == 2 || n == 3) return true;
        if (n % 2 == 0) return false;
        for (int i = 3; i <= std::sqrt(n); i += 2) {
            if (n % i == 0) {
                return false;
            }
        }
        return true;
    };

    int primeCandidate = num;
    while (true) {
        if (isPrime(primeCandidate)) {
            return primeCandidate;
        }
        ++primeCandidate;
    }
}

