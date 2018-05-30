# asm.mk
ASMSRC = main.c # TODO: Fix conflics

ASMSRC := $(addprefix $(ASMDIR), $(ASMSRC))
ASMSRC := $(ASMSRC) $(COMMONSRC)
ASMOBJ := $(ASMSRC:.c=.o)

$(ASM): $(ASMOBJ) $(LIB)
	printf "\n$(LOG_U)$(OK_C)[$(_LD_)]$(NO_C) Linking file:$(SILENT_C) %s\n" $@
	$(CC) $(CFLAGS_ASM) -I$(INCLUDES) -o $@ $^
