#include "WordStatistic.h"

int  main(int argc, char* argv[]){
    if (argc > 2) {
        WordStatistic wordStatistic;
        for (int i = 1; i < argc - 1; ++i) {
            wordStatistic.addFile(argv[i]);
        }
        wordStatistic.writeCSV(argv[argc - 1]);
    }
    else {
        std::cout << "Write at least two arguments (e.g. '../input.txt ../output.csv' )" << std::endl;
    }
}
