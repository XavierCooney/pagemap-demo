CC = clang
CFLAGS = -Wall -Werror -Wextra
INCLUDES = addr_info.h

PROGRAMS = print_addr fork hack_my_func

.PHONY: all
all: addr_info.o $(PROGRAMS)
	@:

$(PROGRAMS): %: %.c $(INCLUDES) addr_info.o
	$(CC) $(CFLAGS) -o $@ addr_info.o $<

addr_info.o: addr_info.c $(INCLUDES)
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	rm -f *.o $(PROGRAMS)
