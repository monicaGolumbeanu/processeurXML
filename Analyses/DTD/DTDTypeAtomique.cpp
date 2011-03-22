/*
 * DTDTypeAtomique.cpp
 *
 *  Created on: 15 mars 2011
 *      Author: jdepotter1
 */

#include "DTDTypeAtomique.h"

DTDTypeAtomique::DTDTypeAtomique(string name, string card) : DTDType(card, TYPE_ATOMIC)
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
