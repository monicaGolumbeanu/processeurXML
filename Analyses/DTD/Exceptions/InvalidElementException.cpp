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
        message = "Invalid element '" + element->getName() + "' in the scope of '" +
                context->getName() + "'.\n" +
                "    * Either this tag is not allowed or it wasn't expected right now.";
        return message.c_str();
    }

}
