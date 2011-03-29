#include <XMLNode.h>
#include <XMLTag.h>
#include <DTDElement.h>
#include <DTDRule.h>

DTDRule::DTDRule(string card, RULE_ID identifType) {
    cardinalite = card;
    idType = identifType;
    element = NULL;
}

RULE_ID DTDRule::getType() {
    return idType;
}

string DTDRule::getCardinalite() {
    return cardinalite;
}

DTDElement* DTDRule::getElement() {
    return element;
}

void DTDRule::setElement(DTDElement* element) {
    this->element = element;
}

string DTDRule::getTagName() {
    if(element)
        return element->getName();
    else
        return "";
}

bool DTDRule::isOptional() {
	return (cardinalite=="?" || cardinalite=="*");
}

bool DTDRule::canRepeat() {
	return (cardinalite=="+" || cardinalite=="*");
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
            ;//throw InvalidElementException
            cout << "Error: " << tag->getName() << ". InvalidElementException --> " << endl;
            return position;
        }
        else {
            childTag = static_cast<XMLTag*>((*children)[position]);
            if(childRule->getTagName() != childTag->getName()) {
                ;//throw InvalidElementException
                cout << "Error: " << tag->getName() << ". InvalidElementException --> " << endl;
                return position;
            }
            else {
                //childRule->validate(childTag);
                return position + 1;
            }
        }
    }
}
