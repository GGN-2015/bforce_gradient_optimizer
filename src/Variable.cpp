#include "Variable.h"

// 记录当前实例化的变量的总个数
int Variable::variable_count = 0;

// 由于偏导数有很多维度，所以需要指定维度
// 给定参数取值，计算函数值和偏导数的值
void Variable::calculate(AbstractCalculateValue& value_storage, ValueSet& derivative_storage, const ValueSet& value_set) {
    value_storage.setValue(*value_set.getValueById(this -> variable_index)); // 存储函数值

    derivative_storage.clear();
    for(auto [id, ptr]: value_set.getAll()) {
        if(!derivative_storage.checkValueById(id)) {
            derivative_storage.setValueById(id, value_storage); // 这里赋值不重要，随便赋一个值
        }
        if(id == this -> variable_index) {
            derivative_storage.setIntValueById(id, 1, value_storage); // 将对应偏导数设置为 1, value_storage 仅仅提供类型
        }else {
            derivative_storage.setIntValueById(id, 0, value_storage); // 将对应偏导数设置为 0, value_storage 仅仅提供类型
        }
    }
}

// 得到字符串形式
std::string Variable::toString() const {
    return "x_" + std::to_string(this -> variable_index);
}
