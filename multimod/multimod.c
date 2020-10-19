#include <stdint.h>

uint64_t data[70]={};

static inline uint64_t my_mod(uint64_t a,uint64_t m){
  while(a>=m){
    int i=0;
    for(i=0;data[i]!=0;++i){
      if(data[i]<=a) continue;
      if(i!=0)
      a-=data[i-1];
      break;
    }
  }
  return a; 
}

static inline void init(uint64_t m){
  int i;
  data[0]=m;
  for(i=1;;++i){
    if((m<<i) < (m<<(i-1))) break;
    data[i]=(m<<i);
  }
}

static inline addmod(uint64_t a,uint64_t b,uint64_t m){
  if(a+b>a&&a+b>b) return my_mod(a+b,m);
  else return addmod(my_mod(a+b+1,m),my_mod(-1ULL,m),m);
}

uint64_t multimod(uint64_t a, uint64_t b, uint64_t m) {
  uint64_t ans = 0;
  int p=0,i,j;
  init(m);
  while(a>1){
    if(a&1)
      for(i=0;i<b;++i)
      ans=addmod(ans,1<<p,m);
    p++;
    a>>=1;
  }
  for(i=0;i<b;++i)
  ans=addmod(ans,1<<p,m);
  return ans;
}
