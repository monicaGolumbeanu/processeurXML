/*
 * DTDType.h
 *
 *  Created on: 15 mars 2011
 *      Author: jdepotter1
 */

#ifndef DTDTYPE_H_
#define DTDTYPE_H_

#include <iostream>
#include <string>
#include <list>
using namespace std;

typedef enum {
	TYPE_SEQUENCE, TYPE_CHOICE, TYPE_ATOMIC
} TYPE_ID;

class DTDType
{
private:
		string cardinalite;
		TYPE_ID idType;
	public:
		DTDType();
		DTDType(string, TYPE_ID);
		TYPE_ID get_idType();
		string get_card();
};

#endif /* DTDTYPE_H_ */
