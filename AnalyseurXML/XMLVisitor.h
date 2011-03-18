#ifndef XMLVISITOR_H_
#define XMLVISITOR_H_

class XMLTag;
#include "XMLPCDATA.h"

typedef enum {
	VISITOR_PRINT, VISITOR_XSLT
} VISITOR_TYPE;

class XMLVisitor {
	private:
		VISITOR_TYPE type;
	public:
		XMLVisitor(VISITOR_TYPE type);
		virtual void visitXMLTag(XMLTag* tag);
		virtual void visitXMLPCDATA(XMLPCDATA* pcdata);
};

#endif
