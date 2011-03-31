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
        DTDRule(RULE_ID);
        DTDRule(string, RULE_ID);
        RULE_ID getType();
        char getCardinality();
        void setCardinality(char);
        virtual bool validate(XMLTag* tag) = 0;
        virtual int partialValidate(XMLTag* tag, unsigned int position) = 0;
        DTDElement* getElement();
        void setElement(DTDElement* element);
        string getTagName();
        void setName(string name);
        string getName();
        bool isOptional();
        bool canRepeat();
        virtual void printRule() = 0;
    protected:
        int applyChildRule(XMLTag* tag, unsigned int position, DTDRule* childRule);
    private:
        char cardinality;
        string name;
        DTDElement* element;
        RULE_ID idType;
};

#endif /* DTDRULE_H_ */
