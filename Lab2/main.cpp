#include <fstream>
#include <iostream>
#include "Calculator.h"

int main(int argc, char *argv[]) {
    Calculator calc;
    if (argc == 2) {
        std::ifstream input(argv[1]);
        if (!input) {
            std::cout << "Cannot open input file" << std::endl;
            return 1;
        }
        calc.calculate(input);
    } else {
        std::cout << "Write commands to command prompt" << std::endl;
        calc.calculate(std::cin);
    }
}
