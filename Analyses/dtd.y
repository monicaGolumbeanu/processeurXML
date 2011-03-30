%{
using namespace std;
#include <stack>
#include <list>
#include <cstring>
#include <cstdio>
#include <cstdlib>

#include "DTD.h"
#include "DTDElement.h"
#include "DTDAttribute.h"
#include "DTDRule.h"


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

int correctUnlinked() // ?????
// This function check if there are not define elements needed by attributes
{
    /*for ( unsigned int i=0; i < problems.size(); i++ )
    {
        if (  )
        {
            problems.erase( i );
            i--;
        }
    }*/
    return problems.size();
}

%}

%union { 
   char *s; 
   }

%token ELEMENT ATTLIST CLOSE OPENPAR CLOSEPAR COMMA PIPE FIXED EMPTY ANY PCDATA AST QMARK PLUS CDATA
%token <s> NAME TOKENTYPE DECLARATION STRING NSNAME

%type <s> debut

%%

main: dtd  
    {
        if ( !problems->empty() )
        {
            int nbUnlinked = correctUnlinked();
            if ( unlinked != 0 )
            {
                printf( "There are %d attributes with no element\n", nbUnliked );
                printf( "The elements needed are : \n" );
            }
        }
    }                         
    ;
dtd
: dtd attlist
| dtd element
| /* empty */
	{
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
	{
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
  }
| TOKENTYPE
  {
    currAttribute = new DTDAttribute();
	/*currAttribut->add_data($1);*/
  }
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
|/*empty*/
	{
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
;
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
