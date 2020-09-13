#ifndef LAB0B_WORDSTATISTIC_H
#define LAB0B_WORDSTATISTIC_H

#include <string>
#include <map>
#include <iostream>
#include <vector>

using std::map;
using std::multimap;
using std::string;

class WordStatistic {
    map<string, int> wordMap;
    multimap<int, string> sortedWordMap;

    void sortMap();

    int wordCounter = 0;

public:
    WordStatistic();

    void addFile(const std::string &fileName);

    void writeCSV(const std::string &fileName);
};


#endif //LAB0B_WORDSTATISTIC_H
