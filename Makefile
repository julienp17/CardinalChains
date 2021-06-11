##
## EPITECH PROJECT, 2021
## strace
## File description:
## Makefile
##

CC			=	gcc

MAIN		=	$(addprefix $(SRC_D), main.c)
OBJ_M		=	$(MAIN:.c=.o)

SRC			=	$(addprefix $(SRC_D), $(SRC_F))
OBJ			=	$(SRC:.c=.o)
SRC_D		=	source/
SRC_F		=	grid.c \
				print_grid.c \
				file_reading/get_file_size.c \
				file_reading/get_file_buffer.c \
				file_reading/get_file_lines.c \
				file_reading/my_count_char.c \
				file_reading/my_count_until_sep.c \
				file_reading/my_str_to_word_array.c \
				file_reading/my_strarr_len.c \
				file_reading/my_str_isnum_pos.c

CFLAGS		=	-W -Wall -Wextra $(INC) $(LDFLAGS) -g -g3

INC			=	-I./includes

LDFLAGS		=

LDFLAGS_UT  =	-lcriterion --coverage

DBFLAGS		=	-g -g3 -ggdb

BINARY			=	chains

UT_BIN		=	unit_tests

all: $(BINARY)

$(BINARY): $(OBJ_M) $(OBJ)
	$(CC) $(CFLAGS) -o $(BINARY) $(OBJ_M) $(OBJ)

clean:
	rm -f $(OBJ)
	rm -f $(OBJ_M)
	rm -f $(OBJ_UT)
	rm -f *.gc*

fclean: clean
	rm -f $(BINARY)
	rm -f $(BIN_UT)

re: fclean all