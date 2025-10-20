#pragma once

#include "AbstractFunction.h"
#include "BoxRangeSet.h"
#include "ValueSet.h"

class GradientSolver {
protected:
    AbstractFunction* absfunc;
    BoxRangeSet* boxset;
    ValueSet* valnow; // 变量当前取值
    AbstractCalculateValue* steplen;
    AbstractCalculateValue* lr;
    AbstractCalculateValue* fvalnow; // 函数当前取值
    long long iter_time; // 记录迭代次数

public:
    GradientSolver(
        const AbstractFunction& _absfunc, 
        const BoxRangeSet& _boxset,
        const ValueSet& _init_val,
        const AbstractCalculateValue& _step,
        const AbstractCalculateValue& _lr): iter_time(0) {
    
        absfunc  =  _absfunc.clone();
        boxset   =   _boxset.clone();
        valnow   = _init_val.clone();
        steplen  =     _step.clone(); // 初始步长
        lr       =       _lr.clone(); // 学习率
        fvalnow  = nullptr;
    }

    double getStepLenReal() const {
        return steplen -> toReal();
    }

    ~GradientSolver() {
        delete absfunc;
        delete boxset;
        delete valnow;
        delete steplen;
        delete lr;
        delete fvalnow;
    }

    std::string toString() const {
        std::string ans = "";
        ans += "MINIMIZE     " + absfunc->toString() + "\n";
        ans += "SUBJECT TO   " + boxset->toString() + "\n";
        ans += "POSITION     " + valnow->toString() + "\n";
        ans += "STEP LENGTH  " + steplen->toString() + "\n";
        ans += "LEANING RATE " + lr->toString() + "\n";
        ans += "ITER TIME    " + std::to_string(iter_time) + "\n";

        if(fvalnow != nullptr) {
            ans += "FUNCTION VAL " + fvalnow -> toString() + "\n";
        }
        return ans;
    }

    void step() { // 对当前的优化问题优化一个步进
        iter_time += 1;

        // funcval 用于存储当前位置的函数值
        AbstractCalculateValue* funcval = lr -> clone();
        funcval -> fromInt(0);

        // derivative 用于存储函数的导数
        ValueSet derivative;
        derivative.copy(*valnow);
        derivative.setZero();

        // 计算当前处的函数值以及导数值
        absfunc -> calculate(*funcval, derivative, *valnow);
        fvalnow = funcval -> clone();

        // 寻找一个合适的前进步长
        ValueSet forward_direction;
        ValueSet next_position;

        // 下个位置的函数值
        AbstractCalculateValue* nextval = lr -> clone();
        nextval -> fromInt(0);

        // 下个位置的导数值
        ValueSet next_derivative;

        forward_direction.copy(derivative); // 导数函数的反方向，表示下降方向
        forward_direction.div(-1.0);
        forward_direction.mul(*steplen);

        // 记录下一次前进到的位置
        next_position.copy(*valnow);
        next_position.add(forward_direction);
        boxset->fixValueSet(next_position); // 修正定义域

        // 计算下个位置的函数值
        absfunc->calculate(*nextval, next_derivative, next_position);

        if(nextval -> lt(*funcval)) {    // 可以前进
            valnow->copy(next_position); // 直接走过去
            fvalnow->setValue(*nextval); // 记录新的函数值
        }else {
            steplen->mul(*lr); // 不可以前进，调整学习率，使得未来可能可以前进
        }

        // 清空临时变量
        delete funcval;
        delete nextval;
    }

    // 禁用拷贝构造函数
    GradientSolver(const GradientSolver&) = delete;
    GradientSolver& operator=(const GradientSolver&) = delete;
    GradientSolver(GradientSolver&&) = delete;
    GradientSolver& operator=(GradientSolver&&) = delete;
};
