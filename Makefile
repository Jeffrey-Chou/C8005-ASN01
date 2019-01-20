CC=gcc
CFLAGS=-Wall -g

process_spawner: process_spawner.o primedecompose.o task_parameter.o
	$(CC) $(CFLAGS) process_spawner.o primedecompose.o task_parameter.o -o process_spawner -lgmp

clean:
	rm -f *.o *bak *.out *.txt process_spawner

primedecompose.o: primedecompose.c 
	$(CC) $(CFLAGS) -O -c primedecompose.c

task_parameter.o: task_parameter.c
	$(CC) $(CFLAGS) -O -c task_parameter.c

process_spawner.o: process_spawner.c
	$(CC) $(CFLAGS) -O -c process_spawner.c