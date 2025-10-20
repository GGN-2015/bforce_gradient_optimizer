#pragma once

#include <map>
#include "Variable.h"
#include "BoxRange.h"
#include "ValueSet.h"

// 描述每一个变量的定义域约束范围，如果不存在则说明没有约束
class BoxRangeSet {
protected:
    std::map<int, BoxRange*> box_set;

public:
    BoxRangeSet(){}
    ~BoxRangeSet(){
        clear();
    }

    // 清空当前的所有约束条件
    void clear() {
        for(auto [id, ptr]: box_set) {
            delete ptr;
        }
        box_set.clear();
    }

    // 为某一个变量设置约束范围
    void setRange(int id, const BoxRange& new_box_range) {
        if(box_set.count(id) != 0) {
            delete box_set[id];
        }
        box_set[id] = new_box_range.clone();
    }

    // 删除掉对某个指定变量的约束
    void eraseRange(int id) {
        box_set.erase(id);
    }

    // 修正一个 valueSet 中的所有值的取值范围
    void fixValueSet(ValueSet& valset) const {
        for(auto [id, ptr]: valset.getAll()) {
            if(box_set.count(id) != 0) {
                box_set.lower_bound(id) -> second -> fixRange(*ptr);
            }
        }
    }

    // 转字符串：描述每个变量的取值范围
    std::string toString() const {
        std::string ans = "{";
        for(auto [id, ptr]: box_set) {
            Variable vtmp(id);
            ans += "\n    " + vtmp.toString() + " \\in " + ptr -> toString();
        }
        return box_set.size() == 0 ? (ans + "}") : (ans + "\n}");
    }
};