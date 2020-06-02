all:q1.out

q1.out: q1.o
	gcc -Wall -o q1.out q1.o

q1.o: q1.c q1.h
	gcc -Wall -c q1.c

.PHONY: clean all

clean:
	rm -f *.o *.out *.so