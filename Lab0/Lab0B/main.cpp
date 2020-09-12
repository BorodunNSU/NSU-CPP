#include "WordStat.h"

int main(int argc, char* argv[]) {
    if (argc <= 2) {
        std::cout << "Wrong number of arguments" << std::endl;
        return 0;
    }

    std::string in = argv[1];
    //std::string out = argv[2];
    WordStat wordStat;
    wordStat.AddFile(in);

    return 0;
}
