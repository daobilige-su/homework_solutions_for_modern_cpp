#include "ipb_algorithm.hpp"

namespace ipb {

inline bool even(int i) { return i % 2 == 0; }
auto PrintArray = [](const int &kN) { std::cout << kN << ","; };
auto UpperCase(char c) { return std::toupper(c); }

int accumulate(named_vector<int> &nv) {
  return std::accumulate(nv.vector().begin(), nv.vector().end(), 0);
}

int count(named_vector<int> &nv, int kVal) {
  return std::count(nv.vector().begin(), nv.vector().end(), kVal);
}

bool all_even(named_vector<int> &nv) {
  return std::all_of(nv.vector().begin(), nv.vector().end(), even);
}

named_vector<int> clamp(named_vector<int> &nv, const int kMin, const int kMax) {
  for (auto &v : nv.vector()) {
    v = std::clamp(v, kMin, kMax);
  }
  return nv;
}

named_vector<int> fill(named_vector<int> &nv, const int kVal) {
  std::fill(nv.vector().begin(), nv.vector().end(), kVal);
  return nv;
}

bool find(named_vector<int> &nv, const int kVal) {
  auto res = std::find(nv.vector().begin(), nv.vector().end(), kVal);
  if (res != std::end(nv.vector())) {
    return true;
  } else {
    return false;
  }
}

void print(named_vector<int> &nv) {
  std::cout << "\"" << nv.name() << "\": ";
  std::for_each(nv.vector().begin(), nv.vector().end(), PrintArray);
  std::cout << std::endl;
}

named_vector<int> toupper(named_vector<int> &nv) {
  std::transform(nv.name().begin(), nv.name().end(), nv.name().begin(),
                 UpperCase);
  return nv;
}

named_vector<int> sort(named_vector<int> &nv) {
  std::sort(nv.vector().begin(), nv.vector().end());
  return nv;
}

named_vector<int> rotate(named_vector<int> &nv, const int kVal) {
  std::rotate(nv.vector().begin(), nv.vector().begin() + kVal,
              nv.vector().end());
  return nv;
}

named_vector<int> reverse(named_vector<int> &nv) {
  std::reverse(nv.vector().begin(), nv.vector().end());
  return nv;
}

}