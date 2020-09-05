#include <iterator>
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <cctype>
#include <vector>
#include <algorithm>

bool cmp(std::pair<std::string, int> &a, std::pair<std::string, int> &b) {
    return a.second > b.second;
}

std::vector<std::pair<std::string, int>> sort(std::map<std::string, int> &M) {
    std::vector<std::pair<std::string, int>> sorted;
    sorted.reserve(M.size());
    for (auto &it : M) {
        sorted.emplace_back(it);
    }
    std::sort(sorted.begin(), sorted.end(), cmp);
    return sorted;
}

std::string getNextToken(std::istream &in) {
    char symbol;
    std::string ans = "";
    symbol = in.get();
    while (!std::isalpha(symbol) && !in.eof()) {
        symbol = in.get();
    }
    while (std::isalpha(symbol)) {
        ans.push_back(std::tolower(symbol));
        symbol = in.get();
    }
    return ans;
}

int main() {
    std::map<std::string, int> words;
    std::ifstream file("../input.txt");
    std::string word;
    int wordCount = 0;
    while (!(word = getNextToken(file)).empty()) {
        ++words[word];
        ++wordCount;
    }
    std::vector<std::pair<std::string, int>> finishedWords = sort(words);
    for (auto &it : finishedWords) {
        float frequency = (float)it.second/wordCount;
        std::cout << it.first << ' ' << it.second << ' ' << frequency << std::endl;
    }
    return 0;
}
