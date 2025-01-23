#ifndef HISTOGRAM_HPP_
#define HISTOGRAM_HPP_

#include <opencv2/core/mat.hpp>
#include <ostream>
#include <string>
#include <vector>
#include <iostream>
#include "BowDictionary.hpp"

namespace ipb {

class Histogram {
public:
  Histogram();
  Histogram(const std::vector<int>& data);
  Histogram(const cv::Mat &descriptors,
            const BowDictionary& dictionary);

//   std::ostream& operator<<(std::ostream &os);
  int& operator[](std::size_t idx);
  const int& operator[](std::size_t idx) const;

  bool WriteToCSV(std::string filaname);
  static Histogram ReadFromCSV(std::string filaname);
  // Imitate stl_vector functionality

  std::vector<int> data() const;
  int size() const;
  bool empty() const;
  std::vector<int>::iterator begin();
  std::vector<int>::const_iterator begin() const;
  std::vector<int>::const_iterator cbegin() const;
  std::vector<int>::iterator end();
  std::vector<int>::const_iterator end() const;
  std::vector<int>::const_iterator cend() const;

private:
  // data members:
  std::vector<int> data_;
};

std::ostream &operator<<(std::ostream &os, const Histogram &histogram);

} // namespace ipb

#endif