all: comp val clean

comp:
	gcc -Wall -g -o main *.c -lm

run:
	./main

val:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./main

clean:
	rm -f main