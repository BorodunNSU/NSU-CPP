#pragma once

#include <cmath>
#include <iostream>
#include <utility>
#include <list>
#include "Context.h"

class Operation {
public:
    virtual void run(std::list<std::string> &args, Context &context) = 0;

    virtual ~Operation() = default;
};

