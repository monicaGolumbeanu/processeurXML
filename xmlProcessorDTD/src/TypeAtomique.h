/*
 * TypeAtomique.h
 *
 *  Created on: 15 mars 2011
 *      Author: jdepotter1
 */
#include <iostream>
#include <string>
#include <vector>
#include "Type.h"
using namespace std;


#ifndef TYPEATOMIQUE_H_
#define TYPEATOMIQUE_H_

class TypeAtomique : public Type
{
private:
	string nameType;
public:
	TypeAtomique(string, string);
	string get_name();
	virtual ~TypeAtomique();
};

#endif /* TYPEATOMIQUE_H_ */
