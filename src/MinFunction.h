#pragma once

#include "MinMaxFunction.h"

class MinFunction: public MinMaxFunction {
public:
    virtual ~MinFunction(){}
    MinFunction(): MinMaxFunction("min") {}

    virtual void makeMinOrMaxOrSum(AbstractCalculateValue* lhs, const AbstractCalculateValue* rhs) const override {
        lhs -> min(*rhs);
    }

    // 由于 MinMaxSumFunction 不能实例化，所以只能在这里实现 clone
    virtual AbstractFunction* clone() const override final {
        MinFunction* ans = new MinFunction;
        for(auto ptr: this -> sub_functions) {
            ans -> addSubFunction(*ptr);
        }
        return ans;
    }
};
