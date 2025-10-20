#pragma once
#include "CalculateValue.h"
#include "Function.h"

class Constant: public AbstractFunction {
protected:
    AbstractCalculateValue* value_now;
public:
    virtual ~Constant(){
        delete value_now;
    }

    // 决定一个常系数
    Constant(const AbstractCalculateValue& acv) {
        value_now = acv.clone();
    }

    // 给定参数取值，计算函数值和偏导数的值，函数值存储在 value_storage, 偏导数存储在 derivative_storage
    virtual void calculate(AbstractCalculateValue& value_storage, ValueSet& derivative_storage, const ValueSet& value_set) override {
        // 常数的函数值就是常数本身
        value_storage.setValue(*value_now);

        // 常数的导函数是 0
        derivative_storage.copy(value_set);
        derivative_storage.setZero();
    }

    // 得到字符串形式
    virtual std::string toString() const override {
        return value_now -> toString();
    }

    // 克隆一个完全一模一样的，采用深拷贝，调用者负责释放空间
    virtual AbstractFunction* clone() override {
        return new Constant(*(this -> value_now));
    }
};
