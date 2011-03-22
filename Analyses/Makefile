COMPILER=g++
CPPFLAGS=-Wall -IXML -IDTD
SRC_C=$(wildcard *.c)
OBJS_C=$(SRC_C:.c=.c.o)
SRC_CPP=$(wildcard *.cpp) 
SRC_CPP+= $(wildcard XML/*.cpp)
SRC_CPP+= $(wildcard DTD/*.cpp)
OBJS_CPP=$(SRC_CPP:.cpp=.cpp.o)
VPATH=XML DTD
OBJDIR=obj
BINDIR=bin

all: bison analyse

bison: *.l *.y
	flex  -Pxml_ xml.l
	flex  -Pdtd_ dtd.l
	bison -pxml_ --debug --verbose --defines=yy.tab_xml.h xml.y
	bison -pdtd_ --debug --verbose --defines=yy.tab_dtd.h dtd.y

analyse: $(OBJS_CPP) $(OBJS_C)
	g++ -g -DYYDEBUG=1 $(OBJS_CPP) $(OBJS_C) $(CPPFLAGS) \
	analyse.cpp -o $(BIN)/analyse

clean:
	-rm -rf *.tab.c lex.*.c *.tab.h *.output
	-rm -f $(OBJDIR)/*.o

%.cpp.o: %.cpp
	$(COMPILER) -c $(CPPFLAGS) $< -o $@

%.c.o: %.c %.h
	$(COMPILER) -c $(CPPFLAGS) $< -o $@