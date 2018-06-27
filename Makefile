CC=gcc

test: test.c spawnlib.h spawnlib.o
	$(CC) -o test test.c spawnlib.o

spawnlib.o: spawnlib.c spawnlib.h
	$(CC) -c spawnlib.c

clean:
	rm -rf test spawnlib.o
