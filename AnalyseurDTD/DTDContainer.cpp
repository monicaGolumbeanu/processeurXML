/*
 * DTDContainer.cpp
 *
 *  Created on: 18 mars 2011
 *      Author: jdepotter1
 */

#include "DTDContainer.h"

DTDContainer::DTDContainer(vector<DTDInfo*> infos)
{
	vectorInfo = infos;
}

vector<DTDInfo*> DTDContainer::getVectorInfo()
{
	return vectorInfo;
}
