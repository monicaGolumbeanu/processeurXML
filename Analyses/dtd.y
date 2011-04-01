%{
using namespace std;
#include <list>
#include <vector>
#include <map>
#include <cstring>
#include <cstdio>
#include <cstdlib>

#include <DTD.h>
#include <DTDParserActionHandler.h>

void yyerror(char *msg);
int  yywrap(void);
int  yylex(void);

%}

%union { 
   char *s; 
   }

%token ELEMENT ATTLIST CLOSE OPENPAR CLOSEPAR COMMA PIPE FIXED EMPTY ANY PCDATA AST QMARK PLUS CDATA
%token <s> NAME TOKENTYPE DECLARATION STRING NSNAME

%type <s> debut item_enum

%%

main: dtd  
    {
        handler.checkProblems();
    }                         
    ;
dtd
: dtd attlist
| dtd element
| /* empty */
;
attlist
: ATTLIST debut att_definition CLOSE
    {
        handler.finishAttlist($2);
    }
;
element
: ELEMENT debut contenu CLOSE
	{
        handler.finishElement($2);
	}
;
debut
: NAME
| NSNAME
;
att_definition
: att_definition attribut
| /* empty */
;
attribut
: debut att_type defaut_declaration
	{
        handler.finishAttribute($1);
	}
;
att_type
: CDATA
  {
    handler.setNewAttributeType("CDATA");
  }
| TOKENTYPE
  {
    handler.setNewAttributeType("TOKENTYPE");
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
| NSNAME
;
defaut_declaration
: DECLARATION 
| STRING     
| FIXED STRING 
;

contenu
: EMPTY
	{
        handler.createNewEmptyRule();
	}
| ANY
    {
        handler.createNewAnyRule();
    }
| mixed
| children
;
mixed
:OPENPAR PCDATA contenu_mixed CLOSEPAR cardinalite
    {
        handler.createNewItem("#PCDATA");
        handler.finishRuleChoice();
    }
;
contenu_mixed
:contenu_mixed PIPE debut
    {
        handler.createNewItem($3);
    }
|/*empty*/
	{
		handler.pushNewItemList();
	}
;
children
: sequence_ou_choix cardinalite
  {
    handler.updateCardinality();
  }
;
cardinalite
: QMARK
	{
		handler.setNewRuleCardinality('?');
	}
| AST
	{
		handler.setNewRuleCardinality('*');
	}
| PLUS
	{
		handler.setNewRuleCardinality('+');
	}
| /*empty*/
;
sequence_ou_choix
: sequence
| choix
;
sequence
:parOpen liste_sequence CLOSEPAR
 {
    handler.finishRuleSequence();
 }
;
liste_sequence
: item
| liste_sequence COMMA item
;
item
: debut cardinalite
{
    handler.createNewItem($1);
}
| children
;
parOpen : OPENPAR
{
    handler.pushNewItemList();
}
choix
: parOpen liste_choix_plus CLOSEPAR
  {
    handler.finishRuleChoice();
  }
;
liste_choix_plus
: liste_choix PIPE item
;
liste_choix
: liste_choix PIPE item
| item
;

%%
