#include <iostream>
#include "XMLAttr.h"
#include "XMLNode.h"
#include "XMLTag.h"
#include "XMLPrintVisitor.h"

using namespace std;

void XMLPrintVisitor::pretty_print(XMLTag* tag) {
	cout << "<" << tag->get_name() << ">" << endl;
	list<XMLNode *>* children = tag->get_children();
	list<XMLNode *>:Iterator iter;
	if(!children)
		return;
	for(int i = iter.begin(); i != iter.end(); ++i) {
		cout << "    ";
		
	}
	cout << "</" << tag->get_name() << ">" << endl;
}
