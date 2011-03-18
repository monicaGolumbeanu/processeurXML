#ifndef _XMLPRINTVISITOR_
#define _XMLPRINTVISITOR_

#define TAB_LENGTH 4

class XMLPrintVisitor {
 public:
	void pretty_print(XMLNode* node);
};

#endif
