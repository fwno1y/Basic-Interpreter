#pragma once

#include <memory>
#include <string>

class VarState;

class Expression {//基类
 public:
  virtual ~Expression() = default;//虚析构函数
  virtual int evaluate(const VarState& state) const = 0;//纯虚函数
};

class ConstExpression : public Expression {//派生类1：整数常量
 public:
  explicit ConstExpression(int value);//构造函数
  ~ConstExpression() = default;//析构函数
  int evaluate(const VarState& state) const override;//重定义虚函数

 private:
  int value_;
};

class VariableExpression : public Expression {//派生类2：字符串
 public:
  explicit VariableExpression(std::string name);//构造函数
  ~VariableExpression() = default;//析构函数
  int evaluate(const VarState& state) const override;

 private:
  std::string name_;
};

class CompoundExpression : public Expression {//派生类3，二元运算
 public:
  CompoundExpression(Expression* left, char op, Expression* right);//构造函数
  ~CompoundExpression();//析构函数
  int evaluate(const VarState& state) const override;

 private:
  Expression* left_;
  Expression* right_;
  char op_;
};
