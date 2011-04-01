#include <iostream>
#include <XMLNode.h>
#include <XMLTag.h>
#include <DTD.h>
#include <DTDElement.h>
#include <DTDRule.h>
#include <DTDRuleSequence.h>
#include <DTDRuleChoice.h>
#include <DTDRuleAtomic.h>
#include <DTDRuleFinal.h>
#include <InvalidElementException.h>

using namespace DTDExceptions;

DTDRule::DTDRule(RULE_ID idType) {
    this->idType = idType;
    cardinality = '\0';
    element = NULL;
}

RULE_ID DTDRule::getType() {
    return idType;
}

char DTDRule::getCardinality() {
    return cardinality;
}

void DTDRule::setCardinality(char cardinality) {
    this->cardinality = cardinality;
}


DTDElement* DTDRule::getElement() {
    return element;
}

void DTDRule::setElement(DTDElement* element) {
    this->element = element;
}

string DTDRule::getName() {
    return name;
}

void DTDRule::setName(string name) {
    this->name = name;
}

string DTDRule::getTagName() {
    if(element)
        return element->getName();
    else
        return name;
}

bool DTDRule::isOptional() {
	return (cardinality=='?' || cardinality=='*');
}

bool DTDRule::canRepeat() {
	return (cardinality=='+' || cardinality=='*');
}

int DTDRule::applyChildRule(XMLTag* tag, unsigned int position, DTDRule* childRule) {
    XMLTag* childTag;
    vector<XMLNode*>* children = tag->getChildren();
    //===============
    //Wrong user call
    //===============
    if(position >= children->size())
        return -1;
    //=================
    //Try to match rule
    //=================
    if(childRule->getTagName() == tag->getName())
        return childRule->partialValidate(tag, position);
    else {
        if((*children)[position]->getType() != NODE_XMLTAG) {
            throw InvalidElementException(tag, (*children)[position]);
            return position;
        }
        else {
            childTag = static_cast<XMLTag*>((*children)[position]);
            if(childRule->getTagName() != childTag->getName()) {
                throw InvalidElementException(tag, (*children)[position]);
                return position;
            }
            else {
#ifdef DEBUG
                cout << "[VALIDATED] " << tag->getName() << " --- ";
                cout << childRule->getTagName() << endl;
#endif
                return position + 1;
            }
        }
    }
}

void DTDRule::replaceIncompleteRules(DTD* dtd) {
    bool valid = false;
    vector<DTDRule*> *children;
    vector<DTDElement*> *elements;
    DTDRuleSequence* sequence;
    DTDRuleChoice* choice;
    DTDRuleAtomic* atomic;
    DTDRuleFinal* final;
    DTDRule* rule;
    RULE_ID type;
    switch(getType()) {
        case RULE_SEQUENCE:
#ifdef DEBUG
            cout << "[INFO] Handling sequence rule: '" << this->getTagName()
                 << "'" << endl;
#endif
            sequence = static_cast<DTDRuleSequence*>(this);
            children = sequence->getChildrenRules();
            valid = true;
            break;
        case RULE_CHOICE:
#ifdef DEBUG
            cout << "[INFO] Handling choice rule: '" << this->getTagName()
                 << "'" << endl;
#endif
            choice = static_cast<DTDRuleChoice*>(this);
            children = choice->getChildrenRules();
            valid = true;
            break;
        default:
            return;
            break;
    }

    //Iterating children
    for(unsigned int i = 0; i < children->size(); i++) {
        //Replacing "incomplete" atomic rules
        type = (*children)[i]->getType();
        if(type == RULE_ATOMIC) {
            atomic = static_cast<DTDRuleAtomic*>((*children)[i]);
            rule = dynamic_cast<DTDRule*>(atomic);
        }
        else if(type == RULE_FINAL) {
            final = static_cast<DTDRuleFinal*>((*children)[i]);
            rule = dynamic_cast<DTDRule*>(final);
        }
        if(type == RULE_ATOMIC || type == RULE_FINAL) {
            elements = dtd->getElements();
            //Searching corresponding "complete" rule
            for(unsigned int j = 0; j < 1; j++) {
            //for(unsigned int j = 0; j < elements->size(); j++) {
#ifdef DEBUG
                cout << "[INFO] Checking... "
                     << " * Element: " << (*elements)[j]->getName()
                     << ", Atomic: " << atomic->getName() << endl
                     << " ==================================" << endl;
#endif
                if((*elements)[j]->getName() == atomic->getName()) {
                    (*children)[i] = (*elements)[j]->getRule();
                    (*children)[i]->setName(atomic->getName());
                }
            }
        }
        else {
            (*children)[i]->replaceIncompleteRules(dtd);
        }
    }
}
