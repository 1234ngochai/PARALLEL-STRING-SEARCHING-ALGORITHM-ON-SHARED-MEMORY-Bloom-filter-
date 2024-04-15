#ifndef UNIQUEWORDSPARR_H
#define UNIQUEWORDSPARR_H

#include <string>
#include <vector>

bool isWordInList(const std::string& word, const std::vector<std::string>& wordList);
int ReadFromFileToArray(const std::string& filename, int fileLength, std::vector<std::string>& words);

#endif // UNIQUEWORDSPARR_H
