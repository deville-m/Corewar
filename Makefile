#    ______
#   / ____/___  ________ _      ______ ______
#  / /   / __ \/ ___/ _ \ | /| / / __ `/ ___/
# / /___/ /_/ / /  /  __/ |/ |/ / /_/ / /
# \____/\____/_/   \___/|__/|__/\__,_/_/
#
# -------~-------~--~------------------~------
ASM        = asm
COREWAR    = corewar
# -------~-------~--~------------------~------
RULES      = rules
include $(RULES)/env.mk
include $(RULES)/utils.mk
include $(RULES)/commons.mk
include $(RULES)/asm.mk
include $(RULES)/corewar.mk
include $(RULES)/clean.mk
# -------~-------~--~------------------~------
.PHONY: all clean fclean re
