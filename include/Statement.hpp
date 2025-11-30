#pragma once

#include <memory>
#include <string>

#include "Expression.hpp"

class Program;
class VarState;

class Statement {
 public:
  explicit Statement(std::string source);
  virtual ~Statement() = default;

  virtual void execute(VarState& state, Program& program) const = 0;

  const std::string& text() const noexcept;

 private:
  std::string source_;
};

//要写`LET`、`PRINT`、`INPUT`、`GOTO`、`IF`、`REM`、`END`
class LETStatement : public Statement {
public:
  explicit LETStatement(std::string source,std::string var,Expression* expr);
  ~LETStatement() override;

  void execute(VarState& state, Program& program) const override;

private:
  std::string var;
  Expression* expr;

};

class PRINTStatement : public Statement {
public:
  explicit PRINTStatement(std::string source,Expression* expr);
  ~PRINTStatement() override;

  void execute(VarState& state, Program& program) const override;

private:
  Expression* expr;
};

class INPUTStatement : public Statement {
public:
  explicit INPUTStatement(std::string source,std::string var);

  void execute(VarState& state, Program& program) const override;

private:
  std::string var;
};

class GOTOStatement : public Statement{
public:
  explicit GOTOStatement(std::string source,int line);

  void execute(VarState& state, Program& program) const override;

private:
  int line;
};

class IFStatement : public Statement {
public:
  explicit IFStatement(std::string source,Expression* expr1,char op,Expression* expr2,int line);
  ~IFStatement() override;

  void execute(VarState& state, Program& program) const override;

private:
  Expression* expr1;
  char op;
  Expression* expr2;
  int line;
};

class REMStatement : public Statement {
public:
  explicit REMStatement(std::string source);

  void execute(VarState& state, Program& program) const override;

};

class ENDStatement : public Statement {
public:
  explicit ENDStatement(std::string source);

  void execute(VarState& state, Program& program) const override;

};
// TODO: Other statement types derived from Statement, e.g., GOTOStatement,
// LetStatement, etc.

//Scope
class INDENTStatement : public Statement {
public:
  explicit INDENTStatement(std::string source);

  void execute(VarState& state, Program& program) const override;
};
class DEDENTStatement : public Statement {
public:
  explicit DEDENTStatement(std::string source);

  void execute(VarState& state, Program& program) const override;
};