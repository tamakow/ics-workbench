#include "common.h"
#include <inttypes.h>

void mem_read(uintptr_t block_num, uint8_t *buf);
void mem_write(uintptr_t block_num, const uint8_t *buf);

static uint64_t cycle_cnt = 0;
static uint32_t total_width; // cache的数据大小宽度
static uint32_t associate_width; // cache关联度的宽度，即一个cache组里有2^associate_width个cache行
static uint32_t total_line_number; //cache总共的行数
static cache_line *cache;


void cycle_increase(int n) { cycle_cnt += n; }

// TODO: implement the following functions
// 使用组相联映射
uint32_t cache_read(uintptr_t addr) {
  //要得到标记，cache组号，块内地址，要先知道cache组号的宽度，标记的宽度这些东西

  return 0;
}

void cache_write(uintptr_t addr, uint32_t data, uint32_t wmask) {
}

void init_cache(int total_size_width, int associativity_width) {
  total_width = total_size_width;
  associate_width = associativity_width;
  //创建cache
  total_line_number = exp2(total_size_width - BLOCK_WIDTH);
  cache = (cache_line*)malloc(sizeof(cache_line)*total_line_number);
  
}

void display_statistic(void) {
}
