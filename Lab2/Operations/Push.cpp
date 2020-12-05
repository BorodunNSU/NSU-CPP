#include "../Operation.h"
#include "../OperationMaker.h"

class Push : public Operation {
public:
    void run(std::list<std::string> &args, Context &context) override {
        if (args.empty()) {
            throw std::runtime_error("Not enough arguments for push");
        }
        std::string variable = args.back();
        if (context.findVariable(variable)) {
            context.push(context.getVariables().at(variable));
        } else {
            context.push(stod(variable));
        }
    }
};

ADD_OPERATION(Push, PUSH)