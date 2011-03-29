#include <string>
#include <vector>
#include <stack>
#include <DTD.h>
#include <DTDElement.h>
#include <DTDRule.h>
#include <DTDAttribute.h>
#include <XMLTag.h>
#include <XMLVisitor.h>
#include <XMLValidateWithDTDVisitor.h>
#include <XMLAttr.h>
#include <XMLNode.h>

using namespace std;

XMLValidateWithDTDVisitor::XMLValidateWithDTDVisitor() :
    XMLVisitor(VISITOR_DTDVALIDATION) {
}

void XMLValidateWithDTDVisitor::setDTD(DTD* dtd) {
    this->dtd = dtd;
    elements = dtd->getElements();
}

bool XMLValidateWithDTDVisitor::visitXMLTag(XMLTag* tag) {
    DTDElement* element = NULL;
    vector<DTDAttribute*>* dtdAttrs;
    vector<XMLAttr*>* xmlAttrs = tag->getAttrs();
    unsigned int i,j;

    //==================
    //Element is defined
    //==================
    for(i = 0; i < elements->size(); i++) {
        if( (*elements)[i]->getName() == tag->getName() ) {
            element = (*elements)[i];
            dtdAttrs = element->getAttributes();
            break;
        }
    }
    if(!element) {
        cout << "TagNotDefined!!!" << tag->getName();
        ; //throw TagNotDefinedException;
        return false;
    }

    //=========================
    //Verify children hierarchy
    //=========================
    element->getRule()->validate(tag);

    //=================
    //Verify attributes
    //=================
    /*for(i = 0; i < dtdAttrs.size(); i++) {
        //verification des elements obligatoires (pas demandée)
    }*/
    bool attributeDefined;
    for(i = 0; i < xmlAttrs->size(); i++) {
        attributeDefined = false;
        for(j = 0; j < dtdAttrs->size(); j++) {
            if( (*dtdAttrs)[j]->getName() == (*xmlAttrs)[i]->getName() ) {
                attributeDefined = true;
                break;
            }
        }
        if(!attributeDefined)
            ;//throw AttributeNotDefinedException
    }

    return true;
}

bool XMLValidateWithDTDVisitor::visitXMLPCDATA(XMLPCDATA *pcdata) {
    return true;
}
