#include "../base/cpu_check.hpp"

int main() {
  fm::CpuChecker checker;
  checker.check();
  if(checker.Error){
    return -1;
  }
  if (checker.SSE4_2Support) {
    return 0;
  }
  return -1;
}