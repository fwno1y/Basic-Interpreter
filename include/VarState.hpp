#pragma once

#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

class VarState {
 public:
  void setValue(const std::string& name, int value);//构造函数
  int getValue(const std::string& name) const;//得到变量名对应的值
  void clear();//清空变量

 private:
  std::unordered_map<std::string, int> values_;//键值对存储变量
};
