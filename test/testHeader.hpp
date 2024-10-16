#ifndef TESTHEADER_HPP
#define TESTHEADER_HPP

#include "Math/Constants.h"
#include "Math/Functions.h"
#include "Math/Transform.h"
#include "Matrix/FoxMat4x4.h"
#include "Vector/FoxVec3.h"
#include "Vector/FoxVec4.h"
#include "FoxDef.h"
#include <string>
#include <functional>
#include <chrono>
#include <iostream>
#include <random>
#include <stdint.h>
#include <vector>

inline void Timebenchmark(std::function<FMFLOAT(FMFLOAT)> funca,
	const std::string& funcaname, std::vector<FMFLOAT>& premute) {
	std::cout.precision(17);
	std::cout << std::fixed;
	auto beg = std::chrono::steady_clock::now();
	volatile FMFLOAT tmp;
	for (auto t : premute) {
		tmp = funca(t);
	}
	auto end = std::chrono::steady_clock::now();

	std::cout << funcaname << " costs ==> "
		<< std::chrono::duration_cast<std::chrono::milliseconds>(end - beg)
		.count() /
		1000.
		<< "s\n\n";
}

inline void precisionTest(std::function<FMFLOAT(FMFLOAT)> funca,
	std::function<FMFLOAT(FMFLOAT)> funcB,
	const std::string& funcbname, FMFLOAT min, FMFLOAT max,
	FMFLOAT step) {
	std::cout.precision(17);
	long double totalCount = (max - min) / step;
	long double meanError = 0;
	long double maxError = 0;
	double pos = 0;
	for (long double t = min; t < max; t += step) {
		long double tmp = std::abs(funca(t) - funcB(t));
		if (std::isnan(tmp)) {
			volatile int k = funcB(t);
		}
		meanError += tmp;
		if (tmp > maxError) {
			maxError = tmp;
			pos = t;
		}
	}
	std::cout << funcbname << " Error test:\n"
		<< "Mean Error: " << meanError / totalCount
		<< "\nMax Error bounding: " << maxError << std::fixed << " at " << pos << "\n\n";
}

inline std::vector<FMFLOAT> preMute(uint32_t num, FMFLOAT min, FMFLOAT max) {

	std::vector<FMFLOAT> ret;
	std::random_device seed;      // 硬件生成随机数种子
	std::ranlux48 engine(seed()); // 利用种子生成随机数引擎
	std::uniform_real_distribution<FMFLOAT> dist(min, max);
	for (long long i = 0; i < num; ++i) {
		ret.push_back(dist(engine));
	}
	return ret;
}

#endif