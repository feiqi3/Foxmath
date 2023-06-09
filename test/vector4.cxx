#include "base/basic_def.h"
#include <iostream>
#include <cassert>
#include "vector/vector4.h"  

void dotTest();

void crossTest();

void lengthTest();

void maxElemTest() {
	std::cout << fm::vector4(2, 5, 1, 0).maxElement();
}


int main() {
	dotTest();
	crossTest();
	lengthTest();
	maxElemTest();
}

void crossTest() {
	//TODO: BUGs in Cross
	fm::vector4 veca(4, 1, 0, 0);
	fm::vector4 vecb(1, 0, 3, 0);
	std::cout << veca.cross(vecb) << std::endl;
}


void lengthTest() {
	fm::vector4 veca(1, 1, 1, 1);
	assert(veca.length() == 2);
}

void dotTest() {
	fm::vector4 veca(9, 9, 9, 9);
	fm::vector4 vecb(1, 1, 1, 1);
	assert(veca.dot(vecb) == 36);
}