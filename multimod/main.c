#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>

static inline uint64_t my_mod(uint64_t a,uint64_t m){
  while(a>=m) a-=m;
  return a;
}

static inline uint64_t addmod(uint64_t a,uint64_t b,uint64_t m){
  return my_mod(a + b , m);
}

uint64_t multimod(uint64_t a, uint64_t b, uint64_t m) {
  static uint64_t l[64]={};
  int p=0,i,j;
  while(a>1){
    if(my_mod(a,2)==0) l[p++]=0;
    else l[p++]=1;
    a>>=1;
  }
  l[p]=1;
  uint64_t ans = 0;
  for(i=0;i<=p;++i){
    if(l[i]==0) continue;
    for(j=0;j<b;++j){
      ans=addmod(ans,1<<i,m);
    }
  }
  return ans;
}


void test(uint64_t a, uint64_t b, uint64_t m) {
  #define U64 "%" PRIu64
  printf(U64 " * " U64 " mod " U64 " = " U64 "\n", a, b, m, multimod(a, b, m));
}

int main() {
  test(123, 456, 789);
  test(123, 456, -1ULL);
  test(-2ULL, -2ULL, -1ULL); // should be 1
}
