GCC = gcc
CFLAGS = -g -Wall -Wshadow
all : pa07

clean :
	rm -rf *.o pa07

pa07 : answer07.o pa07.o
	$(GCC) $(CFLAGS) answer07.o pa07.o -o pa07

pa07.o : pa07.c pa07.h
	$(GCC) $(CFLAGS) -c pa07.c

answer07.o : answer07.c pa07.h
	$(GCC) $(CFLAGS) -c answer07.c 

test : test0 test1 test2 test3 test4 test5 test6 test7 test8 test9

test0 : pa07
	./pa07 inputs/input0_A inputs/input0_B > outputs/output0
	diff -q outputs/output0 expected/expected0
	valgrind --leak-check=full --verbose --log-file==valgrindlog1 ./pa07 inputs/input0_A inputs/input0_B

test1 : pa07
	./pa07 inputs/input1_A inputs/input1_B > outputs/output1
	diff -q outputs/output1 expected/expected1
	valgrind --leak-check=full --verbose --log-file==valgrindlog2 ./pa07 inputs/input1_A inputs/input1_B

test2 : pa07
	./pa07 inputs/input2_A inputs/input2_B > outputs/output2
	diff -q outputs/output2 expected/expected2
	valgrind --leak-check=full --verbose --log-file==valgrindlog2 ./pa07 inputs/input2_A inputs/input2_B

test3 : pa07
	./pa07 inputs/input3_A inputs/input3_B > outputs/output3
	diff -q outputs/output3 expected/expected3
	valgrind --leak-check=full --verbose --log-file==valgrindlog3 ./pa07 inputs/input3_A inputs/input3_B

test4 : pa07
	./pa07 inputs/input4_A inputs/input4_B > outputs/output4
	diff -q outputs/output4 expected/expected4
	valgrind --leak-check=full --verbose --log-file==valgrindlog4 ./pa07 inputs/input4_A inputs/input4_B

test5 : pa07
	./pa07 inputs/input5_A inputs/input5_B > outputs/output5
	diff -q outputs/output5 expected/expected5
	valgrind --leak-check=full --verbose --log-file==valgrindlog5 ./pa07 inputs/input5_A inputs/input5_B

test6 : pa07
	./pa07 inputs/input6_A inputs/input6_B > outputs/output6
	diff -q outputs/output6 expected/expected6
	valgrind --leak-check=full --verbose --log-file==valgrindlog6 ./pa07 inputs/input6_A inputs/input6_B

test7 : pa07
	./pa07 inputs/input7_A inputs/input7_B > outputs/output7
	diff -q outputs/output7 expected/expected7
	valgrind --leak-check=full --verbose --log-file==valgrindlog7 ./pa07 inputs/input7_A inputs/input7_B

test8 : pa07
	./pa07 inputs/input8_A inputs/input8_B > outputs/output8
	diff -q outputs/output8 expected/expected8
	valgrind --leak-check=full --verbose --log-file==valgrindlog8 ./pa07 inputs/input8_A inputs/input8_B

test9 : pa07
	./pa07 inputs/input9_A inputs/input9_B > outputs/output9
	diff -q outputs/output9 expected/expected9
	valgrind --leak-check=full --verbose --log-file==valgrindlog9 ./pa07 inputs/input9_A inputs/input9_B
