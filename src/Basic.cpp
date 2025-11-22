#include <iostream>
#include <memory>
#include <string>

#include "Lexer.hpp"
#include "Parser.hpp"
#include "Program.hpp"
#include "Token.hpp"
#include "utils/Error.hpp"

int main() {
  Lexer lexer;
  Parser parser;
  Program program;

  std::string line;
  while (std::getline(std::cin, line)) {
    if (line.empty()) {
      continue;
    }
    try {
      // TokenStream tokens = lexer.tokenize(line);
      // auto parsedLine = parser.parseLine(tokens, line);
      //
      // auto lineNumber = parsedLine.getLine();
      // Statement* stmt = parsedLine.fetchStatement();
      //
      // if (lineNumber.has_value()) {
      //   // 有行号的情况 - 添加到程序或删除行
      //   if (stmt) {
      //     program.addStmt(lineNumber.value(), stmt);
      //   } else {
      //     program.removeStmt(lineNumber.value());
      //   }
      // } else {
      //   // 立即执行指令
      //   if (stmt) {
      //     program.execute(stmt);
      //     delete stmt;  // 立即执行的语句需要手动删除
      //   }
      // }
      // TODO: The main function.
    } catch (const BasicError& e) {
      std::cout << e.message() << "\n";
    }
  }
  return 0;
}