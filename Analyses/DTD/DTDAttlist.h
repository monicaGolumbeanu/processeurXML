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
#include <vector>
#include "DTDInfo.h"
#include "DTDAttribut.h"
using namespace std;

class DTDAttlist : public DTDInfo
{
	private:
		string name;
		vector<DTDAttribut*> attVector;
	public:
		DTDAttlist(string, vector<DTDAttribut*>);
		string get_attName();
		vector<DTDAttribut*> get_attList();
};

#endif /* DTDATTLIST_H_ */
