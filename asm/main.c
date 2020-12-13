#include "asm.h"
#include <assert.h>
#include <stdio.h>

int main() {
  asm_jmp_buf buf;
  int r = asm_setjmp(buf);
  if (r == 0) {
    assert(asm_add(1234, 5678) == 6912);
    assert(asm_popcnt(0x0123456789abcdefULL) == 32);
    assert(asm_popcnt(0xffffffffffffffffULL) == 64);
    assert(asm_popcnt(0xff) == 8);
    // TODO: add more tests here.
    asm_longjmp(buf, 1);
  } else {
    assert(r == 123);
    printf("PASSED.\n");
  }
}
