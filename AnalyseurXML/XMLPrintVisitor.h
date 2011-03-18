#ifndef _XMLPRINTVISITOR_
#define _XMLPRINTVISITOR_

#include "XMLVisitor.h"

#define TAB_LENGTH 4

class XMLPrintVisitor: public XMLVisitor {
	public:
		XMLPrintVisitor();
		void visitXMLTag(XMLTag* tag);
		void visitXMLPCDATA(XMLPCDATA* pcdata);
};

#endif
