#ifndef DTDATTRIBUTE_H_
#define DTDATTRIBUTE_H_

#include <iostream>
#include <string>

using namespace std;

class DTDAttribute {
    private:
        string name;
        string data;
        string flag;
    public:
        DTDAttribute(string, string, string);
        string getName();
        string getData();
        string getFlag();
        void   setName( string aName ){name = aName;}
        void   setFlag( string aFlag ){flag = aFlag;}
};

#endif /* DTDATTRIBUTE_H_ */
