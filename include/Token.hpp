#pragma once

#include <string>
#include <vector>

enum class TokenType {//枚举类
  // Keywords
  LET,
  PRINT,
  INPUT,
  END,
  REM,
  GOTO,
  IF,
  THEN,
  RUN,
  LIST,
  CLEAR,
  QUIT,
  HELP,
  //Scope
  INDENT,
  DEDENT,
  // Basic lexical units
  IDENTIFIER,
  NUMBER,
  REMINFO,
  // Operators and symbols
  PLUS,
  MINUS,
  MUL,
  DIV,
  EQUAL,
  GREATER,
  LESS,
  LEFT_PAREN,
  RIGHT_PAREN,
  COMMA,
  // Reserved placeholder
  UNKNOWN
};

struct Token {//类型、内容
  TokenType type{TokenType::UNKNOWN};
  std::string text{};
  int column{0};
};

class TokenStream {
 public:
  TokenStream() = default;
  explicit TokenStream(std::vector<Token>&& tokens);

  const Token* peek() const;
  const Token* get();
  bool empty() const;
  void reset();

  int position() const;
  int size() const;

  void push(Token&& token);
  const std::vector<Token>& data() const;

 private:
  std::vector<Token> tokens_{};//存储tokens
  int cursor_{0};//光标
};
