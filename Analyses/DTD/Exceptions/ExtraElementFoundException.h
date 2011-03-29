#ifndef EXTRAELEMENTFOUNDEXCEPTION_H_
#define EXTRAELEMENTFOUNDEXCEPTION_H_

#include <exception>

class XMLTag;
class XMLNode;

namespace DTDExceptions {

    class ExtraElementFoundException: public std::exception {
        public:
            ExtraElementFoundException(XMLTag* context, XMLNode* element);
            virtual const char* what() const throw ();
            virtual ~ExtraElementFoundException();
        private:
            XMLTag* context;
            XMLNode* element;
    };

}

#endif /* EXTRAELEMENTFOUNDEXCEPTION_H_ */
