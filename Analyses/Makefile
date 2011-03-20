COMPILER=g++
CPPFLAGS=-Wall
OBJSCPP=XMLAttr.ocpp XMLNode.ocpp XMLTag.ocpp XMLPCDATA.ocpp XMLPrintVisitor.ocpp XMLVisitor.ocpp
OBJSC=lex.xml_.oc  xml.tab.oc lex.dtd_.oc  dtd.tab.oc

BIN=bin

all: bison analyse

bison: *.l *.y
	flex  -Pxml_ xml.l
	flex  -Pdtd_ dtd.l
	bison -pxml_ --debug --verbose --defines=yy.tab_xml.h xml.y
	bison -pdtd_ --debug --verbose --defines=yy.tab_dtd.h dtd.y

analyse: $(OBJSCPP) $(OBJSC)
	g++ -g -DYYDEBUG=1 -o $(BIN)/analyse $(OBJSCPP) $(OBJSC) analyse.cpp 

clean:
	-rm -rf *.tab.c lex.*.c *.tab.h *.output
	-rm -f *.oc *.ocpp

%.ocpp: %.cpp %.h
	$(COMPILER) -c $(CPPFLAGS) $< -o $@

%.oc: %.c
	$(COMPILER) -c $(CPPFLAGS) $< -o $@
