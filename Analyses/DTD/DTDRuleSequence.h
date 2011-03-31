#ifndef DTDRULESEQUENCE_H_
#define DTDRULESEQUENCE_H_

#include <iostream>
#include <string>
#include <vector>
#include "DTDRule.h"

using namespace std;

class DTDRuleSequence : public DTDRule {
    private:
        vector<DTDRule*>* rules;
    public:
        DTDRuleSequence();
        virtual void addRule(DTDRule* rule);
        vector<DTDRule*>* getChildrenRules();
        virtual bool validate(XMLTag* tag);
        virtual int partialValidate(XMLTag* tag, unsigned int position);
};

#endif /* DTDRULESEQUENCE_H_ */
