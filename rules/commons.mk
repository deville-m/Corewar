# commons.mk
COMMONSRC = op.c swap_endian.c

COMMONSRC:= $(addprefix $(COMMONDIR), $(COMMONSRC))
COMMONOBJ:= $(COMMONOBJ:.c=.o)

CDEPS = $(COMMONOBJ:.o=.d)
vpath %.h $(INCLUDES)

all: $(COREWAR)
	printf "\n$(LOG_U)$(OK_C)[LOVE COOKER]$(NO_C) Cooked targets: $(SILENT_C) %s %s 💖\n$(NO_C)" $(ASM) $(COREWAR)

%.o: %.c $(HDEPS)
	$(CC) $(CFLAGS) -I$(INCLUDES) -Ilibft/includes -c $< -o $@
	printf "\n$(LOG_U)$(OK_C)[$(_CC_)]$(NO_C) Compiling file: $(SILENT_C) %s\n" $@

$(LIB):
	printf "\n$(LOG_U)$(OK_C)[MAKE]$(NO_C) Checking library:$(SILENT_C) %s\n" $@
	$(MAKE) -C libft/
