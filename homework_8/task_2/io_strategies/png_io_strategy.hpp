#ifndef PNG_IO_STRATEGY_HPP_
#define PNG_IO_STRATEGY_HPP_

#include "io_strategy.hpp"
#include <png++/png.hpp>

namespace igg {
class PngIoStrategy : public IoStrategy {
public:
  ImageData ReadFromDisk(const std::string &file_name) override;
  bool WriteToDisk(const ImageData &image_data,
                   const std::string &file_name) const override;
  
};
}

#endif