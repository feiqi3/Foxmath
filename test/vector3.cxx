#include <cmath>
#include <iostream>
#include <cassert>
#include "../vector/vector3.h"

void dotTest();

void crossTest();

void lengthTest();

void maxElemTest();

void minElemTest();

void sqrtTest();

void squareTest();

void mulTest();

void scaleTest();

void divTest();

void hasNanTest();

void memAlignTest();
int main() {
	dotTest();
	crossTest();
	lengthTest();
	maxElemTest();
	minElemTest();
	sqrtTest();
	squareTest();
	mulTest();
	scaleTest();
	divTest();
	hasNanTest();
    memAlignTest();
}

bool equ(FMFLOAT a, FMFLOAT b) {
	return abs(a - b) < 0.000001;
}

void crossTest() {
	fm::vector3 veca(0, 1, 0);
	fm::vector3 vecb(1, 0, 0);
	fm::vector3 ans = veca.cross(vecb);
	assert(ans[2] == -1);
	std::cout << veca << " Cross " << vecb << " = " << ans << std::endl;
}


void lengthTest() {
	fm::vector3 veca(1, 1, 1);
	assert( equ(veca.length(),sqrtf(3)) );
	std::cout << veca << ".length = " << veca.length() << std::endl;
}

void dotTest() {
	fm::vector3 veca(3, 2, 1);
	fm::vector3 vecb(1, 1, 1);
	std::cout << veca << " Dot " << vecb << " = " << veca.dot(vecb) << std::endl;
	assert(veca.dot(vecb) == 6);
}

void maxElemTest() {
	fm::vector3 veca(100, 200, 300);
	assert(veca.maxElement() == 300);
	std::cout << "Max element of " << veca << " is " << veca.maxElement() << std::endl;
}

void minElemTest() {
	fm::vector3 veca(100, 200, 300);
	assert(veca.minElement() == 100);
	std::cout << "Min element of " << veca << " is " << veca.minElement() << std::endl;
}

void sqrtTest() {
	fm::vector3 veca(100, 9, 4);
	fm::vector3 vecb = veca.sqrt();
	assert(vecb[0] == 10 && vecb[1] == 3 && vecb[2] == 2);
	std::cout << "sqrt " << veca << " = " << vecb << std::endl;
}

void squareTest() {
	fm::vector3 veca(1, 4, 9);
	fm::vector3 vecb = veca.square();
	assert(vecb[0] == 1 && vecb[1] == 16 && vecb[2] == 81);
	std::cout << "square " << veca << " = " << vecb << std::endl;
}

void mulTest() {
	fm::vector3 veca(1, 2, 3);
	fm::vector3 vecb(0.3, 0.4, 0.5);
	fm::vector3 vecc = veca * vecb;
	std::cout << veca << " * " << vecb << " = " << vecc << std::endl;
	assert(equ(vecc[0], 0.3) && equ(vecc[1], 0.8) && equ(vecc[2], 1.5));
}

void scaleTest() {
	fm::vector3 veca(1, 2, 3);
	fm::vector3 vecb = veca * 3;
	assert(equ(vecb[0], 3) && equ(vecb[1], 6) && equ(vecb[2], 9));
	std::cout << veca << " * " << 3 << " = " << vecb << std::endl;
	vecb = 3 * veca;
	assert(equ(vecb[0], 3) && equ(vecb[1], 6) && equ(vecb[2], 9));
	std::cout << 3 << " * " << veca << " = " << vecb << std::endl;
}

void divTest() {
	fm::vector3 veca(4, 8, 16);
	fm::vector3 vecb = veca / 2;
	assert(equ(vecb[0], 2) && equ(vecb[1], 4) && equ(vecb[2], 8));
	std::cout << veca << " / " << 2 << " = " << vecb << std::endl;
	veca = vecb / vecb;
	assert(equ(veca[0], 1) && equ(veca[1], 1) && equ(veca[2], 1));
	std::cout << vecb << " / " << vecb << " = " << veca << std::endl;

}

void hasNanTest() {
	fm::vector3 veca(-10, -9, -4);
	fm::vector3 vecb = veca.sqrt();
	assert(fm::hasNan(vecb));
	std::cout << "sqrt " << veca << " = " << vecb << std::endl;

}

void memAlignTest(){
	for (int i = 0; i < 1000; ++i) {
		auto t = FM_ALIGN_NEW(fm::vector3)(2,3,5); 
		fm::simd::MEM_ALIGN_CHECK(t, FM_ALIGN_REQ);
	}
}