# env.mk
LIB            = libft/libft.a
MAKEFLAGS      += --silent
CFLAGS         = -Wall -Wextra -g
CFLAGS_ASM     = $(CFLAGS)
CFLAGS_VM      = $(CFLAGS) -lncurses
INCLUDES       = include
SRCDIR         = src/
COMMONDIR      = commons/
ASMDIR         = asm_src/
COREWARDIR     = corewar_src/
INSTRUCTIONDIR = instructions/
OBJDIR         = .objs

# Paths
COMMONDIR := $(addprefix $(SRCDIR), $(COMMONDIR))
ASMDIR:= $(addprefix $(SRCDIR), $(ASMDIR))
COREWARDIR:= $(addprefix $(SRCDIR), $(COREWARDIR))
INSTRDIR:= $(addprefix $(COREWARDIR), $(INSTRUCTIONDIR))
