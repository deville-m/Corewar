#    ______
#   / ____/___  ________ _      ______ ______
#  / /   / __ \/ ___/ _ \ | /| / / __ `/ ___/
# / /___/ /_/ / /  /  __/ |/ |/ / /_/ / /
# \____/\____/_/   \___/|__/|__/\__,_/_/
#

# -------~-------~--~------------------~------
ASM=			asm
COREWAR=		corewar
LIB=			libft/libft.a
AARCH:=         $(shell uname -s)
ifeq ($(AARCH), Linux)
	CC = gcc
else
	CC = clang
endif
CFLAGS=			-Wall -Wextra -Werror
INCLUDES=		include
SRCDIR=			src/
COMMONDIR=		commons/
ASMDIR=			asm_src/
COREWARDIR=		corewar_src/

# -------~-------~--~------------------~------
COMMONSRC=		op.c swap_endian.c

ASMSRC=			asm.c stupid_assembler.c predicate.c utils.c lexer.c

COREWARSRC=		main.c

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
# -------~-------~--~------------------~------
vpath %.c $(SRCS)
vpath %.h $(INCLDIRS)
# -------~-------~--~------------------~------
_CC_ = `echo $(CC) | tr a-z A-Z`
_LD_ = `echo $(LD) | tr a-z A-Z`
# -------~-------~--~------------------~------
LOG_C    = \033[2J
LOG_U    = \033[A
NO_C     := \x1b[0m
OK_C     := \033[0;32m
ERROR_C  := \x1b[31;01m
WARN_C   := \x1b[33;01m
SILENT_C := \x1b[30;01m
# -------~-------~--~------------------~------
all: $(ASM) $(COREWAR)
	@printf "\n$(LOG_U)$(OK_C)[LOVE COOKER]$(NO_C) Cooked targets: $(SILENT_C) %s %s 💖\n" $(ASM) $(COREWAR)

%.o: %.c
	@$(CC) $(CFLAGS) -I$(INCLUDES) -Ilibft/includes -c $< -o $@
	@printf "$(LOG_U)$(OK_C)[$(_CC_)]$(NO_C) Compiling file: $(SILENT_C) %s\n" $@

$(LIB):
	$(MAKE) -C libft/

$(ASM): $(ASMOBJ) $(LIB)
	@echo "\tLinking $@"
	@printf "$(LOG_U)$(OK_C)[$(_LD_)]$(NO_C) Linking file: $(SILENT_C) %s\n" $@
	@$(CC) $(CFLAGS) -I$(INCLUDES) -o $@ $^

$(COREWAR): $(COREWAROBJ) $(LIB)
	@printf "$(LOG_U)$(OK_C)[$(_LD_)]$(NO_C) Linking file: $(SILENT_C) %s\n" $@
	@$(CC) $(CFLAGS) -I$(INCLUDES) -o $@ $^

clean:
	@rm -f $(ASMOBJ) $(COREWAROBJ)
	@printf "$(LOG_U)$(OK_C)[RM]$(NO_C) Cleaned up objects$(SILENT_C)\n"

fclean: clean
	@printf "$(LOG_U)$(OK_C)[RM]$(NO_C) Cleaned up targets:$(SILENT_C)%s %s\n" $(ASM) $(COREWAR)
	@rm -f $(ASM) $(COREWAR)

re: fclean
	@$(MAKE)

# -------~-------~--~------------------~------
.PHONY: all clean fclean re pretty
.IGNORE: pretty
