#ifndef _XMLTAG_
#define _XMLTAG_

#include <string>
#include <vector>
#include <XMLNode.h>
class XMLAttr;
class XMLVisitor;

class XMLTag : public XMLNode {
    public:
        XMLTag(std::string name, std::string ns = "");
        std::string getName();
        std::string getNamespace();
        void addChild(XMLNode *child);
        std::vector<XMLNode *>* getChildren();
        bool hasChildren();
        void addAttr(XMLAttr* attr);
        std::vector<XMLAttr*>* getAttrs();
        virtual bool accept(XMLVisitor* v);
    private:
        std::string name;
        std::string ns;
        std::vector<XMLNode *>* children;
        std::vector<XMLAttr*>* attrs;
};

#endif
