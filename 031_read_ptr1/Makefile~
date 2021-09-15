CFLAGS = -Wall -Werror -pedantic -std=gnu99 -ggdb3

hello: hello.o name.o
	gcc -o hello $(CFLAGS) hello.o name.o
hello.o: hello.c
	gcc $(CFLAGS) -c hello.c
name.o: name.c name.h
	gcc $(CFLAGS) -c name.c

.PHONY: clean
clean:
	rm -f *~ *.o hello
