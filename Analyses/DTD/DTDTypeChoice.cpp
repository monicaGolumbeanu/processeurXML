/*
 * DTDTypeChoice.cpp
 *
 *  Created on: 15 mars 2011
 *      Author: jdepotter1
 */

#include "DTDTypeChoice.h"

DTDTypeChoice::DTDTypeChoice(vector<DTDType*> vectorTypeChoice, string card) : DTDType(card, TYPE_CHOICE)
{
	vectorType = vectorTypeChoice;
}

vector<DTDType*> DTDTypeChoice::getvectorType()
{
	return vectorType;
}
