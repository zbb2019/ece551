CFLAGS = -Wall -Werror -pedantic -std=gnu99 -ggdb3

test: test.o
	gcc -o test $(CFLAGS) test.o
test.o: test.c
	gcc $(CFLAGS) -c test.c

.PHONY: clean
clean:
	rm -f *~ *.o test
