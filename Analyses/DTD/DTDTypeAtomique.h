/*
 * DTDTypeAtomique.h
 *
 *  Created on: 15 mars 2011
 *      Author: jdepotter1
 */
#include <iostream>
#include <string>
#include <vector>
#include "DTDType.h"
using namespace std;


#ifndef DTDTYPEATOMIQUE_H_
#define DTDTYPEATOMIQUE_H_

class DTDTypeAtomique : public DTDType
{
private:
	string nameType;
public:
	void set_name(string);
	DTDTypeAtomique();
	string get_name();
	virtual ~DTDTypeAtomique();
};

#endif /* DTDTYPEATOMIQUE_H_ */
