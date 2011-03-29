#include <string>
#include "XMLPCDATA.h"
#include "XMLVisitor.h"

using namespace std;

XMLPCDATA::XMLPCDATA(string content) : XMLNode(NODE_XMLPCDATA) {
    this->content = content;
}

string XMLPCDATA::getContent() {
    return content;
}

bool XMLPCDATA::accept(XMLVisitor* v) {
    return v->visitXMLPCDATA(this);
}
