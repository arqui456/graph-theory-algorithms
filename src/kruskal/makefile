all: kruskal clean

kruskal: main.o utils.o algorithms.o graph.o
	gcc -o kruskal.bin main.o utils.o algorithms.o graph.o

main.o: main.c ../../include/utils.h
	gcc -o main.o main.c -I../../include -c -W -Wall -Wextra -pedantic -g

utils.o: ../utils.c ../../include/utils.h graph.o algorithms.o
	gcc -o utils.o ../utils.c -I../../include -c -W -Wall -Wextra -pedantic -g

algorithms.o: ../algorithms.c ../../include/algorithms.h graph.o
	gcc -o algorithms.o ../algorithms.c -I../../include -c -W -Wall -Wextra -pedantic -g

graph.o: ../graph.c ../../include/graph.h
	gcc -o graph.o ../graph.c -I../../include -c -W -Wall -Wextra -pedantic -g

clean:
	rm -rf *.o