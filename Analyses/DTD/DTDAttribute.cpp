#include "DTDAttribute.h"

DTDAttribute::DTDAttribute(string attName, string attData, string attFlag) {
    name = attName;
    data = attData;
    flag = attFlag;
}

string DTDAttribute::getName() {
    return name;
}

string DTDAttribute::getData() {
    return data;
}

string DTDAttribute::getFlag() {
    return flag;
}
