#include <cstdint>

#include "fmt/core.h"
#include "jit.h"

int main(int argc, char *argv[]) {
  if (argc != 3) {
    fmt::print("Usage: {} int, int\n", argv[0]);
    return 1;
  }

  int x = std::atoi(argv[1]);
  int y = std::atoi(argv[2]);

  // This machine code is valid on x86 linux.
  std::vector<uint8_t> machine_code = {
      0x8d, 0x04, 0x37,  // lea    eax,[edi+esi*1]
      0xc3               // ret
  };

  JitRun jit(machine_code);

  // Cast the address of our generated code to a function pointer and call the
  // function
  // int (*func)(int x, int y);
  // func = (int (*)(int, int))jit.GetCode();

  int (*func)(int, int) = jit.GetCode<int (*)(int, int)>();

  fmt::print("{} + {} = {}\n", x, y, func(x, y));

  return 0;
}
