#ifndef DTDRULEFINAL_H_
#define DTDRULEFINAL_H_

#include "DTDRule.h"

class DTDRuleFinal : public DTDRule {
    public:
        DTDRuleFinal();
        bool isEmpty();
        bool isAny();
        void setEmpty(bool);
        void setAny(bool);
        virtual bool validate(XMLTag* tag);
        virtual int partialValidate(XMLTag* tag, unsigned int position);
    private:
        bool empty;
        bool any;
        std::string tagName;
};

#endif /* DTDRULEFINAL_H_ */
