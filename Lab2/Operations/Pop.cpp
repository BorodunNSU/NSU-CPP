#include "../Operation.h"
#include "../OperationMaker.h"
#include "../Exceptions.h"

class Pop : public Operation {
public:
    void run( std::list<std::string> &args, Context &context) override{
        if (!args.empty()) {
            throw badArgsException("Too much arguments for 'POP'");
        }
        if (context.stackIsEmpty()) {
            throw emptyStackException("POP: Stack is empty");
        }
        context.pop();
    }
};

ADD_OPERATION(Pop, POP)