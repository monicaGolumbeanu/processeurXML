#ifndef _XMLNODE_
#define _XMLNODE_

class XMLTag;

class XMLNode {
 protected:
 	XMLTag* parent;
 public:
	void set_parent(XMLTag* parent);
};

#endif