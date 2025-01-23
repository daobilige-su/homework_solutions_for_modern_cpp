#ifndef IMAGE_HPP_
#define IMAGE_HPP_

#include <cstddef>
#include <string>
#include <vector>
#include <algorithm>
#include <filesystem>

// #include "io_tools.hpp"

#include "png_io_strategy.hpp"
#include "ppm_io_strategy.hpp"

namespace igg {


class Image {
public:
  Image();
  Image(int rows, int cols);
  int rows() const;
  int cols() const;
  RgbPixel at(const int row, const int col) const;
  RgbPixel& at(const int row, const int col);
  bool ReadFromDisk(const std::string &file_name);
  void WriteToDisk(const std::string &file_name) const;
  // std::vector<float> ComputeHistogram(int bins) const;
  void DownScale(int scale);
  void UpScale(int scale);
  void SetIoStrategy(std::shared_ptr<IoStrategy> strategy_ptr);

private:
  int rows_=0, cols_=0;
  std::vector<RgbPixel> data_;
  std::shared_ptr<IoStrategy> strategy_ptr_ = nullptr;
};
}

#endif