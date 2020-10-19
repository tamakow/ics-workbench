#include <stdint.h>

uint64_t multimod(uint64_t a, uint64_t b, uint64_t m) {
  static uint64_t l[64]={};
  int p=0,i,j;
  while(a>1){
    if(a<<63) l[p++]=0;
    else l[p++]=1;
    a>>=1;
  }
  l[p]=1;
  uint64_t ans = 0;
  for(i=0;i<=p;++i){
    if(l[i]==0) continue;
    for(j=0;j<b;++j){
      ans=ans+(1<<i);
    }
  }
  printf("%d\n",ans);
  ans = ans & (m-1);
  return ans;
}
