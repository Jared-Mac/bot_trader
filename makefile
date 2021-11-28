#g++ -std=c++17 -o bot main.cpp -lboost_iostreams -lboost
#_system -lboost_filesystem -lcurl


###################################
# OS COURSE - CS 433 example
#
###################################
CC = g++			# use g++ for compiling c++ code or gcc for c code
CFLAGS = -o -Wall -std=c++17		# compilation flags: -g for debugging. Change to -O or -O2 for optimized code.
LIB = -lcurl -lboost_system -lboost_iostreams -lboost_filesystem			# linked libraries
LDFLAGS = -L.			# link flags
PROG = bot			# target executable (output)
SRC = main.cpp Bot.cpp Interval.cpp Position.cpp Stock.cpp time_utils.cpp     # .c or .cpp source files.
OBJ = $(SRC:.cpp=.o) 	# object files for the target. Add more to this and next lines if there are more than one source files.
VER=c++11
all : $(PROG)

$(PROG): $(OBJ)
	$(CC)  -o $(PROG) $(OBJ) $(LDFLAGS) $(LIB)

.cpp.o:
	$(CC) -c $(CFLAGS) $< -o $@

# cleanup
clean:
	/bin/rm -f *.o $(PROG)

# DO NOT DELETE
