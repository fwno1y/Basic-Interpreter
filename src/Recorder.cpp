#include "Recorder.hpp"
#include <iostream>
#include <map>

Recorder::~Recorder() {
  clear();
}
void Recorder::add(int line, Statement* stmt) {
  auto it = lines.find(line);
  if (it != lines.end()) {
    delete it->second;
    it->second = stmt;
  }
  else {
    lines.insert({line,stmt});
  }
}

void Recorder::remove(int line) {
  auto it = lines.find(line);
  if (it != lines.end()) {
    delete it->second;
    lines.erase(it);
  }
}

const Statement* Recorder::get(int line) const noexcept {
  auto it = lines.find(line);
  if (it != lines.end()) {
    return it->second;
  }
  return nullptr;
}

bool Recorder::hasLine(int line) const noexcept {
  auto it = lines.find(line);
  if (it != lines.end()) {
    return true;
  }
  return false;
}

void Recorder::clear() noexcept {
  for (auto & line : lines) {
    delete line.second;
  }
  lines.clear();
}

void Recorder::printLines() const {
  for (auto line : lines) {
    std::cout << line.first << " " << line.second << std::endl;
  }
}

int Recorder::nextLine(int line) const noexcept {
  auto it = lines.upper_bound(line);
  if (it != lines.end()) {
    return it->first;
  }
  return -1;
}

// TODO: Imply interfaces declared in the Recorder.hpp.