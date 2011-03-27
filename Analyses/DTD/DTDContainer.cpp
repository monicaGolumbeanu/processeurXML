/*
 * DTDContainer.cpp
 *
 *  Created on: 18 mars 2011
 *      Author: jdepotter1
 */

#include "DTDContainer.h"

DTDContainer::DTDContainer()
{

}

void DTDContainer::printDTD()
{
	for(map<string, DTDAttlist*>::iterator i = mapAttlist.begin(); i != mapAttlist.end(); i++)
	{
		cout << "<!ATTLIST " <<  " " << i->first << " ";

		(i->second)->printAttlist();

		cout << ">" << endl;
	}

	for(map<string, DTDElement*>::iterator i = mapElement.begin(); i != mapElement.end(); i++)
	{
		cout << "<!ELEMENT " <<  " " << i->first << " ";

		(i->second)->printElement();

		cout << ">" << endl;
	}
}

void DTDContainer::addAttlist(string name, DTDAttlist* att)
{
	mapAttlist[name] = att;
}

void DTDContainer::addElement(string name, DTDElement* elem)
{
	mapElement[name] = elem;
}

map<string, DTDAttlist*> DTDContainer::getVectorAttlist()
{
	return mapAttlist;
}

map<string, DTDElement*> DTDContainer::getVectorElement()
{
	return mapElement;
}

void DTDContainer::makeLink()
{
	for(map<string, DTDElement*>::iterator i = mapElement.begin(); i != mapElement.end(); i++)
	{
		string elemName = i->first;

		if(mapAttlist.find(elemName) != mapAttlist.end())
		{
			DTDElement* elem = i->second;
			DTDAttlist* attl = mapAttlist.find(elemName)->second;
			elem->set_Attlist(attl);
		}
	}
}


