/*
 * DTDElement.cpp
 *
 *  Created on: 15 mars 2011
 *      Author: jdepotter1
 */

#include "DTDElement.h"

DTDElement::DTDElement()
{}

void DTDElement::set_type(DTDType* elementType)
{
	type = elementType;
}

DTDType* DTDElement::get_type()
{
	return type;
}

void DTDElement::set_Attlist(DTDAttlist* attList)
{
	attl = attList;
}

vector<DTDAttribut*>* DTDElement::get_Attributs()
{
	return (&(attl->getAttribut()));
}

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

		cout << ")";

		switch(seq->get_card())
		{
			case QMARK : cout << "?"; break;
			case AST : cout << "*"; break;
			case PLUS : cout << "+"; break;
			case EMPTY : cout << ""; break;
		}
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

		cout << ")";

		switch(choice->get_card())
		{
			case QMARK : cout << "?"; break;
			case AST : cout << "*"; break;
			case PLUS : cout << "+"; break;
			case EMPTY : cout << ""; break;
		}
	}
	else if(elemType->get_idType() == TYPE_ATOMIC)
	{
		DTDTypeAtomique* atom = static_cast<DTDTypeAtomique*>(elemType);

		cout << atom->get_name();

		switch(atom->get_card())
		{
			case QMARK : cout << "?"; break;
			case AST : cout << "*"; break;
			case PLUS : cout << "+"; break;
			case EMPTY : cout << ""; break;
		}
	}
}

void DTDElement::printElement()
{
	DTDType* elemType = get_type();

	writeTypeName(elemType);
}


