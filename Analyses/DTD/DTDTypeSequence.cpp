/*
 * DTDTypeSequence.cpp
 *
 *  Created on: 15 mars 2011
 *      Author: jdepotter1
 */

#include "DTDTypeSequence.h"

DTDTypeSequence::DTDTypeSequence(vector<DTDType*> vectorTypeSeq, string card) : DTDType(card, TYPE_SEQUENCE)
{
	vectorType = vectorTypeSeq;
}

vector<DTDType*> DTDTypeSequence::getvectorType()
{
	return vectorType;
}
