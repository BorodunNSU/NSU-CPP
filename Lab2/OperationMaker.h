#pragma once

#include "OperationInterface.h"
#include "OperationFactory.h"

#define ADD_OPERATION(T, NAME) static AddOperation<T> maker(#NAME);

template<typename T>
class AddOperation : public OperationInterface {
public:
    explicit AddOperation(const std::string &name) {
        OperationFactory::getFactory().addMaker(name, this);
    }

    virtual std::unique_ptr<Operation> make() const override {
        std::unique_ptr<Operation> unique_ptr(new T());
        return unique_ptr;
    }
};