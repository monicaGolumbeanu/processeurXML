#ifndef _XMLTAG_
#define _XMLTAG_

#include <list>
#include <string>

class XMLTag : public XMLNode {
 private:
	std::string name;
	std::list<XMLNode *>* children;
	std::list<XMLAttr>* attrs;
 public:
	XMLTag(std::string name);
	std::string get_name();
	void add_child(XMLNode *child);
	std::list<XMLNode *>* get_children(); //confirmar que operador new não retorna ponteiro
	void add_attr(XMLAttr attr);
	std::list<XMLAttr>* get_attrs();
};

#endif
