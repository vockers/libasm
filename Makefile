NAME := libasm.a

NASM := nasm -f elf64
AR   := ar rcs

SRC_DIR := ./src
OBJ_DIR := ./.obj
SOURCES := $(wildcard $(SRC_DIR)/*.asm)
OBJECTS := $(patsubst $(SRC_DIR)/%.asm,$(OBJ_DIR)/%.o,$(SOURCES))

all: $(NAME)

test: all
	$(CC) -o test tests/test.c -L. -lasm
	./test

$(NAME): $(OBJECTS)
	$(AR) $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.asm
	@mkdir -p $(OBJ_DIR)
	$(NASM) -o $@ $<

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re test
