#include "homework_5.h"
#include <iostream>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Error: No arg provided." << std::endl;
    std::cerr << "Usage: convert_freiburg_dataset <image folder path>."
              << std::endl;
  }

  std::filesystem::path img_data(argv[1]);

  ipb::serialization::sifts::ConvertDataset(img_data);
}