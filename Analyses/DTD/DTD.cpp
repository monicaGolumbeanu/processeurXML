#include <iostream>
#include <vector>
#include <DTDElement.h>
#include <DTD.h>

using namespace std;

DTD::DTD() {
	elements = new vector<DTDElement*>();
}

void DTD::addElement(DTDElement* element) {
    elements->push_back(element);
}

vector<DTDElement*>* DTD::getElements() {
    return elements;
}

DTDElement* DTD::getElementByName(string name) {
    for (unsigned int i = 0; i < elements->size(); i++) {
        if ((*elements)[i]->getName() == name)
            return (*elements)[i];
    }
    return NULL;
}
