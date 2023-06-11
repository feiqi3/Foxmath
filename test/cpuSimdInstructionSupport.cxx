#include "../base/cpu_check.hpp"

//Use 'ctest --verbose' to see outcome 
int main() {
  fm::CpuChecker checker;
  checker.check();
  if(checker.Error){
    return -1;
  }
  checker.show();
}