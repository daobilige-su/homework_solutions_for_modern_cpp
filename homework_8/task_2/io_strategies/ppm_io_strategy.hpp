#ifndef PPM_IO_STRATEGY_HPP_
#define PPM_IO_STRATEGY_HPP_

#include "io_strategy.hpp"
#include <fstream>
#include <iostream>

namespace igg {
class PpmIoStrategy : public IoStrategy {
public:
  ImageData ReadFromDisk(const std::string &file_name) override;
  bool WriteToDisk(const ImageData &image_data,
                   const std::string &file_name) const override;
  
};

}

#endif