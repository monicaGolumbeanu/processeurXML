#include <string>
#include <XMLTag.h>
#include "TagNotDefinedException.h"

using namespace std;

namespace DTDExceptions {

    TagNotDefinedException::TagNotDefinedException(XMLTag* tag) {
        this->tag = tag;
    }

    const char* TagNotDefinedException::what() const throw () {
        string message;
        message = "Element '" + tag->getName() + "' not defined in DTD.";
        return message.c_str();
    }

}
