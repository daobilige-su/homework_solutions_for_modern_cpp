#include "image.hpp"
#include <algorithm>
#include <filesystem>

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

uint8_t Image::at(const int row, const int col) const {
  return data_[row * cols_ + col];
}
uint8_t& Image::at(const int row, const int col) {
  return data_[row * cols_ + col];
}

bool Image::FillFromPgm(const std::string &file_name) {
  if (!std::filesystem::exists(file_name)) {
    return false;
  }

  igg::io_tools::ImageData img_data = igg::io_tools::ReadFromPgm(file_name);
  rows_ = img_data.rows;
  cols_ = img_data.cols;
  data_ = img_data.data;

  return true;
}

void Image::WriteToPgm(const std::string &file_name) const {
  igg::io_tools::WriteToPgm(
      {rows_, cols_, *std::max_element(data_.begin(), data_.end()), data_},
      file_name);
}

std::vector<float> Image::ComputeHistogram(int bins) const {
  std::vector<float> hist;
  hist.resize(bins);
  std::fill(hist.begin(), hist.end(), 0.0);

  int hist_idx;
  for (const auto &e : data_) {
    if (e == 255) {
      hist_idx=bins-1;
    } else {
      hist_idx = int(float(e) / (255.0 / float(bins)));
    }
    hist[hist_idx] += 1.0/float(data_.size());
  }

  return hist;
}

void Image::DownScale(int scale) {
  int rows_before_scale = rows_;
  int cols_before_scale = cols_;
  std::vector<uint8_t> data_before_scale = data_;

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
  std::vector<uint8_t> data_before_scale = data_;

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

} // namespace igg