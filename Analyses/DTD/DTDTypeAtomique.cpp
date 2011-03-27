/*
 * DTDTypeAtomique.cpp
 *
 *  Created on: 15 mars 2011
 *      Author: jdepotter1
 */

#include "DTDTypeAtomique.h"

DTDTypeAtomique::DTDTypeAtomique() : DTDType(TYPE_ATOMIC)
{
}

void DTDTypeAtomique::set_name(string name)
{
	nameType = name;
}

string DTDTypeAtomique::get_name()
{
	return nameType;
}

DTDTypeAtomique::~DTDTypeAtomique()
{
	// TODO Auto-generated destructor stub
}
