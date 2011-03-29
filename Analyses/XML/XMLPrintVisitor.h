#ifndef _XMLPRINTVISITOR_
#define _XMLPRINTVISITOR_

class XMLTag;
class XMLPCDATA;

#include "XMLVisitor.h"

#define TAB_LENGTH 4

class XMLPrintVisitor : public XMLVisitor {
    public:
        XMLPrintVisitor();
        virtual bool visitXMLTag(XMLTag* tag);
        virtual bool visitXMLPCDATA(XMLPCDATA* pcdata);
};

#endif
