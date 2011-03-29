#ifndef EMPTYTAGEXCEPTION_H_
#define EMPTYTAGEXCEPTION_H_

#include <exception>

class XMLTag;

namespace DTDExceptions {

    class EmptyTagException: public std::exception {
        public:
            EmptyTagException(XMLTag* context);
            virtual const char* what() const throw ();
            virtual ~EmptyTagException();
        private:
            XMLTag* context;
    };

}

#endif /* EMPTYTAGEXCEPTION_H_ */
