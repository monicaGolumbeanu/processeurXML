/*
 * DTDTypeChoice.cpp
 *
 *  Created on: 15 mars 2011
 *      Author: jdepotter1
 */

#include "DTDTypeChoice.h"

DTDTypeChoice::DTDTypeChoice() : DTDType(TYPE_CHOICE)
{
}

void DTDTypeChoice::add_type(DTDType* newType)
{
	vectorType.push_back(newType);
}

vector<DTDType*> DTDTypeChoice::getvectorType()
{
	return vectorType;
}
