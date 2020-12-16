#pragma once

#include "Operation.h"
#include "OperationInterface.h"
#include "OperationMaker.h"
#include "Exceptions.h"

class Factory {
private:
    std::map<std::string, OperationInterface *> operationMakers;

    Factory() = default;

    ~Factory() = default;

public:
    static Factory &getFactory() {
        static Factory factory;
        return factory;
    }

    [[nodiscard]] std::unique_ptr<Operation> getOperation(std::string &operationName) const {
        auto i = operationMakers.find(operationName);
        if (i == operationMakers.end()) {
            std::string name = "'" + operationName + "'";
            throw badOperationException("Unknown operation " + name);
        }
        OperationInterface *operationMaker = i->second;
        return operationMaker->make();
    }

    void addMaker(const std::string &key, OperationInterface *maker) {
        operationMakers[key] = maker;
    }
};