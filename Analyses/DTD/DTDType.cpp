/*
 * DTDType.cpp
 *
 *  Created on: 15 mars 2011
 *      Author: jdepotter1
 */

#include "DTDType.h"

DTDType::DTDType()
{
}

DTDType::DTDType(string card, TYPE_ID identifType)
{
	cardinalite = card;
	idType = identifType;
}

TYPE_ID DTDType::get_idType()
{
	return idType;
}

string DTDType::get_card()
{
	return cardinalite;
}

