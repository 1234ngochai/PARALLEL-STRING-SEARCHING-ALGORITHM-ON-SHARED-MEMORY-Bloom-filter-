#include <iostream>
#include <chrono>
#include <vector>
#include <string>
#include "function/UniqueWordsParr.h"
#include "function/hash.h"
#include "function/BloomFilter.h"
#include <fstream>     // Include for std::ifstream
#include <sstream>     // Include for std::istringstream
#include <algorithm>   // Include for std::find
#include <omp.h>


int main() {

    // Get current clock time.
    auto start = std::chrono::high_resolution_clock::now();

    std::vector<std::string> filenames = {"TextFiles2Read/MOBY_DICK.txt", "TextFiles2Read/LITTLE_WOMEN.txt", "TextFiles2Read/SHAKESPEARE.txt"};
    std::vector<int> fileLengths = {215724, 195467, 965465};

    std::vector<std::vector<std::string>> ppWordListArray(3);
    std::vector<int> wordListLengthArray(3);

    int n = 0;

    // read all the file
    for(int i = 0; i < 3; i++){
        wordListLengthArray[i] = ReadFromFileToArray(filenames[i], fileLengths[i], ppWordListArray[i]);
        n += wordListLengthArray[i];
    }

    auto end = std::chrono::high_resolution_clock::now();
    double time_taken = std::chrono::duration<double>(end - start).count();

    std::cout << "Total unique words from read files: " << n << ". Process time(s): " << time_taken << '\n';
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    auto start1 = std::chrono::high_resolution_clock::now();

    double falsePositiveRate = 0.01; //  false positive rate
    int estimatedUniqueWordsCount = n; //  estimate of unique words count

    BloomFilter bloomFilter(falsePositiveRate, estimatedUniqueWordsCount);

    // precompute all hash value
    auto allHashValues = bloomFilter.precomputeAllHashValues(ppWordListArray);

    auto end1 = std::chrono::high_resolution_clock::now();
    double time_taken1 = std::chrono::duration<double>(end1 - start1).count();
    std::cout << "Time to hash all the value" << n << ". Process time(s): " << time_taken1 << '\n';

    // inserting it into an array of hashed value 
    for(std::size_t i = 0; i < ppWordListArray.size(); ++i) {
        for(std::size_t j = 0; j < ppWordListArray[i].size(); ++j) {
            bloomFilter.insert(allHashValues[i][j]);
        }
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    auto start2 = std::chrono::high_resolution_clock::now();

    std::vector<std::pair<std::string, int>> queries;
    std::ifstream queryFile("TextFiles2Read/query.txt");
    if (!queryFile.is_open()) {
        std::cerr << "Could not open the query file\n";
        return 1;
    }

    std::string line;
    while (std::getline(queryFile, line)) {
        std::istringstream iss(line);
        std::string word;
        int expected_result;
        
        if (!(iss >> word >> expected_result)) {
            std::cerr << "Error reading query file\n";
            continue;
        }

        queries.emplace_back(word, expected_result);
    }

    queryFile.close();

    // Step 2: Use a parallelized loop to query the Bloom filter
    #pragma omp parallel for schedule(dynamic) num_threads(16)
    for (size_t i = 0; i < queries.size(); ++i) 
    {
        const auto& [word, expected_result] = queries[i];

        bool result = bloomFilter.query(word);

        bool actualResult = false;
        for(const auto& wordList : ppWordListArray) {
            if(std::find(wordList.begin(), wordList.end(), word) != wordList.end()) {
                actualResult = true;
                break;
            }
        }
        #pragma omp critical //for easy visuallization
        {
            std::cout << "Query Word: " << word << '\n';
            std::cout << "Bloom Filter Result: " << (result ? "Present" : "Absent") << '\n';
            std::cout << "Actual Result: " << (actualResult ? "Present" : "Absent") << '\n';
            std::cout << "Is Bloom Filter Correct: " << (result == actualResult ? "Yes" : "No") << '\n';
            std::cout << "Expected Result: " << (expected_result ? "Present" : "Absent") << '\n';
            std::cout << "---------------------------------\n";
        }
    }


    // Get the clock current time again
    // Subtract end from start to get the CPU time used.

    auto end2 = std::chrono::high_resolution_clock::now();
    double time_taken2 = std::chrono::duration<double>(end2 - start2).count();

    std::cout << "Time to query all the input. Process time(s): " << time_taken2 << "number of word" << '\n';


    return 0;
}
