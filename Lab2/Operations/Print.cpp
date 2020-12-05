#include "../Operation.h"
#include "../OperationMaker.h"

class Print : public Operation {
public:
    void run( std::list<std::string> &args, Context &context) override{
        if (context.stackSize() == 0) {
            throw std::runtime_error("PRINT: Stack is empty");
        }
        double num = context.top();
        std::cout << num << std::endl;
    }
};

ADD_OPERATION(Print, PRINT)