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

OBJECTS := $(addprefix $(OBJ_DIR)/, $(SOURCES:.asm=.o))

BONUS_SOURCES := \
	ft_atoi_base_bonus.asm \
	ft_list_push_front_bonus.asm \

BONUS_OBJECTS := $(addprefix $(OBJ_DIR)/, $(BONUS_SOURCES:.asm=.o))

all: $(NAME)

test: all
	$(CC) -o test test.c -L. -lasm -z noexecstack
	./test

$(NAME): $(OBJECTS)
	$(AR) $@ $^

test_bonus: bonus
	$(CC) -o test_bonus test_bonus.c -L. -lasm -z noexecstack
	./test_bonus

bonus: $(OBJECTS) $(BONUS_OBJECTS)
	$(AR) $(NAME) $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.asm
	@mkdir -p $(OBJ_DIR)
	$(NASM) -o $@ $<

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re test bonus test_bonus
