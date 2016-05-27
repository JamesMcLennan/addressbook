SOURCES=addressbook.c addressbook_list.c commands.c helpers.c
HEADERS=addressbook.h addressbook_list.h commands.h helpers.h
PROGRAM=addressbook
FLAGS=-ansi -pedantic -Wall

all:
	gcc $(FLAGS) -o $(PROGRAM) $(SOURCES)

clean:
	rm $(PROGRAM)
    
archive:
	zip $(USER)-a2 $(SOURCES) $(HEADERS) Makefile

default: addressbook

addressbook: addressbook.o addressbook_list.o commands.o helpers.o
	gcc $(FLAGS) -o $(PROGRAM) $(SOURCES)

addressbook.o: addressbook.c commands.h addressbook_list.h helpers.h
	gcc $(FLAGS) -c addressbook.c 

commands.o: commands.c addressbook_list.h helpers.h
	gcc $(FLAGS) -c commands.c

addressbook_list.o: addressbook_list.c helpers.h
	gcc $(FLAGS) -c addressbook_list.c

helpers.o: helpers.c
	gcc $(FLAGS) -c helpers.c




