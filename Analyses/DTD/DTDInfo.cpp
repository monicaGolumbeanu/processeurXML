/*
 * DTDInfo.cpp
 *
 *  Created on: 15 mars 2011
 *      Author: jdepotter1
 */

#include "DTDInfo.h"

DTDInfo::DTDInfo(TYPE_INFO identifInfo)
{
	idInfo = identifInfo;
}

TYPE_INFO DTDInfo::get_idInfo()
{
	return idInfo;
}
