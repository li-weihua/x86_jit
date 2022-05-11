#include "cpu_isa.h"
#include "fmt/core.h"

int main() {
  fmt::print("current cpu supported features:\n");

  for (auto x : IsaMap) {
    if (cpu_has_isa(x.first)) fmt::print("{}\n", x.second);
  }

  return 0;
}
