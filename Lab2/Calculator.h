#pragma once

#include "Context.h"

class Calculator {
private:
    Context context;
public:
    Calculator() = default;

    ~Calculator() = default;

    void calculate(std::istream &stream);
};