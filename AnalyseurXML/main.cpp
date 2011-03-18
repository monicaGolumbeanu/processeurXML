#include "XMLAttr.h"
#include "XMLNode.h"
#include "XMLPCDATA.h"
#include "XMLTag.h"
#include "XMLVisitor.h"
#include "XMLPrintVisitor.h"
#include <list>
#include <string>

using namespace std;

/*void pretty_print(XMLNode* node) {
	XMLPrintVisitor* visitor = new XMLPrintVisitor();
	XMLTag *tag;
	XMLPCDATA *pcdata;
	list<XMLNode *> children;
	list<XMLNode *>::iterator iter;
	switch (node->get_type()) {
		case NODE_XMLTAG:
			tag = static_cast<XMLTag*> (node);
			children = *(tag->get_children());
			tag->accept(visitor);
			if (!children.empty())
				for (iter = children.begin(); iter != children.end(); iter++)
					pretty_print(*iter);
			tag->accept(visitor);
			break;
		case NODE_XMLPCDATA:
			//pas encore defini XMLPCDATA
			pcdata = static_cast<XMLPCDATA*>(node);
			pcdata->accept(visitor);
			break;
		default:
			break;
	}
}*/

int main(int argc, char *argv[]) {
	XMLTag* root = new XMLTag("html");
	XMLTag* body = new XMLTag("body");
	root->add_child(body);
	XMLTag* p = new XMLTag("p");
	body->add_child(p);
	p->add_attr(XMLAttr("style", "color: rgb(80,0,0)"));
	//pretty_print(root);
}
