/*
 * DTDAttlist.cpp
 *
 *  Created on: 15 mars 2011
 *      Author: jdepotter1
 */

#include "DTDAttlist.h"

DTDAttlist::DTDAttlist(string attListName, vector<DTDAttribut*> theAttVector) : DTDInfo(TYPE_ATTLIST)
{
	name = attListName;
	attVector = theAttVector;
}

string DTDAttlist::get_attName(){return name;}

vector<DTDAttribut*> DTDAttlist::get_attList(){return attVector;}
