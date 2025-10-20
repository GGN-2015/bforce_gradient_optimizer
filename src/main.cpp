#include <iostream>
#include "BoxRangeSet.h"
#include "CalculateValue.h"
#include "Constant.h"
#include "ConstantProduct.h"
#include "MinFunction.h"
#include "ValueSet.h"
#include "Variable.h"

int main() {
    // 定义变量
    Variable v1, v2;
    std::cout << v1.toString() << std::endl;
    std::cout << v2.toString() << std::endl;

    // 定义变量的取值组合
    ValueSet valset;
    valset.setValueById(1, RealCalculateValue(-1.1));
    valset.setValueById(2, RealCalculateValue(-0.5));

    // 描述每个变量的值的取值范围
    BoxRangeSet boxset;
    boxset.setRange(1, BoxRange(RealCalculateValue(-1.0), RealCalculateValue(+1.0)));
    boxset.setRange(2, BoxRange(RealCalculateValue(-1.0), RealCalculateValue(+1.0)));


    // 修正一个取值范围
    std::cout << valset.toString() << std::endl;
    boxset.fixValueSet(valset);
    std::cout << valset.toString() << std::endl;

    // 定义常量
    Constant cval(RealCalculateValue(-1.0));
    Constant coef(RealCalculateValue( 2.0));

    // 定义表达式
    ConstantProduct cprod(coef, v2);

    MinFunction func;
    func.addSubFunction(v1);
    func.addSubFunction(cprod);
    func.addSubFunction(cval);

    // 计算表达式的取值和导数
    RealCalculateValue ans_calc;
    ValueSet der_calc;
    func.calculate(ans_calc, der_calc, valset);

    std::cout << func.toString() << std::endl;
    std::cout << ans_calc.toString() << std::endl;
    std::cout << der_calc.toString() << std::endl;
    return 0;
}
