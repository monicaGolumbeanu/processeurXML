/*
 * DTDAttlist.h
 *
 *  Created on: 15 mars 2011
 *      Author: jdepotter1
 */

#ifndef DTDATTLIST_H_
#define DTDATTLIST_H_

#include <iostream>
#include <string>
#include <map>
#include "DTDAttribut.h"
using namespace std;

class DTDAttlist
{
	private:
		vector<DTDAttribut*> attVector;
	public:
		DTDAttlist();
		void addAttribut(DTDAttribut*);
		void printAttlist();
		vector<DTDAttribut*> getAttribut();
};

#endif /* DTDATTLIST_H_ */
