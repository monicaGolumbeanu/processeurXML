#ifndef XMLPCDATA_H_
#define XMLPCDATA_H_

#include "XMLNode.h"

class XMLPCDATA : public XMLNode {
    public:
        XMLPCDATA(std::string content);
        std::string getContent();
        virtual bool accept(XMLVisitor* v);
    private:
        std::string content;
};

#endif
