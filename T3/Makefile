all: arvorePV.o main.c
	gcc -Wall arvorePV.o main.c -o all
arvorePV.o: arvorePV.h arvorePV.c
	gcc -Wall -c arvorePV.c
run: all
	./all
clean:
	rm -f *.o all
