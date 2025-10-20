#include <algorithm>
#include <cassert>
#include "ValueSet.h"

bool ValueSet::checkValueById(int id) const {
    return value_set.count(id) > 0;
}

// 用于给每个变量的值都除以一个数
void ValueSet::div(double val) {
    AbstractCalculateValue* tmp = nullptr; // 利用辅助变量存储 val 的值
    for(auto [id, ptr]: this -> value_set) {
        if(tmp == nullptr) {
            tmp = ptr -> clone(); // 利用其中第一个原型初始化
            tmp->fromReal(val);
        }
        ptr -> div(*tmp);
    }
    delete tmp; // 删除辅助变量
}

// 用于给每个变量的值都乘以一个数
void ValueSet::mul(const AbstractCalculateValue& val) {
    for(auto [id, ptr]: this -> value_set) {
        ptr -> mul(val);
    }
}

AbstractCalculateValue* ValueSet::getValueById(int id) const {
    assert(checkValueById(id)); // 如果使用了不存在的编号，直接报错
    return value_set.lower_bound(id) -> second;
}

void ValueSet::setValueById(int id, const AbstractCalculateValue& new_value) {
    if(checkValueById(id)) {
        value_set[id]->setValue(new_value);
    }else {
        value_set[id] = new_value.clone();
    }
}

void ValueSet::setIntValueById(int id, int val, const AbstractCalculateValue& prototype) {
    if(checkValueById(id)) {
        value_set[id]->fromInt(val);
    }else {
        value_set[id] = prototype.clone();
        value_set[id]->fromInt(val);
    }
}

void ValueSet::setRealValueById(int id, double val,  const AbstractCalculateValue& prototype) {
    if(checkValueById(id)) {
        value_set[id]->fromReal(val);
    }else {
        value_set[id] = prototype.clone();
        value_set[id]->fromInt(val);
    }
}

std::string ValueSet::toString() const {
    std::string ans = "{";

    int cnt = value_set.size();
    int posnow = 0;

    for(auto [id, ptr]: value_set) {
        posnow += 1;
        ans += "\n    " + std::to_string(id) + ": " + getValueById(id)->toString();

        if(posnow < cnt) { // 不是最后一个元素
            ans += ",";
        }
    }
    return cnt == 0 ? (ans + "}") : (ans + "\n}");
}
