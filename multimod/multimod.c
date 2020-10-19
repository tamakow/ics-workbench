#include <stdint.h>

uint64_t multimod(uint64_t a, uint64_t b, uint64_t m) {
  int i,j;
  uint64_t ans = 0;
  for(i=0;i<a;++i){
    ans+=b;
  }
  ans = ans & (m-1);
  return ans;
}
