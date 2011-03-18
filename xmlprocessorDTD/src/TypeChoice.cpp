/*
 * TypeChoice.cpp
 *
 *  Created on: 15 mars 2011
 *      Author: jdepotter1
 */

#include "TypeChoice.h"

TypeChoice::TypeChoice(list<Type*> listTypeChoice)
{
	listType = listTypeChoice;
}

list<Type*> TypeChoice::getListType()
{
	return listType;
}


TypeChoice::~TypeChoice()
{

}
