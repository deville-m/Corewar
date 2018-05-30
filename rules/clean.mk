# clean.mk

clean:
	rm -fr $(COREWAROBJ) $(ASMOBJ) $(COMMONOBJ)
	$(MAKE) -C libft/ clean
	printf "\n$(LOG_U)$(OK_C)[RM]$(NO_C) Cleaned up objects$(SILENT_C)\n"
	@printf "\e[0;33m"
	@cat $(BANNER)
	@printf "\e[0;37m"

fclean: clean
	rm -fr $(ASM) $(COREWAR)
	$(MAKE) -C libft/ fclean
	printf "\n$(LOG_U)$(OK_C)[RM]$(NO_C) Cleaned up targets:$(SILENT_C) %s %s\n" $(ASM) $(COREWAR)

re: fclean
	$(MAKE)
