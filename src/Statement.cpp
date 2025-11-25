#include "Statement.hpp"

#include <iostream>
#include <limits>
#include <sstream>
#include <utility>

#include "Program.hpp"
#include "VarState.hpp"
#include "utils/Error.hpp"

Statement::Statement(std::string source) : source_(std::move(source)) {}

const std::string& Statement::text() const noexcept { return source_; }

LETStatement::LETStatement(std::string source, std::string var,Expression* expr) : Statement(std::move(source)),var(std::move(var)),expr(expr) {}

LETStatement::~LETStatement() {
  delete expr;
}

void LETStatement::execute(VarState& state, Program& program) const {
  int value = expr->evaluate(state);
  state.setValue(var,value);
}

PRINTStatement::PRINTStatement(std::string source,Expression* expr) : Statement(std::move(source)),expr(expr) {}

PRINTStatement::~PRINTStatement() {
  delete expr;
}

void PRINTStatement::execute(VarState& state, Program& program) const {
  int value = expr->evaluate(state);
  std::cout << value << std::endl;
}

INPUTStatement::INPUTStatement(std::string source, std::string var) : Statement(std::move(source)),var(std::move(var)) {}

void INPUTStatement::execute(VarState& state, Program& program) const {
  std::cout << ' ' << '?' << ' ';
  int value;
  std::cin >> value;
  state.setValue(var,value);
}

GOTOStatement::GOTOStatement(std::string source, int line) : Statement(std::move(source)),line(line) {}

void GOTOStatement::execute(VarState& state, Program& program) const {
  program.changePC(line);
}

IFStatement::IFStatement(std::string source, Expression* expr1, char op,Expression* expr2, int line) : Statement(std::move(source)),expr1(expr1),op(op),expr2(expr2),line(line) {}

IFStatement::~IFStatement() {
  delete expr1;
  delete expr2;
}

void IFStatement::execute(VarState& state, Program& program) const {
  int left = expr1->evaluate(state);
  int right = expr2->evaluate(state);
  bool flag = false;
  if (op == '=') {
    if (left == right) {
      flag = true;
    }
  }
  else if (op == '>') {
    if (left > right) {
      flag = true;
    }
  }
  else if (op == '<') {
    if (left < right) {
      flag = true;
    }
  }
  if (flag) {
    program.changePC(line);
  }
}

REMStatement::REMStatement(std::string source) : Statement(std::move(source)) {}

void REMStatement::execute(VarState& state, Program& program) const {}

ENDStatement::ENDStatement(std::string source) : Statement(std::move(source)) {}

void ENDStatement::execute(VarState& state, Program& program) const {
  program.programEnd();
}
// TODO: Imply interfaces declared in the Statement.hpp.
