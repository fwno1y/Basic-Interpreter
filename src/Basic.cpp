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
      TokenStream tokens = lexer.tokenize(line);
      const Token* firstToken = tokens.peek();
      if (firstToken && tokens.size() == 1) {
        switch (firstToken->type) {
          case TokenType::RUN:
            program.run();
            continue;
          case TokenType::LIST:
            program.list();
            continue;
          case TokenType::CLEAR:
            program.clear();
            continue;
          case TokenType::QUIT:
            return 0;
          case TokenType::HELP:
            std::cout << "help" << std::endl;
          default:break;
        }
      }
      ParsedLine parsedLine = parser.parseLine(tokens, line);
      std::optional<int> lineNumber = parsedLine.getLine();
      Statement* stmt = parsedLine.fetchStatement();

      if (lineNumber.has_value()) {
        if (stmt != nullptr) {
          program.addStmt(lineNumber.value(), stmt);
        } else {
          program.removeStmt(lineNumber.value());
        }
      } else {
        if (stmt != nullptr) {
          program.execute(stmt);
          delete stmt;
        }
      }
      // TODO: The main function.
    } catch (const BasicError& e) {
      std::cout << e.message() << "\n";
    }
  }
  return 0;
}