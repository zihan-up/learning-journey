SRCS:=$(wildcard *.cc)
OBJS:=$(patsubst %.cc, %, $(SRCS))
CC:=g++
FLAGS:=-g

ALL:$(OBJS)

%:%.cc
	$(CC)  $^ -o $@ $(FLAGS)

clean:
	rm -rf $(OBJS)
