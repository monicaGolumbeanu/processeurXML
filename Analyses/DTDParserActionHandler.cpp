#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <DTD.h>
#include <DTDRule.h>
#include <DTDRuleAtomic.h>
#include <DTDRuleChoice.h>
#include <DTDRuleSequence.h>
#include <DTDRuleFinal.h>
#include <DTDElement.h>
#include <DTDAttribute.h>
#include "DTDParserActionHandler.h"

using namespace std;

DTDParserActionHandler::DTDParserActionHandler(DTD* dtd) {
    this->dtd = dtd;
    currAttribute = NULL;
    currCardinality = '\0';
    rule = NULL;

}

DTDParserActionHandler::~DTDParserActionHandler() {
    // TODO Auto-generated destructor stub
}

void DTDParserActionHandler::finishElement(string name) {
    //=============================================
    //RULE: element --> ELEMENT debut contenu CLOSE
    //=============================================
    bool found = false;
    DTDElement * element = dtd->getElementByName(name);
    if (element == NULL) {
        element = new DTDElement(name);
        dtd->addElement(element);
#ifdef DEBUG
        cout << "[ACTION] Element '" << name << "' added." << endl;
#endif
    }
    else {
        for(unsigned int i = 0; i < attlistProblems.size(); i++) {
            if (attlistProblems[i] == name) {
                if(!found) {
                    attlistProblems.erase(attlistProblems.begin() + i);
                    found = true;
#ifdef DEBUG
                    cout << "[ATTRPROBLEM] [SOLVED] Element '" << name
                         << "' is now defined." << endl;
#endif
                }
                else {
#ifdef DEBUG
                    cout << "[ERROR] The ATTLIST for element '" << name
                         << "' was defined more than once." << endl;
#endif
                }
            }
        }
    }
    element->setRule(rule);
    rule = NULL;
}

void DTDParserActionHandler::finishAttribute(string name) {
    //=====================================================
    //RULE: attribut --> debut att_tapy default_declaration
    //=====================================================
    //OBS.: default_declaration ignored (considering #IMPLIED)
    if(currAttribute == NULL) {
        currAttribute = new DTDAttribute(name, "CDATA", "#IMPLIED");
#ifdef DEBUG
        cout << "[ATTRIBUTE] [WARNING] " << "Finishing incomplete attribute '"
             << name << "'. Using CDATA and #IMPLIED." << endl;
#endif
    }
    else {
        currAttribute->setName(name);
        currAttributes.push_back(currAttribute);
#ifdef DEBUG
        cout << "[ACTION] Attribute '" << name << "' added to current Attlist."
             << endl;
#endif
    }
}

void DTDParserActionHandler::finishAttlist(string name) {
    //=====================================================
    //RULE: attlist --> ATTLIST debut att_definition CLOSE;
    //=====================================================
    DTDAttribute *attribute;
    int last;
    DTDElement *element = dtd->getElementByName(name);
    if (element == NULL) {
        element = new DTDElement(name);
        dtd->addElement(element);
        attlistProblems.push_back(name);
#ifdef DEBUG
        cout << "[ATTRIBUTE] [WARNING] Attlist for element '" << name
             << "' was defined before the element definition." << endl;
#endif
    }
    for (unsigned int i = 0; i < currAttributes.size(); i++) {
        last = currAttributes.size() - 1;
        attribute = currAttributes[last];
        element->addAttribute(attribute);
        currAttributes[last] = NULL;
#ifdef DEBUG
        cout << "[ATTLIST] [INFORMATION] Temporary attribute '"
             << attribute->getName() << "' is now added to element "
             << element->getName() << endl;
#endif
    }
    currAttributes.clear();
#ifdef DEBUG
    cout << "[ACTION] Attlist for element '" << name << "' defined." << endl;
#endif
}

void DTDParserActionHandler::finishRuleSequence() {
    //===================================================
    //RULE: sequence --> parOpen liste_sequence CLOSEPAR;
    //===================================================
    vector<DTDRule*> *currItems = subrules.top();
    subrules.pop(); //won't call the destructor for a pointer
    DTDRuleSequence* seq = new DTDRuleSequence();
    for(unsigned int i = 0; i < currItems->size(); i++)
        seq->addRule((*currItems)[i]);
    if(subrules.empty()) {//last child rule
        rule = seq;
#ifdef DEBUG
        cout << "[INFO] Top-level sequence rule created." << endl;
#endif
    }
    else {
        (subrules.top())->push_back(seq);
#ifdef DEBUG
        cout << "[INFO] Sequence rule being added to parent rule." << endl;
#endif
    }
}

void DTDParserActionHandler::finishRuleChoice() {
    //==================================================
    //RULE: choix --> parOpen liste_choix_plus CLOSEPAR;
    //==================================================
    vector<DTDRule*> *currItems = subrules.top();
    subrules.pop();
    DTDRuleChoice* choice = new DTDRuleChoice();
    for(unsigned int i = 0; i < currItems->size(); i++)
        choice->addRule((*currItems)[i]);
    if(subrules.empty()) {//last child rule
        rule = choice;
#ifdef DEBUG
        cout << "[INFO] Top-level choice rule created." << endl;
#endif
    }
    else {
        (subrules.top())->push_back(choice);
#ifdef DEBUG
        cout << "[INFO] Choice rule being added to parent rule." << endl;
#endif
    }
}

void DTDParserActionHandler::createNewEmptyRule() {
    //=======================
    //RULE: contenu --> EMPTY
    //=======================
    if(rule != NULL) {
#ifdef DEBUG
        cout << "[ERROR] Creating new empty rule with other rule being "
             << "parsed." << endl;
#endif
    }
    else {
        rule = new DTDRuleFinal();
        (static_cast<DTDRuleFinal*>(rule))->setEmpty(true);
#ifdef DEBUG
        cout << "[INFO] Final rule (with EMPTY) created." << endl;
#endif
    }
}

void DTDParserActionHandler::createNewAnyRule() {
    //=====================
    //RULE: contenu --> ANY
    //=====================
    if(rule != NULL) {
#ifdef DEBUG
        cout << "[ERROR] Creating new empty rule with other rule being "
             << "parsed." << endl;
#endif
    }
    else {
        rule = new DTDRuleFinal();
        (static_cast<DTDRuleFinal*>(rule))->setAny(true);
#ifdef DEBUG
        cout << "[INFO] Final rule (with ANY) created." << endl;
#endif
    }
}

void DTDParserActionHandler::createNewItem(string name) {
    //=================================================================
    //RULE: mixed --> OPENPAR PCDATA contenu_mixed CLOSEPAR cardinalite
    //      contenu_mixed --> contenu_mixed PIPE debut
    //=================================================================
    DTDRuleAtomic* atomic = new DTDRuleAtomic();
    atomic->setName(name);
    atomic->setCardinality(currCardinality);
    if(subrules.empty()) {
#ifdef DEBUG
        cout << "[ERROR] Trying to add rule '" << name
             << "' to current pile's top element, which is NULL." << endl;
#endif
        return;
    }
    (subrules.top())->push_back(atomic);
    currCardinality = '\0';
#ifdef DEBUG
    cout << "[INFO] New simple rule '" << name <<"' created"
         << " with cardinality '" << atomic->getCardinality() << "'." << endl;
#endif
}

void DTDParserActionHandler::pushNewItemList() {
    //=============================
    //RULE: contenu_mixed --> EMPTY
    //      parOpen --> OPENPAR
    //=============================
    subrules.push(new vector<DTDRule*>());
#ifdef DEBUG
    cout << "[INFO] New item list pushed." << endl;
#endif
}

void DTDParserActionHandler::updateCardinality() {
    if(rule) {
        rule->setCardinality(currCardinality);
#ifdef DEBUG
        cout << "[INFO] Cardinality '" << currCardinality
             << "'has been set to new composite rule." << endl;
#endif
        currCardinality = '\0';
    }
#ifdef DEBUG
    else {
        cout << "[ERROR] Trying to set cardinality '" << currCardinality
             << "' to NULL." << endl;
    }
#endif
}

void DTDParserActionHandler::checkProblems() {
    //Varrer árvore substituindo DTDRuleAtomic com name pela regra
    //apropriada...;
}

void DTDParserActionHandler::setNewAttributeType(string att_type) {
    //===================================================
    //RULE: att_type --> CDATA | TOKENTYPE | type_enumere
    //===================================================
    //OBS.: type_enumere disabled for simplification purposes.
    if(currAttribute == NULL)
        currAttribute = new DTDAttribute();
    currAttribute->setData(att_type);
#ifdef DEBUG
    cout << "[ATTRIBUTE] Current attribute has type " << att_type
         << "." << endl;
#endif
}

void DTDParserActionHandler::setNewRuleCardinality(char cardinality) {
    currCardinality = cardinality;
#ifdef DEBUG
    cout << "[INFO] Current cardinality set to " << cardinality << "." << endl;
#endif
}


/*void DTDParserActionHandler::linkRules() {
    MapIncompleteRules::const_iterator end = incomplete.end();
    vector<string> names;
    DTDRuleChoice *ruleChoice;
    DTDRuleSequence *ruleSequence;
    DTDRuleAtomic *ruleAtomic;
    DTDElement *elem;
    for (MapIncompleteRules::const_iterator it = incomplete.begin(); it != end; ++it) {
        names = it->second;
        switch(it->first->getType()) {
            case RULE_CHOICE:
                ruleChoice = static_cast<DTDRuleChoice*>(it->first);
                for(unsigned int i = 0; i < names.size(); i++) {
                    elem = high->getElementByName(names[i]);
                    if(elem != NULL)
                        cout << "Error! Element " << names[i] << "not defined.";
                    else
                        ruleChoice->addRule(elem->getRule());
                }
                break;
            case RULE_SEQUENCE:
                ruleSequence = static_cast<DTDRuleSequence*>(it->first);
                for(unsigned int i = 0; i < names.size(); i++) {
                    elem = high->getElementByName(names[i]);
                    if(elem != NULL)
                        cout << "Error! Element " << names[i] << "not defined.";
                    else
                        ruleSequence->addRule(elem->getRule());
                }
                break;
            case RULE_ATOMIC:
                ruleAtomic = static_cast<DTDRuleAtomic*>(it->first);
                for(unsigned int i = 0; i < names.size(); i++) {
                    elem = high->getElementByName(names[i]);
                    if(elem != NULL)
                        cout << "Error! Element " << names[i] << "not defined.";
                    else
                        ruleAtomic->setRule(elem->getRule());
                }
                break;
        }
    }
}*/
