#pragma once

#include <map>
#include <tuple>
#include "AbstractFunction.h"

class MatrixFunction {
protected:
    int row, col;
    std::map<std::tuple<int, int>, AbstractFunction*> matrix;

public:
    virtual ~MatrixFunction() {
        for(auto [pr, ptr]: matrix) {
            if(ptr != nullptr) {
                delete ptr;
            }
        }
    }
    MatrixFunction(int _row, int _col): row(_row), col(_col) {
        assert(row > 0);
        assert(col > 0);
        for(int i = 0; i < row; i += 1) {
            for(int j = 0; j < col; j += 1) {
                matrix[std::make_tuple(i, j)] = nullptr;
            }
        }
    }

    // 设置某个位置的值
    virtual void setPosition(int r, int c, const AbstractFunction& absfun) final {
        assert(0 <= r && r < row);
        assert(0 <= c && c < col);
        matrix[std::make_tuple(r, c)] = absfun.clone();
    }

    // 获得矩阵中一个指定位置的值
    virtual AbstractFunction* getPosition(int r, int c) const final {
        assert(0 <= r && r < row);
        assert(0 <= c && c < col);
        return matrix.lower_bound(std::make_tuple(r, c)) -> second;
    }

    // 定义矩阵乘法中的数乘
    virtual AbstractFunction* dot(const AbstractFunction* lhs, const AbstractFunction* rhs) const = 0;

    // 定义矩阵乘法中的求和
    virtual AbstractFunction* sum(std::vector<const AbstractFunction*> val_list) const = 0;

    std::string toString() const {
        std::string ans = "[";
        for(int r = 0; r < row; r += 1) {
            std::string row_ans = "[";
            for(int c = 0; c < col; c += 1) {
                auto ptr = matrix.lower_bound(std::make_tuple(r, c)) -> second;
                if(ptr == nullptr) {
                    ans += "NULL";
                }else {
                    ans += ptr -> toString();
                }
                if(c != col - 1) {
                    ans += ", ";
                }else {
                    ans += "]";
                }
            }
            ans += "\n    " + row_ans;
            if(r != row - 1) {
                ans += ", ";
            }
        }
        return ans + "\n]";
    }

    // 这里由于很难实例化一个对象，所以需要将来定义克隆函数
    virtual MatrixFunction* clone() const = 0;
};
