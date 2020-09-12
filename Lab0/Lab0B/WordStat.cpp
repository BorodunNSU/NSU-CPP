#include "WordStat.h"
#include <string>
#include <fstream>
#include <algorithm>

WordStat::WordStat() {
    wordCounter = 0;
}

using namespace std;

string GetNextWord(istream &in) {
    char symbol;
    string ans = "";
    symbol = in.get();
    while (!isalpha(symbol) && !in.eof()) {
        symbol = in.get();
    }
    while (isalpha(symbol)) {
        ans.push_back(symbol);
        symbol = in.get();
    }
    return ans;
}

multimap<int, string> sortMap(map<string, int> &words) {
    multimap<int, string> sortedWordMap;

    for (auto & word : words) {
        sortedWordMap.insert(pair<int, string>(word.second, word.first));
    }

    return sortedWordMap;
}

void WordStat::AddFile(const string& fileName) {
    ifstream file(fileName);
    string word;
    while (!(word = GetNextWord(file)).empty()) {
        ++words[word];
        ++wordCounter;
    }
    multimap<int, string> sortedWords = sortMap(words);
    //ofstream file(FileName);
    for (auto &it : sortedWords) {
        float frequency = (float)it.first/wordCounter * 100;
        std::cout << it.first << ' ' << it.second << ' ' << frequency << std::endl;
    }
}
