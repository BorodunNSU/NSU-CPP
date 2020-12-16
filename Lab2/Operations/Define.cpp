#include "../Operation.h"
#include "../OperationMaker.h"
#include "../Exceptions.h"


class Define : public Operation {
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
        if (args.size() < 2) {
            throw badArgsException("Not enough arguments for 'DEFINE'");
        }
        if (args.size() > 2) {
            throw badArgsException("Too much arguments for 'DEFINE'");
        }
        std::string variable = args.front();
        if (isNumber(args.back())) {
            double value = std::stod(args.back());
            context.addVariable(variable, value);
        } else {
            throw badArgsException(args.back() + "is not a number");
        }

    }
};

ADD_OPERATION(Define, DEFINE)