# Compiler settings
CXX := g++

# Flags and globals
IncDIR := ./include
LibDIR := ./lib
ObjDIR := ./obj
# CXXFLAGS := -g -O3 -Wall -Wextra -pedantic -mwindows
CXXFLAGS := -g -O3 -Wall -Wextra -pedantic --std=c++20 -mwindows
LibFLAGS := -lmingw32 -lraylib $(addprefix -L,$(LibDIR))
#LibFLAGS := -lraylib $(addprefix -L,$(LibDIR))
IncFLAGS := $(addprefix -I,$(IncDIR))

# Call it whatever you like
NAME := c0nw4y

# Separate source files
SRC := $(wildcard ./src/*.c)
CPPSRC := $(wildcard ./src/*.cpp)
CXXSRC := $(wildcard ./src/*.cxx)
OBJ := $(addprefix $(ObjDIR)/, $(notdir $(SRC:.c=.o) $(CPPSRC:.cpp=.o) $(CXXSRC:.cxx=.o)))

# The Meat and Potatoes...
.PHONY: all clean strip

all: target

target: $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) $(LibFLAGS) -o $(NAME)

$(ObjDIR)/%.o: $(SRC) $(CPPSRC) $(CXXSRC)
	mkdir -p $(ObjDIR)
	$(CXX) $(CXXFLAGS) $(IncFLAGS) -c $< -o $@

clean:
	rm -f target $(OBJ)

strip:
	strip --strip-all $(NAME)
