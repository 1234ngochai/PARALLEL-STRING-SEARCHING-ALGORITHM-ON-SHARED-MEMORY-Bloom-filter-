#include "UniqueWordsParr.h"
#include <fstream>
#include <iostream>
#include <cctype>
#include <omp.h>

#define MAX_WORD_LENGTH 100


// helper function
bool isWordInList(const std::string& word, const std::vector<std::string>& wordList) {
    for(const auto& existingWord : wordList) {
        if (word == existingWord) {
            return true;
        }
    }
    return false;
}

// function to read the file
int ReadFromFileToArray(const std::string& filename, int fileLength, std::vector<std::string>& words) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error opening file: " << filename << '\n';
        return -1;
    }

    std::string word;
    std::vector<std::string> FileWordList(fileLength);
    std::vector<std::string> UniqueWordList;
    int UniqueWordListLength = 0;

    for(int i = 0; i < fileLength; i++){
        file >> word;
        FileWordList[i] = word;
    }

    #pragma omp parallel for schedule(dynamic) num_threads(16)
    for(int i = 0; i < fileLength; i++){
        // Convert word to lowercase for case-insensitive comparison
        for(char& ch : FileWordList[i]) {
            ch = tolower(ch);
        }
        // Check if word is unique
        if (!isWordInList(FileWordList[i], UniqueWordList)) {
            #pragma omp critical
            {
                UniqueWordList.push_back(FileWordList[i]);
                UniqueWordListLength++;
            }
        }
    }

    UniqueWordList.resize(UniqueWordListLength);

    words = UniqueWordList;

    return UniqueWordListLength;
}
