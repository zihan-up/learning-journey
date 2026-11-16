OUT := main
XXXX := main.o sum.o

$(OUT): $(XXXX)
	gcc $^  -o $@
main.o: main.c
	gcc -c $< -o $@
sum.o: sum.c
	gcc -c $< -o  $@
.PHONY: clean clean_main rebuild
clean:
	$(RM) $(OUT) $(XXXX)
clean_main:
	$(RM) $(OUT)
rebuild: clean main
