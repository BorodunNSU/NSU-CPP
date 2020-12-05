#include "../Operation.h"
#include "../OperationMaker.h"

class Define : public Operation {
public:
    void run( std::list<std::string> &args, Context &context) override{
        if (args.size() < 2) {
            throw std::runtime_error("Not enough arguments for define");
        }
        std::string variable = args.back();
        double value = std::stod(args.front());
        context.addVariable(variable, value);
    }
};

ADD_OPERATION(Define, DEFINE)