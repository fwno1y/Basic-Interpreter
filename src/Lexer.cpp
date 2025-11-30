#include "Lexer.hpp"

#include <limits>
#include <string>
#include <unordered_map>
#include <vector>

#include "utils/Error.hpp"

const std::unordered_map<std::string, TokenType> TABLE = {//把字符串转为TokenType
    {"LET", TokenType::LET},     {"PRINT", TokenType::PRINT},
    {"INPUT", TokenType::INPUT}, {"END", TokenType::END},
    {"REM", TokenType::REM},     {"GOTO", TokenType::GOTO},
    {"IF", TokenType::IF},       {"THEN", TokenType::THEN},
    {"RUN", TokenType::RUN},     {"LIST", TokenType::LIST},
    {"CLEAR", TokenType::CLEAR}, {"QUIT", TokenType::QUIT},
    {"HELP", TokenType::HELP},
    //Scope
    {"INDENT",TokenType::INDENT},{"DEDENT",TokenType::DEDENT} };

bool isOverflow(const std::string& digits, bool negative) {//判断是否溢出
  constexpr long long max_limit = std::numeric_limits<int>::max();
  return negative ? std::stol(digits) > max_limit
                  : std::stol(digits) > max_limit + 1;
}

TokenStream Lexer::tokenize(const std::string& line) const {
  std::vector<Token> tokens;
  int column = 0;
  while (column < line.size()) {
    char ch = line[column];
    if (std::isspace(static_cast<int>(ch))) {//判断是否为空白字符
      ++column;
      continue;
    }

    if (isLetterChar(ch)) {//判断是否为字符
      int start = column;
      ++column;
      while (column < line.size() && isLetterChar(line[column])) {
        ++column;
      }
      std::string text = line.substr(start, column - start);//读取一个词
      TokenType type = matchKeyword(text);
      switch (type) {//判断类型
        case TokenType::REM://注释行
          tokens.push_back(Token{TokenType::REM, text, column});
          if (column < line.size()) {
            std::string comment = line.substr(column);
            tokens.push_back(Token{TokenType::REMINFO, comment, column + 1});//注释内容
          }
          return TokenStream(std::move(tokens));
        case TokenType::UNKNOWN:
          tokens.push_back(Token{TokenType::IDENTIFIER, text, column});
          break;
        default:
          tokens.push_back(Token{type, text, column});
      }
      continue;
    }

    if (isNumberChar(ch)) {//判断是否为数字并加入到tokens中
      int start = column;
      while (column < line.size() && isNumberChar(line[column])) {
        ++column;
      }
      std::string text = line.substr(start, column - start);
      tokens.push_back(Token{TokenType::NUMBER, text, column});
      continue;
    }

    TokenType symbolType = TokenType::UNKNOWN;
    switch (ch) {
      case '+':
        symbolType = TokenType::PLUS;
        break;
      case '-':
        symbolType = TokenType::MINUS;
        break;
      case '*':
        symbolType = TokenType::MUL;
        break;
      case '/':
        symbolType = TokenType::DIV;
        break;
      case '=':
        symbolType = TokenType::EQUAL;
        break;
      case '>':
        symbolType = TokenType::GREATER;
        break;
      case '<':
        symbolType = TokenType::LESS;
        break;
      case '(':
        symbolType = TokenType::LEFT_PAREN;
        break;
      case ')':
        symbolType = TokenType::RIGHT_PAREN;
        break;
      case ',':
        symbolType = TokenType::COMMA;
        break;
      default:
        break;
    }
    if (symbolType != TokenType::UNKNOWN) {//只要读取了正常的符号
      tokens.push_back(Token{symbolType, std::string(1, ch), column});
      ++column;
      continue;
    }

    throw BasicError("Unexpected character '" + std::string(1, ch) +
                     "' at column " + std::to_string(column));
  }
  return TokenStream(std::move(tokens));
}

bool Lexer::isLetterChar(char ch) noexcept {//判断字母
  return std::isalpha(static_cast<unsigned char>(ch));
}

bool Lexer::isNumberChar(char ch) noexcept {//判断数字
  return std::isalnum(static_cast<unsigned char>(ch)) || ch == '_';
}

TokenType Lexer::matchKeyword(const std::string& text) noexcept {//匹配TokenType
  auto it = TABLE.find(text);
  if (it != TABLE.end()) {
    return it->second;
  }
  return TokenType::UNKNOWN;
}