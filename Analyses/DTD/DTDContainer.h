/*
 * DTDContainer.h
 *
 *  Created on: 18 mars 2011
 *      Author: jdepotter1
 */

#ifndef DTDCONTAINER_H_
#define DTDCONTAINER_H_

#include <map>
#include "DTDAttlist.h"
#include "DTDElement.h"
using namespace std;

class DTDContainer
{
private:
	map<string, DTDAttlist*> mapAttlist;
	map<string, DTDElement*> mapElement;
public:
	DTDContainer();
	void addAttlist(string, DTDAttlist*);
	void addElement(string, DTDElement*);
	map<string, DTDAttlist*> getVectorAttlist();
	map<string, DTDElement*> getVectorElement();
	void makeLink();
	void printDTD();
};

#endif /* DTDCONTAINER_H_ */
