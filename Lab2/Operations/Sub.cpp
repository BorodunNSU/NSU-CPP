#include "../Operation.h"
#include "../OperationMaker.h"
#include "../Exceptions.h"

class Sub : public Operation {
public:
    void run(std::list<std::string> &args, Context &context) override {
        if (context.stackSize() < 2) {
            throw badArgsException("Not enough operands for '-'");
        }
        if (!args.empty()) {
            throw badArgsException("Too much arguments for '-'");
        }
        double num1 = context.pop();
        double num2 = context.pop();
        double sub = num2 - num1;
        context.push(sub);
    }
};

ADD_OPERATION(Sub, -)