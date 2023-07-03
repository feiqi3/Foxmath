#include <iostream>
#include <cassert>
#include <ostream>
#include "../vector/vector4.h"

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
	const int tt = FM_ALIGN_REQ;
	FMFLOAT Ttt = 3.0;
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
	return std::abs(a - b) < 0.000001;
}

void crossTest() {
	fm::vector4 veca(0, 1, 0, 0);
	fm::vector4 vecb(1, 0, 0, 0);
	fm::vector4 ans = veca.cross(vecb);
	assert(ans[2] == -1);
	std::cout << veca << " Cross " << vecb << " = " << ans << std::endl;
}


void lengthTest() {
	fm::vector4 veca(1, 1, 1, 1);
	assert(veca.length() == 2);
	std::cout << veca << ".length = " << veca.length() << std::endl;
}

void dotTest() {
	fm::vector4 veca(3, 2, 1, 0);
	fm::vector4 vecb(1, 1, 1, 1);
	std::cout << veca << " Dot " << vecb << " = " << veca.dot(vecb) << std::endl;
	assert(veca.dot(vecb) == 6);
}

void maxElemTest() {
	fm::vector4 veca(100, 200, 300, 0);
	assert(veca.maxElement() == 300);
	std::cout << "Max element of " << veca << " is " << veca.maxElement() << std::endl;
}

void minElemTest() {
	fm::vector4 veca(100, 200, 300, 0);
	assert(veca.minElement() == 0);
	std::cout << "Min element of " << veca << " is " << veca.minElement() << std::endl;
}

void sqrtTest() {
	fm::vector4 veca(100, 9, 4, 36);
	fm::vector4 vecb = veca.sqrt();
	assert(vecb[0] == 10 && vecb[1] == 3 && vecb[2] == 2 && vecb[3] == 6);
	std::cout << "sqrt " << veca << " = " << vecb << std::endl;
}

void squareTest() {
	fm::vector4 veca(1, 4, 9, 16);
	fm::vector4 vecb = veca.square();
	assert(vecb[0] == 1 && vecb[1] == 16 && vecb[2] == 81 && vecb[3] == 256);
	std::cout << "square " << veca << " = " << vecb << std::endl;
}

void mulTest() {
	fm::vector4 veca(1, 2, 3, 4);
	fm::vector4 vecb(0.3, 0.4, 0.5, 0.6);
	fm::vector4 vecc = veca * vecb;
	std::cout << veca << " * " << vecb << " = " << vecc << std::endl;
	assert(equ(vecc[0], 0.3) && equ(vecc[1], 0.8) && equ(vecc[2], 1.5) && equ(vecc[3], 2.4));
}

void scaleTest() {
	fm::vector4 veca(1, 2, 3, 4);
	fm::vector4 vecb = veca * 3;
	assert(equ(vecb[0], 3) && equ(vecb[1], 6) && equ(vecb[2], 9) && equ(vecb[3], 12));
	std::cout << veca << " * " << 3 << " = " << vecb << std::endl;
	vecb = 3 * veca;
	assert(equ(vecb[0], 3) && equ(vecb[1], 6) && equ(vecb[2], 9) && equ(vecb[3], 12));
	std::cout << 3 << " * " << veca << " = " << vecb << std::endl;
}

void divTest() {
	fm::vector4 veca(4, 8, 16, 32);
	fm::vector4 vecb = veca / 2;
	assert(equ(vecb[0], 2) && equ(vecb[1], 4) && equ(vecb[2], 8) && equ(vecb[3], 16));
	std::cout << veca << " / " << 2 << " = " << vecb << std::endl;
	veca = vecb / vecb;
	assert(equ(veca[0], 1) && equ(veca[1], 1) && equ(veca[2], 1) && equ(veca[3], 1));
	std::cout << vecb << " / " << vecb << " = " << veca << std::endl;

}

void hasNanTest() {
	fm::vector4 veca(-10, -9, -4, -36);
	fm::vector4 vecb = veca.sqrt();
	assert(fm::hasNan(vecb));
	std::cout << "sqrt " << veca << " = " << vecb << std::endl;
}

void memAlignTest() {
	size_t totalAlloctMem = 0;
	for (int i = 0; i < 1000; ++i) {
		totalAlloctMem += 8 * sizeof(FMFLOAT);
		fm::simd::fmAlignFLoat4 tmp{ 1,2,3,4 };
		auto a = FM_ALIGN_NEW(fm::vector4)(tmp._v);
		auto b = FM_ALIGN_NEW(fm::vector4)(tmp._v);
		a->dot(*b);
		fm::simd::MEM_ALIGN_CHECK(a, FM_ALIGN_REQ);
	}
	std::cout << "Memory align test has allocte " << totalAlloctMem << "B, test passed.\n";
}
