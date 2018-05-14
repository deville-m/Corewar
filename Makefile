#    ______
#   / ____/___  ________ _      ______ ______
#  / /   / __ \/ ___/ _ \ | /| / / __ `/ ___/
# / /___/ /_/ / /  /  __/ |/ |/ / /_/ / /
# \____/\____/_/   \___/|__/|__/\__,_/_/
#

# -------~-------~--~------------------~------
ASM=			asm
COREWAR=		corewar
AARCH:=         $(shell uname -s)
ifeq ($(AARCH), Linux)
	CC = gcc
else
	CC = clang
endif
CFLAGS=			#-Wall -Wextra -Werror
INCLUDES=		include
SRCDIR=			src/
COMMONDIR=		commons/
ASMDIR=			asm/
COREWARDIR=		corewar/
OBJDIR=         .objs

# -------~-------~--~------------------~------
COMMONSRC=		op.c swap_endian.c

ASMSRC=			main.c

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
all: $(OBJDIR) $(ASM) $(COREWAR)
	@echo "\tDONE !!"

$(OBJDIR):
	mkdir -p $(OBJDIR)
	mkdir -p $(OBJDIR)/{$(ASMDIR),$(COREWARDIR),$(COMMONDIR)}

$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) -I$(INCLUDES) -Ilibft/includes -c $< -o $@
	printf "\n$(LOG_U)$(OK_C)[$(_CC_)]$(NO_C) Compiling file: $(SILENT_C) %s\n" $@

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

# -------~-------~--~------------------~------
.PHONY: all clean fclean re pretty
.IGNORE: pretty
