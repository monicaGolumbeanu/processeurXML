#ifndef XMLPCDATA_H_
#define XMLPCDATA_H_

#include "XMLNode.h"

class XMLPCDATA : public XMLNode {
    public:
        XMLPCDATA(std::string content);
        std::string get_content();
        virtual void accept(XMLVisitor* v);
    private:
        std::string content;
};

#endif
