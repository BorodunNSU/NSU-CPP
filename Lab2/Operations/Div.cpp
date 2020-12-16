#include "../Operation.h"
#include "../OperationMaker.h"
#include "../Exceptions.h"

class Div : public Operation {
public:
    void run(std::list<std::string> &args, Context &context) override {
        if (context.stackSize() < 2) {
            throw badArgsException("Not enough operands for '/'");
        }
        if (!args.empty()) {
            throw badArgsException("Too much arguments for '/'");
        }
        double num1 = context.pop();
        double num2 = context.pop();
        if (num1 == 0) {
            std::string errorStr = std::to_string(num2) + "/" + std::to_string(num1);
            throw divisionByZeroException( "Division by zero: "+std::to_string(num2) + "/" + std::to_string(num1));
        }
        context.push(num2 / num1);
    }
};

ADD_OPERATION(Div, /)