all: main
	gcc -Wall -wextra -pedantic -L/usr/local/lib -lcrypto -o main main.c
	./main
