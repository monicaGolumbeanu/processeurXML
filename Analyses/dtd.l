%option 8bit nodefault

%{
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "yy.tab_dtd.h"

static char* skipSpace(char *s) {
  char *buf;
  int i,lastnonspace;
  for (buf=s;isspace(*buf);buf++) ;
  for (i=0,lastnonspace=0;buf[i];i++) {
     if (!isspace(buf[i]))
        lastnonspace = i;
  }
  buf[lastnonspace+1] = '\0';
  return strdup(buf);
}
  
/* affecte la valeur de la chaine de caractère et renvoie le token */
#define stringreturn(tokenval) dtd_lval.s=skipSpace(dtd_text);return(tokenval)

%}
%option noyywrap

nl		(\r\n|\r|\n)
ws		[ \t\r\n]+
open		{nl}?"<"
close		">"{nl}?
openpar "("
closepar ")"
comma ","
pipe "|"
esc		"&#"[0-9]+";"|"&#x"[0-9a-fA-F]+";"
namestart	[A-Za-z\200-\377_]
namechar	[A-Za-z\200-\377_0-9.-]
tokentype "ID"|"IDREF"|"IDREFS"|"ENTITY"|"ENTITIES"|"NMTOKEN"|"NMTOKENS"
name		{namestart}{namechar}*
comment		{open}"!--"([^-]|"-"[^-])*"--"{close}
string		\"([^"&]|{esc})*\"|\'([^'&]|{esc})*\'
element {open}"!ELEMENT"{ws}
attlist {open}"!ATTLIST"{ws}
declaration "#"("REQUIRED"|"IMPLIED"){ws}?
fixed "#FIXED"{ws}
pcdata "#PCDATA"{ws}?
cdata "CDATA"{ws}?
qmark "?"
ast "*"
plus "+"
empty "EMPTY"
any "ANY"

%s INSIDE

/* 
   INITIAL : en dehors d'un bloc ELEMENT ou ATTLIST
   INSIDE : dans un bloc ELEMENT ou ATTLIST
*/

%%

<INITIAL>{ws}		            { /* skip */}
<INITIAL>{element}            {printf("%s",dtd_text); BEGIN(INSIDE); return ELEMENT; }
<INITIAL>{attlist}            {printf("%s",dtd_text); BEGIN(INSIDE); return ATTLIST; }
<INSIDE>{close}               {printf("%s",dtd_text); BEGIN(INITIAL); return CLOSE; }
<INSIDE>{openpar}             {printf("%s",dtd_text); return OPENPAR; }
<INSIDE>{closepar}{ws}?       {printf("%s",dtd_text); return CLOSEPAR; }
<INSIDE>{comma}{ws}?          {printf("%s",dtd_text); return COMMA; }
<INSIDE>{pipe}{ws}?           {printf("%s",dtd_text); return PIPE; }
<INSIDE>{declaration}         {printf("%s",dtd_text); stringreturn(DECLARATION); }
<INSIDE>{fixed}               {printf("%s",dtd_text); return FIXED; }
<INSIDE>{ast}                 {printf("%s",dtd_text); return AST ; }
<INSIDE>{qmark}               {printf("%s",dtd_text); return QMARK ; }
<INSIDE>{plus}                {printf("%s",dtd_text); return PLUS ; }
<INSIDE>{empty}               {printf("%s",dtd_text); return EMPTY; }
<INSIDE>{any}                 {printf("%s",dtd_text); return ANY; }
<INSIDE>{pcdata}              {printf("%s",dtd_text); return PCDATA; }
<INSIDE>{cdata}               {printf("%s",dtd_text); return CDATA; }
<INSIDE>{string}              {printf("%s",dtd_text); stringreturn(STRING); }
<INSIDE>{tokentype}{ws}?      {printf("%s",dtd_text); stringreturn(TOKENTYPE); }
<INSIDE>{name}{ws}?           {printf("%s",dtd_text); stringreturn(NAME); }
{comment}		               {printf("%s",dtd_text); /* skip comments stringreturn(COMMENT); */ }

.			{printf("%s",dtd_text);fprintf(stderr, "!ERROR(%c)\n", *dtd_text);}
{nl}			{printf("%s",dtd_text);/* skip, must be an extra one at EOF */;}
