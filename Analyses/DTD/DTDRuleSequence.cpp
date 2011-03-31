#include <vector>
#include <XMLNode.h>
#include <XMLTag.h>
#include "DTDRuleSequence.h"
#include <InvalidElementException.h>

using namespace DTDExceptions;

DTDRuleSequence::DTDRuleSequence() : DTDRule(RULE_SEQUENCE) {
    rules = new vector<DTDRule*>();
}

void DTDRuleSequence::addRule(DTDRule* rule) {
	rules->push_back(rule);
}

vector<DTDRule*>* DTDRuleSequence::getChildrenRules() {
    return rules;
}

bool DTDRuleSequence::validate(XMLTag* tag) {
    unsigned int i;
    unsigned int position = 0;
    DTDRule* rule;
    vector<XMLNode*>* children = tag->getChildren();
    bool repeat = canRepeat();
    do {  //must check the rule at least one time
        for(i = 0; i < rules->size(); i++) {
            rule = (*rules)[i];
            //======================
            //For optional sequences
            //======================
            if(i==0 && isOptional()) {
                try {
                    position = applyChildRule(tag, position, rule);
                }
                catch(...) {
                    if(children->size() != 0)
                        throw InvalidElementException(tag, (*children)[0]);
                    return false; //required child rule inside optional parent rule
                }
            }
            else
                position = applyChildRule(tag, position, rule);
        }
        //================================
        //End conditions of the validation
        //================================
        if(position == 0) {
            return false;
        }
        else if(position >= children->size()) {
            return true;
        }
    } while(repeat);
    return false;
}

int DTDRuleSequence::partialValidate(XMLTag* tag, unsigned int position) {
    unsigned int i;
    unsigned int firstPosition = position;
    unsigned int backupPosition;
    DTDRule* rule;
    vector<XMLNode*>* children = tag->getChildren();
    bool repeat = canRepeat();
    //===============
    //Wrong user call
    //===============
    if(position >= children->size())
        return -1;
    do {  //must check the rule at least one time
        backupPosition = position;
        for(i = 0; i < rules->size(); i++) {
            rule = (*rules)[i];
            //======================
            //For optional sequences
            //======================
            if(i==0 && isOptional()) {
                try {
                    position = applyChildRule(tag, position, rule);
                }
                catch(int error) { //catch Exception
                    return position; //required child rule inside optional parent rule
                }
            }
            else
                position = applyChildRule(tag, position, rule);
        }
        //================================
        //End conditions of the validation
        //================================
        if(position == firstPosition || position >= children->size())
            return position;
        if(!repeat)
            return backupPosition;
    } while(repeat);
    return position;
}

void DTDRuleSequence::printRule()
{
    vector<DTDRule *> * childrenRules = this->getChildrenRules();
    cout << "( ";
    // print first rule
    (*childrenRules)[0]->printRule();
    for ( int i=1; i < childrenRules->size(); i++ )
    {
        cout << " , ";
        (*childrenRules)[i]->printRule();
    }
    cout << " )" << this->getCardinalite();
}

