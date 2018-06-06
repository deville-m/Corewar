# warrior.mk

RES        = resources
CHAMPD     = champion
ASM_SAMPLE = $(RES)/asm_sample
CHAMPION   = $(addprefix $(CHAMPD) dwarf.s forkbomb.s)

warrior_sample:
	for champ in $(CHAMPD)/*.s; do \
		$(ASM_SAMPLE) $$champ; \
	done

warrior:
	for champ in $(CHAMPD)/*.s; do \
		./$(ASM) $$champ; \
	done
