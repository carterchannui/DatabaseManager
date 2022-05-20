CC = gcc
INC_DIR = include
OBJ_DIR = obj
SRC_DIR = src
CFLAGS = -Wall -std=c99 -pedantic -g -I.
MAIN = main
OBJS = $(OBJ_DIR)/main.o $(OBJ_DIR)/arraylist.o $(OBJ_DIR)/splitstring.o $(OBJ_DIR)/main_tests.o
DEPS = $(INC_DIR)/arraylist.h $(INC_DIR)/typedef.h $(INC_DIR)/splitstring.h $(INC_DIR)/main_tests.h
SRC = $(SRC_DIR)/main.c $(SRC_DIR)/arraylist.c $(SRC_DIR)/splitstring.c $(SRC_DIR)/main_tests.c

all : $(MAIN)

$(MAIN) : $(OBJS) $(DEPS)
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS)

$(OBJ_DIR)/main.o : $(SRC) $(DEPS)
	$(CC) $(CFLAGS) -c main.c

$(OBJ_DIR)/arraylist.o : $(SRC) $(DEPS)
	$(CC) $(CFLAGS) -c arraylist.c

$(OBJ_DIR)/splitstring.o : $(SRC) $(DEPS)
	$(CC) $(CFLAGS) -c splitstring.c

$(OBJ_DIR)/main_tests.o: $(SRC) $(DEPS)
	$(CC) $(CFLAGS) -c main_tests.c

clean :
	rm -f *.o $(MAIN) core

