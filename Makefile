CC = gcc
CFLAGS = -Wall -pedantic -ansi -Werror -g
OBJ = game.o terminal.o UCPLinkedList.o main.o
EXEC = box

ifdef PULL
CFLAGS += -D PULL=1
endif

$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

game.o : game.c game.h 
	$(CC) -c game.c $(CFLAGS)

terminal.o : terminal.c terminal.h
	$(CC) -c terminal.c $(CFLAGS)

UCPLinkedList.o : UCPLinkedList.c UCPLinkedList.h main.h
	$(CC) -c UCPLinkedList.c $(CFLAGS)

main.o : main.c game.h main.h terminal.h UCPLinkedList.h
	$(CC) -c main.c $(CFLAGS)

clean :
	rm -f $(EXEC) $(OBJ)