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

.PHONY : all

bison: *.l *.y
	flex  -Pxml_ xml.l
	flex  -Pdtd_ dtd.l
	flex  -Pxsl_ xsl.l
	bison -pxml_ --debug --verbose --defines=yy.tab_xml.h xml.y
	bison -pdtd_ --debug --verbose --defines=yy.tab_dtd.h dtd.y
	bison -pxsl_ --debug --verbose --defines=yy.tab_xsl.h xsl.y

analyse: $(OBJS_CPP) $(OBJS_C)
	mkdir -p $(BINDIR)
	g++ -g -DYYDEBUG=1 $(OBJS_CPP) $(OBJS_C) $(CPPFLAGS) -o $(BINDIR)/analyse

clean:
	-rm -rf *.tab.c lex.*.c *.tab.h *.output
	-rm -f *.o
	-rm -f XML/*.o
	-rm -f DTD/*.o

%.cpp.o: %.cpp %.h
	$(COMPILER) -c $(CPPFLAGS) $< -o $@

%.c.o: %.c
	$(COMPILER) -c $(CPPFLAGS) $< -o $@
