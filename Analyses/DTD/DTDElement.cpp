#include <DTDAttribute.h>
#include <DTDRule.h>
#include <DTDElement.h>

DTDElement::DTDElement(string elementName) {
    name = elementName;
    attributes = new vector<DTDAttribute*>();
}

string DTDElement::getName() {
    return name;
}

void DTDElement::setRule(DTDRule* rule) {
	this->rule = rule;
	rule->setElement(this);
}

DTDRule* DTDElement::getRule() {
    return rule;
}

void DTDElement::addAttribute(DTDAttribute* attribute) {
	attributes->push_back(attribute);
}

vector<DTDAttribute*>* DTDElement::getAttributes() {
	return attributes;
}

