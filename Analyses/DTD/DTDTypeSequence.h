/*
 * DTDTypeSequence.h
 *
 *  Created on: 15 mars 2011
 *      Author: jdepotter1
 */

#ifndef DTDTYPESEQUENCE_H_
#define DTDTYPESEQUENCE_H_

#include <iostream>
#include <string>
#include <vector>
using namespace std;
#include "DTDType.h"

class DTDTypeSequence : public DTDType
{
private:
	vector<DTDType*> vectorType;
public:
	DTDTypeSequence(vector<DTDType*>, string);
	vector<DTDType*> getvectorType();
};

#endif /* DTDTYPESEQUENCE_H_ */
