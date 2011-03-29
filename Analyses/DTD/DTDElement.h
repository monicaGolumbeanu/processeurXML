#ifndef DTDELEMENT_H_
#define DTDELEMENT_H_

#include <iostream>
#include <vector>
#include <string>

class DTDRule;
class DTDAttribute;

class DTDElement {
    public:
        DTDElement(std::string);
        std::string getName();
        void setRule(DTDRule* rule);
        DTDRule* getRule();
        std::vector<DTDAttribute*>* getAttributes();
        void addAttribute(DTDAttribute* attribute);
    private:
        std::string name;
        DTDRule* rule;
        std::vector<DTDAttribute*>* attributes;
};

#endif /* DTDELEMENT_H_ */
