#    ______
#   / ____/___  ________ _      ______ ______
#  / /   / __ \/ ___/ _ \ | /| / / __ `/ ___/
# / /___/ /_/ / /  /  __/ |/ |/ / /_/ / /
# \____/\____/_/   \___/|__/|__/\__,_/_/
#

# -------~-------~--~------------------~------
ASM        = asm
COREWAR    = corewar
LIB        = libft/libft.a
MAKEFLAGS += --silent
AARCH     := $(shell uname -s)
ifeq ($(AARCH), Linux)
	CC = gcc
else
	CC = clang
endif

CFLAGS=			-Wall -Wextra # -fsanitize=address
INCLUDES=		include
SRCDIR=			src/
COMMONDIR=		commons/
ASMDIR=			asm_src/
COREWARDIR=		corewar_src/
OBJDIR=         .objs

# -------~-------~--~------------------~------
COMMONSRC=		op.c swap_endian.c

ASMSRC=			asm.c tokenize.c utils.c lexer.c lexer2.c syntax_check.c \
				check_instruction.c token_utils.c craft_out.c crafting.c \
				crafting_tools.c create_output_file.c toolbox.c collision.c

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

vpath %.c $(SRCDIR)
vpath %.h $(INCLUDES)
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
$(OBJDIR):
	printf "\n$(LOG_U)$(OK_C)[MK]$(NO_C) Creating temp directory: $(SILENT_C) %s\n" $(OBJDIR)
	mkdir -p $(OBJDIR)
	mkdir -p $(OBJDIR)/{$(ASMDIR),$(COREWARDIR),$(COMMONDIR)}

all: $(OBJDIR) $(ASM) $(COREWAR)
	printf "\n$(LOG_U)$(OK_C)[LOVE COOKER]$(NO_C) Cooked targets: $(SILENT_C) %s %s 💖\n$(NO_C)" $(ASM) $(COREWAR)

%.o: %.c
	$(CC) $(CFLAGS) -I$(INCLUDES) -Ilibft/includes -c $< -o $@
	printf "\n$(LOG_U)$(OK_C)[$(_CC_)]$(NO_C) Compiling file: $(SILENT_C) %s\n" $@

$(LIB):
	printf "\n$(LOG_U)$(OK_C)[MAKE]$(NO_C) Checking library: $(SILENT_C) %s\n" $@
	$(MAKE) -C libft/

$(ASM): $(ASMOBJ) $(LIB)
	printf "\n$(LOG_U)$(OK_C)[$(_LD_)]$(NO_C) Linking file: $(SILENT_C) %s\n" $@
	$(CC) $(CFLAGS) -I$(INCLUDES) -o $@ $^

$(COREWAR): $(COREWAROBJ) $(LIB)
	printf "\n$(LOG_U)$(OK_C)[$(_LD_)]$(NO_C) Linking file: $(SILENT_C) %s\n" $@
	$(CC) $(CFLAGS) -I$(INCLUDES) -o $@ $^

clean:
	rm -rf $(OBJDIR)
	$(MAKE) -C libft/ clean
	printf "\n$(LOG_U)$(OK_C)[RM]$(NO_C) Cleaned up objects$(SILENT_C)\n"

fclean: clean
	rm -fr $(ASM) $(COREWAR)
	$(MAKE) -C libft/ fclean
	printf "\n$(LOG_U)$(OK_C)[RM]$(NO_C) Cleaned up targets:$(SILENT_C)%s %s\n" $(ASM) $(COREWAR)

re: fclean
	$(MAKE)

# -------~-------~--~------------------~------
.PHONY: all clean fclean re $(LIB)
