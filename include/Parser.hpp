#pragma once

#include <memory>
#include <optional>

#include "Token.hpp"

class Statement;
class Expression;

class ParsedLine {
 private:
  std::optional<int> line_number_;//存储行号
  Statement* statement_;//语句

 public:
  ParsedLine();
  ~ParsedLine();

  void setLine(int line);//插入行号
  std::optional<int> getLine();//获取所有行
  void setStatement(Statement* stmt);//为语句赋值
  Statement* getStatement() const;//获取语句
  Statement* fetchStatement();//拿出语句
};

class Parser {
 public:
  ParsedLine parseLine(TokenStream& tokens,
                       const std::string& originLine) const;

 private:
  Statement* parseStatement(TokenStream& tokens,
                            const std::string& originLine) const;
  Statement* parseLet(TokenStream& tokens, const std::string& originLine) const;
  Statement* parsePrint(TokenStream& tokens,
                        const std::string& originLine) const;
  Statement* parseInput(TokenStream& tokens,
                        const std::string& originLine) const;
  Statement* parseGoto(TokenStream& tokens,
                       const std::string& originLine) const;
  Statement* parseIf(TokenStream& tokens, const std::string& originLine) const;
  Statement* parseRem(TokenStream& tokens, const std::string& originLine) const;
  Statement* parseEnd(TokenStream& tokens, const std::string& originLine) const;
  //Scope
  Statement* parseIndent(TokenStream& tokens, const std::string& originLine) const;
  Statement* parseDedent(TokenStream& tokens, const std::string& originLine) const;

  Expression* parseExpression(TokenStream& tokens) const;
  Expression* parseExpression(TokenStream& tokens, int precedence) const;

  int getPrecedence(TokenType op) const;
  int parseLiteral(const Token* token) const;

  mutable int leftParentCount{0};
};
