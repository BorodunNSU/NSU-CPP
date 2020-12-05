#include <cmath>
#include "../Operation.h"
#include "../OperationMaker.h"

class Sqrt : public Operation {
public:
    void run(std::list<std::string> &args, Context &context) override {
        if (context.stackSize() == 0) {
            throw std::runtime_error("No operand for sqrt");
        }
        context.push(sqrt(context.pop()));
    }
};

ADD_OPERATION(Sqrt, SQRT)