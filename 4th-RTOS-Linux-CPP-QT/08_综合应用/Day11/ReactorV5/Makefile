SRCS:=$(wildcard *.cc)
OBJS:=$(patsubst %.cc, %.o, $(SRCS))
CC:=g++
EXE:=server.exe
FLAGS:=-g 

$(EXE):$(OBJS)
	$(CC) -o $@ $^ $(FLAGS)

%.o:%.cc
	$(CC) -c  $^ -o $@ $(FLAGS)

clean:
	rm -rf $(OBJS) $(EXE)

echo:
	@echo $(SRCS)
	@echo $(OBJS)

