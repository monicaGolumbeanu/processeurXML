#include "XMLPCDATA.h"
#include "XMLVisitor.h"

using namespace std;

XMLPCDATA::XMLPCDATA(string content) {
	this->content = content;
}

string XMLPCDATA::get_content() {
	return content;
}

/*void XMLPCDATA::accept(XMLVisitor* v) {
	v->visitXMLPCDATA(this);
}*/
