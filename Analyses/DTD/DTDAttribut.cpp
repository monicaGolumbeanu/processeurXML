/*
 * DTDAttribut.cpp
 *
 *  Created on: 18 mars 2011
 *      Author: jdepotter1
 */

#include "DTDAttribut.h"


DTDAttribut::DTDAttribut(string attName, string attData, string attFlag) : DTDInfo(TYPE_ATTLIST)
{
	name = attName;
	data = attData;
	flag = attFlag;
}

string DTDAttribut::get_Name(){return name;}

string DTDAttribut::get_Data(){return data;}

string DTDAttribut::get_Flag(){return flag;}

