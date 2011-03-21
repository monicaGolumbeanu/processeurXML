#include <iostream>
#include <iomanip>
#include <list>
#include "XMLNode.h"
#include "XMLAttr.h"
#include "XMLTag.h"
#include "XMLPCDATA.h"
#include "XMLPrintVisitor.h"

using namespace std;

//OBS.: Pas encore un Visiteur!

XMLPrintVisitor::XMLPrintVisitor() : XMLVisitor(VISITOR_PRINT) {
}

void XMLPrintVisitor::visitXMLTag(XMLTag* tag) {
    list<XMLAttr>* attrs;
    list<XMLAttr>::iterator iter;
    list<XMLAttr>::iterator end;
    string ns;
    if (!tag->get_visited()) {
        attrs = tag->get_attrs();
        cout << setw(tag->get_depth() * TAB_LENGTH) << "<";
        ns = tag->get_namespace();
        if(!ns.empty())
            cout << ns << ':';
        cout << tag->get_name();
        if (!attrs->empty()) {
            cout << " ";
            end = attrs->end();
            end--;
            for (iter = attrs->begin(); iter != attrs->end(); iter++) {
                if (iter != end) //pas d'espace pour le dernière attribut
                    cout << " ";
                cout << iter->get_name() << "=\"" << iter->get_value() << '"';
            }
        }
        cout << ">" << endl;
    }
    else
        cout << setw(tag->get_depth() * TAB_LENGTH) << "</" << tag->get_name()
             << ">" << endl;
    tag->set_visited(!tag->get_visited());
}

void XMLPrintVisitor::visitXMLPCDATA(XMLPCDATA* pcdata) {
    //@TODO: Wrap lines to column 80
    //@OBS: Empty string in the following cout may be required in some platforms
    if (!pcdata->get_visited())
        cout << setw(pcdata->get_depth() * TAB_LENGTH) << ""
             << pcdata->get_content() << endl;
    pcdata->set_visited(!pcdata->get_visited());
}
