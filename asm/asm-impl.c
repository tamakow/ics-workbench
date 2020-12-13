#include "asm.h"
#include <string.h>

int64_t asm_add(int64_t a, int64_t b) {//返回有符号64位加法
  asm("add %1, %0;"
      : "+r"(a)//%0
      : "r"(b)//%1
  );
  return a;
}

int asm_popcnt(uint64_t x) {//无符号64位整数x二进制表示中1的数量
  int s = 0;
  /*
  for (int i = 0; i < 64; i++) {
    if ((x >> i) & 1) s++;
  }
  */
 //先使用 gcc -S 将c代码转换至汇编代码再写内联汇编
  asm("mov %1, -24(%%rbp);"//mov %rdi -24(%rbp) rdi寄存器中存储x 
      "movl $0, -4(%%rbp);"
      "jmp temp2;"
      "temp4: mov -4(%%rbp), %%eax;"//eax 存储 i
      "mov -24(%%rbp), %%rdx;" //rdx 存储 x
      "mov %%eax, %%ecx;"//ecx存储i
      "shr %%cl, %%rdx;" //逻辑右移
      "mov %%rdx, %%rax;" 
      "and $1, %%eax;"
      "test %%rax, %%rax;"
      "je temp3;"
      "addl $1, %0;"
      "temp3: addl $1, -4(%%rbp);"
      "temp2: cmpl $63, -4(%%rbp);"
      "jle temp4;"
      : "+r"(s)
      : "r"(x)
      : "%rax", "%eax", "%ecx","%rdx","%cl"
  );
  return s;
}

void *asm_memcpy(void *dest, const void *src, size_t n) {
  return memcpy(dest, src, n);
}

int asm_setjmp(asm_jmp_buf env) {
  return setjmp(env);
}

void asm_longjmp(asm_jmp_buf env, int val) {
  longjmp(env, val);
}
;