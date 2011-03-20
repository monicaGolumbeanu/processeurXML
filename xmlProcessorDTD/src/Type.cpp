/*
 * Type.cpp
 *
 *  Created on: 15 mars 2011
 *      Author: jdepotter1
 */

#include "Type.h"

Type::Type()
{
}

Type::Type(string card, TYPE_ID identifType)
{
	cardinalite = card;
	idType = identifType;
}

TYPE_ID Type::get_idType()
{
	return idType;
}

string Type::get_card()
{
	return cardinalite;
}

Type::~Type()
{
}
