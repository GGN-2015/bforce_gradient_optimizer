#include <algorithm>
#include <iomanip>  // 包含 setprecision、scientific 等
#include <sstream>  // 包含 stringstream
#include <string>

#include "CalculateValue.h"

static std::string doubleToSciString(double value) {
    std::stringstream ss;
    // 启用科学记数法，并设置总有效数字为 15 位（确保小数部分 15 位）
    ss << std::scientific << std::setprecision(15) << value;
    return ss.str();
}

void RealCalculateValue::add(const AbstractCalculateValue& rhs) {
    const RealCalculateValue& sub_rhs = dynamic_cast<const RealCalculateValue&>(rhs);
    real_value += sub_rhs.real_value;
}

void RealCalculateValue::sub(const AbstractCalculateValue& rhs) {
    const RealCalculateValue& sub_rhs = dynamic_cast<const RealCalculateValue&>(rhs);
    real_value -= sub_rhs.real_value;
}

void RealCalculateValue::mul(const AbstractCalculateValue& rhs) {
    const RealCalculateValue& sub_rhs = dynamic_cast<const RealCalculateValue&>(rhs);
    real_value *= sub_rhs.real_value;
}

void RealCalculateValue::div(const AbstractCalculateValue& rhs) {
    const RealCalculateValue& sub_rhs = dynamic_cast<const RealCalculateValue&>(rhs);
    real_value /= sub_rhs.real_value;
}

void RealCalculateValue::min(const AbstractCalculateValue& rhs) {
    const RealCalculateValue& sub_rhs = dynamic_cast<const RealCalculateValue&>(rhs);
    real_value = std::min(real_value, sub_rhs.real_value);
}

void RealCalculateValue::max(const AbstractCalculateValue& rhs) {
    const RealCalculateValue& sub_rhs = dynamic_cast<const RealCalculateValue&>(rhs);
    real_value = std::max(real_value, sub_rhs.real_value);
}

void RealCalculateValue::fromInt(int int_value) {
    real_value = int_value;
}

void RealCalculateValue::fromReal(double _real_value) {
    real_value = _real_value;
}

std::string RealCalculateValue::toString() const {
    return doubleToSciString(real_value);
}

AbstractCalculateValue* RealCalculateValue::clone() const {
    return new RealCalculateValue(this -> real_value);
}

void RealCalculateValue::setValue(const AbstractCalculateValue& rhs) {
    const RealCalculateValue& sub_rhs = dynamic_cast<const RealCalculateValue&>(rhs);
    real_value = sub_rhs.real_value;
}

bool RealCalculateValue::leq(const AbstractCalculateValue& rhs) const {
    const RealCalculateValue& sub_rhs = dynamic_cast<const RealCalculateValue&>(rhs);
    return (this -> real_value <= sub_rhs.real_value) || (std::abs(this -> real_value - sub_rhs.real_value) < 1e-8);
}
