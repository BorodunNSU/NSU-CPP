#include "../Operation.h"
#include "../OperationMaker.h"
#include "../Exceptions.h"

class Sum : public Operation {
public:
    void run(std::list<std::string> &args, Context &context) override {
        if (context.stackSize() < 2) {
            throw badArgsException("Not enough operands for '+'");
        }
        if (!args.empty()) {
            throw badArgsException("Too much arguments for '+'");
        }
        double sum = context.pop() + context.pop();
        context.push(sum);
    }
};

ADD_OPERATION(Sum, +)