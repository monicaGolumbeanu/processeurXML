/*
 * TypeSequence.cpp
 *
 *  Created on: 15 mars 2011
 *      Author: jdepotter1
 */

#include "TypeSequence.h"

TypeSequence::TypeSequence(vector<Type*> vectorTypeSeq, string card) : Type(card, TYPE_SEQUENCE)
{
	vectorType = vectorTypeSeq;
}

vector<Type*> TypeSequence::getvectorType()
{
	return vectorType;
}

TypeSequence::~TypeSequence()
{

}
