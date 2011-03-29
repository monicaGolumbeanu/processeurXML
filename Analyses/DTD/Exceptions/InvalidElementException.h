#ifndef INVALIDELEMENTEXCEPTION_H_
#define INVALIDELEMENTEXCEPTION_H_

#include <exception>

class XMLTag;
class XMLNode;

namespace DTDExceptions {

    class InvalidElementException: public std::exception {
        public:
            InvalidElementException(XMLTag* context, XMLNode* element);
            virtual const char* what() const throw ();
            virtual ~InvalidElementException();
        private:
            XMLTag* context;
            XMLNode* element;
    };

}

#endif /* INVALIDELEMENTEXCEPTION_H_ */
