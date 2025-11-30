#include "VarState.hpp"

#include <algorithm>

#include "utils/Error.hpp"
 VarState::VarState() {
   scopes_.push_back({});
 }
void VarState::setValue(const std::string& name, int value) {
   if (scopes_.empty()) {
     throw BasicError("SCOPE ERROR");
   }
   scopes_.back()[name] = value;
 }

int VarState::getValue(const std::string& name) const {
   for (int i = scopes_.size() - 1; i >= 0; i--) {
     const auto& scope = scopes_[i];
     auto it = scope.find(name);
     if (it != scope.end()) {
       return it->second;
     }
   }
   throw BasicError("VARIABLE NOT DEFINED");
 }

void VarState::clear() {
   scopes_.clear();
   scopes_.push_back({});
 }

void VarState::indent() {
   scopes_.push_back({});
 }


void VarState::dedent() {
   if (scopes_.size() <= 1) {
     throw BasicError("SCOPE UNDERFLOW");
   }
   scopes_.pop_back();
 }

// void VarState::setValue(const std::string& name, int value) {//加入变量
//   values_[name] = value;
// }
//
// int VarState::getValue(const std::string& name) const {//得到变量的值
//   auto it = values_.find(name);
//   if (it == values_.end()) {
//     throw BasicError("VARIABLE NOT DEFINED");
//   }
//   return it->second;
// }
//
// void VarState::clear() { values_.clear(); }//清空变量
