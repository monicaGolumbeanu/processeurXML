#ifndef DTD_H_
#define DTD_H_

class DTDElement;

class DTD {
    public:
        DTD();
        void addElement(DTDElement* element);
        std::vector<DTDElement*>* getElements();
        DTDElement* getElementByName(std::string name);
        //void print();
    private:
        std::vector<DTDElement*>* elements;
};

#endif /* DTD_H_ */
