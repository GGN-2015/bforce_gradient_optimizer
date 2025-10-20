#include <iostream>
#include "Constant.h"
#include "ConstantProduct.h"
#include "GradientSolver.h"
#include "MaxFunction.h"
#include "SumFunction.h"

int main() {
    Variable x1, x2;
    Constant c1(RealCalculateValue( 1.0));
    Constant n1(RealCalculateValue(-1.0));

    SumFunction sum1;
    sum1.addSubFunction(c1);
    sum1.addSubFunction(ConstantProduct(RealCalculateValue(-1.0), x1));

    SumFunction sum2;
    sum2.addSubFunction(n1);
    sum2.addSubFunction(x2);

    MaxFunction max1;
    max1.addSubFunction(sum1);
    max1.addSubFunction(sum2);

    BoxRangeSet brs;
    brs.setRange(1, BoxRange(RealCalculateValue(-1.0), RealCalculateValue(1.0)));
    brs.setRange(2, BoxRange(RealCalculateValue(-1.0), RealCalculateValue(1.0)));

    ValueSet vs;
    vs.setIntValueById(1, 0, RealCalculateValue());
    vs.setIntValueById(2, 0, RealCalculateValue());

    Constant cf0(RealCalculateValue(0.1));
    AbstractFunction* r1 = max1.replaceVar(2, &cf0);

    GradientSolver gs(*r1, brs, vs, RealCalculateValue(4.0), RealCalculateValue(0.95));

    while(gs.getStepLenReal() > 1e-8) {
        gs.step();

        // std::string ans = "";
        // std::getline(std::cin, ans);
    }
    std::cout << gs.toString() << std::endl;
    delete r1;
    return 0;
}
