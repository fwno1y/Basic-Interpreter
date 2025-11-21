#pragma once

#include <stdexcept>
#include <string>

class BasicError : public std::runtime_error {
 public:
  explicit BasicError(std::string&& message);

  const std::string& message() const noexcept;//声明该函数不会抛出异常

 private:
  std::string message_;
};
