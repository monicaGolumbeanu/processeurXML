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
};

#endif /* DTDATTRIBUTE_H_ */
