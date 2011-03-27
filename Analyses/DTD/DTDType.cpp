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

DTDType::DTDType(TYPE_ID identifType)
{
	idType = identifType;
}

void DTDType::set_card(CARD card)
{
	cardinalite = card;
}

TYPE_ID DTDType::get_idType()
{
	return idType;
}

CARD DTDType::get_card()
{
	return cardinalite;
}

