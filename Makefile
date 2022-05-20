CC = gcc
CFLAGS = -Wall -std=c99 -pedantic -g
MAIN = main
OBJS = main.o arraylist.o splitstring.o main_tests.o

all : $(MAIN)

$(MAIN) : $(OBJS) arraylist.h
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS)

main.o : main.c arraylist.h typedef.h splitstring.h main_tests.h
	$(CC) $(CFLAGS) -c main.c

arraylist.o : arraylist.c arraylist.h typedef.h
	$(CC) $(CFLAGS) -c arraylist.c

splitstring.o : splitstring.c arraylist.h typedef.h
	$(CC) $(CFLAGS) -c splitstring.c

main_tests.o: main_tests.c typedef.h
	$(CC) $(CFLAGS) -c main_tests.c

clean :
	rm -f *.o $(MAIN) core

