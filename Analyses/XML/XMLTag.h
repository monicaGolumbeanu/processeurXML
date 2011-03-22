#ifndef _XMLTAG_
#define _XMLTAG_

#include "XMLNode.h"
class XMLAttr;
class XMLVisitor;

class XMLTag : public XMLNode {
    public:
        XMLTag(std::string name, std::string ns = "");
        std::string get_name();
        std::string get_namespace();
        void add_child(XMLNode *child);
        std::list<XMLNode *>* get_children(); //confirmar que operador new não retorna ponteiro
        void add_attr(XMLAttr* attr);
        std::list<XMLAttr*>* get_attrs();
        virtual void accept(XMLVisitor* v);
    private:
        std::string name;
        std::string ns;
        std::list<XMLNode *>* children;
        std::list<XMLAttr*>* attrs;
};

#endif
