#ifndef  CPU_CHECK_HPP__
#define  CPU_CHECK_HPP__
#include <string>

namespace fm {

	//Ref:https://www.felixcloutier.com/x86/cpuid

	class CpuChecker {
	public:
		CpuChecker();
		void check();
		void show();
		bool MMXSupport;

		bool SSESupport;
		bool SSE2Support;
		bool SSE3Support;

		bool SSSE3Support;
		bool SSE4_1Support;
		bool SSE4_2Support;

		bool AVXSupport;
		bool AVX2Support;

		bool AVX512Support;
		bool Error;
	private:
		void m_cpuid(int[4], int, int);
		void setHinter(const char* set, bool isSupported);
		std::string cpuVendor;



	};

}

#endif

