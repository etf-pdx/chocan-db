# Makefile for cs300 ChocAnDB program
# Follow format below for adding any new files.
# Variabless (INCLUDE, etc) probably wont need any further updating

INCLUDE = -I /usr/include -I.
LIB = -L /usr/lib
LINK = -lsqlite3 
OBJ = ChocAnDB.o Operator.o Service.o User.o

output: $(OBJ)
	g++ -ggdb -Wall -o output Main.cpp $(OBJ) $(INCLUDE) $(LIB) $(LINK) 

ChocAnDB.o: ChocAnDB.cpp ChocAnDB.h 
	g++ -ggdb -Wall -c -o ChocAnDB.o ChocAnDB.cpp $(INCLUDE)

Operator.o: Operator.cpp Operator.h
	g++ -ggdb -Wall -c -o Operator.o Operator.cpp $(INCLUDE)

Service.o: Service.cpp Service.h 
	g++ -ggdb -Wall -c -o Service.o Service.cpp $(INCLUDE)

User.o: User.cpp User.h 
	g++ -ggdb -Wall -c -o User.o User.cpp $(INCLUDE)

clean:
	@for obj in $(OBJ); do\
		if test -f $$obj; then rm $$obj; fi; done
	@if (test -f output); then rm output; fi;

