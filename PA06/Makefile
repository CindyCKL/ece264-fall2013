
GCC = gcc
CFLAGS = -g -Wall -Wshadow

all: pa06

clean:
	rm -rf *.o pa06

pa06: answer06.o pa06.o
	$(GCC) $(CFLAGS) answer06.o pa06.o -o pa06

pa06.o: pa06.c pa06.h
	$(GCC) $(CFLAGS) -c pa06.c 

answer06.o: answer06.c pa06.h
	$(GCC) $(CFLAGS) -c answer06.c

test : test1 test2 test3 test4 test5 test6

test1 : pa06
	./pa06 images/01-unnormalized-smile.ee264  outputs/output1
	diff outputs/output1 expected/01-smile.ppm
	valgrind --leak-check-full --verbose --log-file=valgrindlog1 ./pa06

