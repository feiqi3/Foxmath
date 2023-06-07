#ifndef  CPU_CHECK_HPP__
#define  CPU_CHECK_HPP__
#include <string>

class CpuChecker{
    public:
    void check();
    void show();
    private:
    void m_cpuid(int[4],int);
    void setHinter(const char* set,bool isSupported);
    std::string cpuVendor;

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
};

#endif

