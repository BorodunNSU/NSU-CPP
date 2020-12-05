#pragma once

#include <stack>
#include <string>
#include <map>

class Context {
    std::stack<double> stack;
    std::map<std::string, double> variables;
public:
    std::map<std::string, double> getVariables() {
        return variables;
    }

    double top() {
        return stack.top();
    }

    double pop() {
        double num = stack.top();
        stack.pop();
        return num;
    }

    void push(double num) {
        stack.push(num);
    }

    int stackSize() {
        return stack.size();
    }

    void addVariable(const std::string &key, double num) {
        variables[key] = num;
    }

    bool findVariable(const std::string &key) {
        return variables.find(key) != variables.end();
    }

};