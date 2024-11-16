// Online C++ compiler to run C++ program online
#include <iostream>
#include <bit>
using namespace std;

int main() {
  for (unsigned int i = 1; i < 10; i++){
    cout << "I: " << i << " " << bit_width(i) - 1 << "\n";
  }
  return 0;
}