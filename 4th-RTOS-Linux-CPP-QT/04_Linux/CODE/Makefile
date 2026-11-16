SRCS := $(wildcard *.c)
OUT := $(patsubst %.c, %, $(SRCS))
CC := gcc
COM_OP := -Wall -g
.PHONY: clean clean_main rebuild all

all: $(OUT)
%: %.c
	$(CC) $< -o $@  $(COM_OP)
clean:
	$(RM) $(OUT)
clean_main:
	$(RM) $(OUT)
rebuild: clean main
