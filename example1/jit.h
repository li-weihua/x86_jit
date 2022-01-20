#pragma once

#include <cstdint>
#include <vector>

class JitRun {
 public:
  JitRun(const std::vector<uint8_t>& machine_code);
  ~JitRun();

  void* GetCode() const { return executable_memory_; }

  template <typename F>
  const F GetCode() const {
    return reinterpret_cast<F>(executable_memory_);
  }

 private:
  // Return a multiple of the machine page size that can store the generated
  // machine code
  size_t GetMemorySize(size_t machine_code_size);

 private:
  void* executable_memory_;
  size_t executable_memory_size_;
};
