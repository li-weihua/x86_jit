#include "jit.h"

#include <sys/mman.h>
#include <unistd.h>  // sysconf
#include <cstdlib>
#include <cstring>  // memcpy

#include "fmt/core.h"

JitRun::JitRun(const std::vector<uint8_t> &machine_code) {
  executable_memory_size_ = GetMemorySize(machine_code.size());

  executable_memory_ = mmap(NULL, executable_memory_size_, PROT_READ | PROT_WRITE,
                            MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

  if (executable_memory_ == MAP_FAILED) {
    fmt::print("mmap can't allocate memory\n");
    std::abort();
  }

  std::memcpy(executable_memory_, machine_code.data(), machine_code.size());

  // add code executable and remove writable access
  if (mprotect(executable_memory_, executable_memory_size_, PROT_READ | PROT_EXEC) == -1) {
    fmt::print("set excutable failed!\n");
    std::abort();
  }
}

size_t JitRun::GetMemorySize(size_t machine_code_size) {
  size_t page_size = sysconf(_SC_PAGESIZE);  // Get the os page size, default 4K

  return (machine_code_size + page_size - 1) & page_size;
}

JitRun::~JitRun() {
  munmap(executable_memory_, executable_memory_size_);
  executable_memory_ = nullptr;
}
