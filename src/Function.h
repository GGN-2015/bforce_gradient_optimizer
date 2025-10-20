#pragma once
#include <string>
#include <vector>
#include "CalculateValue.h"
#include "ValueSet.h"

class AbstractFunction {
public:
    virtual ~AbstractFunction(){}

    // 给定参数取值，计算函数值和偏导数的值，函数值存储在 value_storage, 偏导数存储在 derivative_storage
    virtual void calculate(AbstractCalculateValue& value_storage, ValueSet& derivative_storage, const ValueSet& value_set) = 0;

    // 得到字符串形式
    virtual std::string toString() const = 0;

    // 克隆一个完全一模一样的，采用深拷贝，调用者负责释放空间
    virtual AbstractFunction* clone() const = 0;
};
