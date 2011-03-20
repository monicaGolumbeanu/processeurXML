/*
 * TypeChoice.cpp
 *
 *  Created on: 15 mars 2011
 *      Author: jdepotter1
 */

#include "TypeChoice.h"

TypeChoice::TypeChoice(vector<Type*> vectorTypeChoice, string card) : Type(card, TYPE_CHOICE)
{
	vectorType = vectorTypeChoice;
}

vector<Type*> TypeChoice::getvectorType()
{
	return vectorType;
}


TypeChoice::~TypeChoice()
{

}
