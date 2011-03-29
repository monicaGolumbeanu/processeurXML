#include <string>
#include "RequiredElementNotFoundException.h"
#include "XMLTag.h"
#include "XMLNode.h"

using namespace std;

namespace DTDExceptions {

    RequiredElementNotFoundException::RequiredElementNotFoundException(XMLTag* context,
            XMLNode* element) {
        this->context = context;
        this->element = element;
    }

    const char* RequiredELementNotFoundException::what() const throw () {
        string message;
        message = "Required element '" + element->getName()
                + "' not found in the scope of '" + context->getName() + "'.";
        return message.c_str();
    }

    RequiredElementNotFoundException::~RequiredElementNotFoundException() {
    }

}
