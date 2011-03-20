/*
 * Info.h
 *
 *  Created on: 15 mars 2011
 *      Author: jdepotter1
 */

#ifndef INFO_H_
#define INFO_H_

typedef enum {
	TYPE_ELEMENT, TYPE_ATTLIST
} TYPE_INFO;

class Info {
private:
	TYPE_INFO idInfo;
public:
	Info(TYPE_INFO);
	TYPE_INFO get_idInfo();
	virtual ~Info();
};

#endif /* INFO_H_ */
