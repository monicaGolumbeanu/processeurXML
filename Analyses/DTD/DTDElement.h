/*
 * DTDElement.h
 *
 *  Created on: 15 mars 2011
 *      Author: jdepotter1
 */
#ifndef DTDELEMENT_H_
#define DTDELEMENT_H_

#include <iostream>
#include <string>
#include "DTDType.h"
#include "DTDElement.h"
#include "DTDTypeSequence.h"
#include "DTDTypeChoice.h"
#include "DTDTypeAtomique.h"
#include "DTDAttlist.h"
#include "DTDAttribut.h"

using namespace std;

class DTDElement
{
	private:
		DTDAttlist* attl;
		DTDType* type;

	public:
		DTDElement();
		vector<DTDAttribut*>* get_Attributs();
		void set_Attlist(DTDAttlist*);
		void set_type(DTDType*);
		DTDType* get_type();
		void printElement();

};

#endif /* DTDELEMENT_H_ */
