#include <iostream>
#include <string>
#include <vector>
#include "DTDRule.h"

using namespace std;

#ifndef DTDRULEATOMIC_H_
#define DTDRULEATOMIC_H_

class XMLTag;

class DTDRuleAtomic : public DTDRule {
    private:
        DTDRule *rule;
    public:
        DTDRuleAtomic();
        DTDRule* getRule();
        void setRule(DTDRule* rule);
        virtual bool validate(XMLTag* tag);
        virtual int partialValidate(XMLTag* tag, unsigned int position);
        virtual void print();
};

#endif /* DTDRULEATOMIC_H_ */
