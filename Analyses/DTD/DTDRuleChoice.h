#ifndef DTDRULECHOICE_H_
#define DTDRULECHOICE_H_

#include <iostream>
#include <string>
#include <vector>
#include <DTDRule.h>

using namespace std;

class DTDRuleChoice : public DTDRule {
    private:
        vector<DTDRule*>* rules;
    public:
        DTDRuleChoice(string cardinalite = "");
        void addRule(DTDRule* rule);
        vector<DTDRule*>* getChildrenRules();
        virtual bool validate(XMLTag* tag);
        virtual int partialValidate(XMLTag* tag, unsigned int position);
        virtual void printRule();
};

#endif /* DTDRULECHOICE_H_ */
