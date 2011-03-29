#ifndef DTDRULE_H_
#define DTDRULE_H_

#include <iostream>
#include <string>
#include <list>
using namespace std;

class XMLTag;
class DTDElement;

typedef enum {
    RULE_SEQUENCE, RULE_CHOICE, RULE_ATOMIC, RULE_FINAL
} RULE_ID;

class DTDRule {
    public:
        DTDRule(string, RULE_ID);
        RULE_ID getType();
        string getCardinalite();
        virtual bool validate(XMLTag* tag) = 0;
        virtual int partialValidate(XMLTag* tag, unsigned int position) = 0;
        DTDElement* getElement();
        string getTagName();
        void setElement(DTDElement* element);
        bool isOptional();
        bool canRepeat();
    protected:
        int applyChildRule(XMLTag* tag, unsigned int position, DTDRule* childRule);
    private:
        string cardinalite;
        DTDElement* element;
        RULE_ID idType;
};

#endif /* DTDRULE_H_ */
