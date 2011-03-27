/*
 * DTDAttribut.cpp
 *
 *  Created on: 18 mars 2011
 *      Author: jdepotter1
 */

#include "DTDAttribut.h"


DTDAttribut::DTDAttribut()
{
}

void DTDAttribut::set_name(string attName){name = attName;}

void DTDAttribut::add_data(string attData){data.push_back(attData);}

void DTDAttribut::set_flag(string attFlag){flag = attFlag;}

string DTDAttribut::get_Name(){return name;}

vector<string> DTDAttribut::get_Data(){return data;}

string DTDAttribut::get_Flag(){return flag;}

