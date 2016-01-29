# define the CPP compiler to use
CC = g++

# define any compile-time flags
DFLAGS = -Wall -g

# define the CPP source files
SRCS = bTree_main.cpp bTree.cpp 

# define the CPP object files 

# This uses Suffix Replacement within a macro:
#   $(name:string1=string2)

OBJS = $(SRCS:.cpp=.o)

# define the executable file 
MAIN = bTree

all: $(MAIN)
	@echo $(MAIN) compiled, no errors 

$(MAIN): $(OBJS) 
	$(CC) $(DFLAGS) $(OBJS) -o $(MAIN)
#
# this is a suffix replacement rule for building .o's from .c's
# it uses automatic variables $<: the name of the prerequisite of
# the rule(a .c file) and $@: the name of the target of the rule (a .o file) 

.cpp.o:
	$(CC) $(DFLAGS) $(INCLUDES) -c $<  -o $@

clean:
	$(RM) *.o *~ $(MAIN)
