#ifndef DTDPARSERACTIONHANDLER_H_
#define DTDPARSERACTIONHANDLER_H_

#include <string>

class DTD;
class DTDElement;
class DTDAttribute;

//typedef map<DTDRule*, vector<string> > MapIncompleteRules;


class DTDParserActionHandler {
    public:
        DTDParserActionHandler(DTD* dtd);
        virtual ~DTDParserActionHandler();
        void finishElement(std::string);
        void finishAttlist(std::string);
        void finishAttribute(std::string);
        void setNewAttributeType(std::string);
        void checkProblems();
    private:
        DTD* dtd;
        DTDAttribute* currAttribute;
        vector<DTDAttribute*> currAttributes; //peut avoir NULL comme element

        //Problems related
        vector<string> attlistProblems; //ATTLIST without ELEMENT
        //void linkRules();
        //MapIncompleteRules incompleteRules;
};

#endif /* DTDPARSERACTIONHANDLER_H_ */
