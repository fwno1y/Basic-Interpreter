#pragma once

#include <string>

#include "Token.hpp"

class Lexer {
 public:
  TokenStream tokenize(const std::string& line) const;//读取输入

 private:
  static bool isLetterChar(char ch) noexcept;//判断是否为字母
  static bool isNumberChar(char ch) noexcept;//判断是否为数字
  static TokenType matchKeyword(const std::string& text) noexcept;//找到text对应的TokenType
};
