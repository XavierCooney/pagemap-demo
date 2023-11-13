#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdbool.h>
#include <unistd.h>

#include "addr_info.h"


int foo;

int main(void) {
    // int x;

    PRINT_ADDR_INFO(&foo);
    printf(" === setting foo = 7...\n");
    foo = 7;
    PRINT_ADDR_INFO(&foo);

    fflush(stdout);
    setbuf(stdout, NULL);

    int fork_ret = fork();

    if (fork_ret == -1) {
        perror("fork");
        return 1;
    } else if (fork_ret == 0) {
        // child
        printf(" === child's version of foo:\n");
        PRINT_ADDR_INFO(&foo);

        sleep(2);

        printf(" === child setting foo = 7\n");
        foo = 8;

        printf(" === child's version of foo:\n");
        PRINT_ADDR_INFO(&foo);
    } else {
        // parent
        sleep(1);
        printf(" === parent's version of foo:\n");
        PRINT_ADDR_INFO(&foo);

        printf(" === parent setting foo = 8\n");
        foo = 8;

        printf(" === parent's version of foo:\n");
        PRINT_ADDR_INFO(&foo);

        sleep(2);
    }
}
