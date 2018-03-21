LIB = libft/libft.a

LIB_PATH = libft

NM_SRC = srcs/ft_nm.c
NM_SRC += srcs/list.c
NM_SRC += srcs/handler_64.c
NM_SRC += srcs/print_output.c
NM_SRC += srcs/utils.c
NM_SRC += srcs/handler_32.c
NM_SRC += srcs/handler_fat.c

OTOOL_SRC = srcs/ft_otool.c
OTOOL_SRC += srcs/utils.c

INC = -I ./incs/

NM = ft_nm
OTOOL = ft_otool

NM_OBJ = $(NM_SRC:.c=.o)
OTOOL_OBJ = $(OTOOL_SRC:.c=.o)

FLAG = -Wall -Werror -Wextra
DEBUG_FLAG = -fsanitize=address -Wall -Werror -Wextra

CG = \033[92m
CY =  \033[93m
CE = \033[0m
CB = \033[34m

all: $(NM) $(OTOOL)

$(NM): start $(NM_OBJ)
	@echo "\033[K$(CY)[ft_nm] :$(CE) $(CG)Compiling ft_nm ...$(CE)";
	@make -C libft
	@gcc $(FLAG) -o $(NM) $(NM_SRC) $(LIB);

$(OTOOL): $(OTOOL_OBJ)
	@echo "\033[K$(CY)[ft_otool] :$(CE) $(CG)Compiling ft_otool ...$(CE)";
	@make -C libft
	@gcc $(FLAG) -o $(OTOOL) $(OTOOL_SRC) $(LIB);

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
	@/bin/rm -rf $(NM_OBJ);
	@echo "\033[K$(CY)[ft_otool] :$(CE) $(CG)Cleaning ft_otool objects$(CE)\033[1A";
	@/bin/rm -rf $(OTOOL_OBJ);
	-@make clean -C $(LIB_PATH);

fclean: start clean
	@echo "\033[K$(CY)[ft_nm] :$(CE) $(CG)Cleaning ft_nm ...$(CE)\033[1A";
	@/bin/rm -f $(NM);
	@echo "\033[K$(CY)[ft_nm] :$(CE) $(CG)Cleaning ft_otool ...$(CE)\033[1A";
	@/bin/rm -f $(OTOOL);
	-@make fclean -C $(LIB_PATH);

re: fclean all

.PHONY: all clean fclean re