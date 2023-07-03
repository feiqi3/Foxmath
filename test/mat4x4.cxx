#include "../matrix/matrix4x4.h"
#include <iostream>

void MultiTest();
void AddTest();
void SubTest();
void TransposeTest();

int main() {
  MultiTest();
  TransposeTest();
}

void MultiTest() {
  fm::mat4 a({1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16});
  fm::mat4 b({2, 3, 4, 5}, {2, 3, 4, 5}, {1, 1, 2, 3}, {2, 3, 4, 5});
  assert((a*b)[3][3] == 260);
  std::cout<<a<<"\n*\n"<<b <<"\n=\n"<< (a*b)<<"\n---" << std::endl;
  fm::vector4 aa(2,3,4,5);
  assert((aa*a)[2] == 146);
  std::cout<<aa<<"\n*\n"<<a <<"\n=\n"<< (aa*a)<<"\n---" << std::endl;
  assert((a*aa)[1] == 96);
  std::cout<<a<<"\n*\n"<<aa <<"\n=\n"<< (a*aa)<<"\n---" << std::endl;
}

void TransposeTest() {
  fm::mat4 a({1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16});
  std::cout<<a<<"\nTranspose\n=\n" << a.transpose()<<"\n---"<<std::endl;
  assert(a.transpose()[0][3] == 13 && a.transpose()[3][0] == 4);
}
