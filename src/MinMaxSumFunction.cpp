#include "MinMaxSumFunction.h"

// 得到字符串形式
std::string MinMaxSumFunction::toString() const {
    std::string ans = this -> function_name + "(";

    int cnt = sub_functions.size();
    int posnow = 0;
    for(auto sub: sub_functions) {
        posnow += 1;
        ans += sub -> toString();
        if(posnow != cnt) {
            ans += ", ";
        }
    }
    return ans + ")";
}

// 给定参数取值，计算函数值和偏导数的值，函数值存储在 value_storage, 偏导数存储在 derivative_storage
void MinMaxSumFunction::calculate(AbstractCalculateValue& value_storage, ValueSet& derivative_storage, const ValueSet& value_set) {
    assert(sub_functions.size() > 0);

    // function_values 用于存储每个子函数的函数值
    std::vector<AbstractCalculateValue*> function_values;
    for(int i = 0; i < (int)sub_functions.size(); i += 1) {
        function_values.push_back(value_storage.clone());
        function_values[i] -> fromInt(0);
    }

    // function_derivatives 用于存储每个子函数的导数情况
    std::vector<ValueSet*> function_derivatives;
    for(int i = 0; i < (int)sub_functions.size(); i += 1) {
        function_derivatives.push_back(value_set.clone());
    }

    // 循环计算所有 sub_function 的导数和值
    for(int i = 0; i < (int)sub_functions.size(); i += 1) {
        sub_functions[i] -> calculate(*function_values[i], *function_derivatives[i], value_set);
    }

    // 计算所有函数的最大值（或者最小值）
    AbstractCalculateValue* max_or_max_value = value_storage.clone();
    max_or_max_value->setValue(*function_values[0]);
    for(int i = 1; i < (int)sub_functions.size(); i += 1) { // 考虑到 sum 这里就必须跳过第一个
        this -> makeMinOrMaxOrSum(max_or_max_value, function_values[i]);
    }

    // 通过函数值，子函数的函数值，子函数的导函数值，合并得到新的导函数值 derivative_storage
    this -> mergeDerivative(derivative_storage, max_or_max_value, function_values, function_derivatives);

    // 保存函数的取值
    value_storage.setValue(*max_or_max_value);

    // 释放所有用于辅助计算的变量
    delete max_or_max_value;
    for(int i = 0; i < (int)sub_functions.size(); i += 1) {
        delete function_values[i];
        delete function_derivatives[i];
    }
}
