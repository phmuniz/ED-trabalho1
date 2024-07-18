all: comp run clean

comp:
	gcc -Wall -g -o main *.c -lm

run:
	./main < casos_de_teste/bfs/inputs/en1 > casos_de_teste/bfs/outputs/s1
	./main < casos_de_teste/bfs/inputs/en2 > casos_de_teste/bfs/outputs/s2
	./main < casos_de_teste/bfs/inputs/en3 > casos_de_teste/bfs/outputs/s3
	./main < casos_de_teste/bfs/inputs/en4 > casos_de_teste/bfs/outputs/s4
	./main < casos_de_teste/bfs/inputs/en5 > casos_de_teste/bfs/outputs/s5
	./main < casos_de_teste/bfs/inputs/en6 > casos_de_teste/bfs/outputs/s6
	./main < casos_de_teste/bfs/inputs/en7 > casos_de_teste/bfs/outputs/s7

	./main < casos_de_teste/dfs/inputs/en1 > casos_de_teste/dfs/outputs/s1
	./main < casos_de_teste/dfs/inputs/en2 > casos_de_teste/dfs/outputs/s2
	./main < casos_de_teste/dfs/inputs/en3 > casos_de_teste/dfs/outputs/s3
	./main < casos_de_teste/dfs/inputs/en4 > casos_de_teste/dfs/outputs/s4
	./main < casos_de_teste/dfs/inputs/en5 > casos_de_teste/dfs/outputs/s5
	./main < casos_de_teste/dfs/inputs/en6 > casos_de_teste/dfs/outputs/s6
	./main < casos_de_teste/dfs/inputs/en7 > casos_de_teste/dfs/outputs/s7

	./main < casos_de_teste/ucs/inputs/en1 > casos_de_teste/ucs/outputs/s1
	./main < casos_de_teste/ucs/inputs/en2 > casos_de_teste/ucs/outputs/s2
	./main < casos_de_teste/ucs/inputs/en3 > casos_de_teste/ucs/outputs/s3
	./main < casos_de_teste/ucs/inputs/en4 > casos_de_teste/ucs/outputs/s4
	./main < casos_de_teste/ucs/inputs/en5 > casos_de_teste/ucs/outputs/s5
	./main < casos_de_teste/ucs/inputs/en6 > casos_de_teste/ucs/outputs/s6
	./main < casos_de_teste/ucs/inputs/en7 > casos_de_teste/ucs/outputs/s7

val:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./main

clean:
	rm -f main