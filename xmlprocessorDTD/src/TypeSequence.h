/*
 * TypeSequence.h
 *
 *  Created on: 15 mars 2011
 *      Author: jdepotter1
 */

#ifndef TYPESEQUENCE_H_
#define TYPESEQUENCE_H_

#include <iostream>
#include <string>
#include <list>
using namespace std;
#include "Type.h"

class TypeSequence : public Type
{
private:
	list<Type*> listType;
public:
	TypeSequence(list<Type*>);
	list<Type*> getListType();
	virtual ~TypeSequence();
};

#endif /* TYPESEQUENCE_H_ */
