#pragma once

#include <cassert>
#include "CalculateValue.h"

// 用于描述一个变量的取值区间
class BoxRange {
protected:
    AbstractCalculateValue* minval;
    AbstractCalculateValue* maxval;

public:
    BoxRange(const AbstractCalculateValue& _minval, const AbstractCalculateValue& _maxval) {
        minval = _minval.clone();
        maxval = _maxval.clone();
        assert(minval -> leq(*maxval)); // 区间下界必须小于等于区间上界
    }
    ~BoxRange() {
        delete minval;
        delete maxval;
    }

    // 利用当前区间修正一个变量的值，保证这个变量值在这个区间里
    void fixRange(AbstractCalculateValue& var_now) const {
        if(var_now.leq(*minval)) { // 小于等于区间下界
            var_now.setValue(*minval);
        }else if(var_now.geq(*maxval)) { // 大于等于区间上界
            var_now.setValue(*maxval);
        }
    }

    // 判断变量值是否在区间范围内
    bool checkRange(const AbstractCalculateValue& var_now) const {
        return var_now.geq(*minval) && var_now.leq(*maxval);
    }

    // 转字符串
    std::string toString() const {
        return "[" + minval -> toString() + ", " + maxval -> toString() + "]";
    }

    // 克隆一个
    BoxRange* clone() const {
        return new BoxRange(*this -> minval, *this -> maxval);
    }
};
