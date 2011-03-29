#include <vector>
#include <XMLNode.h>
#include <XMLTag.h>
#include <DTDRuleFinal.h>

DTDRuleFinal::DTDRuleFinal(bool empty) :
    DTDRule("", RULE_FINAL) {
    this->empty = empty;
}

bool DTDRuleFinal::isEmpty() {
    return empty;
}

bool DTDRuleFinal::validate(XMLTag* tag) {
    vector<XMLNode*>* children;
    //==================
    //Rule for empty tag
    //==================
    if(isEmpty()) {
        if(tag->hasChildren()) {
            ;//throw ExtraElementException
            return false;
        }
        else
            return true;
    }
    //========================
    //Rule for #PCDATA content
    //========================
    else {
        if(!tag->hasChildren()) {
            ;//throw RequiredElementNotFound("PCDATA")
            return false;
        }
        else {
            children = tag->getChildren();
            if ((*children)[0]->getType() != NODE_XMLPCDATA) {
                ;//throw InvalidElement : Tag no lugar de PCDATA
                return false;
            }
            else if (children->size() > 1) {
                ;//throw ExtraElementFound :
                return false;
            }
            else
                return true;
        }
    }
}

int DTDRuleFinal::partialValidate(XMLTag* tag, unsigned int position) {
    vector<XMLNode*>* children = tag->getChildren();
    //===============
    //Wrong user call
    //===============
    if(position >= children->size())
        return -1;
    //=======================
    //Trying to match #PCDATA
    //=======================
    if ((*children)[position]->getType() != NODE_XMLPCDATA) {
        ;//throw InvalidElement : Tag no lugar de PCDATA
        return position;
    }
    else
        return position+1;
}

