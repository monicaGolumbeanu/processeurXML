#include <string>
#include "InvalidElementException.h"
#include "XMLTag.h"
#include "XMLNode.h"

using namespace std;

namespace DTDExceptions {

    InvalidElementException::InvalidElementException(XMLTag* context, XMLNode* element) {
        this->context = context;
        this->element = element;
    }

    const char* InvalidElementException::what() const throw () {
        string message;
        XMLTag* elementTag;
        message = "Invalid element '" + element->getName() + "' in the scope of '"
                + context->getName() + "'.";
        return message.c_str();
    }

    InvalidElementException::~InvalidElementException() {
    }

}
