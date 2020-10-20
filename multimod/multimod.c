#include <stdint.h>
#include <stdio.h>
uint64_t data[70]={0};
uint64_t temp = 0;
int x=0;
static inline uint64_t my_mod(uint64_t a,uint64_t m){
  if(a>=m){
    int i;
    for(i=x;i>=0;--i){
      while(data[i]<=a) a-=data[i];
    }
  }
  return a; 
}

static inline void init(uint64_t m){
  int i;
  data[0]=m;
  for(i=1;i<64;++i){
    if((m<<i) < data[i-1]){x=i-1;break;}
    data[i]=(m<<i);    
  }
}

static inline uint64_t addmod(uint64_t a,uint64_t b,uint64_t m){
  if(a+b>=a&&a+b>=b) return my_mod(a+b,m);
  else return addmod(my_mod(a+b,m),temp,m);
}

uint64_t multimod(uint64_t a, uint64_t b, uint64_t m) {
  uint64_t ans = 0;
  init(m);
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
