/*
 * DTDTypeChoice.h
 *
 *  Created on: 15 mars 2011
 *      Author: jdepotter1
 */


#ifndef DTDTYPECHOICE_H_
#define DTDTYPECHOICE_H_


#include <iostream>
#include <string>
#include <vector>
using namespace std;
#include "DTDType.h"

class DTDTypeChoice : public DTDType
{
	private:
		vector<DTDType*> vectorType;
	public:
		DTDTypeChoice(vector<DTDType*>, string);
		vector<DTDType*> getvectorType();
};

#endif /* DTDTYPECHOICE_H_ */
