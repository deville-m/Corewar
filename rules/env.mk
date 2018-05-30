# env.mk
NPROC          = $(shell sysctl -n hw.physicalcpu)
LIB            = libft/libft.a
MAKEFLAGS      += --silent -k -j$(NPROC) --no-print-directory
CFLAGS         = -Wall -Wextra -Werror
CCFLAGS        = -MD -MMD
CFLAGS_ASM     = $(CFLAGS)
CFLAGS_VM      = $(CFLAGS) -lncurses
INCLUDES       = include
SRCDIR         = src/
COMMONDIR      = commons/
ASMDIR         = asm_src/
COREWARDIR     = corewar_src/
INSTRUCTIONDIR = instructions/
OBJDIR         = .objs
BANNER         = $(RULES)/.banner
HDEP           = op.h vm.h asm.h
HDEPS          = $(addprefix $(INCLUDES)/, $(HDEP))

.SUFFIXES:
.SUFFIXES: .c .o .d

# Paths
COMMONDIR := $(addprefix $(SRCDIR), $(COMMONDIR))
ASMDIR:= $(addprefix $(SRCDIR), $(ASMDIR))
COREWARDIR:= $(addprefix $(SRCDIR), $(COREWARDIR))
INSTRDIR:= $(addprefix $(COREWARDIR), $(INSTRUCTIONDIR))
