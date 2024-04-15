#ifndef UNIQUEWORDSSEQ_H
#define UNIQUEWORDSSEQ_H

#include <string>
#include <vector>

bool isWordInList(const std::string& word, const std::vector<std::string>& wordList);
int ReadFromFileToArray(const std::string& filename, int fileLength, std::vector<std::string>& words);

#endif // UNIQUEWORDSSEQ_H
