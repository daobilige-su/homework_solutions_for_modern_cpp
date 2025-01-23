#include "homework_6.h"
#include <iostream>

// to test even if the default constructor is defined in igg::Image class, the
// rest of the 5 special functions are created by default.
// this means the 6 specials might be wrong on slides. It might be 5 speicals,
// excluding the default constructor.
int main() {
  
  igg::Image a;
  igg::Image b(10, 10);
  igg::Image c = b;
  igg::Image d(c);
  igg::Image e;
  e = d;

  std::cout << "size of Image e is : " << e.rows() << "x" << e.cols()
            << std::endl;

  std::cout << "with default constructor defined, the copy constructor and "
               "copy assign operator are still auto-generated and working. "
               "Instead of special 6, it might be special 5, excluding the "
               "default constructor."
            << std::endl;

  std::cout << "The program terminated cleanly." << std::endl;
  return 0;
}