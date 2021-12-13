CFLAGS=-std=gnu++98 -pedantic -Wall -Werror -ggdb3
all: cyoa-step1 cyoa-step2 cyoa-step3 cyoa-step4
cyoa-step1: cyoa-step1.cpp s1-page.hpp
	g++ -o cyoa-step1 $(CFLAGS) cyoa-step1.cpp
cyoa-step2: cyoa-step2.cpp s2-page.hpp
	g++ -o cyoa-step2 $(CFLAGS) cyoa-step2.cpp
cyoa-step3: cyoa-step3.cpp s3-page.hpp
	g++ -o cyoa-step3 $(CFLAGS) cyoa-step3.cpp
cyoa-step4: cyoa-step4.cpp s4-page.hpp
	g++ -o cyoa-step4 $(CFLAGS) cyoa-step4.cpp
.PHONY: clean
clean:
	rm -f *~ cyoa-step1 cyoa-step2 cyoa-step3 cyoa-step4
