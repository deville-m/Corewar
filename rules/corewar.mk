# corewar.mk
COREWARSRC   =  main.c utils.c options.c curses.c kernel.c keybinds.c \
				checker.c parser.c init.c process_utils.c check_process.c \
				set_instruction.c printer.c verbose.c dump.c dump2.c utils2.c \
				network.c curses2.c
COREWARINSTR =	live.c ld.c st.c add_sub.c and_or_xor.c zjmp.c ldi.c sti.c \
				vm_fork.c lld.c lldi.c lfork.c aff.c toolbox_vm.c

COREWARSRC   := $(addprefix $(COREWARDIR), $(COREWARSRC))
INSTRSRC     := $(addprefix $(INSTRDIR), $(COREWARINSTR))
COREWARSRC   := $(COREWARSRC) $(COMMONSRC) $(INSTRSRC)
COREWAROBJ   := $(COREWARSRC:.c=.o)

$(COREWAR): $(COREWAROBJ) $(LIB)
	printf "\n$(LOG_U)$(OK_C)[$(_LD_)]$(NO_C) Linking file:$(SILENT_C) %s\n" $@
	$(CC) $(CFLAGS_VM) -I$(INCLUDES) -o $@ $^
