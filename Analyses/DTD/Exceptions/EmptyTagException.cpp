#include <string>
#include "EmptyTagException.h"
#include "XMLTag.h"
#include "XMLNode.h"

using namespace std;

namespace DTDExceptions {

    EmptyTagException::EmptyTagException(XMLTag* context) {
        this->context = context;
    }

    const char* EmptyTagException::what() const throw () {
        string message;
        message = "Element '" + context->getName() + "' cannot be empty.";
        return message.c_str();
    }

    EmptyTagException::~EmptyTagException() {
    }

}
