#include "../Operation.h"
#include "../OperationMaker.h"

class Pop : public Operation {
public:
    void run( std::list<std::string> &args, Context &context) override{
        if (context.stackSize() == 0) {
            throw std::runtime_error("POP: Stack is empty");
        }
        context.pop();
    }
};

ADD_OPERATION(Pop, POP)