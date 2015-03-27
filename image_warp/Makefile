COMPILER=g++
FLAGS=-O3 -lopencv_core -lopencv_imgproc -lopencv_highgui
COMMON_FILES=
COMMON_OBJS=$(COMMON_FILES:.=.o)
MAIN_PROGRAM=warp.cpp
EXEC=warp
REMOVE=$(EXEC) $(COMMON_OBJS) 

all: $(COMMON_OBJS)
	$(COMPILER) $(MAIN_PROGRAM) $(COMMON_OBJS) $(FLAGS) -o $(EXEC)
debug: $(COMMON_OBJS)
	$(COMPILER) $(MAIN_PROGRAM) $(COMMON_OBJS) $(FLAGS) -DDEBUG -o $(EXEC)

$(COMMON_OBJS):
	$(COMPILER) -c $(COMMON_FILES) $(FLAGS)

clean: c
c:
	rm -rf $(REMOVE)