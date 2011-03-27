/*
 * DTDTypeSequence.cpp
 *
 *  Created on: 15 mars 2011
 *      Author: jdepotter1
 */

#include "DTDTypeSequence.h"

DTDTypeSequence::DTDTypeSequence() : DTDType(TYPE_SEQUENCE)
{
}

void DTDTypeSequence::add_type(DTDType* type)
{
	vectorType.push_back(type);
}

vector<DTDType*> DTDTypeSequence::getvectorType()
{
	return vectorType;
}
