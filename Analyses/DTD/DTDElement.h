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
#include "DTDInfo.h"
using namespace std;

class DTDElement : public DTDInfo
{
	private:
		string name;
		DTDType* type;

	public:
		DTDElement(string, DTDType*);
		string get_name();
		DTDType* get_type();
};

#endif /* DTDELEMENT_H_ */
