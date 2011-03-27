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

typedef enum
{
	TYPE_SEQUENCE, TYPE_CHOICE, TYPE_ATOMIC
} TYPE_ID;

typedef enum
{
	QMARK, AST, PLUS, EMPTY
} CARD;

class DTDType
{
protected:
		CARD cardinalite;
private:
		TYPE_ID idType;
	public:
		DTDType();
		DTDType(TYPE_ID);
		void set_card(CARD);
		TYPE_ID get_idType();
		CARD get_card();
};

#endif /* DTDTYPE_H_ */
