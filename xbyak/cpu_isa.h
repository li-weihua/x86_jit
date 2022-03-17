#pragma once

#include <unordered_map>

#include "xbyak/xbyak_util.h"

inline const Xbyak::util::Cpu& cpu() {
  // one instance
  const static Xbyak::util::Cpu g_cpu;
  return g_cpu;
}

enum Isa { AVX, AVX2, AVX512_CORE, AVX512_CORE_VNNI, AVX512_CORE_BF16 };

const std::unordered_map<Isa, const char*> IsaMap = {
    {AVX, "AVX"},
    {AVX2, "AVX2"},
    {AVX512_CORE, "AVX512_CORE"},
    {AVX512_CORE_VNNI, "AVX512_CORE_VNNI"},
    {AVX512_CORE_BF16, "AVX512_CORE_BF16"},
};

static inline bool cpu_has_isa(Isa isa) {
  using Xbyak::util::Cpu;

  switch (isa) {
    case AVX:
      return cpu().has(Cpu::tAVX);
    case AVX2:
      return cpu().has(Cpu::tAVX2);
    case AVX512_CORE:
      return cpu().has(Cpu::tAVX512F) && cpu().has(Cpu::tAVX512BW) && cpu().has(Cpu::tAVX512VL) &&
             cpu().has(Cpu::tAVX512DQ);
    case AVX512_CORE_VNNI:
      return cpu_has_isa(AVX512_CORE) && cpu().has(Cpu::tAVX512_VNNI);
    case AVX512_CORE_BF16:
      return cpu_has_isa(AVX512_CORE_VNNI) && cpu().has(Cpu::tAVX512_BF16);
  }

  return false;
}
