# Compiler settings
CC := gcc
CXX := g++

# Flags and globals
IncDIR := ./include
LibDIR := ./lib
ObjDIR := ./obj
# CXXFLAGS := -g -O3 -Wall -Wextra -pedantic -mwindows
CXXFLAGS := -g -O3 -Wall -Wextra -pedantic
# LibFLAGS := -lmingw32 -lraylib -L$(addprefix $(LibDIR)/,SDL2/lib)
LibFLAGS := -lraylib $(addprefix -L,$(LibDIR))
IncFLAGS := $(addprefix -I,$(IncDIR))

# Call it whatever you like
NAME := c0nw4y

# Separate source files
SRC := $(wildcard ./src/*.c)
CPPSRC := $(wildcard ./src/*.cpp)
CXXSRC := $(wildcard ./src/*.cxx)
OBJ := $(addprefix $(ObjDIR)/, $(notdir $(SRC:.c=.o) $(CPPSRC:.cpp=.o) $(CXXSRC:.cxx=.o)))

# The Meat and Potatoes...
.PHONY: all clean fclean strip

all: target

target: $(OBJ)
	$(CC) $(CXXFLAGS) $(OBJ) $(LibFLAGS) -o $(NAME)
	strip --strip-unneeded $(NAME) -o $(NAME)

$(ObjDIR)/%.o: $(SRC) $(CPPSRC) $(CXXSRC)
	mkdir -p $(ObjDIR)
	$(CXX) $(CXXFLAGS) $(IncFLAGS) -c $< -o $@

clean:
	rm -f target $(OBJ)

fclean: clean
	rm -f $(NAME)

strip:
	strip --strip-all $(NAME)
