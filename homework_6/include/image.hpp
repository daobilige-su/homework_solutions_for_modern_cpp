#ifndef IMAGE_HPP_
#define IMAGE_HPP_

#include <cstddef>
#include <string>
#include <vector>
#include <algorithm>
#include <filesystem>

#include "io_tools.hpp"

namespace igg {
class Image {
public:
  Image();
  Image(int rows, int cols);
  int rows() const;
  int cols() const;
  uint8_t at(const int row, const int col) const;
  uint8_t& at(const int row, const int col);
  bool FillFromPgm(const std::string &file_name);
  void WriteToPgm(const std::string &file_name) const;
  std::vector<float> ComputeHistogram(int bins) const;
  void DownScale(int scale);
  void UpScale(int scale);

private:
  int rows_=0, cols_=0;
  std::vector<uint8_t> data_;
};
}

#endif