// Xavier Cooney <x.cooney@unsw.edu.au> 23T2

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "addr_info.h"


char bss_padding[PAGE_SIZE];

void print_page_table_info(const char *spelling, void *ptr) {
    uint64_t virtual_addr = (uint64_t) ptr;

    uint64_t virtual_page_num = virtual_addr >> PAGE_SHIFT;
    uint64_t offset = virtual_addr & (PAGE_SIZE - 1);

    FILE *pagemap_file = fopen("/proc/self/pagemap", "r");
    if (pagemap_file == NULL) {
        perror("pagemap");
        exit(1);
    }

    if (fseek(pagemap_file, virtual_page_num * 8, SEEK_SET) != 0) {
        perror("fseek(pagemap)");
        exit(1);
    }

    uint64_t pagemap_entry;
    if (fread(&pagemap_entry, 8, 1, pagemap_file) != 1) {
        perror("read(pagemap)");
        exit(1);
    }

    fclose(pagemap_file);

    printf("\n%s is 0x%012" PRIx64 " (virtual addr), which has a\n", spelling, virtual_addr);
    printf("    virtual page num of 0x%09" PRIx64 " and offset of 0x%03" PRIx64 "\n", virtual_page_num, offset);

    if (pagemap_entry == 0) {
        printf(" (no entry in pagemap!)\n\n");
        return;
    }

    bool is_present = PAGEMAP_PRESENT & pagemap_entry;
    bool is_swapped = PAGEMAP_SWAP & pagemap_entry;
    uint64_t frame_num = PAGEMAP_PFRAME_MASK & pagemap_entry;
    uint64_t physical_addr = (frame_num << PAGE_SHIFT) | offset;

    if (is_present) {
        printf("VPN mapped by page table to physical frame num 0x%012" PRIx64 "\n", frame_num);
        printf("    so the physical address is 0x%012" PRIx64 "\n", physical_addr);
    } else {
        printf("Page not present in page table!\n");
    }

    // printf("flags: is_present = %d, is_swapped = %d\n", is_present, is_swapped);
    (void) is_present; (void) is_swapped;

    printf("\n");
}

void dump_maps(void) {
    FILE *maps_file = fopen("/proc/self/maps", "r");
    if (maps_file == NULL) {
        perror("maps");
        exit(1);
    }

    int byte;
    while ((byte = fgetc(maps_file)) != EOF) {
        putchar(byte);
    }

    fclose(maps_file);
}

char stuff[PAGE_SIZE];
