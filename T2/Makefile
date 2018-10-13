all: dicionario.o skip_list.o main.c
	gcc -Wall dicionario.o skip_list.o main.c -o all
skip_list.o: skip_list.h skip_list.c
	gcc -Wall -c skip_list.c
dicionario.o: dicionario.h dicionario.c
	gcc -Wall -c dicionario.c
run: all
	./all
clean:
	rm -f *.o all
