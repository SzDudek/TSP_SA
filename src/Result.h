//
// Created by PC on 10/9/2023.
//

#ifndef PEA2_RESULT_H
#define PEA2_RESULT_H

#include <variant>
#include <optional>
#include "Status.h"

template<class Value>
class Result {
    std::variant<Value, Status> res;
public:

    Result(Value val):res(val){}


    Result(Status status):res(status){}


    bool hasValue() const{
        return std::holds_alternative<Value>(res);
    }


    bool hasError() const{
        return std::holds_alternative<Status>(res);
    }


    std::optional<Status> error() const{
        if(std::holds_alternative<Status>(res)) return std::get<Status>(res);
        return {};
    }


    Status status() const{
        if(std::holds_alternative<Value>(res)) return Status::SUCCESS;
        return std::get<Status>(res);
    }


    std::optional<int> value() const{
        if(std::holds_alternative<Value>(res)) return std::get<Value>(res);
        return {};
    }
};

#endif //PEA2_RESULT_H
