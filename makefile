CC = gcc
OBJS = Main.o
EXEC = sudoku-console
COMP_FLAGS = -ansi -O3 -Wall -Wextra -Werror -pedantic-errors
GUROBI_COMP = -I/usr/local/lib/gurobi563/include
GUROBI_LIB = -L/usr/local/lib/gurobi563/lib -lgurobi56

$(EXEC): $(OBJS)
	$(CC) $(OBJS) $(GUROBI_LIB) -o $@ -lm
Main.o: Main.c
	$(CC) $(COMP_FLAGS) $(GUROBI_COMP) -c $*.c
clean:
	rm -f *.o $(EXEC)

CC = gcc
OBJS	= Main.o Algorithem.o AuxFunctions.o Commands.o Constants.o DebugTools.o IOCommands.o List.o UserInput.o
EXEC = sudoku
COMP_FLAG = -ansi -Wall -Wextra \-Werror -pedantic-errors -g
GUROBI_COMP = -I/usr/local/lib/gurobi563/include
GUROBI_LIB = -L/usr/local/lib/gurobi563/lib -lgurobi56

$(EXEC): $(OBJS)
	$(CC) $(OBJS) $(GUROBI_LIB) -o $@ -lm

Main.o: Main.o Algorithem.o AuxFunctions.o Commands.o Constants.o DebugTools.o IOCommands.o List.o UserInput.o
	$(CC) $(COMP_FLAG) $(GUROBI_COMP) -c $*.c

Algorithem.o: Algorithem.c  Algorithem.h 
	$(CC) $(COMP_FLAG) $(GUROBI_COMP) -c $*.c

AuxFunctions.o: AuxFunctions.c AuxFunctions.h
	$(CC) $(COMP_FLAG) $(GUROBI_COMP) -c $*.c

Commands.o: Commands.c Commands.h 
	$(CC) $(COMP_FLAG) $(GUROBI_COMP) -c $*.c

Constants.o: Constants.c Constants.h
	$(CC) $(COMP_FLAG) $(GUROBI_COMP) -c $*.c

DebugTools.o: DebugTools.c DebugTools.h
	$(CC) $(COMP_FLAG) $(GUROBI_COMP) -c $*.c

IOCommands.o: IOCommands.c IOCommands.h
	$(CC) $(COMP_FLAG) $(GUROBI_COMP) -c $*.c

List.o: List.c List.h
	$(CC) $(COMP_FLAG) $(GUROBI_COMP) -c $*.c

UserInput.o: UserInput.c UserInput.h
	$(CC) $(COMP_FLAG) $(GUROBI_COMP) -c $*.c
	
	
clean:
	rm -f $(OBJS) $(EXEC)