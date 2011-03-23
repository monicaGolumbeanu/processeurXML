%option 8bit nodefault
%option noyywrap

%{
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "commun.h"
#include "yy.tab_xsl.h"

static char* skipSpace(char *s) {
  char *buf;
  int i,lastnonspace;
  for (buf=s;isspace(*buf);buf++) ;
  for (i=0,lastnonspace=0;buf[i];i++) {
     if (!isspace(buf[i]))
        lastnonspace = i;
  }
  buf[lastnonspace+1] = '\0';
  return buf;
}

// enlève les " au début et à la fin
static char * getString(char *s) {
   s++;
   s[strlen(s)-1] = '\0';
   return s;
}

static char* word(char *s)
{
  char *buf;
  int i, k;
  for (k = 0; isspace(s[k]) || s[k] == '<'; k++) ;
  for (i = k; s[i] && ! isspace(s[i]); i++) ;
  buf = (char *) malloc((i - k + 1) * sizeof(char));
  strncpy(buf, &s[k], i - k);
  buf[i - k] = '\0';
  return buf;
}

static char * nameSpace(char *s)  /* extrait la première partie, l'espace de nom */
{
   char *name;
   int i,k;
   for (k = 0; isspace(s[k]) || s[k] == '<'; k++) ;
   for (i=k;s[i]!=':';i++) ;
   name = (char*) malloc((i-k+1)*sizeof(char));
   strncpy(name,s+k,i-k);
   name[i-k] = '\0';
   return name;
}

static char *split_namespace(char *s) { /* extrait la deuxième partie après l'espace de nom */
   char *name;
   int i,k;
   for (i=0;s[i]!=':';i++) ;
   i++;
   name = (char*) malloc((strlen(s+i)+1)*sizeof(char));
   strcpy(name,s+i);
   return name;
}

%}

nl		(\r\n|\r|\n)
ws		[ \t\r\n]+
open		{ws}?"<"
close		">"{nl}?
namestart	[A-Za-z\200-\377_]
namechar	[A-Za-z\200-\377_0-9.-]
esc		"&#"[0-9]+";"|"&#x"[0-9a-fA-F]+";"
name		{namestart}{namechar}*
nsname		{namestart}{namechar}*":"{namestart}{namechar}*
data		([^<\n&]|\n[^<&]|\n{esc}|{esc})+
pcdata		[^<]+
comment		{open}"!--"([^-]|"-"[^-])*"--"{close}
string		\"([^"&]|{esc})*\"|\'([^'&]|{esc})*\'
xmlversion   {ws}?"<?xml"{ws}"version="{string}{ws}"encoding="{string}"?>"{nl}?
doctype     {ws}?"<!DOCTYPE"{ws}
openspecial {ws}?"<?"
closespecial "?>"{nl}?

/*
 * Le mode CONTENT est utilse pour le contenu des elements, c a d
 *  entre le ">" et le "<" des balises 
 *  Le mode INITIAL est utlise en dehors de l'element RACINE 
 * et a l'interieur des balises
 */

%s CONTENT


%%

<INITIAL>{ws}		{/* skip */}
<INITIAL>{xmlversion} {/* skip */}
<INITIAL>{doctype} {return DOCTYPE;}
<INITIAL>"/"		{return SLASH;}
<INITIAL>"="		{return EQ;}
<INITIAL>{close}	{BEGIN(CONTENT); return CLOSE;}
<INITIAL>{closespecial}	{return CLOSESPECIAL;}
<INITIAL>{name}		{xsl_lval.s = strdup(xsl_text); return NAME;}
<INITIAL>{nsname}		{xsl_lval.s = strdup(xsl_text); return NSNAME;}
<INITIAL>{string}	{xsl_lval.s = strdup(getString(xsl_text)); return VALUE;}

{openspecial}{ws}?{name}	{BEGIN(INITIAL); char * tmp = word(xsl_text); xsl_lval.en = new ElementName("",tmp); free(tmp); return STARTSPECIAL;}
{open}{ws}?{name}	{BEGIN(INITIAL); char * tmp = word(xsl_text); xsl_lval.en = new ElementName("",tmp); free(tmp); return START;}
{open}{ws}?{nsname}	{BEGIN(INITIAL); char *tmp1 = nameSpace(xsl_text); char * tmp2 = split_namespace(xsl_text); xsl_lval.en = new ElementName(tmp1,tmp2); free(tmp1); free(tmp2); return NSSTART;}
{open}{ws}?"/"		{BEGIN(INITIAL); return END;}
{comment}		{xsl_lval.s = strdup(xsl_text); return COMMENT;}

<CONTENT>{ws}?{pcdata}		{xsl_lval.s = strdup(skipSpace(xsl_text)); return DATA;}

{nl}		{/* skip */}
.			{fprintf(stderr, "!ERROR(%c)\n", *xsl_text);}
