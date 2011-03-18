#include <iostream>
#include <iomanip>
#include "XMLAttr.h"
#include "XMLNode.h"
#include "XMLTag.h"
#include "XMLPrintVisitor.h"

using namespace std;

//OBS.: Pas encore un Visiteur!

void XMLPrintVisitor::pretty_print(XMLNode* node) {
	XMLTag *tag;
	list<XMLNode *> children;
	list<XMLNode *>::iterator iter;
	switch (node->get_type()) {
	  case NODE_XMLTAG:
	    tag = static_cast<XMLTag*>(node);
		children = *(tag->get_children());
		cout << setw(node->get_depth()*TAB_LENGTH) << "<" << tag->get_name() << ">" << endl;
		if(!children.empty())
			for(iter = children.begin(); iter != children.end(); iter++)
				pretty_print(*iter);
		cout << setw(node->get_depth()*TAB_LENGTH) << "</" << tag->get_name() << ">" << endl;
		break;
	  case NODE_XMLPCDATA:
	    //pas encore defini XMLPCDATA
		break;
	  default:
	    break;
	}
}
