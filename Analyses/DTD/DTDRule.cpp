#include <iostream>
#include <XMLNode.h>
#include <XMLTag.h>
#include <DTDElement.h>
#include <DTDRule.h>
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

void DTDRule::setName(string Name) {
    this->name = name;
}

string DTDRule::getTagName() {
    if(element)
        return element->getName();
    else
        return "";
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
