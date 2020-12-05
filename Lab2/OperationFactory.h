#pragma once

#include "Operation.h"
#include "OperationInterface.h"
#include "OperationMaker.h"

class OperationFactory {
private:
    std::map<std::string, OperationInterface *> makers;

    OperationFactory() = default;

    ~OperationFactory() = default;

public:
    OperationFactory(const OperationFactory &) = delete;

    static OperationFactory &getFactory() {
        static OperationFactory factory;
        return factory;
    }

    [[nodiscard]] std::unique_ptr<Operation> getOperation(const std::string &operationName) const {
        auto i = makers.find(operationName);
        if (i == makers.end()) {
            throw std::runtime_error("Unknown operation " + operationName);
        }
        OperationInterface *maker = i->second;
        return maker->make();
    }

    void addMaker(const std::string &key, OperationInterface *maker) {
        makers[key] = maker;
    }
};