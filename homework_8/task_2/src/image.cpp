#include "image.hpp"
// #include "io_strategy.hpp"
// #include <algorithm>
// #include <bits/stdint-uintn.h>
// #include <filesystem>

namespace igg {

Image::Image() {
  rows_ = 0;
  cols_ = 0;
  data_.clear();
}

Image::Image(int rows, int cols) {
  rows_ = rows;
  cols_ = cols;
  data_.resize(rows * cols);
}

int Image::rows() const { return rows_; }

int Image::cols() const { return cols_; }

RgbPixel Image::at(const int row, const int col) const {
  return data_[row * cols_ + col];
}

RgbPixel& Image::at(const int row, const int col) {
  return data_[row * cols_ + col];
}

bool Image::ReadFromDisk(const std::string &file_name) {
  if (strategy_ptr_ == nullptr) {
    std::exit(EXIT_FAILURE);
  }

  if (!std::filesystem::exists(file_name)) {
    return false;
  }

  // igg::io_tools::ImageData img_data = igg::io_tools::ReadFromPgm(file_name);

  ImageData img_read = strategy_ptr_->ReadFromDisk(file_name);
  rows_ = img_read.rows;
  cols_ = img_read.cols;
  data_ = img_read.data;

  return true;
}

void Image::WriteToDisk(const std::string &file_name) const {
  if (strategy_ptr_ == nullptr) {
    std::exit(EXIT_FAILURE);
  }
  // igg::io_tools::WriteToPgm(
  //     {rows_, cols_, *std::max_element(data_.begin(), data_.end()), data_},
  //     file_name);
  ImageData data_to_write;
  data_to_write.rows = rows_;
  data_to_write.cols = cols_;
  data_to_write.data = data_;
  strategy_ptr_->WriteToDisk(data_to_write, file_name);
}

// std::vector<float> Image::ComputeHistogram(int bins) const {
//   std::vector<float> hist;
//   hist.resize(bins);
//   std::fill(hist.begin(), hist.end(), 0.0);

//   int hist_idx;
//   const uint8_t kMaxVal = 255;
//   for (const auto &e : data_) {
//     if (e == kMaxVal) {
//       hist_idx=bins-1;
//     } else {
//       hist_idx = int(float(e) / (float(kMaxVal) / float(bins)));
//     }
//     hist[hist_idx] += 1.0/float(data_.size());
//   }

//   return hist;
// }

void Image::DownScale(int scale) {
  int rows_before_scale = rows_;
  int cols_before_scale = cols_;
  std::vector<RgbPixel> data_before_scale = data_;

  rows_ = rows_before_scale / scale;
  cols_ = cols_before_scale / scale;
  data_.resize(rows_ * cols_);
  for (int r = 0; r < rows_; r++) {
    for (int c = 0; c < cols_; c++) {
      data_[r * cols_ + c] =
          data_before_scale[r * scale * cols_before_scale + c * scale];
    }
  }
}

void Image::UpScale(int scale) {
  int rows_before_scale = rows_;
  int cols_before_scale = cols_;
  std::vector<RgbPixel> data_before_scale = data_;

  rows_ = rows_before_scale * scale;
  cols_ = cols_before_scale * scale;
  data_.resize(rows_ * cols_);

  for (int r = 0; r < rows_; r++) {
    for (int c = 0; c < cols_; c++) {
      data_[r * cols_ + c] =
          data_before_scale[int(r / scale) * cols_before_scale + int(c / scale)];
    }
  }
}

void Image::SetIoStrategy(std::shared_ptr<IoStrategy> strategy_ptr) {
  strategy_ptr_ = strategy_ptr;
}

} // namespace igg