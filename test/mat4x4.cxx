#include "Matrix/FoxMat4x4.h"
#include <iostream>
#include <ostream>

void MultiTest();
void AddTest();
void SubTest();
void TransposeTest();
void determinant();
void inverse();
void memoryLayout(){
  auto mat = fm::mat4::identity();
  double* ptr = (double*)&mat[0];  
  for (int i = 0; i < 16; ++i) {
    std::cout<<ptr[i]<<" ";
  }
  std::cout<<std::endl;
}
int main() {
  MultiTest();
  TransposeTest();
  determinant();
  inverse();
  memoryLayout();
}

void MultiTest() {
  fm::mat4 a({1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16});
  fm::mat4 b({2, 3, 4, 5}, {2, 3, 4, 5}, {1, 1, 2, 3}, {2, 3, 4, 5});
  assert((a * b)[3][3] == 260);
  std::cout << a << "\n*\n" << b << "\n=\n" << (a * b) << "\n---" << std::endl;
  fm::vector4 aa(2, 3, 4, 5);
  assert((aa * a)[2] == 146);
  std::cout << aa << "\n*\n"
            << a << "\n=\n"
            << (aa * a) << "\n---" << std::endl;
  assert((a * aa)[1] == 96);
  std::cout << a << "\n*\n"
            << aa << "\n=\n"
            << (a * aa) << "\n---" << std::endl;
}

void determinant() {
  fm::mat4 a({1, 2, 3, 4}, {2, 3, 4, 5}, {9, 1, 3, 3}, {1, 44, 1, 5});
  assert(std::abs(a.determinant() - (-298))<0.1);
  std::cout << a << "\ndeterminant\n=\n"
            << a.determinant() << "\n---" << std::endl;
}

void inverse() {
  fm::mat4 a({1, 2, 3, 4}, {2, 3, 4, 5}, {9, 1, 3, 3}, {1, 44, 1, 5});
  std::cout << a << "\nInverse\n=\n"
            << a.inverse() << "\n---" << std::endl;
}

void TransposeTest() {
  fm::mat4 a({1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16});
  std::cout << a << "\nTranspose\n=\n" << a.transpose() << "\n---" << std::endl;
  assert(a.transpose()[0][3] == 13 && a.transpose()[3][0] == 4);
}
