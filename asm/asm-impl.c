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
  asm("push %%rbp;"
      "mov %%rsp, %%rbp;"
      "mov %1, -24(%%rbp);"//mov %rdi -24(%rbp) rdi寄存器中存储x 
      "movl $0, -4(%%rbp);"
      "jmp L2;"
      "L4: mov -4(%%rbp), %%eax;"//eax 存储 i
      "mov -24(%%rbp), %%rdx;" //rdx 存储 x
      "mov %%eax, %%ecx;"//ecx存储i
      "shr %%cl, %%rdx;" //逻辑右移
      "mov %%rdx, %%rax;" 
      "and $1, %%eax;"
      "test %%rax, %%rax;"
      "je L3;"
      "addl $1, %0;"
      "L3: addl $1, -4(%%rbp);"
      "L2: cmpl $63, -4(%%rbp);"
      "jle L4;"
      "pop %%rbp;"
      : "+r"(s)
      : "r"(x)
      : "%rax", "%eax", "%ecx","%rdx","%cl"

  );
  return s;
}

void *asm_memcpy(void *dest, const void *src, size_t n) {
  //return memcpy(dest, src, n);
  /*
   int d0, d1, d2;
   asm volatile("rep ; movsl\n\t"
                 "movl %4,%%ecx\n\t"
                 //"andl $3,%%ecx;"
                 //"jz 1f;"
                 "rep ; movsb;\n\t"
                 //"1:"
                 : "=&c" (d0), "=&D" (d1), "=&S" (d2)
                 : "0" (n >> 4), "g" (n & 3), "1" (dest), "2" (src)
                 : "memory"
                );
    */            
  asm(//"push %%rbp;"
      //"mov %%rsp, %%rbp;"
      "mov %0, %%rdi;"//dest
      "mov %1, %%rsi;"//src
      //"mov %1, ;"//src
      //"mov %2, ;"//n
      //"mov %0, %%rax;" // rax=dest
      "jmp mem1;"
      "mem2: sub $1, %2;"
      //"mov %%rsi, %%rdx;"
      //"mov %%dl, %%rdi;"
      //"addq $1, %%rdi;"
      //"addq $1, %%rsi;"
      "mem1: mov %2, %%rax;"
      "test %%rax, %%rax;"
      "jne mem2;"
      //"pop %%rbp;"
      :
      : "r"(dest), "r"(src), "r"(n)
      : "%rax","%rdx","%rdi","%rsi","%dl"
  );
  return dest;
}

int asm_setjmp(asm_jmp_buf env) {
  return setjmp(env);
}

void asm_longjmp(asm_jmp_buf env, int val) {
  longjmp(env, val);
}
;