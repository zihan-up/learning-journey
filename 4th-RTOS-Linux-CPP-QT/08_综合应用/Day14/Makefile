SRCS:=$(wildcard *.cc)
OBJS:=$(patsubst %.cc, %, $(SRCS))
CC:=g++ 
FLAGS:=-g 
LIBS:=-lmysqlclient

ALL:$(OBJS)

%:%.cc
	$(CC)  $^ -o $@ $(FLAGS) $(LIBS)

clean:
	rm -rf $(OBJS)
