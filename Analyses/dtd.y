//%{
using namespace std;
#include <stack>
#include <list>
#include <vector>
#include <map>
#include <cstring>
#include <cstdio>
#include <cstdlib>

#include "DTD.h"
#include "DTDElement.h"
#include "DTDAttribute.h"
#include "DTDRule.h"
#include "DTDRuleChoice.h"
#include "DTDRuleAtomic.h"
#include "DTDRuleSequence.h"


void yyerror(char *msg);
int  yywrap(void);
int  yylex(void);

DTD             * high = NULL; // DTD root
DTDElement      * currElement;
DTDAttribute    * currAttribute;

DTDRule         * currRule;
DTDRuleAtomic   * currRuleAtomique;
string            keyAttribute;

vector<DTDAttribute*> currAttributes;
vector<DTDElement*>   problems;
typedef map<DTDRule*, vector<string> > MapIncompleteRules;
MapIncompleteRules incomplete;

void linkRules() {
    MapIncompleteRules::const_iterator end = incomplete.end();
    vector<string> names;
    DTDRuleChoice *ruleChoice;
    DTDRuleSequence *ruleSequence;
    DTDRuleAtomic *ruleAtomic;
    DTDElement *elem;
    for (MapIncompleteRules::const_iterator it = incomplete.begin(); it != end; ++it) {
        names = it->second;
        switch(it->first->getType()) {
            case RULE_CHOICE:
                ruleChoice = static_cast<DTDRuleChoice*>(it->first);
                for(unsigned int i = 0; i < names.size(); i++) {
                    elem = high->getElementByName(names[i]);
                    if(elem != NULL)
                        cout << "Error! Element " << names[i] << "not defined.";
                    else
                        ruleChoice->addRule(elem->getRule());
                }
                break;
            case RULE_SEQUENCE:
                ruleSequence = static_cast<DTDRuleSequence*>(it->first);
                for(unsigned int i = 0; i < names.size(); i++) {
                    elem = high->getElementByName(names[i]);
                    if(elem != NULL)
                        cout << "Error! Element " << names[i] << "not defined.";
                    else
                        ruleSequence->addRule(elem->getRule());
                }
                break;
            case RULE_ATOMIC:
                ruleAtomic = static_cast<DTDRuleAtomic*>(it->first);
                for(unsigned int i = 0; i < names.size(); i++) {
                    elem = high->getElementByName(names[i]);
                    if(elem != NULL)
                        cout << "Error! Element " << names[i] << "not defined.";
                    else
                        ruleAtomic->setRule(elem->getRule());
                }
                break;
        }
    }
}

//%}

/*%union {
   char *s; 
   }

%token ELEMENT ATTLIST CLOSE OPENPAR CLOSEPAR COMMA PIPE FIXED EMPTY ANY PCDATA AST QMARK PLUS CDATA
%token <s> NAME TOKENTYPE DECLARATION STRING NSNAME

%type <s> debut

%%

main: dtd  
    {
        if ( !problems.empty() )
        {
            printf( "There are %d attributes with no element\n", problems.size() );
            printf( "The elements needed are : \n" );
        }
    }                         
    ;
dtd
: dtd attlist
| dtd element*/
//| /* empty */
/*	{
		if(high == NULL) 
			high = new DTD();
	}
   ;
attlist
: ATTLIST debut att_definition CLOSE
    {
        DTDElement * elem = dtd->getElementByName($2);
        if ( elem == NULL ) { 
            elem = new DTDElement($2);
            problems.push_back(elem);
        }
        while ( currAttributes.size() != 0 )
        {
            elem->addAttribute( currAttributes.pop_back(0) );
        }
    }
;
element
: ELEMENT debut contenu CLOSE
	{
	    currElement = new DTDElement($2);
		currElement->setRule(currRule);
		high->addElement(currElement);
	}
;
debut
: NAME
| NSNAME
;
att_definition
: att_definition attribut
| /* empty */
/*	{
		currAttributes.clear();
	}
;
attribut
: debut att_type defaut_declaration
	{
	    currAttribute->setName( $1 );
		currAtttributes.push_back( currAttribute );
	}
;
att_type
: CDATA
  {
    currAttribute = new DTDAttribute();
	/*currAttribut->add_data($1);*/ // ne marche pas car ce n'est pas du texte
//  }
//| TOKENTYPE
//  {
//    currAttribute = new DTDAttribute();
	/*currAttribut->add_data($1);*/
/*  }
| type_enumere
;
type_enumere
: OPENPAR liste_enum_plus CLOSEPAR
;
liste_enum_plus
: liste_enum PIPE item_enum
;
liste_enum
: item_enum
| liste_enum PIPE item_enum
;
item_enum
: NAME
	{
		currAttribute->setName($1); // A confirmer si enum name ou data
	}
| NSNAME
	{
		currAttribute->setName($1); // A confirmer si enum name ou data
	}
;
defaut_declaration
: DECLARATION 
	{
		currAttribute->setFlag($1); 
	}
| STRING     
	{
		currAttribute->setFlag($1); 
	}
| FIXED STRING 
	{
		currAttribute->setFlag($2);
	}
;

contenu
: EMPTY
	{
		currRule = new DTDRuleFinal(true);
	}
| ANY
	{
	    currRule = new DTDRuleFinal();
	}
| mixed //TODO
| children
;
mixed
:OPENPAR PCDATA contenu_mixed CLOSEPAR cardinalite
    {
        currRule->addRule(new DTDRuleFinal(false));
    }
;
contenu_mixed
:contenu_mixed PIPE debut
    {
        currRule->addRule(new DTDRuleAtomic(
    }
|/*empty*/
/*	{
		currRule = new DTDRuleChoice();
	}
;
children
: sequence_ou_choix cardinalite
;
cardinalite
: QMARK
	{
		currType->set_card(QMARK);
	}
| AST
	{
		currType->set_card(AST);
	}
| PLUS
	{
		currType->set_card(PLUS);
	}
| /*empty*/
/*;
sequence_ou_choix
: sequence
| choix
;
sequence
:OPENPAR liste_sequence CLOSEPAR
;
liste_sequence
: item
| liste_sequence COMMA item
{
	currType->addType( currType );
}
;
item // Peut-être vaut-il mieux créer un vector
: debut cardinalite
{
	currType = new DTDTypeSequence();
    currType->set_name( $1 );
	currElement->addType(currType);
}
| children
;
choix
: OPENPAR liste_choix_plus CLOSEPAR
;
liste_choix_plus
: liste_choix PIPE item
;
liste_choix
: liste_choix PIPE item
| item
;

%%
