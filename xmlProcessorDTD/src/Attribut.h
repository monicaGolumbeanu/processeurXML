/*
 * Attribut.h
 *
 *  Created on: 18 mars 2011
 *      Author: jdepotter1
 */

#ifndef ATTRIBUT_H_
#define ATTRIBUT_H_

#include <iostream>
#include <string>
#include "Info.h"
using namespace std;

class Attribut : public Info
{
private:
	string name;
	string data;
	string flag;
public:
	Attribut();
	Attribut(string, string, string);
	string get_Name();
	string get_Data();
	string get_Flag();
	virtual ~Attribut();
};

#endif /* ATTRIBUT_H_ */
