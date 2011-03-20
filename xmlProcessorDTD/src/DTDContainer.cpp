/*
 * DTDContainer.cpp
 *
 *  Created on: 18 mars 2011
 *      Author: jdepotter1
 */

#include "DTDContainer.h"

DTDContainer::DTDContainer(vector<Info*> infos)
{
	vectorInfo = infos;
}

vector<Info*> DTDContainer::getVectorInfo()
{
	return vectorInfo;
}


DTDContainer::~DTDContainer()
{
	// TODO Auto-generated destructor stub
}
