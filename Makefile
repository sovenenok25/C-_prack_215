CC = g++
CFLAGS = -g -std=c++23 -Wall -Wextra -Werror
main: main.o StringList.o
	$(CC) main.o StringList.o -o main

main.o : main.cpp
	$(CC) $(CFLAGS) -c main.cpp

StringList.o : StringList.cpp
	$(CC) $(CFLAGS) -c StringList.cpp

clean:
	rm *.o main