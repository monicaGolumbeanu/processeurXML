/*
 * DTDAttribut.h
 *
 *  Created on: 18 mars 2011
 *      Author: jdepotter1
 */

#ifndef DTDATTRIBUT_H_
#define DTDATTRIBUT_H_

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class DTDAttribut
{
private:
	string name;
	vector<string> data;
	string flag;
public:
	DTDAttribut();
	void set_name(string name);
	void add_data(string attData);
	void set_flag(string flag);
	bool make_link();

	string get_Name();
	vector<string> get_Data();
	string get_Flag();
};

#endif /* DTDATTRIBUT_H_ */
