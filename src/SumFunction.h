#pragma once

#include "MinMaxSumFunction.h"

class SumFunction: public MinMaxSumFunction {
public:
    virtual ~SumFunction(){}
    SumFunction(): MinMaxSumFunction("sum"){}

    // 这个函数用于计算 lhs 和 rhs 的 min 或者 max 最终把结果保存在 lhs 中
    // 需要在子类中覆写这个方法
    virtual void makeMinOrMaxOrSum(AbstractCalculateValue* lhs, const AbstractCalculateValue* rhs) const override {
        lhs -> add(*rhs);
    }

    // 使用当前函数的函数值，子函数的函数值，子函数的导数值，合并得到当前函数的导数值
    virtual void mergeDerivative(
        ValueSet& derivative_storage, 
        const AbstractCalculateValue* max_or_max_value,              // SumFunction 并不使用这个参数，不影响正确性 
        const std::vector<AbstractCalculateValue*>& function_values, // SumFunction 并不使用这个参数，不影响正确性 
        const std::vector<ValueSet*>& function_derivatives) const override {

        // 对所有导函数无脑求和即可
        derivative_storage.copy(*function_derivatives[0]);
        for(int i = 1; i < (int)sub_functions.size(); i += 1) {
            derivative_storage.add(*function_derivatives[i]);
        }
    }

    // 由于 MinMaxSumFunction 不能实例化，所以只能在这里实现 clone
    virtual AbstractFunction* clone() override final {
        SumFunction* ans = new SumFunction;
        for(auto ptr: this -> sub_functions) {
            ans -> addSubFunction(ptr);
        }
        return ans;
    }
};
