CC := gcc

IncDIR := ./include
LibDIR := ./lib
ObjDIR := ./obj
CFLAGS := -g -O3 -Wall -Wextra -pedantic -std=c11
LibFLAGS := -lmingw32 -lraylib $(addprefix -L,$(LibDIR))
IncFLAGS := $(addprefix -I,$(IncDIR))

NAME := c0nw4y

SRC := $(wildcard ./src/*.c)
CPPSRC := $(wildcard ./src/*.cpp)
CXXSRC := $(wildcard ./src/*.cxx)
OBJ := $(addprefix $(ObjDIR)/, $(notdir $(SRC:.c=.o) $(CPPSRC:.cpp=.o) $(CXXSRC:.cxx=.o)))

.PHONY: all clean strip

all: target

target: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LibFLAGS) -o $(NAME)

$(ObjDIR)/%.o: $(SRC) $(CPPSRC) $(CXXSRC)
	mkdir -p $(ObjDIR)
	$(CC) $(CFLAGS) $(IncFLAGS) -c $< -o $@

clean:
	rm -f $(NAME) $(OBJ)

strip:
	strip --strip-all $(NAME)
