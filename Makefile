CC=gcc

test: test.c spawnlib.h spawnlib.o
	$(CC) -o test test.c spawnlib.o

exploit: exploit-1996.c spawnlib.h spawnlib.o
	$(CC) -o exploit-1996 exploit-1996.c spawnlib.o

spawnlib.o: spawnlib.c spawnlib.h
	$(CC) -c spawnlib.c

clean:
	rm -rf test exploit-1996 spawnlib.o
