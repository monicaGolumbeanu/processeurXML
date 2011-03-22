/*
 * DTDElement.cpp
 *
 *  Created on: 15 mars 2011
 *      Author: jdepotter1
 */

#include "DTDElement.h"

DTDElement::DTDElement(string elementName, DTDType* elementType) : DTDInfo(TYPE_ELEMENT)
{
	name = elementName;
	type = elementType;
}

string DTDElement::get_name()
{
	return name;
}

DTDType* DTDElement::get_type()
{
	return type;
}

