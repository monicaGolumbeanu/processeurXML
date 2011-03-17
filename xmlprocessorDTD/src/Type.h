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

class Type
{
private:
		string cardinalite;
	public:
		Type();
		Type(string);
		string get_card();
		virtual ~Type();
};

#endif /* TYPE_H_ */
