#ifndef LAB0B_WORDSTAT_H
#define LAB0B_WORDSTAT_H

#include <string>
#include <map>
#include <iostream>
#include <vector>

using std::string;
using std::map;

class WordStat {
    map<string, int> words;
    int wordCounter = 0;

public:
    WordStat();
    void AddFile(const string&);
    //void OutFile(string);
};


#endif //LAB0B_WORDSTAT_H
