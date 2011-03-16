COMPILER=g++
CPPFLAGS=-Wall
OBJS=XMLAttr.o XMLNode.o XMLTag.o XMLPrintVisitor.o
BIN=bin

all: xmltest analyseXML

analyseXML: *.l *.y
	flex  xml.l
	bison --debug --verbose --defines=yy.tab.h xml.y
	g++ -g -DYYDEBUG=1 -o $(BIN)/analyseXML  lex.yy.c  xml.tab.c

xmltest: main.cpp $(OBJS)
	mkdir -p bin
	$(COMPILER) main.cpp XMLAttr.o XMLNode.o XMLTag.o XMLPrintVisitor.o -o $(BIN)/xmltest

clean:
	-rm -rf *.tab.c lex.*.c *.tab.h *.output analyseXML
	-rm -f *.o

%.o: %.cpp %.h
	$(COMPILER) -c $(CPPFLAGS) $< -o $@
