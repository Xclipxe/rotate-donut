all: donut

donut: main.o
	gcc -g main.o -o donut

main.o: main.c
	gcc -g -Wall -c main.c

clean:
	rm -f donut *.o
