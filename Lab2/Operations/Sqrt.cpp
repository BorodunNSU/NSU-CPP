#include <cmath>
#include "../Operation.h"
#include "../OperationMaker.h"
#include "../Exceptions.h"

class Sqrt : public Operation {
public:
    void run(std::list<std::string> &args, Context &context) override {
        if (context.stackIsEmpty()) {
            throw badArgsException("No operand for 'SQRT'");
        }
        if (!args.empty()){
            throw badArgsException("Too much arguments for 'SQRT'");
        }
        context.push(sqrt(context.pop()));
    }
};

ADD_OPERATION(Sqrt, SQRT)