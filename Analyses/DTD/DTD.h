#ifndef DTD_H_
#define DTD_H_

#include <string>

class DTDElement;
class XMLNode;
class XMLValidateWithDTDVisitor;

class DTD {
    public:
        DTD();
        void addElement(DTDElement* element);
        std::vector<DTDElement*>* getElements();
        DTDElement* getElementByName(std::string name);
        bool validate(XMLNode* root);
        void printDTD();
    private:
        std::vector<DTDElement*>* elements;
        XMLValidateWithDTDVisitor* validate_visitor;
};

#endif /* DTD_H_ */
