all: analyse
analyse: *.l *.y makefile
	flex  -Pxml_ xml.l
	flex  -Pdtd_ dtd.l
	bison -pxml_ --debug --verbose --defines=yy.tab_xml.h xml.y
	bison -pdtd_ --debug --verbose --defines=yy.tab_dtd.h dtd.y
	g++ -g -DYYDEBUG=1 -o analyse  lex.xml_.c  xml.tab.c lex.dtd_.c  dtd.tab.c analyse.cpp
clean:
	-rm -rf *.tab.c lex.*.c *.tab.h *.output analyse

