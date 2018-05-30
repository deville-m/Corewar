# clean.mk

clean:
	rm -fr $(COREWAROBJ) $(ASMOBJ) $(COMMONOBJ)
	$(MAKE) -C libft/ clean
	printf "\n$(LOG_U)$(OK_C)[RM]$(NO_C) Cleaned up objects$(SILENT_C)\n"

fclean: clean
	rm -fr $(ASM) $(COREWAR)
	$(MAKE) -C libft/ fclean
	printf "\n$(LOG_U)$(OK_C)[RM]$(NO_C) Cleaned up targets:$(SILENT_C) %s %s\n" $(ASM) $(COREWAR)

re: fclean
	$(MAKE)
