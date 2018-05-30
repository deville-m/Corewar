# utils.mk
# -------~-------~--~------------------~------
AARCH     := $(shell uname -s)
ifeq ($(AARCH), Linux)
	CC = gcc
else
	CC = clang
endif
# -------~-------~--~------------------~------
_CC_ = `echo $(CC) | tr a-z A-Z`
_LD_ = `echo $(LD) | tr a-z A-Z`
# -------~-------~--~------------------~------
LOG_C    = \033[2J
LOG_U    = \033[A
NO_C     := \x1b[0m
OK_C     := \033[0;32m
ERROR_C  := \x1b[31;01m
WARN_C   := \x1b[33;01m
SILENT_C := \x1b[30;01m
# -------~-------~--~------------------~------
