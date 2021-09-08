CFLAGS = -Wall -Werror -pedantic -std=gnu99

power: power.o test-power.o
	gcc -o power power.o test-power.o
power.o: power.c
	gcc $(CFLAGS) -c power.c
test-power.o: test-power.c
	gcc $(CFLAGS) -c test-power.c

.PHONY: clean
clean:
	rm -f *~ *.o hello
