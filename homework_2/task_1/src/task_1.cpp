#include <cstdlib>
#include <iostream>
#include <random>
#include <cstdlib>

int main() {
  const int kNumMax = 99;
  const int kNumMin = 0;
  
  std::random_device rd;
  std::uniform_int_distribution<int> dist(kNumMin, kNumMax);

  const int kNumToGuess = dist(rd);
  bool guess_going_on = true;
  int input_num = -1;

  while (guess_going_on) {
    std::cout << "Provide your guess:";
    std::cin >> input_num;

    if (std::cin.fail()) {
      std::cerr << "Error encountered, exiting..." << std::endl;
      std::cout << "The generated number is: " << kNumToGuess << std::endl;
      std::exit(EXIT_FAILURE);
    }
    else if (input_num > kNumMax || input_num < kNumMin) {
      std::cerr << "[WARNING] : Number must be between 0 and 99" << std::endl;
    } else if (input_num > kNumToGuess) {
      std::cout << "The number is smaller." << std::endl;
    } else if (input_num < kNumToGuess) {
      std::cout << "The number is larger." << std::endl;
    } else if (input_num == kNumToGuess) {
      std::cout << "You have won." << std::endl;
      std::cout << "The generated number is: " << kNumToGuess << std::endl;
      guess_going_on = false;
    }
  }
  std::exit(EXIT_SUCCESS);
}