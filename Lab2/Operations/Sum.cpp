#include "../Operation.h"
#include "../OperationMaker.h"

class Sum : public Operation {
public:
    void run(std::list<std::string> &args, Context &context) override {
        if (context.stackSize() < 2) {
            throw std::runtime_error("Not enough operands for summation");
        }
        double sum = context.pop() + context.pop();
        context.push(sum);
    }
};

ADD_OPERATION(Sum, +)