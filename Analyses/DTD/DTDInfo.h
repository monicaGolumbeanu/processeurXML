/*
 * DTDInfo.h
 *
 *  Created on: 15 mars 2011
 *      Author: jdepotter1
 */

#ifndef DTDINFO_H_
#define DTDINFO_H_

typedef enum {
	TYPE_ELEMENT, TYPE_ATTLIST
} TYPE_INFO;

class DTDInfo {
public:
	DTDInfo(TYPE_INFO);
	TYPE_INFO get_idInfo();
private:
	TYPE_INFO idInfo;
};

#endif /* DTDINFO_H_ */
