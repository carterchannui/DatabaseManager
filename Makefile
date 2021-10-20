CC = gcc
CFLAGS = -Wall -std=c99 -pedantic -g
MAIN = manage_data
OBJS = manage_data.o arraylist.o splitstring.o manage_data_tests.o

all : $(MAIN)

$(MAIN) : $(OBJS) arraylist.h
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS)

manage_data.o : manage_data.c arraylist.h typedef.h splitstring.h manage_data_tests.h
	$(CC) $(CFLAGS) -c manage_data.c

arraylist.o : arraylist.c arraylist.h typedef.h
	$(CC) $(CFLAGS) -c arraylist.c

splitstring.o : splitstring.c arraylist.h typedef.h
	$(CC) $(CFLAGS) -c splitstring.c

manage_data_tests.o: manage_data_tests.c typedef.h
	$(CC) $(CFLAGS) -c manage_data_tests.c

clean :
	rm -f *.o $(MAIN) core

