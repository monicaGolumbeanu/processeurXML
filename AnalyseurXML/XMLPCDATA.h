#ifndef XMLPCDATA_H_
#define XMLPCDATA_H_

#include <string>
#include "XMLNode.h"

class XMLPCDATA: public XMLNode {
	private:
		std::string content;
	public:
		XMLPCDATA(std::string content);
		std::string get_content();
		//void accept(XMLVisitor* v);
};

#endif
