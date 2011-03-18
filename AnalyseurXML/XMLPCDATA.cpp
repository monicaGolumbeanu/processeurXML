#include "XMLPCDATA.h"

XMLPCDATA::XMLPCDATA(string content) {
	this->content = content;
}

string XMLPCDATA::get_content() {
	return content;
}
