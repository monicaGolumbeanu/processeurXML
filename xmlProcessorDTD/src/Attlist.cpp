/*
 * Attlist.cpp
 *
 *  Created on: 15 mars 2011
 *      Author: jdepotter1
 */

#include "Attlist.h"

Attlist::Attlist(string attListName, vector<Attribut*> theAttVector) : Info(TYPE_ATTLIST)
{
	name = attListName;
	attVector = theAttVector;
}

string Attlist::get_attName(){return name;}

vector<Attribut*> Attlist::get_attList(){return attVector;}

Attlist::~Attlist()
{

}
