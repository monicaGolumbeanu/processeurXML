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
#include <vector>
using namespace std;
#include "Type.h"

class TypeSequence : public Type
{
private:
	vector<Type*> vectorType;
public:
	TypeSequence(vector<Type*>, string);
	vector<Type*> getvectorType();
	virtual ~TypeSequence();
};

#endif /* TYPESEQUENCE_H_ */
