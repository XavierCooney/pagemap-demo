// not finished yet...

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdbool.h>

#include <sys/mman.h>

#include "addr_info.h"

void my_func(void);


int main(void) {
    PRINT_ADDR_INFO(my_func);

    if (getchar() == 'y') {
        printf("running mprotect()...\n");

        uint64_t my_funcaddr = (uint64_t) my_func;
        my_funcaddr = 4096 * (my_funcaddr / 4096);
        if (mprotect((void *) my_funcaddr, 4096, PROT_READ | PROT_WRITE) != 0) {
            perror("mprotect");
        }
        printf("(un-)mprotected...");

        // *(uint64_t *) my_funcaddr = 0;

        // if (mprotect((void *) my_funcaddr, 4096, PROT_READ | PROT_EXEC) != 0) {
        //     perror("mprotect");
        // }
    } else {
        printf("not running mprotect()...\n");
    }

    while (getchar() != EOF); // wait

    PRINT_ADDR_INFO(my_func);
    my_func();
}


char my_func_data[4096];

void my_func(void) {
    printf("Hello there this is a totally innocent function!\n");
}
