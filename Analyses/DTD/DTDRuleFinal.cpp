#include <iostream>
#include <vector>
#include <XMLNode.h>
#include <XMLTag.h>
#include <DTDRuleFinal.h>
#include <InvalidElementException.h>
#include <EmptyTagException.h>
#include <ExtraElementFoundException.h>
//*
#ifndef DEBUG
#define DEBUG
#endif
//*/
using namespace DTDExceptions;

DTDRuleFinal::DTDRuleFinal() : DTDRule(RULE_FINAL) {
    empty = false;
    any = false;
}

bool DTDRuleFinal::isEmpty() {
    return empty;
}

void DTDRuleFinal::setEmpty(bool empty) {
    this->empty = empty;
}

bool DTDRuleFinal::isAny() {
    return any;
}

void DTDRuleFinal::setAny(bool any) {
    this->any = any;
}

bool DTDRuleFinal::validate(XMLTag* tag) {
    vector<XMLNode*>* children;
    //==================
    //Rule for empty tag
    //==================
    if(isEmpty()) {
        if(tag->hasChildren()) {
            throw ExtraElementFoundException(tag, (*tag->getChildren())[0]);
            return false;
        }
        else {
#ifdef DEBUG
            cout << "[VALIDATED] " << getTagName() << " --> ";
            cout << "<EMPTY>" << endl;
#endif
            return true;
        }
    }
    //============
    //Rule for ANY
    //============
    else if (isAny()) {
#ifdef DEBUG
            cout << "[VALIDATED] " << getTagName() << " --> ";
            cout << "<ANY>" << endl;
#endif
        return true;
    }
    //========================
    //Rule for #PCDATA content
    //========================
    else {
        if(!tag->hasChildren()) {
            throw EmptyTagException(tag);
            return false;
        }
        else {
            children = tag->getChildren();
            if ((*children)[0]->getType() != NODE_XMLPCDATA) {
                throw InvalidElementException(tag, (*children)[0]);
                return false;
            }
            else if (children->size() > 1) {
                throw ExtraElementFoundException(tag, (*children)[1]);
                return false;
            }
            else {
#ifdef DEBUG
                cout << "[VALIDATED] " << getTagName() << " --> ";
                cout << "#PCDATA" << endl;
#endif
                return true;
            }
        }
    }
}int DTDRuleFinal::partialValidate(XMLTag* tag, unsigned int position) {
    vector<XMLNode*>* children = tag->getChildren();
    //===============
    //Wrong user call
    //===============
    if(position >= children->size())
        return -1;
    //=======================
    //Trying to match #PCDATA
    //=======================
    if ((*children)[position]->getType() != NODE_XMLPCDATA) {
        throw InvalidElementException(tag, (*children)[position]);
        return position;
    }
    else {
#ifdef DEBUG
        //@TODO: Add ANY rule
        cout << "[VALIDATED] " << getTagName() << " --> ";
        cout << (isEmpty() ? "<EMPTY>" : "#PCDATA") << endl;
#endif
        return position+1;
    }
}
    
void DTDRuleFinal::print( )
{
    /*if(this->getTagName() == "")
    {*/
        if (this->isEmpty())
            cout << "EMPTY";
        else if (this->isAny())
            cout << "ANY";
        else
            cout << "#PCDATA";
    /*}
    else {
        cout << "test" << this->getTagName();
        cout << this->getCardinality();
    }*/
    /*if (this->isEmpty())
        cout << "(EMPTY)";
    else if (this->isAny())
        cout << "(ANY)";*/
}

