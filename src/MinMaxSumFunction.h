#pragma once

#include "Function.h"

// 用于计算最大值或者最小值的函数
class MinMaxSumFunction: public AbstractFunction {
protected:
    std::vector<AbstractFunction*> sub_functions;
    std::string function_name = "min_or_max";

public:
    MinMaxSumFunction(std::string _func_name){
        function_name = _func_name;
        assert(function_name == "min" || function_name == "max" || function_name == "sum");
    }
    virtual ~MinMaxSumFunction(){
        for(auto ptr: sub_functions) { // 释放所有指针，这里应当由当前对象负责释放
            delete ptr;
        }
    }

    // 这个函数用于计算 lhs 和 rhs 的 min 或者 max 最终把结果保存在 lhs 中
    // 需要在子类中覆写这个方法
    virtual void makeMinOrMaxOrSum(AbstractCalculateValue* lhs, const AbstractCalculateValue* rhs) const = 0;

    // 使用当前函数的函数值，子函数的函数值，子函数的导数值，合并得到当前函数的导数值
    virtual void mergeDerivative(
        ValueSet& derivative_storage, 
        const AbstractCalculateValue* max_or_max_value, 
        const std::vector<AbstractCalculateValue*>& function_values, 
        const std::vector<ValueSet*>& function_derivatives) const = 0;

    virtual void addSubFunction(AbstractFunction* new_func) { // 增加一个新的成员，不会使用参数提供的成员，而是克隆一个
        sub_functions.push_back(new_func -> clone());
    }

    // 得到字符串形式
    virtual std::string toString() const override final;

    // 克隆一个完全一模一样的，采用深拷贝，调用者负责释放空间
    virtual AbstractFunction* clone() override = 0;

    // 给定参数取值，计算函数值和偏导数的值，函数值存储在 value_storage, 偏导数存储在 derivative_storage
    virtual void calculate(AbstractCalculateValue& value_storage, ValueSet& derivative_storage, const ValueSet& value_set) override final;
};
