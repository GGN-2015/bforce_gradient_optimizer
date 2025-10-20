#pragma once
#include <string>
#include <vector>
#include "CalculateValue.h"
#include "ValueSet.h"

class AbstractFunction {
public:
    AbstractFunction(){}
    virtual ~AbstractFunction(){}

    // 给定参数取值，计算函数值和偏导数的值，函数值存储在 value_storage, 偏导数存储在 derivative_storage
    virtual void calculate(AbstractCalculateValue& value_storage, ValueSet& derivative_storage, const ValueSet& value_set) = 0;

    // 得到字符串形式
    virtual std::string toString() const = 0;

    // 克隆一个完全一模一样的，采用深拷贝，调用者负责释放空间
    virtual AbstractFunction* clone() const = 0;

    // 判断当前表达式是否是一个变量
    virtual bool isVar() const {
        return false;
    }
    virtual int  getVarId() const { // 只有在是变量的条件下才可以获取变量 id
        assert(isVar());
        return -1; // 无效的变量 id
    }

    // 递归取代所有变量，得到新表达式，不允许出现交叉依赖
    virtual AbstractFunction* replaceVar(int var_id, AbstractFunction* new_exp) const = 0;

    // 禁用拷贝构造函数
    AbstractFunction(const AbstractFunction&) = delete;
    AbstractFunction& operator=(const AbstractFunction&) = delete;
    AbstractFunction(AbstractFunction&&) = delete;
    AbstractFunction& operator=(AbstractFunction&&) = delete;
};
