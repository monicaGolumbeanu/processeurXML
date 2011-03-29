#include <string>
#include <XMLTag.h>
#include <XMLAttr.h>
#include "AttributeNotDefinedException.h"

using namespace std;

namespace DTDExceptions {

    AttributeNotDefinedException::AttributeNotDefinedException(XMLTag* tag,
            XMLAttr* attr) {
        this->tag = tag;
        this->attr = attr;
    }

    const char* AttributeNotDefinedException::what() const throw () {
        string message;
        message = "Attribute '" + attr->getName() + "' not defined for " +
                  "tag '" + tag->getName() + "'.";
        return message.c_str();
    }

}
