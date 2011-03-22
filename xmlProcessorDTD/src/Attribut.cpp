/*
 * Attribut.cpp
 *
 *  Created on: 18 mars 2011
 *      Author: jdepotter1
 */

#include "Attribut.h"


Attribut::Attribut(string attName, string attData, string attFlag) : Info(TYPE_ATTLIST)
{
	name = attName;
	data = attData;
	flag = attFlag;
}

string Attribut::get_Name(){return name;}

string Attribut::get_Data(){return data;}

string Attribut::get_Flag(){return flag;}


Attribut::~Attribut() {
	// TODO Auto-generated destructor stub
}
