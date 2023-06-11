#include "cpu_check.hpp"
#include "intrin.h"
#include <bitset>
#include <iostream>

namespace fm {


	void CpuChecker::m_cpuid(int registers[4], int eax, int ecx = 0) {
		__cpuidex(registers, eax, ecx);
	}

	CpuChecker::CpuChecker() :Error(false) {
	}

	void CpuChecker::check() {
		Error = false;

		int rgstr[4];
		memset(rgstr, 0x00000000, 4 * sizeof(int));

		m_cpuid(rgstr, 0x00000000);

		if (rgstr[0] < 1) {
			Error = true;
			return;
		}

		char vendor[17];
		memset(vendor, '\0', 14);

		memcpy(vendor, rgstr + 1, sizeof(int));
		memcpy(vendor + sizeof(int), rgstr + 3, sizeof(int));
		memcpy(vendor + 2 * sizeof(int), rgstr + 2, sizeof(int));

		this->cpuVendor = std::string(vendor);

		m_cpuid(rgstr, 0x00000001);
		std::bitset<32> bitInfo(rgstr[3]);
		MMXSupport = bitInfo[23];
		SSESupport = bitInfo[25];
		SSE2Support = bitInfo[26];

		bitInfo = std::bitset<32>(rgstr[2]);
		SSE3Support = bitInfo[0];
		SSSE3Support = bitInfo[9];
		SSE4_1Support = bitInfo[19];
		SSE4_2Support = bitInfo[20];
		AVXSupport = bitInfo[16];
		rgstr[2] = 0;
		//When eax = 0x07h, the output depend on ecx
		m_cpuid(rgstr, 0x00000007, 0x00000000);
		bitInfo = std::bitset<32>(rgstr[1]);
		AVX2Support = bitInfo[5];
		AVX512Support = bitInfo[16];

	}

	void CpuChecker::show() {
		if (Error) {
			std::cout << "Error occurred when scanning cpu." << std::endl;
			std::terminate();
		}

		std::cout << "Your CPU Vendor is " << cpuVendor << ".\n";
		setHinter("MMX", MMXSupport);
		if (MMXSupport) {
			std::cout << "***Safe to use MMX***"
				<< "\n";
		}
		else {
			return;
		}
		setHinter("SSE", SSESupport);
		setHinter("SSE2", SSE2Support);
		setHinter("SSE3", SSE3Support);
		setHinter("SSSE3", SSSE3Support);
		if (SSSE3Support) {
			std::cout << "***Safe to use SSE3***"
				<< "\n";
		}
		else {
			return;
		}
		setHinter("SSE4.1", SSE4_1Support);
		setHinter("SSE4.2", SSE4_2Support);
		if (SSE4_2Support) {
			std::cout << "***Safe to use SSE4***"
				<< "\n";
		}
		else {
			return;
		}
		setHinter("AVX", AVXSupport);
		setHinter("AVX2", AVX2Support);
		if (AVX2Support) {
			std::cout << "***Safe to use AVX2***"
				<< "\n";
		}
		else {
			return;
		}
		setHinter("AVX512", AVX512Support);
		if (AVX512Support) {
			std::cout << "***Safe to use AVX512 [AVX512F]***"
				<< "\n";
		}
		else {
			return;
		}
	}

	void CpuChecker::setHinter(const char* set, bool isSupported) {
		if (isSupported) {
			std::cout << set << " is Supported.\n";
		}
	}
}