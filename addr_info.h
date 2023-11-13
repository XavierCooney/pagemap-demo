#ifndef ADDR_INFO_H
#define ADDR_INFO_H


#define PAGE_SHIFT 12
#define PAGE_SIZE  (1 << PAGE_SHIFT) // 4096

#define PRINT_ADDR_INFO(ptr) print_page_table_info(#ptr, (ptr));

// Various masks and constants,
// from linux/fdf0eaf1/fs/proc/task_mmu.c:1344
#define PAGEMAP_PRESENT (1ull << 63)
#define PAGEMAP_SWAP (1ull << 62)
#define PAGEMAP_FILE (1ull << 61)
#define PAGEMAP_PFRAME_BITS 55
#define PAGEMAP_PFRAME_MASK ((1ull << PAGEMAP_PFRAME_BITS) - 1)


void print_page_table_info(const char *spelling, void *ptr);
void dump_maps(void);


#endif
