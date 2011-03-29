#ifndef REQUIREDELEMENTNOTFOUNDEXCEPTION_H_
#define REQUIREDELEMENTNOTFOUNDEXCEPTION_H_

#include <exception>

class XMLTag;
class XMLNode;

namespace DTDExceptions {

    class RequiredElementNotFoundException: public std::exception {
        public:
            RequiredElementNotFoundException(XMLTag* context, XMLNode* element);
            virtual const char* what() const throw ();
            virtual ~RequiredElementNotFoundException();
        private:
            XMLTag* context;
            XMLNode* element;
    };

}

#endif /* REQUIREDELEMENTNOTFOUNDEXCEPTION_H_ */
