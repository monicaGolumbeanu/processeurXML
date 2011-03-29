#include <iostream>
#include <vector>
#include <XMLNode.h>
#include <XMLTag.h>
#include <DTDRuleAtomic.h>

using namespace std;

DTDRuleAtomic::DTDRuleAtomic(string card) :
    DTDRule(card, RULE_ATOMIC) {
}

DTDRule* DTDRuleAtomic::getRule() {
    return rule;
}

void DTDRuleAtomic::setRule(DTDRule* rule) {
    RULE_ID type = rule->getType();
    if(type != RULE_ATOMIC && type != RULE_FINAL) {
        ;//throw InvalidAtomicRule
        return;
    }
    else
        this->rule = rule;
}


bool DTDRuleAtomic::validate(XMLTag* tag) {
    unsigned int i;
    XMLTag* childTag;
    vector<XMLNode*>* children = tag->getChildren();
    //====================
    //Tag with no children
    //====================
    if(!tag->hasChildren()) {
        if (!isOptional()) {
        cout << "Error: " << tag->getName() << ". RequiredRuleNotMached " << rule->getTagName() << endl;
            ;//throw RequiredRuleNotMatched
        }
        return false;
    }
    //============
    //General case
    //============
    else {
        i = 0;
        do {
            //PCDATA not allowed here. Only for DTDRuleFinal
            if((*children)[i]->getType() != NODE_XMLTAG) {
                ;//throw InvalidElement
                return false;
            }
            //Child tag must have the proper name (rule name)
            childTag = static_cast<XMLTag*>((*children)[i]);
            if(childTag->getName() != rule->getTagName()) {
                ;//throw InvalidElement
                return false;
            }
            i++;
        } while(canRepeat() && i < children->size());
        if(i < children->size()) {
            ;//throw ExtraElementFound
            return false;
        }
        else
            return true;
    }
}


int DTDRuleAtomic::partialValidate(XMLTag* tag, unsigned int position) {
    unsigned int i;
    bool foundOnce = false;
    XMLTag* childTag;
    vector<XMLNode*>* children = tag->getChildren();
    //===============
    //Wrong user call
    //===============
    if(position >= children->size())
        return -1;
    //============
    //General case
    //============
    i = position;
    do {
        //PCDATA not allowed here. Only for DTDRuleFinal
        if((*children)[i]->getType() != NODE_XMLTAG) {
            if(!isOptional() && !foundOnce)
                ;//throw InvalidElement
            return i;
        }
        //Child tag must have the proper name (rule name)
        childTag = static_cast<XMLTag*>((*children)[i]);
        if(childTag->getName() != rule->getTagName()) {
            if(!isOptional() && !foundOnce)
                ;//throw InvalidElement
            return i;
        }
        //Valid child, verify in child's scope
        foundOnce = true;
        i++;
    } while(canRepeat() && i < children->size());
    return i;
}
