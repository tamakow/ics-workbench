#include <stdint.h>
#include <stdio.h>
uint64_t data[70]={};

static inline uint64_t my_mod(uint64_t a,uint64_t m){
  if(a>=m){
    int i=0,p=0;
    for(i=0;data[i]!=0;++i){
      if(data[i]<=a) continue;
      p=i-1;
      break;
    }
    for(i=p;i>=0;--i){
      while(a>=data[i]) a-=data[i];
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

static inline uint64_t addmod(uint64_t a,uint64_t b,uint64_t m){
  if(a+b>=a&&a+b>=b) return my_mod(a+b,m);
  else return addmod(my_mod(a+b,m),my_mod(my_mod(-1ULL,m)+1,m),m);
}

uint64_t multimod(uint64_t a, uint64_t b, uint64_t m) {
  uint64_t ans = 0;
  //init(m);
  while(a){
    if(a&1){
      ans+=b;
      //ans=addmod(ans,b,m);
    }
    b+=b;
    //b=addmod(b,b,m);
    a>>=1;
  }
  ans=addmod(ans,0,m);
  return ans;
}
