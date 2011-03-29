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

DTD    * high; // La racine du document DTD
DTDElement      * currElement;
DTDAttribute     * currAttribut;

DTDRule         * currType;
DTDRuleAtomic * currTypeAtomique;
String            keyAttribut;

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
		if(high == NULL) 
			high = new DTD();
	}
   ;
attlist
: ATTLIST debut att_definition CLOSE
	{
	    //currAttlist->set_name($2);
		high->addAttList(currAttlist);
	}
;
element
: ELEMENT debut contenu CLOSE
	{
	    currElement = new DTDElement();
	    currElement->set_name($2);
		currElement->set_type(currType);
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
		currAttlist = new DTDAttlist();
	}
;
attribut
: debut att_type defaut_declaration
	{
	    currAttribut->set_name( $1 );
		currAttlist->addAttribut(currAttribut);
	}
;
att_type
: CDATA
  {
	/*currAttribut->add_data($1);*/ // ne marche pas car ce n'est pas du texte
  }
| TOKENTYPE
  {
	currAttribut->add_data($1);
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
		currAttribut->set_name($1); // A confirmer si enum name ou data
	}
| NSNAME
	{
		currAttribut->set_name($1); // A confirmer si enum name ou data
	}
;
defaut_declaration
: DECLARATION 
	{
		currAttribut = new DTDAttribut();
		currAttribut->set_flag($1); 
	}
| STRING     
	{
		currAttribut = new DTDAttribut();
		currAttribut->set_flag($1); 
	}
| FIXED STRING 
	{
		currAttribut = new DTDAttribut();
		currAttribut->set_flag($2); // Y a-t-il quelque chose a faire pour le fait que c'est un FIXED??
	}
;

contenu
: EMPTY
	{
		currType = new DTDType();
		currType->set_idType(TYPE_ATOMIC);
		currElement->set_type(currType);
	}
| ANY
	{
		currType = Type();
		currType->set_idType(TYPE_ATOMIC);
		currElement->set_type(currType);
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
		currType = new DTDType();
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
