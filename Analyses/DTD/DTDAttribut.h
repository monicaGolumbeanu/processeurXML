/*
 * DTDAttribut.h
 *
 *  Created on: 18 mars 2011
 *      Author: jdepotter1
 */

#ifndef DTDATTRIBUT_H_
#define DTDATTRIBUT_H_

#include <iostream>
#include <string>
#include "DTDInfo.h"
using namespace std;

class DTDAttribut : public DTDInfo
{
private:
	string name;
	string data;
	string flag;
public:
	DTDAttribut();
	DTDAttribut(string, string, string);
	string get_Name();
	string get_Data();
	string get_Flag();
};

#endif /* DTDATTRIBUT_H_ */
