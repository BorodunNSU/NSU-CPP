#include "../Operation.h"
#include "../OperationMaker.h"

class Div : public Operation {
public:
    void run(std::list<std::string> &args, Context &context) override {
        if (context.stackSize() < 2) {
            throw std::runtime_error("Not enough operands for division");
        }
        double num1 = context.pop();
        double num2 = context.pop();
        if (num1 == 0) {
            throw std::runtime_error("Division by zero");
        }
        context.push(num2 / num1);
    }
};

ADD_OPERATION(Div, /)