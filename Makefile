ASM=			asm
COREWAR=		corewar
CC=				clang
CFLAGS=			-Wall -Wextra -Werror
INCLUDES=		include/
SRCDIR=			src/
COMMONDIR=		commons/
ASMDIR=			asm_src/
COREWARDIR=		corewar_src/

COMMONSRC=		

ASMSRC=			

COREWARSRC=		

COMMONDIR:= $(addprefix $(SRCDIR), $(COMMONDIR))
ASMDIR:= $(addprefix $(SRCDIR), $(ASMDIR))
COREWARDIR:= $(addprefix $(SRCDIR), $(COREWARDIR))

COMMONSRC:= $(addprefix $(COMMONDIR), $(COMMONSRC))
COMMONOBJ:= $(COMMONOBJ:.c=.o)

ASMSRC:= $(addprefix $(ASMDIR), $(ASMSRC))
ASMSRC:= $(ASMSRC) $(COMMONSRC)
ASMOBJ:= $(ASMSRC:.c=.o)

COREWARSRC:= $(addprefix $(COREWARDIR), $(COREWARSRC))
COREWARSRC:= $(COREWARSRC) $(COMMONSRC)
COREWAROBJ:= $(COREWARSRC:.c=.o)

all: $(ASM) $(COREWAR)
	@echo "\tDONE !!"

%.o: %.c
	@zsh -c "echo -n '\tCompiling $<'"
	@$(CC) $(CFLAGS) -I$(INCLUDES) -c $< -o $@
	@zsh -c 'echo -e "\r\t\033[32mCompiled $@\033[0m "'

$(ASM): $(ASMOBJ)
	@echo "\tLinking $@"
	@$(CC) $(CFLAGS) -I$(INCLUDES) -o $@ $^

$(COREWAR): $(COREWAROBJ)
	@echo "\tLinking $@"
	@$(CC) $(CFLAGS) -I$(INCLUDES) -o $@ $^

clean:
	@rm -f $(ASMOBJ) $(COREWAROBJ) && echo "Removed object files."

fclean: clean
	@rm -f $(ASM) $(COREWAR) && echo "Removed target(s)."

re: fclean
	@$(MAKE)

.PHONY: all clean fclean re pretty

.IGNORE: pretty
