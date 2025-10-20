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
        const std::vector<ValueSet*>& function_derivatives) const override {

        // 复制所有的 key，然后将 value 全设置为 0
        derivative_storage.copy(*function_derivatives[0]);
        derivative_storage.setZero();

        int equ_val = 0; // 计算等于 max_or_max 的函数值有多少个
        for(int i = 0; i < (int)sub_functions.size(); i += 1) {
            if(function_values[i] -> equ(*max_or_max_value)) {
                equ_val += 1;
            }
        }
        assert(equ_val >= 1); // 最大值至少有一个

        // 统计所有最大值处对应的导函数的和
        for(int i = 0; i < (int)sub_functions.size(); i += 1) {
            if(function_values[i] -> equ(*max_or_max_value)) {
                derivative_storage.add(*function_derivatives[i]);
            }
        }
        derivative_storage.div(equ_val); // 计算平均值
    }
};
