#include <iostream>
#include <vector>
#include <XMLNode.h>
#include <XMLTag.h>
#include <DTDRuleChoice.h>
#include <EmptyTagException.h>
#include <ExtraElementFoundException.h>

using namespace DTDExceptions;

DTDRuleChoice::DTDRuleChoice() : DTDRule(RULE_CHOICE) {
    rules = new vector<DTDRule*> ();
}

void DTDRuleChoice::addRule(DTDRule* rule) {
    rules->push_back(rule);
}

vector<DTDRule*>* DTDRuleChoice::getChildrenRules() {
    return rules;
}

bool DTDRuleChoice::validate(XMLTag* tag) {
    unsigned int position = 0;
    unsigned int bakPosition;
    unsigned int i;
    bool foundOnce = false;
    bool validated;
    DTDRule* rule;
    vector<XMLNode*>* children = tag->getChildren();
    do {
        bakPosition = position;
        validated = false;
        for (i = 0; i < rules->size(); i++) {
            rule = (*rules)[i];
            try {
                position = applyChildRule(tag, position, rule);
                validated = true;
                if (position != bakPosition)
                    break;
            }
            catch (int error) {
                ;
            }
        }
        //==================
        //Rule never matched
        //==================
        if (!validated && !foundOnce) {
            if (!isOptional())
                throw EmptyTagException(tag);
                
            return false;
        }
        //==========================
        //Rule matched at least once
        //==========================
        else if (foundOnce) {
            if (!canRepeat()) {
                if (position >= children->size())
                    return true;
                else {
                    throw ExtraElementFoundException(tag, (*children)[position+1]);
                    return false;
                }
            }
            //==================
            //If rule can repeat
            //==================
            else if (validated && position >= children->size())
                return true;
            else if (!validated && position < children->size()) {
                throw ExtraElementFoundException(tag, (*children)[position+1]);
                return false;
            }
            //else : yet another iteration...
        }
    } while (canRepeat());
    return true;
}

int DTDRuleChoice::partialValidate(XMLTag* tag, unsigned int position) {
    unsigned int bakPosition;
    unsigned int i;
    bool foundOnce = false;
    bool validated;
    DTDRule* rule;
    vector<XMLNode*>* children = tag->getChildren();
    do {
        bakPosition = position;
        validated = false;
        for (i = 0; i < rules->size(); i++) {
            rule = (*rules)[i];
            try {
                position = applyChildRule(tag, position, rule);
                validated = true;
                if (position != bakPosition)
                    break;
            }
            catch (...) {;}
        }
        //==================
        //Rule never matched
        //==================
        if (!validated && !foundOnce) {
            if (!isOptional())
                throw EmptyTagException(tag);
            return position;
        }
        //==========================
        //Rule matched at least once
        //==========================
        else if (foundOnce) {
            if (!canRepeat()) {
                if (position < children->size())
                    throw ExtraElementFoundException(tag, (*children)[position+1]);
                return position;
            }
            //==================
            //If rule can repeat
            //==================
            else if (validated && position >= children->size())
                return position;
            else if (!validated && position < children->size()) {
                throw ExtraElementFoundException(tag, (*children)[position+1]);
                return position;
            }
            //else : yet another iteration...
        }
    } while (canRepeat());
    return position;
}

void DTDRuleChoice::print()
{
    vector<DTDRule *> * childrenRules = this->getChildrenRules();
    cout << "( ";
    for (unsigned int i=0; i < childrenRules->size(); i++ )
    {
        if(i > 0)
            cout << " | ";
        
        (*childrenRules)[i]->print();
    }
    cout << " )" << this->getCardinality();
}

