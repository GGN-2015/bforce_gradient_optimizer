#pragma once

#include <cassert>
#include <map>
#include <memory>
#include <string>
#include "CalculateValue.h"

// 描述一组变量的赋值情况
class ValueSet {
private:
    // 数据结构中的 AbstractCalculateValue* 指针不应该被其他对象共享
    std::map<int, AbstractCalculateValue*> value_set;

public:
    ValueSet() {} // 建议直接使用午餐构造函数，用来确保内存安全性
    ~ValueSet() {
        // 在析构时候释放所有数值对象
        this -> clear();
    }

    // 检查某一个指定的编号是否存在
    bool checkValueById(int id) const;

    // 用于清空所有值
    void clear() {
        for(auto [id, ptr]: value_set) { 
            delete ptr;
        }
        value_set.clear();
    }

    // 把 rhs 中的每一个值加到当前变量上去
    void add(const ValueSet& rhs) {
        for(auto [id, ptr]: rhs.value_set) {
            assert(this -> checkValueById(id));
            value_set[id] -> add(*ptr);
        }
    }

    // 用于给每个变量的值都除以一个数
    void div(double val);

    // 用于给每个变量的值都乘以一个数
    void mul(const AbstractCalculateValue& val);

    // 复制一个一模一样的 ValueSet
    void copy(const ValueSet& rhs) {
        this -> clear();
        for(auto [id, ptr]: rhs.value_set) { 
            this -> setValueById(id, *ptr);
        }
    }

    // 把所有现有变量对应的值都设置为 0
    void setZero() {
        for(auto [id, ptr]: value_set) { 
            ptr -> fromInt(0);
        }
    }

    // 获得某个编号对应的值，并存储到 acv 中
    AbstractCalculateValue*  getValueById(int id) const;

    // 设置某个指定编号对应的值
    void setValueById(int id, const AbstractCalculateValue& new_value);

    // 直接指定值, prototype 用于指定类型
    void setIntValueById(int id, int val, const AbstractCalculateValue& prototype);
    void setRealValueById(int id, double val, const AbstractCalculateValue& prototype);

    // 将内容转化为字符串输出
    std::string toString() const;

    // 获取不可读写的全体值
    const std::map<int, AbstractCalculateValue*>& getAll() const {
        return value_set;
    }

    // 拷贝一个一模一样的，不负责释放拷贝出来的对象
    ValueSet* clone() const {
        auto* new_obj = new ValueSet;
        for(auto [id, ptr]: value_set) {
            new_obj -> setValueById(id, *ptr);
        }
        return new_obj;
    }

    // 禁用拷贝构造函数
    ValueSet(const ValueSet&) = delete;
    ValueSet& operator=(const ValueSet&) = delete;
    ValueSet(ValueSet&&) = delete;
    ValueSet& operator=(ValueSet&&) = delete;
};
