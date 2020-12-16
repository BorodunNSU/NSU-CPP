#include "Calculator.h"
#include "Operation.h"
#include "OperationMaker.h"
#include <sstream>

void Calculator::calculate(std::istream &stream) {
    for (std::string line; !stream.eof(); std::getline(stream, line)) {
        std::stringstream lineStream(line);
        std::string command;
        lineStream >> command;

        if (command[0] == '#' || command.empty()) {
            continue;
        } else if (command == "EXIT") {
            break;
        }

        std::list<std::string> args;
        while (!lineStream.eof()) {
            std::string argument;
            lineStream >> argument;
            if (argument[0] == '#') {
                break;
            }
            args.push_back(argument);
        }
        try {
            std::unique_ptr<Operation> operation = Factory::getFactory().getOperation(command);
            operation->run(args, context);
        }
        catch (CalculatorException &exception) {
            std::cout << "Exception: " << exception.what() << std::endl;
        }
    }
}
