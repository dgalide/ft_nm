LIB = libft/libft.a

LIB_PATH = libft

SRC = srcs/ft_nm.c
SRC += srcs/list.c
SRC += srcs/handler_64.c
SRC += srcs/print_output.c
SRC += srcs/utils.c
SRC += srcs/handler_32.c

INC = -I ./incs/

NAME = ft_nm

OBJ = $(SRC:.c=.o)
FLAG = -Wall -Werror -Wextra
DEBUG_FLAG = -fsanitize=address -Wall -Werror -Wextra

CG = \033[92m
CY =  \033[93m
CE = \033[0m
CB = \033[34m

all: start $(NAME)

$(NAME): $(OBJ)
	@echo "\033[K$(CY)[ft_nm] :$(CE) $(CG)Compiling ft_nm ...$(CE)";
	@make -C libft
	@gcc $(FLAG) -o $(NAME) $(INC) $(SRC) $(LIB);

%.o: %.c
	@echo "\033[K$(CY)[ft_nm] :$(CE) $(CG)Compiling $<$(CE) \033[1A";
	@gcc $(FLAG) -c $< -o $@ $(INC)

start:
	@echo "\n";
	@echo "	$(CY)            _____                _____                    _____                    _____           $(CE) ";
	@echo "	$(CY)           /\    \              /\    \                  /\    \                  /\    \          $(CE) ";
	@echo "	$(CY)          /::\    \            /::\    \                /::\____\                /::\____\         $(CE) ";
	@echo "	$(CY)         /::::\    \           \:::\    \              /::::|   |               /::::|   |         $(CE) ";
	@echo "	$(CY)        /::::::\    \           \:::\    \            /:::::|   |              /:::::|   |         $(CE) ";
	@echo "	$(CY)       /:::/\:::\    \           \:::\    \          /::::::|   |             /::::::|   |         $(CE) ";
	@echo "	$(CY)      /:::/__\:::\    \           \:::\    \        /:::/|::|   |            /:::/|::|   |         $(CE) ";
	@echo "	$(CY)     /::::\   \:::\    \          /::::\    \      /:::/ |::|   |           /:::/ |::|   |         $(CE) ";
	@echo "	$(CY)    /::::::\   \:::\    \        /::::::\    \    /:::/  |::|   | _____    /:::/  |::|___|______   $(CE) ";
	@echo "	$(CY)   /:::/\:::\   \:::\    \      /:::/\:::\    \  /:::/   |::|   |/\    \  /:::/   |::::::::\    \  $(CE) ";
	@echo "	$(CY)  /:::/  \:::\   \:::\____\    /:::/  \:::\____\/:: /    |::|   /::\____\/:::/    |:::::::::\____\ $(CE) ";
	@echo "	$(CY)  \::/    \:::\   \::/    /   /:::/    \::/    /\::/    /|::|  /:::/    /\::/    / ~~~~~/:::/    / $(CE) ";
	@echo "	$(CY)   \/____/ \:::\   \/____/   /:::/    / \/____/  \/____/ |::| /:::/    /  \/____/      /:::/    /  $(CE) ";
	@echo "	$(CY)            \:::\    \      /:::/    /                   |::|/:::/    /               /:::/    /   $(CE) ";
	@echo "	$(CY)             \:::\____\    /:::/    /                    |::::::/    /               /:::/    /    $(CE) ";
	@echo "	$(CY)              \::/    /    \::/    /                     |:::::/    /               /:::/    /     $(CE) ";
	@echo "	$(CY)               \/____/      \/____/                      |::::/    /               /:::/    /      $(CE) ";
	@echo "	$(CY)                                                         /:::/    /               /:::/    /       $(CE) ";
	@echo "	$(CY)                                                        /:::/    /               /:::/    /        $(CE) ";
	@echo "	$(CY)                                                        \::/    /                \::/    /         $(CE) ";
	@echo "	$(CY)                                                         \/____/                  \/____/          $(CE) ";
	@echo "\n";


clean: start
	@echo "\033[K$(CY)[ft_nm] :$(CE) $(CG)Cleaning ft_nm objects$(CE)\033[1A";
	@/bin/rm -rf $(OBJ);
	@rm $(NAME)
	-@make clean -C $(LIB_PATH);

fclean: start clean
	@echo "\033[K$(CY)[ft_nm] :$(CE) $(CG)Cleaning 42sh ...$(CE)\033[1A";
	@/bin/rm -f $(NAME)_$(HOSTTYPE) "libft_ft_nm.so";
	-@make fclean -C $(LIB_PATH);

re: fclean all

.PHONY: all clean fclean re