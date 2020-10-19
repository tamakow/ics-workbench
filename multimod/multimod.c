#include <stdint.h>

uint64_t data[65]={};
int x=0;
static inline uint64_t my_mod(uint64_t a,uint64_t m){
  while(a>=m){
    int i=0;
    for(i=0;i<=x;++i){
      if(data[i]<a) continue;
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
  for(i=1;;i<<=1){
    if((m<<i) < (m<<(i-1))) break;
    data[++x]=m<<i;
  }
}

uint64_t multimod(uint64_t a, uint64_t b, uint64_t m) {
  uint64_t l[65]={};
  int p=0,i,j;
  while(a>1){
    if(a&1) l[p++]=1;
    else l[p++]=0;
    a>>=1;
  }
  l[p]=1;
  uint64_t ans = 0;
  for(i=0;i<=p;++i){
    if(l[i]==0) continue;
    ans=ans+(b<<i);
  }
  init(m);
  ans = ans & (m-1);
  return ans;
}
