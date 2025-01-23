#ifndef IPB_ALGORITHM_HPP_
#define IPB_ALGORITHM_HPP_

#include <cctype>
#include <numeric>
#include <vector>
#include "named_vector.hpp"
#include <algorithm>
#include <iostream>

namespace ipb {

int accumulate(named_vector<int> &nv);

int count(named_vector<int> &nv, int kVal);

bool all_even(named_vector<int> &nv);

named_vector<int> clamp(named_vector<int> &nv, const int kMin, const int kMax);

named_vector<int> fill(named_vector<int> &nv, const int kVal);

bool find(named_vector<int> &nv, const int kVal);

void print(named_vector<int> &nv);

named_vector<int> toupper(named_vector<int> &nv);

named_vector<int> sort(named_vector<int> &nv);

named_vector<int> rotate(named_vector<int> &nv, const int kVal);

named_vector<int> reverse(named_vector<int> &nv);
}


#endif