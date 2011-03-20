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
#include <vector>
using namespace std;
#include "Type.h"

class TypeChoice : public Type
{
	private:
		vector<Type*> vectorType;
	public:
		TypeChoice(vector<Type*>, string);
		vector<Type*> getvectorType();
		virtual ~TypeChoice();
};

#endif /* TYPECHOICE_H_ */
