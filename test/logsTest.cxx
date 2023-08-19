#include "./testHeader.hpp"
#include "3dOperation/constants.h"
#include "3dOperation/operation.h"
#include "test/testHeader.hpp"
#include <cmath>
#include <functional>
#include <ios>
#include <iostream>
#include <limits>



int main(){
    std::cout.precision(30);
    std::cout<<std::fixed;
    std::function<double(double)> stdlog = [](double in){return std::log(in);};
    auto premuter = preMute(500000, std::numeric_limits<double>::denorm_min(), 10000000);
    precisionTest(stdlog, fm::Log<double>, "fm::Log", 0.0000001, 1000., 0.0001);
    Timebenchmark(stdlog, "std::log",premuter );
    Timebenchmark(fm::Log<double>, "fm::log",premuter );
}