#ifndef DTDPARSERACTIONHANDLER_H_
#define DTDPARSERACTIONHANDLER_H_

#include <string>
#include <stack>
#include <vector>

class DTD;
class DTDElement;
class DTDAttribute;
class DTDRule;

//typedef map<DTDRule*, vector<string> > MapIncompleteRules;


class DTDParserActionHandler {
    public:
        DTDParserActionHandler();
        virtual ~DTDParserActionHandler();
        void finishElement(std::string);
        void finishAttlist(std::string);
        void finishAttribute(std::string);
        void finishRuleSequence();
        void finishRuleChoice();
        void createNewEmptyRule();
        void createNewAnyRule();
        void createNewItem(std::string);
        void pushNewItemList();
        void setNewAttributeType(std::string);
        void setNewRuleCardinality(char);
        void updateCardinality();
        void checkProblems();
        DTD* getDTD();
        void setDTD(DTD*);
    private:
        DTD* dtd;
        DTDAttribute* currAttribute;
        DTDRule * rule;
        char currCardinality;
        vector<DTDAttribute*> currAttributes; //peut avoir NULL comme element
        stack< vector<DTDRule *> *> subrules;

        //Problems related
        vector<string> attlistProblems; //ATTLIST without ELEMENT
};

extern DTDParserActionHandler handler;

#endif /* DTDPARSERACTIONHANDLER_H_ */
