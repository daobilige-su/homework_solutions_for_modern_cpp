#include <cstddef>
#include <iostream>

int main() {

  for(int n=0; n<100; n++) {
    std::byte byte_array_local[102400*(n+1)];
    byte_array_local[0] = std::byte(0);

    std::cerr << (n + 1) * 100 << "[KiB] Allocated in the stack" << std::endl;
    
  }
}