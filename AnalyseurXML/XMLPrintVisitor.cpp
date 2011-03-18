#include <iostream>
#include <iomanip>
#include "XMLAttr.h"
#include "XMLNode.h"
#include "XMLTag.h"
#include "XMLPrintVisitor.h"

using namespace std;

//OBS.: Pas encore un Visiteur!

XMLPrintVisitor::XMLPrintVisitor() : XMLVisitor(VISITOR_PRINT){
	;
}

void XMLPrintVisitor::visitXMLTag(XMLTag* tag) {
	list<XMLAttr>* attrs;
	list<XMLAttr>::iterator iter;
	if (!tag->get_visited()) {
		attrs = tag->get_attrs();
		cout << setw(tag->get_depth() * TAB_LENGTH) << "<" << tag->get_name();
		if (!attrs->empty()) {
			for(iter = attrs->begin(); iter != attrs->end(); iter++) {
				//if (iter == attrs->back()) //pas d'espace pour le dernière attribut
					cout << " ";
				cout << iter->get_name() << "=\"" << iter->get_value() << '"';
			}
		}
		cout << ">" << endl;
	}
	else
		cout << setw(tag->get_depth() * TAB_LENGTH) << "</" << tag->get_name() << ">" << endl;
	tag->set_visited(!tag->get_visited());
}

void XMLPrintVisitor::visitXMLPCDATA(XMLPCDATA* pcdata) {
	//@TODO: Wrap lines to column 80
	if(!pcdata->get_visited())
		cout << setw(pcdata->get_depth() * TAB_LENGTH) << pcdata->get_content() << endl;
	pcdata->set_visited(!pcdata->get_visited());
}
