#include <cstdlib>
#include <iostream>
#include <random>
#include <cstdlib>
#include <sstream>
#include <string>

int main(int argc, char const *argv[]) {
  if (argc != 3) {
    std::cerr << "Error: The number of arguments is not 2." << std::endl;
    std::exit(EXIT_FAILURE);
  }
  else {
    std::stringstream arg1_str(argv[1]);
    std::stringstream arg2_str(argv[2]);

    int arg1_int, arg2_int;
    std::string arg1_ext, arg2_ext;
    arg1_str >> arg1_int >> arg1_ext;
    arg2_str >> arg2_int >> arg2_ext;

    if (arg1_ext == ".txt" && arg2_ext == ".txt") {
      std::cout << (arg1_int + arg2_int) / 2.0 << std::endl;
    } else if (arg1_ext == ".png" && arg2_ext == ".png") {
      std::cout << arg1_int + arg2_int << std::endl;
    } else if (arg1_ext == ".txt" && arg2_ext == ".png") {
      std::cout << arg1_int % arg2_int << std::endl;
    } else {
      std::cerr << "Error: Undefined file extensions." << std::endl;
      std::exit(EXIT_FAILURE);
    }

    std::exit(EXIT_SUCCESS);
  }
}