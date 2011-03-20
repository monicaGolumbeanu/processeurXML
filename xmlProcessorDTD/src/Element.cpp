/*
 * Element.cpp
 *
 *  Created on: 15 mars 2011
 *      Author: jdepotter1
 */

#include "Element.h"

Element::Element(string elementName, Type* elementType) : Info(TYPE_ELEMENT)
{
	name = elementName;
	type = elementType;
}

string Element::get_name()
{
	return name;
}

Type* Element::get_type()
{
	return type;
}

Element::~Element()
{
	// TODO Auto-generated destructor stub
}
