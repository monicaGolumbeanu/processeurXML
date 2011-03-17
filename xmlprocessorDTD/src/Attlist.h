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
#include <list>
#include "Info.h"
using namespace std;

class Attlist : public Info
{
	private:
		list<string> nameList;
		list<string> dataList;
	public:
		Attlist(list<string>, list<string>);
		list<string> get_nameList();
		list<string> get_dataList();
		virtual ~Attlist();
};

#endif /* ATTLIST_H_ */
