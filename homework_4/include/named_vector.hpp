#ifndef NAMED_VECTOR_HPP_
#define NAMED_VECTOR_HPP_

#include <vector>
#include <string>

namespace ipb {

template <typename T>
class named_vector{
private : 
  std::string name_;
  std::vector<T> vector_;

public:
  named_vector(){}
  named_vector(std::string name, std::vector<T> vector) : name_{name}, vector_{vector} {}
  std::string& name() {return name_;}
  std::vector<T>& vector() {return vector_;}
  size_t size() const { return vector_.size() + name_.size(); }
  bool empty() const noexcept { return (vector_.empty() || name_.empty()); }
  void reserve(size_t n) { vector_.reserve(n); }
  void resize(size_t n) { vector_.resize(n); }
  void resize(size_t n, const T& val) { vector_.resize(n, val); }
  size_t capacity() const noexcept {return vector_.capacity();}
};

// named_vector<int> dummy;
} // namespace ipb

#endif