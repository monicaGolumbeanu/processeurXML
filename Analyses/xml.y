%{

using namespace std;
#include <cstring>
#include <string>
#include <cstdio>
#include <cstdlib>

#include "commun.h"
#include "yy.tab_xml.h"
#include "XMLNode.h"
#include "XMLTag.h"
#include "XMLAttr.h"


int    yywrap(void);
void   yyerror(char *msg);
int    yylex(void);

string   nom_dtd;
XMLTag * root;
XMLTag * current = root;
string   buffer;

%}

%union {
   char * s;
   ElementName * en;  /* le nom d'un element avec son namespace */
}

%token EQ SLASH CLOSE END CLOSESPECIAL DOCTYPE
%token <s> ENCODING VALUE DATA COMMENT NAME NSNAME
%token <en> NSSTART START STARTSPECIAL

%%

document
 : declarations element misc_seq_opt
 ;
misc_seq_opt
 : misc_seq_opt misc
 | /*empty*/
 ;
misc
 : COMMENT		
 ;

declarations
 : declaration
 | /*empty*/
 ;
 
declaration
 : DOCTYPE NAME NAME VALUE CLOSE { nom_dtd=$4;}
 ;

element
 : start
   empty_or_content
 ;
start
 : START
    {
        buffer = $1->second;
        if (current == NULL )
        {
            current = new XMLTag(buffer);
        }
        else
        {
            current->add_child( new XMLTag(buffer) );
        }
    }
 | NSSTART
    {
        buffer = $1->second;
        if (current == NULL )
        {
            current = new XMLTag(buffer);
        }
        else
        {
            current->add_child( new XMLTag(buffer) );
        }
    };
empty_or_content
 : SLASH CLOSE	
 | attributes 
   close_content_and_end 
   name_or_nsname_opt CLOSE 
 ;
attributes
: attributes single_attribute
| /*empty*/
;
single_attribute
: NAME EQ VALUE
;
name_or_nsname_opt 
 : NAME     
 | NSNAME  
 | /* empty */
 ;
close_content_and_end
 : CLOSE			
   content 
   END { current = current->get_parent(); }
 ;
content 
 : content DATA		
 | content misc        
 | content element      
 | /*empty*/         
 ;
%%


