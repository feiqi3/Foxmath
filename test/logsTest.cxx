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
    std::function<double(double)> stdlog2 = [](double in){return std::log2(in);};
    std::function<double(double)> stdlog10 = [](double in){return std::log10(in);};
    auto premuter = preMute(500000, std::numeric_limits<double>::denorm_min(), 10000000);
    precisionTest(stdlog, fm::Log<double>, "fm::Log", 0.0000001, 1000., 0.0001);
    Timebenchmark(stdlog, "std::log",premuter );
    Timebenchmark(fm::Log<double>, "fm::Log",premuter );

  std::cout << "<========================>\n\n";
    precisionTest(stdlog, fm::Log<double>, "fm::Log2", 0.0000001, 1000., 0.0001);
    Timebenchmark(stdlog2, "std::log2",premuter );
    Timebenchmark(fm::Log2<double>, "fm::Log2",premuter );
  std::cout << "<========================>\n\n";
    precisionTest(stdlog, fm::Log<double>, "fm::Log10", 0.0000001, 1000., 0.0001);
    Timebenchmark(stdlog2, "std::log10",premuter );
    Timebenchmark(fm::Log2<double>, "fm::Log10",premuter );

}