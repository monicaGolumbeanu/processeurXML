/*
 * Attlist.cpp
 *
 *  Created on: 15 mars 2011
 *      Author: jdepotter1
 */

#include "Attlist.h"

Attlist::Attlist(list<string> theNameList, list<string> theDataList)
{
	nameList = theNameList;
	dataList = theDataList;
}

Attlist::~Attlist()
{

}
