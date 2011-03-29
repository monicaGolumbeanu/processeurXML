#ifndef XMLVALIDATEWITHDTDVISITOR_H_
#define XMLVALIDATEWITHDTDVISITOR_H_

#include "XMLVisitor.h"

class DTD;
class DTDElement;
class DTDRule;

class XMLValidateWithDTDVisitor : public XMLVisitor {
    public:
        XMLValidateWithDTDVisitor();
        virtual bool visitXMLTag(XMLTag* tag);
        virtual bool visitXMLPCDATA(XMLPCDATA* pcdata);
        void setDTD(DTD* dtd);
    private:
        bool rootElementFound;
        DTD* dtd;
        vector<DTDElement*>* elements;

};

#endif /* XMLVALIDATEWITHDTDVISITOR_H_ */
