#pragma once

#include "OperationInterface.h"
#include "Factory.h"

#define ADD_OPERATION(T, NAME) static AddOperation<T> maker(#NAME);

template<typename T>
class AddOperation : public OperationInterface {
public:
    virtual std::unique_ptr<Operation> make() const override {
        std::unique_ptr<Operation> ptr(new T());
        return ptr;
    }

    explicit AddOperation(const std::string &name) {
        Factory::getFactory().addMaker(name, this);
    }
};