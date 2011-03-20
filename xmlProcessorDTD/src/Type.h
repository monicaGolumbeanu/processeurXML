/*
 * Type.h
 *
 *  Created on: 15 mars 2011
 *      Author: jdepotter1
 */

#ifndef TYPE_H_
#define TYPE_H_

#include <iostream>
#include <string>
#include <list>
using namespace std;

typedef enum {
	TYPE_SEQUENCE, TYPE_CHOICE, TYPE_ATOMIC
} TYPE_ID;

class Type
{
private:
		string cardinalite;
		TYPE_ID idType;
	public:
		Type();
		Type(string, TYPE_ID);
		TYPE_ID get_idType();
		string get_card();
		virtual ~Type();
};

#endif /* TYPE_H_ */
