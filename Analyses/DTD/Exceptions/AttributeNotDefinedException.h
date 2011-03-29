#ifndef ATTRIBUTENOTDEFINEDEXCEPTION_H_
#define ATTRIBUTENOTDEFINEDEXCEPTION_H_

#include <exception>
class XMTag;
class XMLAttr;

namespace DTDExceptions {

    class AttributeNotDefinedException : public std::exception {
        public:
            AttributeNotDefinedException(XMLTag* tag, XMLAttr* attr);
            virtual const char* what() const throw ();
        private:
            XMLTag* tag;
            XMLAttr* attr;
    };

}

#endif /* ATTRIBUTENOTDEFINEDEXCEPTION_H_ */
