#ifndef TAGNOTDEFINEDEXCEPTION_H_
#define TAGNOTDEFINEDEXCEPTION_H_

#include <exception>

class XMLTag;

namespace DTDExceptions {

    class TagNotDefinedException : public std::exception {
        public:
            TagNotDefinedException(XMLTag* tag);
            virtual const char* what() const throw ();
        private:
            XMLTag* tag;
    };

}

#endif /* TAGNOTDEFINEDEXCEPTION_H_ */
