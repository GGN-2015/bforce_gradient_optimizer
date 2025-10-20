#include "Constant.h"
#include "AbstractFunction.h"

class ConstantProduct: public AbstractFunction {
protected:
    Constant* cval;
    AbstractFunction* absfunc;

public:
    virtual ~ConstantProduct(){}
    ConstantProduct(const Constant& _cval, const AbstractFunction& _absfunc) {
        cval    = dynamic_cast<Constant*>(_cval.clone());
        absfunc = dynamic_cast<AbstractFunction*>(_absfunc.clone());
    }

    // 给定参数取值，计算函数值和偏导数的值，函数值存储在 value_storage, 偏导数存储在 derivative_storage
    virtual void calculate(AbstractCalculateValue& value_storage, ValueSet& derivative_storage, const ValueSet& value_set) override {
        
        // 先把常数值取出来，存放到 value_storage
        // 这个操作还会清空 derivative_storage，因为常函数导数总是零
        cval -> calculate(value_storage, derivative_storage, value_set);

        // 为了获得同类型的对象，进行一次拷贝
        AbstractCalculateValue* tmp = value_storage.clone();

        // 对子函数进行一次求解
        absfunc -> calculate(value_storage, derivative_storage, value_set);

        // 计算结果
        value_storage.mul(*tmp);

        // 计算导函数
        derivative_storage.mul(*tmp);

        // 析构临时变量
        delete tmp;
    }

    // 得到字符串形式
    virtual std::string toString() const override {
        return "(" + cval -> toString() + " * " + absfunc -> toString() + ")";
    }

    // 克隆一个完全一模一样的，采用深拷贝，调用者负责释放空间
    virtual AbstractFunction* clone() const override {
        return new ConstantProduct(*cval, *absfunc);
    }

    // 禁用拷贝构造函数
    ConstantProduct(const ConstantProduct&) = delete;
    ConstantProduct& operator=(const ConstantProduct&) = delete;
    ConstantProduct(ConstantProduct&&) = delete;
    ConstantProduct& operator=(ConstantProduct&&) = delete;
};
