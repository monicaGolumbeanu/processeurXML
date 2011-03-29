#include <string>
#include "ExtraElementFoundException.h"
#include "XMLTag.h"
#include "XMLNode.h"

using namespace std;

namespace DTDExceptions {

    ExtraElementFoundException::ExtraElementFoundException(XMLTag* context,
            XMLNode* element) {
        this->context = context;
        this->element = element;
    }

    const char* ExtraElementFoundException::what() const throw () {
        string message;
        message = "Extra element '" + element->getName() + "' found in the scope '"
                + context->getName() + "'.";
        return message.c_str();
    }

    ExtraElementFoundException::~ExtraElementFoundException() {
    }

}
