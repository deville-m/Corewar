# warrior.mk

RES        = resources
CHAMPD     = champion
ASM_SAMPLE = $(RES)/asm_sample
CHAMPION   = $(CHAMPD)/dwarf.s

warrior_sample:
	$(ASM_SAMPLE) $(CHAMPION)

warrior:
	./$(ASM) $(CHAMPION)
