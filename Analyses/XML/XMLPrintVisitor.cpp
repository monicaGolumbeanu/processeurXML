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

XMLPrintVisitor::XMLPrintVisitor() : XMLVisitor(VISITOR_PRINT) {}

bool XMLPrintVisitor::visitXMLTag(XMLTag* tag) {
    vector<XMLAttr*>* attrs;
    vector<XMLAttr*>::iterator iter;
    vector<XMLAttr*>::iterator end;
    string ns;
    if (!tag->getVisited()) {
        attrs = tag->getAttrs();
        cout << setw(tag->getDepth() * TAB_LENGTH) << "<";
        ns = tag->getNamespace();
        if(!ns.empty())
            cout << ns << ':';
        cout << tag->getName();
        if (!attrs->empty()) {
            cout << " ";
            end = attrs->end();
            end--;
            for (iter = attrs->begin(); iter != attrs->end(); iter++) {
                if (iter != end) //pas d'espace pour le dernière attribut
                    cout << " ";
                cout << (*iter)->getName() << "=\"" << (*iter)->getValue() << '"';
            }
        }
        cout << ">" << endl;
    }
    else
        cout << setw(tag->getDepth() * TAB_LENGTH) << "</" << tag->getName()
             << ">" << endl;
    tag->setVisited(!tag->getVisited());
    return true;
}

bool XMLPrintVisitor::visitXMLPCDATA(XMLPCDATA* pcdata) {
    //@TODO: Wrap lines to column 80
    //@OBS: Empty string in the following cout may be required in some platforms
    if (!pcdata->getVisited())
        cout << setw(pcdata->getDepth() * TAB_LENGTH) << ""
             << pcdata->getContent() << endl;
    pcdata->setVisited(!pcdata->getVisited());
    return true;
}
