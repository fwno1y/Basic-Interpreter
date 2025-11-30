#include "Token.hpp"

TokenStream::TokenStream(std::vector<Token>&& tokens)//构造函数
    : tokens_(std::move(tokens)), cursor_(0) {}

const Token* TokenStream::peek() const {//返回光标处的token
  if (cursor_ >= tokens_.size()) {
    return nullptr;
  }
  return &tokens_[cursor_];
}

const Token* TokenStream::get() {//返回光标处token并前进一格
  const Token* current = peek();
  if (current != nullptr) {
    ++cursor_;
  }
  return current;
}

bool TokenStream::empty() const { return cursor_ >= tokens_.size(); }//判断光标处是否为空，即光标是否越界

void TokenStream::reset() { cursor_ = 0; }//重置光标位置，回到开头

int TokenStream::position() const { return cursor_; }//返回光标当前位置

int TokenStream::size() const { return tokens_.size(); }//返回当前tokes_数组中token的个数

void TokenStream::push(Token&& token) { tokens_.push_back(std::move(token)); }//尾部插入一个token

const std::vector<Token>& TokenStream::data() const { return tokens_; }//取出整个数组
