CC := gcc

IncDIR := ./include
LibDIR := ./lib
ObjDIR := ./obj
CFLAGS := -g -O3 -Wall -Wextra -pedantic -std=c11
LibFLAGS := -lmingw32 -lraylib $(addprefix -L,$(LibDIR))
IncFLAGS := $(addprefix -I,$(IncDIR))

NAME := c0nw4y

SRC := $(wildcard ./src/*.c)
OBJ := $(addprefix $(ObjDIR)/, $(notdir $(SRC:.c=.o)))

.PHONY: all clean strip

all: target

target: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LibFLAGS) -o $(NAME)

$(ObjDIR)/%.o: $(SRC)
	mkdir -p $(ObjDIR)
	$(CC) $(CFLAGS) $(IncFLAGS) -c $< -o $@

clean:
	rm -f $(NAME)
	rm -f $(OBJ)

strip:
	strip --strip-unneeded $(NAME) -o $(NAME)
