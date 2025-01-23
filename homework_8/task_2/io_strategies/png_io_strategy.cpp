#include "png_io_strategy.hpp"
#include "image.hpp"
#include <fstream>
#include <png++/types.hpp>

namespace igg {

ImageData PngIoStrategy::ReadFromDisk(const std::string &file_name) {
  png::image<png::rgb_pixel> image(file_name);
  // std::ifstream in(file_name, std::ios_base::in);
  // if (!in) {
  //   return {0, 0, 0, {}};
  // }

  // Read integers, if we read chars, we get 1 digit instead of the whole number
  int rows = image.get_height();
  int cols = image.get_width();
  std::vector<RgbPixel> data;

  data.resize(rows * cols);

  for (png::uint_32 y = 0; y < static_cast<png::uint_32>(rows); ++y) {
    for (png::uint_32 x = 0; x < static_cast<png::uint_32>(cols); ++x) {
      data[y * cols + x] = {image[y][x].red, image[y][x].green, image[y][x].blue};
    }
  }

  return {rows, cols, data};
}

bool PngIoStrategy::WriteToDisk(const ImageData &image_data,
                                const std::string &file_name) const {
  png::image<png::rgb_pixel> image(image_data.rows, image_data.cols);
  int rows = image.get_height();
  int cols = image.get_width();

  for (png::uint_32 y = 0; y < static_cast<png::uint_32>(rows); ++y) {
    for (png::uint_32 x = 0; x < static_cast<png::uint_32>(cols); ++x) {
      image[y][x] = png::rgb_pixel(image_data.data[y * cols + x].red,
                                   image_data.data[y * cols + x].green,
                                   image_data.data[y * cols + x].blue);
    }
  }
  image.write(file_name);

  return true;
}

} // namespace igg