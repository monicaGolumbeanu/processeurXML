#include <iostream>
#include <vector>
#include <XMLNode.h>
#include <XMLTag.h>
#include <DTDRuleChoice.h>

DTDRuleChoice::DTDRuleChoice(string card) :
    DTDRule(card, RULE_CHOICE) {
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
    vector<XMLNode*>* children = tag->getChildren();
    do {
        bakPosition = position;
        validated = false;
        for (i = 0; i < rules->size(); i++) {
            try {
                position = (*rules)[i]->partialValidate(tag, position);
                validated = true;
                if (position != bakPosition)
                    break;
            }
            catch (int error) { //catch Exception
                ;
            }
        }
        //==================
        //Rule never matched
        //==================
        if (!validated && !foundOnce) {
            if (!isOptional())
                cout << "Error: " << tag->getName() << ". RequiredRuleNotMatched --> " << endl;
                ;//throw RequiredRuleNotMatched
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
                    cout << "Error: " << tag->getName() << ". ExtraElementFoundException --> " << endl;
                    ;//throw ExtraElementFoundException
                    return false;
                }
            }
            //==================
            //If rule can repeat
            //==================
            else if (validated && position >= children->size())
                return true;
            else if (!validated && position < children->size()) {
                cout << "Error: " << tag->getName() << ". ExtraElementFoundException --> " << endl;
                ;//throw ExtraElementFoundException
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
    vector<XMLNode*>* children = tag->getChildren();
    do {
        bakPosition = position;
        validated = false;
        for (i = 0; i < rules->size(); i++) {
            try {
                position = (*rules)[i]->partialValidate(tag, position);
                validated = true;
                if (position != bakPosition)
                    break;
            }
            catch (int error) { //catch Exception
                ;
            }
        }
        //==================
        //Rule never matched
        //==================
        if (!validated && !foundOnce) {
            if (!isOptional())
                cout << "Error: " << tag->getName() << ". RequiredRuleNotMatched --> " << endl;
                ;//throw RequiredRuleNotMatched
            return position;
        }
        //==========================
        //Rule matched at least once
        //==========================
        else if (foundOnce) {
            if (!canRepeat()) {
                if (position < children->size())
                    cout << "Error: " << tag->getName() << ". ExtraElementFoundException --> " << endl;
                    ;//throw ExtraElementFoundException
                return position;
            }
            //==================
            //If rule can repeat
            //==================
            else if (validated && position >= children->size())
                return position;
            else if (!validated && position < children->size()) {
                cout << "Error: " << tag->getName() << ". ExtraElementFoundException --> " << endl;
                ;//throw ExtraElementFoundException
                return position;
            }
            //else : yet another iteration...
        }
    } while (canRepeat());
    return position;
}
