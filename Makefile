NAME := libasm.a

NASM := nasm -f elf64
AR   := ar rcs

SRC_DIR := ./src
OBJ_DIR := ./.obj
SOURCES := \
	ft_strlen.asm \
	ft_strcpy.asm \
	ft_strcmp.asm \
	ft_write.asm \
	ft_read.asm \
	ft_strdup.asm \
	ft_atoi_base.asm \
	ft_list_push_front.asm \
	ft_list_size.asm \
	ft_list_sort.asm \
	ft_list_remove_if.asm \

OBJECTS := $(addprefix $(OBJ_DIR)/, $(SOURCES:.asm=.o))

all: $(NAME)

test: all
	$(CC) -o test test.c -L. -lasm -z noexecstack -g
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

.PHONY: all clean fclean re test bonus test_bonus
