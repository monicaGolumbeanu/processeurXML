#ifndef XMLPCDATA_H_
#define XMLPCDATA_H_

#include <string.h>
#include "XMLNode.h"

class XMLPCDATA: public XMLNode {
	private:
		string content;
	public:
		XMLPCDATA(string content);
		string get_content();
};

#endif
