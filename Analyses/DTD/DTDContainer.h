/*
 * DTDContainer.h
 *
 *  Created on: 18 mars 2011
 *      Author: jdepotter1
 */

#ifndef DTDCONTAINER_H_
#define DTDCONTAINER_H_

#include <vector>
#include "DTDInfo.h"
using namespace std;

class DTDContainer
{
public:
	DTDContainer(vector<DTDInfo*>);
	vector<DTDInfo*> getVectorInfo();
private:
	vector<DTDInfo*> vectorInfo;
};

#endif /* DTDCONTAINER_H_ */
