#pragma once

#include "MinMaxFunction.h"

class MaxFunction: public MinMaxFunction {
public:
    virtual ~MaxFunction(){}
    MaxFunction(): MinMaxFunction("max") {}

    virtual void makeMinOrMaxOrSum(AbstractCalculateValue* lhs, const AbstractCalculateValue* rhs) const override {
        lhs -> max(*rhs);
    }

    // 由于 MinMaxSumFunction 不能实例化，所以只能在这里实现 clone
    virtual AbstractFunction* clone() const override final {
        MaxFunction* ans = new MaxFunction;
        for(auto ptr: this -> sub_functions) {
            ans -> addSubFunction(*ptr);
        }
        return ans;
    }
};
