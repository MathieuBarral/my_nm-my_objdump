CC = gcc

NAME_NM = my_nm
SRC_NM = $(wildcard src/my_nm/*.c)
OBJ_NM = $(SRC_NM:.c=.o)

NAME_OBJDUMP = my_objdump
SRC_OBJDUMP = $(wildcard src/my_objdump/*.c)
OBJ_OBJDUMP = $(SRC_OBJDUMP:.c=.o)

CFLAGS = -W -Wall -Wextra -I include

all: nm objdump

nm: $(OBJ_NM)
	@ $(CC) -o $(NAME_NM) $(OBJ_NM) $(CFLAGS)
	@ echo "\033[1;34m[OK] \033[1;32mCompiled Binary\033[0m\033[1;31m [$(NAME_NM)]\033[0m"

objdump: $(OBJ_OBJDUMP)
	@ $(CC) -o $(NAME_OBJDUMP) $(OBJ_OBJDUMP) $(CFLAGS)
	@ echo "\033[1;34m[OK] \033[1;32mCompiled Binary\033[0m\033[1;31m [$(NAME_OBJDUMP)]\033[0m"

clean:
	@ $(RM) -f $(OBJ_NM)
	@ echo "\033[1;34m[OK] \033[1;31m[$(NAME_NM)]\033[0m \033[1;32mObject Cleaned\033[0m"
	@ $(RM) -f $(OBJ_OBJDUMP)
	@ echo "\033[1;34m[OK] \033[1;31m[$(NAME_OBJDUMP)]\033[0m \033[1;32mObject Cleaned\033[0m"

fclean: clean
	@ $(RM) -f $(NAME_NM)
	@ echo "\033[1;34m[OK] \033[1;32mBinary Cleaned\033[\033[0m\033[1;31m [$(NAME_NM)]\033[0m"
	@ $(RM) -f $(NAME_OBJDUMP)
	@ echo "\033[1;34m[OK] \033[1;32mBinary Cleaned\033[\033[0m\033[1;31m [$(NAME_OBJDUMP)]\033[0m"

re:	fclean all