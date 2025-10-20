#pragma once
#include "MinMaxSumFunction.h"

class MinMaxFunction: public MinMaxSumFunction {
public:
    virtual ~MinMaxFunction(){}
    MinMaxFunction(std::string _func_name): MinMaxSumFunction(_func_name){}

    // 使用当前函数的函数值，子函数的函数值，子函数的导数值，合并得到当前函数的导数值
    virtual void mergeDerivative(
        ValueSet& derivative_storage, 
        const AbstractCalculateValue* max_or_max_value, 
        const std::vector<AbstractCalculateValue*>& function_values, 
        const std::vector<ValueSet*>& function_derivatives) const override;
};
