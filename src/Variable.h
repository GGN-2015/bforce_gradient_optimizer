#pragma once
#include <cassert>
#include "Function.h"

// 用于描述变量
class Variable: public AbstractFunction {
private:
    static int variable_count;
    int variable_index; // 记录当前变量的 ID

public:

    // 定义一个新变量
    Variable() {
        variable_index = ++variable_count;
    }

    // 使用一个已经出现的变量（如果没出现过会推动变量名计数）
    Variable(int old_id) {
        if(!(1 <= old_id && old_id <= variable_count)) {
            variable_count = old_id;
        }
        variable_index = old_id;
    }

    // 给定参数取值，计算函数值和偏导数的值
    virtual void calculate(AbstractCalculateValue& value_storage, ValueSet& derivative_storage, const ValueSet& value_set) override final;

    // 得到字符串形式
    virtual std::string toString() const override final;

    // 拷贝一个完全一样的变量
    virtual AbstractFunction* clone() const override final{
        return new Variable(this -> variable_index);
    }
};
