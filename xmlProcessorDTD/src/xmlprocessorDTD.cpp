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
#include "Element.h"
#include "Attlist.h"
#include "Attribut.h"
#include "Type.h"
#include "Info.h"
#include "TypeAtomique.h"
#include "TypeSequence.h"
#include "TypeChoice.h"
#include "DTDContainer.h"


using namespace std;

void writeTypeName(Type* elemType)
{

	if(elemType->get_idType() == TYPE_SEQUENCE)
	{
		TypeSequence* seq = static_cast<TypeSequence*>(elemType);

		vector<Type*> vectorType;

		vectorType = seq->getvectorType();

		cout << "(";

		for(unsigned int i = 0; i < vectorType.size(); i++)
		{
			Type* theType = vectorType[i];

			writeTypeName(theType);

			if(i != vectorType.size() - 1)
				cout << ",";
		}

		cout << ")" << seq->get_card();
	}
	else if(elemType->get_idType() == TYPE_CHOICE)
	{
		TypeChoice* choice = static_cast<TypeChoice*>(elemType);

		vector<Type*> vectorType;

		vectorType = choice->getvectorType();

		cout << "(";

		for(unsigned int i = 0; i < vectorType.size(); i++)
		{
			Type* theType = vectorType[i];

			writeTypeName(theType);

			if(i != vectorType.size() - 1)
				cout << "|";
		}

		cout << ")"<< choice->get_card();
	}
	else if(elemType->get_idType() == TYPE_ATOMIC)
	{
		TypeAtomique* atom = static_cast<TypeAtomique*>(elemType);

		cout << atom->get_name() << atom->get_card();
	}
}

void writeElement(Element* element)
{
	cout << "<!ELEMENT " << element->get_name() << " ";

	Type* elemType = element->get_type();

	writeTypeName(elemType);

	cout << ">" << endl;
}

void writeAttlist(Attlist* attlist)
{
	cout << "<!ATTLIST " << attlist->get_attName() << " ";

	vector<Attribut*> vectorAtt = attlist->get_attList();

	for(unsigned int i = 0; i < vectorAtt.size(); i++)
	{
		cout << vectorAtt[i]->get_Name() << " " << vectorAtt[i]->get_Data() << " " << vectorAtt[i]->get_Flag() << " ";
	}

	cout << ">" << endl;
}

void writeDTD(DTDContainer dtd)
{
	vector<Info*> vectorDTD = dtd.getVectorInfo();

	for(unsigned int i = 0; i < vectorDTD.size(); i++)
	{
		if(vectorDTD[i]->get_idInfo() == TYPE_ELEMENT)
		{
			Element* elem = static_cast<Element*>(vectorDTD[i]);

			writeElement(elem);
		}
		else if(vectorDTD[i]->get_idInfo() == TYPE_ATTLIST)
		{
			Attlist* att = static_cast<Attlist*>(vectorDTD[i]);

			writeAttlist(att);
		}

	}

}

int main()
{
	TypeAtomique type1 = TypeAtomique("x", "");
	TypeAtomique type2 = TypeAtomique("y", "");
	TypeAtomique type3 = TypeAtomique("z", "");
	TypeAtomique type4 = TypeAtomique("l", "");

	vector<Type*> vectorType1;

	vectorType1.push_back(&type1);
	vectorType1.push_back(&type2);

	vector<Type*> vectorType2;

	vectorType2.push_back(&type3);
	vectorType2.push_back(&type4);

	TypeSequence seq = TypeSequence(vectorType1, "");

	TypeChoice choix = TypeChoice(vectorType2, "");

	vector<Type*> vectorTypeComplet;

	vectorTypeComplet.push_back(&seq);
	vectorTypeComplet.push_back(&choix);

	TypeSequence seqComplet = TypeSequence(vectorTypeComplet, "*");

	Element* element = new Element("a", &seqComplet);

	vector<Attribut*> vectorAttr;

	Attribut att1 = Attribut("att1", "CDATA", "#IMPLIED");
	Attribut att2 = Attribut("att2", "CDATA", "#IMPLIED");

	vectorAttr.push_back(&att1);
	vectorAttr.push_back(&att2);

	Attlist* attlist = new Attlist("status", vectorAttr);

	vector<Info*> vectorInfo;

	vectorInfo.push_back(element);
	vectorInfo.push_back(attlist);

	DTDContainer newDtd = DTDContainer(vectorInfo);

	writeDTD(newDtd);

	return 0;
}
