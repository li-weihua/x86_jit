#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "xbyak/xbyak.h"

class Sample : public Xbyak::CodeGenerator {
 public:
  Sample() {
    static constexpr float one = 1.0f;
    mov(rax, float2int(one));
    vmovq(xmm1, rax);
    vbroadcastss(xmm0, xmm1);
    haddps(xmm0, xmm0);
    haddps(xmm0, xmm0);
    ret();
  }
  float (*get() const)() { return getCode<float (*)()>(); }

 private:
  static inline int float2int(float x) {
    int t;
    memcpy(&t, &x, sizeof(int));
    return t;
  }
};

int main() {
  Sample s;
  auto *func = s.get();

  printf("%f\n", func());

  return 0;
}
