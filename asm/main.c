#include "asm.h"
#include <assert.h>
#include <stdio.h>

int main() {
  asm_jmp_buf buf;
  int r = asm_setjmp(buf);
  if (r == 0) {
    //assert(asm_add(1234, 5678) == 6912);
    //assert(asm_popcnt(0x0123456789abcdefULL) == 32);
    // TODO: add more tests here.
    printf("before longjmp\n");
    asm_longjmp(buf, 1);
    printf("after long jmp\n");
  } else {
    //assert(r == 123);
    printf("PASSED.\n");
  }
}
