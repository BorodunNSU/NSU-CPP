#include "WordStatistic.h"
#include <string>
#include <fstream>
#include <algorithm>

WordStatistic::WordStatistic() {
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


void WordStatistic::addFile(const string &fileName) {
    ifstream input(fileName);
    if (!input) {
        cout << "Can not open input file";
    }
    string word;
    while (!(word = GetNextWord(input)).empty()) {
        ++wordMap[word];
        ++wordCounter;
    }
}


void WordStatistic::writeCSV(const std::string &fileName) {
    multimap<int, string> sortedWordMap;
    for (auto word = wordMap.rbegin(); word != wordMap.rend(); ++word) {
        sortedWordMap.insert(pair<int, string>(word->second, word->first));
    }
    wordMap.clear();
    ofstream output(fileName);
    if (!output) {
        cout << "Can not open output file";
    }
    for (auto element = sortedWordMap.rbegin(); element != sortedWordMap.rend(); ++element) {
        output << element->second << ',' << element->first << ',' << element->first / (double) wordCounter * 100 << '%'
               << endl;
    }
}
