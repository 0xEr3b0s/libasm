NAME        = libasm.a
TEST        = test

ASM         = nasm
ASMFLAGS    = -f elf64

CC          = gcc
CFLAGS      = -Wall -Wextra -Werror

AR          = ar
ARFLAGS     = rcs

SRCS_DIR    = srcs/
OBJS_DIR    = objs/
INCLUDES    = -Iincludes

SRCS        = $(wildcard $(SRCS_DIR)*.asm)
OBJS        = $(patsubst $(SRCS_DIR)%.asm,$(OBJS_DIR)%.o,$(SRCS))

GREEN       = \033[0;32m
RED         = \033[0;31m
RESET       = \033[0m

all: $(NAME)

$(NAME): $(OBJS)
	@$(AR) $(ARFLAGS) $(NAME) $(OBJS)
	@echo "$(GREEN)$(NAME) created$(RESET)"

$(OBJS_DIR)%.o: $(SRCS_DIR)%.asm
	@mkdir -p $(OBJS_DIR)
	@$(ASM) $(ASMFLAGS) $< -o $@
	@echo "$(GREEN)Compiled $<$(RESET)"

$(TEST): $(NAME) main.c
	@$(CC) $(CFLAGS) $(INCLUDES) main.c -L. -lasm -o $(TEST)
	@echo "$(GREEN)$(TEST) created$(RESET)"

clean:
	@rm -rf $(OBJS_DIR)
	@echo "$(RED)Object files removed$(RESET)"

fclean: clean
	@rm -f $(NAME) $(TEST)
	@echo "$(RED)$(NAME) and $(TEST) removed$(RESET)"

re: fclean all

.PHONY: all clean fclean re
