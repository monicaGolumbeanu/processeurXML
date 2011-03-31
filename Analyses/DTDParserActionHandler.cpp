#include <iostream>
#include <string>
#include <vector>
#include <DTD.h>
#include <DTDElement.h>
#include <DTDAttribute.h>
#include "DTDParserActionHandler.h"

using namespace std;

DTDParserActionHandler::DTDParserActionHandler(DTD* dtd) {
    this->dtd = dtd;
    currAttribute = NULL;

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
    //TODO: Add rule to the element
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

void DTDParserActionHandler::checkProblems() {
    ;
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
