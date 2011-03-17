/*
 * TypeChoice.h
 *
 *  Created on: 15 mars 2011
 *      Author: jdepotter1
 */


#ifndef TYPECHOICE_H_
#define TYPECHOICE_H_


#include <iostream>
#include <string>
#include <list>
using namespace std;
#include "Type.h"

class TypeChoice : public Type
{
	private:
		list<Type*> listType;
	public:
		TypeChoice(list<Type*>);
		list<Type*> getListType();
		virtual ~TypeChoice();
};

#endif /* TYPECHOICE_H_ */
