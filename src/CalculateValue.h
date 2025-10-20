#pragma once
#include <string>

// 什么是数值：就是可以进行计算的
class AbstractCalculateValue {
public:
    AbstractCalculateValue(){}
    virtual ~AbstractCalculateValue(){}

    virtual void add(const AbstractCalculateValue& rhs) = 0;
    virtual void sub(const AbstractCalculateValue& rhs) = 0;
    virtual void mul(const AbstractCalculateValue& rhs) = 0;
    virtual void div(const AbstractCalculateValue& rhs) = 0;
    virtual void min(const AbstractCalculateValue& rhs) = 0;
    virtual void max(const AbstractCalculateValue& rhs) = 0;

    // 从整数或者浮点数获得一个计算结果
    virtual void fromInt (int   ) = 0;
    virtual void fromReal(double) = 0;
    virtual int toInt() = 0;
    virtual double toReal() = 0;

    // 将计算结果显示成字符串
    virtual std::string toString() const = 0;

    // 克隆函数
    // 克隆出来的东西要记得释放
    virtual AbstractCalculateValue* clone() const = 0;

    // 赋值函数
    virtual void setValue(const AbstractCalculateValue& rhs) = 0;

    // 比较大小：给定一个小于等于，用于实现所有其他算符
    virtual bool leq(const AbstractCalculateValue& rhs) const = 0;
    virtual bool equ(const AbstractCalculateValue& rhs) const {
        return this -> leq(rhs) && rhs.leq(*this);
    }
    virtual bool geq(const AbstractCalculateValue& rhs) const {
        return rhs.leq(*this);
    }
    virtual bool lt(const AbstractCalculateValue& rhs) const {
        return !this -> geq(rhs);
    }
    virtual bool gt(const AbstractCalculateValue& rhs) const {
        return !this -> leq(rhs);
    }
    virtual bool neq(const AbstractCalculateValue& rhs) const {
        return !this -> equ(rhs);
    }

    // 禁用拷贝构造函数
    AbstractCalculateValue(const AbstractCalculateValue&) = delete;
    AbstractCalculateValue& operator=(const AbstractCalculateValue&) = delete;
    AbstractCalculateValue(AbstractCalculateValue&&) = delete;
    AbstractCalculateValue& operator=(AbstractCalculateValue&&) = delete;
};

// 用于计算的实数
class RealCalculateValue: public AbstractCalculateValue {
private:
    double real_value;

public:
    RealCalculateValue(double _real_value) {
        real_value = _real_value;
    }
    RealCalculateValue() {
        real_value = 0.0;
    }
    virtual ~RealCalculateValue(){}

    virtual void add(const AbstractCalculateValue& rhs) override;
    virtual void sub(const AbstractCalculateValue& rhs) override;
    virtual void mul(const AbstractCalculateValue& rhs) override;
    virtual void div(const AbstractCalculateValue& rhs) override;
    virtual void min(const AbstractCalculateValue& rhs) override;
    virtual void max(const AbstractCalculateValue& rhs) override;

    // 从整数或者浮点数获得一个计算结果
    virtual void fromInt (int   ) override;
    virtual void fromReal(double) override;
    virtual int toInt() override {
        return (int)real_value;
    }
    virtual double toReal() override {
        return (double)real_value;
    }

    // 将计算结果显示成字符串
    virtual std::string toString() const override;

    // 克隆函数
    // 克隆出来的东西要记得释放
    virtual AbstractCalculateValue* clone() const override;

    // 赋值函数
    virtual void setValue(const AbstractCalculateValue& rhs) override;
    
    // 比较大小
    virtual bool leq(const AbstractCalculateValue& rhs) const override;


    // 禁用拷贝构造函数
    RealCalculateValue(const RealCalculateValue&) = delete;
    RealCalculateValue& operator=(const RealCalculateValue&) = delete;
    RealCalculateValue(RealCalculateValue&&) = delete;
    RealCalculateValue& operator=(RealCalculateValue&&) = delete;
};
