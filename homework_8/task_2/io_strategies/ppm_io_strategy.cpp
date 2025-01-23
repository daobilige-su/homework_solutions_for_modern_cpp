#include "ppm_io_strategy.hpp"
#include "io_strategy.hpp"
#include <bits/stdint-uintn.h>
#include <cstdio>
#include <ios>
#include <sstream>
#include <string>
#include <vector>
// #include "image.hpp"


namespace igg {

ImageData PpmIoStrategy::ReadFromDisk(const std::string &file_name) {
  std::ifstream infile(file_name, std::ios_base::in);
  std::string line, s;

  int count = 0;
  int rows, cols;
  std::vector<RgbPixel> data;

  int s_idx = 0, data_idx = 0;
  RgbPixel rgb;

  while (getline(infile, line)) {
    if(line[0]=='#'){continue;}
    // std::cout << "Read: " << line << std::endl;

    if (count == 0) { // P3
      count++;
    } else if (count == 1) { // width height
      count++;
      std::sscanf(line.c_str(), "%d %d", &cols, &rows);
      data.resize(rows * cols);
    } else if (count == 2) { // max value: unused
      count++;
    } else { // actual data
      std::istringstream iss{line};
      while (std::getline(iss, s, ' ')) {
        if (s_idx == 0) {
          s_idx++;
          rgb.red = std::stoi(s);
        } else if (s_idx == 1) {
          s_idx++;
          rgb.green = std::stoi(s);
        } else if (s_idx == 2) {
          s_idx = 0;
          rgb.blue = std::stoi(s);

          data[data_idx] = rgb;
          data_idx++;
        }
      }
    }

  }

//   png::image<png::rgb_pixel> image(file_name);
  // std::ifstream in(file_name, std::ios_base::in);
  // if (!in) {
  //   return {0, 0, 0, {}};
  // }

  // Read integers, if we read chars, we get 1 digit instead of the whole number
//   int rows = image.get_height();
//   int cols = image.get_width();
//   std::vector<RgbPixel> data;

//   data.resize(rows * cols);

//   for (png::uint_32 y = 0; y < static_cast<png::uint_32>(rows); ++y) {
//     for (png::uint_32 x = 0; x < static_cast<png::uint_32>(cols); ++x) {
//       data[y * cols + x] = {image[y][x].red, image[y][x].green, image[y][x].blue};
//     }
//   }

  return {rows, cols, data};
}

bool PpmIoStrategy::WriteToDisk(const ImageData &image_data,
                                const std::string &file_name) const {
  std::ofstream outfile(file_name, std::ios_base::out);
  outfile << "P3" << std::endl;
  outfile << image_data.cols << " " << image_data.rows << std::endl;
  outfile << 255 << std::endl;

  int count = 0;
  for (const auto &color : image_data.data) {
    count++;
    outfile << color.red << " " << color.green << " " << color.blue << " ";
    if (count == 10) {
      outfile << std::endl;
    }
  }

  return true;
}

} // namespace igg