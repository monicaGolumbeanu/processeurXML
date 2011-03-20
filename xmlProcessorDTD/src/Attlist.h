/*
 * Attlist.h
 *
 *  Created on: 15 mars 2011
 *      Author: jdepotter1
 */

#ifndef ATTLIST_H_
#define ATTLIST_H_

#include <iostream>
#include <string>
#include <vector>
#include "Info.h"
#include "Attribut.h"
using namespace std;

class Attlist : public Info
{
	private:
		string name;
		vector<Attribut*> attVector;
	public:
		Attlist(string, vector<Attribut*>);
		string get_attName();
		vector<Attribut*> get_attList();
		virtual ~Attlist();
};

#endif /* ATTLIST_H_ */
