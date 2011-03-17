/*
 * TypeAtomique.cpp
 *
 *  Created on: 15 mars 2011
 *      Author: jdepotter1
 */

#include "TypeAtomique.h"

TypeAtomique::TypeAtomique(string name)
{
	nameType = name;
}

string TypeAtomique::get_name()
{
	return nameType;
}

TypeAtomique::~TypeAtomique()
{
	// TODO Auto-generated destructor stub
}
