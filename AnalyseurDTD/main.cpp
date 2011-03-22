//============================================================================
// Name        : xmlprocessorDTD.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <vector>
#include "DTDElement.h"
#include "DTDAttlist.h"
#include "DTDAttribut.h"
#include "DTDType.h"
#include "DTDInfo.h"
#include "DTDTypeAtomique.h"
#include "DTDTypeSequence.h"
#include "DTDTypeChoice.h"
#include "DTDContainer.h"

using namespace std;

void writeTypeName(DTDType* elemType)
{

	if(elemType->get_idType() == TYPE_SEQUENCE)
	{
		DTDTypeSequence* seq = static_cast<DTDTypeSequence*>(elemType);

		vector<DTDType*> vectorType;

		vectorType = seq->getvectorType();

		cout << "(";

		for(unsigned int i = 0; i < vectorType.size(); i++)
		{
			DTDType* theType = vectorType[i];

			writeTypeName(theType);

			if(i != vectorType.size() - 1)
				cout << ",";
		}

		cout << ")" << seq->get_card();
	}
	else if(elemType->get_idType() == TYPE_CHOICE)
	{
		DTDTypeChoice* choice = static_cast<DTDTypeChoice*>(elemType);

		vector<DTDType*> vectorType;

		vectorType = choice->getvectorType();

		cout << "(";

		for(unsigned int i = 0; i < vectorType.size(); i++)
		{
			DTDType* theType = vectorType[i];

			writeTypeName(theType);

			if(i != vectorType.size() - 1)
				cout << "|";
		}

		cout << ")"<< choice->get_card();
	}
	else if(elemType->get_idType() == TYPE_ATOMIC)
	{
		DTDTypeAtomique* atom = static_cast<DTDTypeAtomique*>(elemType);

		cout << atom->get_name() << atom->get_card();
	}
}

void writeElement(DTDElement* element)
{
	cout << "<!ELEMENT " << element->get_name() << " ";

	DTDType* elemType = element->get_type();

	writeTypeName(elemType);

	cout << ">" << endl;
}

void writeAttlist(DTDAttlist* attlist)
{
	cout << "<!ATTLIST " << attlist->get_attName() << " ";

	vector<DTDAttribut*> vectorAtt = attlist->get_attList();

	for(unsigned int i = 0; i < vectorAtt.size(); i++)
	{
		cout << vectorAtt[i]->get_Name() << " " << vectorAtt[i]->get_Data() << " " << vectorAtt[i]->get_Flag() << " ";
	}

	cout << ">" << endl;
}

void writeDTD(DTDContainer dtd)
{
	vector<DTDInfo*> vectorDTD = dtd.getVectorInfo();

	for(unsigned int i = 0; i < vectorDTD.size(); i++)
	{
		if(vectorDTD[i]->get_idInfo() == TYPE_ELEMENT)
		{
			DTDElement* elem = static_cast<DTDElement*>(vectorDTD[i]);

			writeElement(elem);
		}
		else if(vectorDTD[i]->get_idInfo() == TYPE_ATTLIST)
		{
			DTDAttlist* att = static_cast<DTDAttlist*>(vectorDTD[i]);

			writeAttlist(att);
		}

	}

}

int main()
{
	DTDTypeAtomique type1 = DTDTypeAtomique("x", "");
	DTDTypeAtomique type2 = DTDTypeAtomique("y", "");
	DTDTypeAtomique type3 = DTDTypeAtomique("z", "");
	DTDTypeAtomique type4 = DTDTypeAtomique("l", "");

	vector<DTDType*> vectorType1;

	vectorType1.push_back(&type1);
	vectorType1.push_back(&type2);

	vector<DTDType*> vectorType2;

	vectorType2.push_back(&type3);
	vectorType2.push_back(&type4);

	DTDTypeSequence seq = DTDTypeSequence(vectorType1, "");

	DTDTypeChoice choix = DTDTypeChoice(vectorType2, "");

	vector<DTDType*> vectorTypeComplet;

	vectorTypeComplet.push_back(&seq);
	vectorTypeComplet.push_back(&choix);

	DTDTypeSequence seqComplet = DTDTypeSequence(vectorTypeComplet, "*");

	DTDElement* element = new DTDElement("a", &seqComplet);

	vector<DTDAttribut*> vectorAttr;

	DTDAttribut att1 = DTDAttribut("att1", "CDATA", "#IMPLIED");
	DTDAttribut att2 = DTDAttribut("att2", "CDATA", "#IMPLIED");

	vectorAttr.push_back(&att1);
	vectorAttr.push_back(&att2);

	DTDAttlist* attlist = new DTDAttlist("status", vectorAttr);

	vector<DTDInfo*> vectorInfo;

	vectorInfo.push_back(element);
	vectorInfo.push_back(attlist);

	DTDContainer newDtd = DTDContainer(vectorInfo);

	writeDTD(newDtd);

	return 0;
}
