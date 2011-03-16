#include "XMLAttr.h"
#include "XMLNode.h"
#include "XMLTag.h"
#include "XMLPrintVisitor.h"

int main(int argc, char *argv[]) {
	XMLTag* root = new XMLTag("html");
	XMLTag* body = new XMLTag("body");
	root->add_child(body);
	XMLTag* p = new XMLTag("p");
	body->add_child(p);
	p->add_attr(XMLAttr("style", "color: rgb(80,0,0)"));
	XMLPrintVisitor visitor = XMLPrintVisitor();
	visitor.pretty_print(root);
}