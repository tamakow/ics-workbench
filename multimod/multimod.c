#include <stdint.h>
#include <stdio.h>
uint64_t data[70]={0};
uint64_t temp = 0;
int x=0;

static inline uint64_t my_mod(uint64_t a,uint64_t m){
  uint64_t i=0;
  while(a>=m){
    if(a>=m<<i){
      a-=m<<i;
      ++i;
    }
    else --i;
  }
  return a;

}

static inline uint64_t addmod(uint64_t a,uint64_t b,uint64_t m){
  if(a+b>=a&&a+b>=b) return my_mod(a+b,m);
  else return addmod(my_mod(a+b,m),temp,m);
}

uint64_t multimod(uint64_t a, uint64_t b, uint64_t m) {
  uint64_t ans = 0;
  temp = my_mod(my_mod(-1ULL,m)+1,m);
  while(a){
    if(a&1){
      ans=addmod(ans,b,m);
    }
    b=addmod(b,b,m);
    a>>=1;
  }
  return ans;
}
