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

Type::Type(string card)
{
	cardinalite = card;
}

string Type::get_card()
{
	return cardinalite;
}

Type::~Type()
{
}
