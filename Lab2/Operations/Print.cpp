#include "../Operation.h"
#include "../OperationMaker.h"
#include "../Exceptions.h"

class Print : public Operation {
public:
    void run(std::list<std::string> &args, Context &context) override {
        if (args.empty()) {
            if (context.stackSize() == 0) {
                throw emptyStackException("PRINT: Stack is empty");
            }
            double num = context.top();
            std::cout << num << std::endl;
        } else {
            for (const auto &arg:args) {
                if (arg == "\\n") {
                    std::cout << std::endl;
                }else {
                    std::cout << arg << " ";
                }
            }
        }
    }
};

ADD_OPERATION(Print, PRINT)