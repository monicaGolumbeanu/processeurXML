/*
 * Info.cpp
 *
 *  Created on: 15 mars 2011
 *      Author: jdepotter1
 */

#include "Info.h"

Info::Info(TYPE_INFO identifInfo)
{
	idInfo = identifInfo;
}

TYPE_INFO Info::get_idInfo()
{
	return idInfo;
}


Info::~Info() {
	// TODO Auto-generated destructor stub
}
