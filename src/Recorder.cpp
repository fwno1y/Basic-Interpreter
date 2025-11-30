#include "Recorder.hpp"
#include <iostream>
#include <map>

Recorder::~Recorder() {
  clear();
}
void Recorder::add(int line, Statement* stmt) {//加入语句，覆盖原有或插入
  auto it = lines.find(line);
  if (it != lines.end()) {
    delete it->second;
    it->second = stmt;
  }
  else {
    lines.insert({line,stmt});
  }
}

void Recorder::remove(int line) {//移除行
  auto it = lines.find(line);
  if (it != lines.end()) {
    delete it->second;
    lines.erase(it);
  }
}

const Statement* Recorder::get(int line) const noexcept {//获取行号对应的语句
  auto it = lines.find(line);
  if (it != lines.end()) {
    return it->second;
  }
  return nullptr;
}

bool Recorder::hasLine(int line) const noexcept {//判断行号是否存在
  auto it = lines.find(line);
  if (it != lines.end()) {
    return true;
  }
  return false;
}

void Recorder::clear() noexcept {//清空map
  for (auto & line : lines) {
    delete line.second;
  }
  lines.clear();
}

void Recorder::printLines() const {//打印当前所有程序行
  for (auto line : lines) {
    std::cout << line.second->text() << std::endl;
  }
}

int Recorder::nextLine(int line) const noexcept {//跳到下一行（比当前行号大的第一行）
  auto it = lines.upper_bound(line);
  if (it != lines.end()) {
    return it->first;
  }
  return -1;
}

// TODO: Imply interfaces declared in the Recorder.hpp.