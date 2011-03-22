/*
 * Element.h
 *
 *  Created on: 15 mars 2011
 *      Author: jdepotter1
 */
#ifndef ELEMENT_H_
#define ELEMENT_H_

#include <iostream>
#include <string>
#include "Type.h"
#include "Info.h"
using namespace std;

class Element : public Info
{
	private:
		string name;
		Type* type;

	public:
		Element(string, Type*);
		string get_name();
		Type* get_type();
		virtual ~Element();
};

#endif /* ELEMENT_H_ */
