#include "../Operation.h"
#include "../OperationMaker.h"
#include "../Exceptions.h"


class Push : public Operation {
private:
    bool isNumber(const std::string &str) {
        for (auto num : str) {
            if (!(isdigit(num) || num == '.' || num == ',')) {
                return false;
            }
        }
        return true;
    }

public:
    void run(std::list<std::string> &args, Context &context) override {
        if (args.empty()) {
            throw badArgsException("Not enough arguments for 'PUSH'");
        }
        if (args.size() > 1) {
            throw badArgsException("Too much arguments for 'PUSH'");
        }
        std::string variable = args.back();
        if (context.variableExists(variable)) {
            context.push(context.getVariable(variable));
        } else if (isNumber(variable)) {
            context.push(stod(variable));
        } else {
            throw badArgsException("'" + variable + "'" + " variable not exists");
        }

    }
};

ADD_OPERATION(Push, PUSH)