/*
 * DTDAttlist.cpp
 *
 *  Created on: 15 mars 2011
 *      Author: jdepotter1
 */

#include "DTDAttlist.h"

DTDAttlist::DTDAttlist()
{}

void DTDAttlist::addAttribut(DTDAttribut* att)
{
	attVector.push_back(att);
}

vector<DTDAttribut*> DTDAttlist::getAttribut()
{
	return attVector;
}

void DTDAttlist::printAttlist()
{
	for(unsigned int i = 0; i < attVector.size(); i++)
	{
		cout << attVector[i]->get_Name() << " ";

		for(unsigned int j = 0; j < (attVector[i]->get_Data()).size(); j++)
		{
			cout << "(";

			if(j < (attVector[i]->get_Data()).size() - 1)
				cout << attVector[i]->get_Data()[j] << "|";
			else
				cout << attVector[i]->get_Data()[j];

			cout << ") ";
		}
	}
}
