#ifndef _XMLATTR_
#define _XMLATTR_

#include <string>

class XMLAttr {
 private:
	std::string name;
	std::string value;
 public:
	XMLAttr(std::string name, std::string value);
	std::string get_name();
	std::string get_value();
};

#endif