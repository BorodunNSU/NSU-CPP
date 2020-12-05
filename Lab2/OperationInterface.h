#pragma once

#include "Operation.h"
#include <memory>

class OperationInterface {
public:
    virtual std::unique_ptr<Operation> make() const = 0;

    virtual ~OperationInterface() = default;
};


