#g++ -std=c++17 -o bot main.cpp -lboost_iostreams -lboost
#_system -lboost_filesystem -lcurl

# Compiler
CC = g++
# Compilation flags: -g for debugging. Change to -O or -O2 for optimized code.
CFLAGS = -o -Wall -std=c++17
# Linked libraries
LIB = -lcurl 
# Link flags
LDFLAGS = -L.
# Target executable (output)
PROG = main.out
# .c or .cpp source files.
SRC = *.cpp $(wildcard **/*.cpp)
# Object files for the target. Add more to this and next lines if there are more than one source files.
OBJ = $(SRC:.cpp=.o)
VER=c++11
all : $(PROG)

$(PROG): $(OBJ)
	$(CC)  -o $(PROG) $(OBJ) $(LDFLAGS) $(LIB)

.cpp.o:
	$(CC) -c $(CFLAGS) $< -o $@

# cleanup
clean:
	/bin/rm -f *.o $(wildcard **/*.o) $(PROG)