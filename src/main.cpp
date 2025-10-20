#include <iostream>
#include "Constant.h"
#include "ConstantProduct.h"
#include "GradientSolver.h"
#include "MaxFunction.h"
#include "SumFunction.h"

int main() {
    Variable x1;
    Constant c1(RealCalculateValue( 1.0));
    Constant n1(RealCalculateValue(-1.0));

    SumFunction sum1;
    sum1.addSubFunction(c1);
    sum1.addSubFunction(ConstantProduct(RealCalculateValue(-1.0), x1));

    SumFunction sum2;
    sum2.addSubFunction(n1);
    sum2.addSubFunction(x1);

    MaxFunction max1;
    max1.addSubFunction(sum1);
    max1.addSubFunction(sum2);

    ValueSet vs;
    vs.setIntValueById(1, -2, RealCalculateValue());

    GradientSolver gs(max1, BoxRangeSet(), vs, RealCalculateValue(4.0), RealCalculateValue(0.95));

    while(gs.getStepLenReal() > 1e-8) {
        gs.step();

        // std::string ans = "";
        // std::getline(std::cin, ans);
    }
    std::cout << gs.toString() << std::endl;
    return 0;
}
