#include "common.h"
#include <inttypes.h>

void mem_read(uintptr_t block_num, uint8_t *buf);
void mem_write(uintptr_t block_num, const uint8_t *buf);

static uint64_t cycle_cnt = 0;
static uint64_t hit_cnt = 0;
static uint64_t miss_cnt = 0;

static uint32_t total_width; // cache的数据大小宽度
static uint32_t associate_width; // cache关联度的宽度，即一个cache组里有2^associate_width个cache行
static uint32_t total_line_number; //cache总共的行数
static uint32_t group_number_width; // cache组数量的宽度，及有2^group_width个cache组
static uint32_t tag_width; // 标签的宽度
static cache_line *cache;


void cycle_increase(int n) { cycle_cnt += n; }

// TODO: implement the following functions
// 使用组相联映射
uint32_t cache_read(uintptr_t addr) {
  //得到块内地址
  uint32_t block_addr = addr & mask_with_len(BLOCK_WIDTH) ;
  //得到cache组号
  uint32_t group_idx = (addr >> BLOCK_WIDTH) & mask_with_len(group_number_width);
  //得到标记
  uint32_t tag = (addr >> (BLOCK_WIDTH + group_number_width)) & mask_with_len(tag_width);
  //得到对应组的行号范围
  uint32_t line_start = group_idx * exp2(associate_width);
  uint32_t line_end = line_start + exp2(associate_width);
  for(int i = line_start; i< line_end; ++i){
    cycle_increase(1);
    if(cache[i].valid_bit&&(cache[i].tag == tag)){
      hit_cnt++;
      uint32_t* ret = (uint32_t*)(cache[i].data + block_addr);
      printf("1\n");
      return *ret;
    }
  }
  //miss
  miss_cnt++;
  //得到在主存的块数
  uint32_t block_idx = (addr >> BLOCK_WIDTH) & mask_with_len(25-BLOCK_WIDTH);
  //寻找是否存在没有使用的cache行
  for(int i = line_start; i< line_end; ++i){
    cycle_increase(1);
    if(!cache[i].valid_bit){ 
      mem_read(block_idx, cache[i].data);
      cache[i].valid_bit = true;
      cache[i].tag = tag;
      uint32_t* ret = (uint32_t*)(cache[i].data + block_addr);
      printf("2\n");
      return *ret;
    }
  }
  //替换算法
  uint32_t random_line = line_start + rand() % exp2(associate_width);
  //不确定写对了没
  uint32_t random_line_block_idx = (cache[random_line].tag << group_number_width) + group_idx;
  if(cache[random_line].dirty_bit){ //cache内容被修改过，需要写回主存
    mem_write(random_line_block_idx, cache[random_line].data);
  }
  mem_read(block_idx,cache[random_line].data);
  cache[random_line].valid_bit = true;
  cache[random_line].tag =tag;
  uint32_t* ret = (uint32_t*)(cache[random_line].data + block_addr);
  printf("3\n");
  return *ret;
}

void cache_write(uintptr_t addr, uint32_t data, uint32_t wmask) {
  //得到块内地址
  uint32_t block_addr = addr & mask_with_len(BLOCK_WIDTH);
  //得到cache组号
  uint32_t group_idx = (addr >> BLOCK_WIDTH) & mask_with_len(group_number_width);
  //得到标记
  uint32_t tag = (addr >> (BLOCK_WIDTH + group_number_width)) & mask_with_len(tag_width);
  //得到对应组的行号范围
  uint32_t line_start = group_idx * exp2(associate_width);
  uint32_t line_end = line_start + exp2(associate_width);
  for(int i = line_start; i< line_end; ++i){
    cycle_increase(1);
    if(cache[i].valid_bit&&(cache[i].tag == tag)){
      hit_cnt++;
      cache[i].dirty_bit = true;
      uint32_t* ret = (uint32_t*)(cache[i].data + block_addr);
      *ret = (*ret & ~wmask) | (data & wmask); 
      return;
    }
  }
  //miss
  miss_cnt++;
  //得到在主存的块数
  uint32_t block_idx = (addr >> BLOCK_WIDTH) & mask_with_len(25-BLOCK_WIDTH);
  //寻找是否存在没有使用的cache行
  for(int i = line_start; i< line_end; ++i){
    cycle_increase(1);
    if(!cache[i].valid_bit){ 
      mem_read(block_idx, cache[i].data);
      cache[i].valid_bit = true;
      cache[i].tag = tag;
      cache[i].dirty_bit = true;
      uint32_t* ret = (uint32_t*)(cache[i].data + block_addr);
      *ret = (*ret & ~wmask) | (data & wmask);  
      return;
    }
  }
  //替换算法
  uint32_t random_line = line_start + rand() % exp2(associate_width);
  //不确定写对了没
  uint32_t random_line_block_idx = (cache[random_line].tag << group_number_width) + group_idx;
  if(cache[random_line].dirty_bit){ //cache内容被修改过，需要写回主存
    mem_write(random_line_block_idx, cache[random_line].data);
  }
  mem_read(block_idx,cache[random_line].data);
  cache[random_line].valid_bit = true;
  cache[random_line].tag =tag;
  cache[random_line].dirty_bit = true;
  uint32_t* ret = (uint32_t*)(cache[random_line].data + block_addr);
  *ret = (*ret & ~wmask) | (data & wmask);  
  return;
}

void init_cache(int total_size_width, int associativity_width) {
  total_width = total_size_width;
  associate_width = associativity_width;
  //创建cache
  total_line_number = exp2(total_size_width - BLOCK_WIDTH);
  cache = (cache_line*)malloc(sizeof(cache_line)*total_line_number);
  group_number_width = total_size_width - BLOCK_WIDTH - associativity_width;
  tag_width = 25 - BLOCK_WIDTH - group_number_width;
  for(int i = 0; i < total_line_number; ++i){
    cache[i].valid_bit = false;
    cache[i].dirty_bit = false;
  }
}

void display_statistic(void) {
  printf("cycle number is %ld\n",cycle_cnt);
  printf("hit number is %ld\n",hit_cnt);
  printf("miss number is %ld\n",miss_cnt);
  return;

}
