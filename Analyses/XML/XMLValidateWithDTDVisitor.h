#ifndef XMLVALIDATEWITHDTDVISITOR_H_
#define XMLVALIDATEWITHDTDVISITOR_H_

#include <vector>
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
        DTD* dtd;
        std::vector<DTDElement*>* elements;

};

#endif /* XMLVALIDATEWITHDTDVISITOR_H_ */
