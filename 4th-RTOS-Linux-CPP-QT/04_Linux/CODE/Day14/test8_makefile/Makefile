OUT := main
SRCS := $(wildcard *.c)
XXXX := $(patsubst %.c, %.o, $(SRCS))
CC := gcc

$(OUT): $(XXXX)
	$(CC) $^  -o $@
%.o: %.c
	$(CC) -c $< -o $@
.PHONY: clean clean_main rebuild
clean:
	$(RM) $(OUT) $(XXXX)
clean_main:
	$(RM) $(OUT)
rebuild: clean main
