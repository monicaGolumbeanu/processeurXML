%{
using namespace std;
#include <stack>
#include <list>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "DTD.h"
#include "DTDElement.h"
#include "DTDAttribute.h"
#include "DTDRule.h"


void yyerror(char *msg);
int  yywrap(void);
int  yylex(void);

DTD             * theDTD; // La racine du document DTD
DTDElement      * currElement;
DTDAttribute    * currAttribute;

DTDRule         * currRule;
DTDRuleAtomic   * currRuleAtomic;
String            keyAttribut;

vector<DTDElement*> probs;

%}

%union { 
   char *s; 
   }

%token ELEMENT ATTLIST CLOSE OPENPAR CLOSEPAR COMMA PIPE FIXED EMPTY ANY PCDATA AST QMARK PLUS CDATA
%token <s> NAME TOKENTYPE DECLARATION STRING NSNAME

%type <s> debut

%%

main: dtd                           
    ;
dtd
: dtd attlist
| dtd element
| /* empty */
	{
		if(theDTD == NULL)
			theDTD = new DTD();
	}
   ;
attlist
: ATTLIST debut att_definition CLOSE
	{
        DTDElement* element;
        currElement = dtd->getElementByName($2);
        if(currElement == NULL) {
            element = new DTDElement($2);
            probs.push_back(element);
        }
	}
;
element
: ELEMENT debut contenu CLOSE
	{
	    currElement = new DTDElement($2);
		currElement->setRule(currRule);
		theDTD->addElement(currElement);
		for(unsigned int i = 0; i < probs.size(); i++)
		    if(probs[i]->getName() == $2)
		        probs.erase(probs.begin() + i);
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
	}
;
attribut
: debut att_type defaut_declaration
	{
	    currAttribute->set_name( $1 );
		currAttlist->addAttribut(currAttribute);
	}
;
att_type
: CDATA
  {
	/*currAttribute->add_data($1);*/ // ne marche pas car ce n'est pas du texte
  }
| TOKENTYPE
  {
	currAttribute->add_data($1);
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
		currAttribute->set_name($1); // A confirmer si enum name ou data
	}
| NSNAME
	{
		currAttribute->set_name($1); // A confirmer si enum name ou data
	}
;
defaut_declaration
: DECLARATION 
	{
		currAttribute = new DTDAttribut();
		currAttribute->set_flag($1);
	}
| STRING     
	{
		currAttribute = new DTDAttribut();
		currAttribute->set_flag($1);
	}
| FIXED STRING 
	{
		currAttribute = new DTDAttribut();
		currAttribute->set_flag($2); // Y a-t-il quelque chose a faire pour le fait que c'est un FIXED??
	}
;

contenu
: EMPTY
	{
		currRule = new DTDRule();
		currRule->set_idType(TYPE_ATOMIC);
		currElement->set_type(currRule);
	}
| ANY
	{
		currRule = new DTDRule();
		currRule->set_idType(TYPE_ATOMIC);
		currElement->set_type(currRule);
	}
| mixed //TODO
| children
;
mixed
:OPENPAR PCDATA contenu_mixed CLOSEPAR cardinalite
    {
        /**/
    }
;
contenu_mixed
:contenu_mixed PIPE debut
|/*empty*/
	{
		currRule = new DTDRule();
	}
;
children
: sequence_ou_choix cardinalite
;
cardinalite
: QMARK
	{
		currRule->set_card(QMARK);
	}
| AST
	{
		currRule->set_card(AST);
	}
| PLUS
	{
		currRule->set_card(PLUS);
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
	currRule->addType( currRule );
}
;
item // Peut-être vaut-il mieux créer un vector
: debut cardinalite
{
	currRule = new DTDTypeSequence();
    currRule->set_name( $1 );
	currElement->addType(currRule);
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
