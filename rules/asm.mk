# asm.mk
ASMSRC = asm.c tokenize.c utils.c lexer.c lexer2.c lexer3.c \
		 syntax_check.c check_instruction.c token_utils.c craft_out.c \
		 crafting.c crafting_tools.c create_output_file.c toolbox.c \
		 collision.c check_labels.c

ASMSRC := $(addprefix $(ASMDIR), $(ASMSRC))
ASMSRC := $(ASMSRC) $(COMMONSRC)
ASMOBJ := $(ASMSRC:.c=.o)
ADEPS = $(ASMOBJ:.o=.d)

$(ASM): $(ASMOBJ) $(LIB)
	printf "\n$(LOG_U)$(OK_C)[$(_LD_)]$(NO_C) Linking file:$(SILENT_C) %s\n" $@
	$(CC) $(CFLAGS_ASM) -I$(INCLUDES) -o $@ $^
