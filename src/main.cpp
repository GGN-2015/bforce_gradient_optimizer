#include <iostream>
#include "CalculateValue.h"
#include "SumFunction.h"
#include "ValueSet.h"
#include "Variable.h"

int main() {
    Variable v1, v2;
    std::cout << v1.toString() << std::endl;
    std::cout << v2.toString() << std::endl;

    ValueSet valset;
    valset.setValueById(1, RealCalculateValue(1.1));
    valset.setValueById(2, RealCalculateValue(1.1));

    SumFunction func;
    func.addSubFunction(&v1);
    func.addSubFunction(&v2);

    RealCalculateValue ans_calc;
    ValueSet der_calc;
    func.calculate(ans_calc, der_calc, valset);

    std::cout << ans_calc.toString() << std::endl;
    std::cout << der_calc.toString() << std::endl;
    return 0;
}
