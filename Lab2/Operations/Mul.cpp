#include "../Operation.h"
#include "../OperationMaker.h"

class Mul : public Operation {
public:
    void run(std::list<std::string> &args, Context &context) override {
        if (context.stackSize() < 2) {
            throw std::runtime_error("Not enough operands for multiplication");
        }
        double mul = context.pop() * context.pop();
        context.push(mul);
    }
};

ADD_OPERATION(Mul, *)