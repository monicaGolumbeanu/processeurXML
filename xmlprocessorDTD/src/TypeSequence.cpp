/*
 * TypeSequence.cpp
 *
 *  Created on: 15 mars 2011
 *      Author: jdepotter1
 */

#include "TypeSequence.h"

TypeSequence::TypeSequence(list<Type*> listTypeSeq)
{
	listType = listTypeSeq;
}

list<Type*> TypeSequence::getListType()
{
	return listType;
}

TypeSequence::~TypeSequence()
{

}
