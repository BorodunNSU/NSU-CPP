#include "../Operation.h"
#include "../OperationMaker.h"

class Sub : public Operation {
public:
    void run(std::list<std::string> &args, Context &context) override {
        if (context.stackSize() < 2) {
            throw std::runtime_error("Not enough operands for subtraction");
        }
        double num1 = context.pop();
        double num2 = context.pop();
        double sub = num2 - num1;
        context.push(sub);
    }
};

ADD_OPERATION(Sub, -)