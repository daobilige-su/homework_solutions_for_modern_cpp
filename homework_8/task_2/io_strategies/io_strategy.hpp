#ifndef IO_STRATEGY_HPP_
#define IO_STRATEGY_HPP_

#include <string>
#include <vector>

namespace igg {

struct RgbPixel {
public:
  uint8_t red = 0;
  uint8_t green = 0;
  uint8_t blue = 0;
};

struct ImageData {
  int rows;
  int cols;
  std::vector<RgbPixel> data;
};

class IoStrategy {
public:
  virtual ImageData ReadFromDisk(const std::string &file_name) = 0;
  virtual bool WriteToDisk(const ImageData &image_data,
                           const std::string &file_name) const = 0;
  virtual ~IoStrategy() = default;
};
}

#endif