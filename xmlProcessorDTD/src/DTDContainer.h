/*
 * DTDContainer.h
 *
 *  Created on: 18 mars 2011
 *      Author: jdepotter1
 */

#ifndef DTDCONTAINER_H_
#define DTDCONTAINER_H_

#include <vector>
#include "Info.h"
using namespace std;

class DTDContainer
{
private:
	vector<Info*> vectorInfo;
public:
	DTDContainer(vector<Info*>);
	vector<Info*> getVectorInfo();
	virtual ~DTDContainer();
};

#endif /* DTDCONTAINER_H_ */
