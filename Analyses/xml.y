%{

using namespace std;
#include <cstring>
#include <string>
#include <cstdio>
#include <cstdlib>

#include "commun.h"
#include "yy.tab_xml.h"
#include "XML/XMLNode.h"
#include "XML/XMLTag.h"
#include "XML/XMLAttr.h"
#include "XML/XMLPCDATA.h"
#include "tools.h"

char   * dtd_name;
char   * xsl_name;
XMLTag * root;
XMLTag * current;

%}

%union {
   char * s;
   ElementName * en;  /* le nom d'un element avec son namespace */
}

%token EQ SLASH CLOSE END CLOSESPECIAL DOCTYPE
%token <s> ENCODING VALUE DATA COMMENT NAME NSNAME
%token <en> NSSTART START STARTSPECIAL

%type <s> debut

%%

document
 : refXSL declarations element misc_seq_opt { current = NULL }
 ;
refXSL
 : STARTSPECIAL NAME EQ VALUE NAME EQ VALUE CLOSESPECIAL { xsl_name=$4; }
 | /*empty*/
 ;
misc_seq_opt
 : misc_seq_opt misc
 | /*empty*/
 ;
misc
 : COMMENT { XMLPCDATA * newData = new XMLPCDATA( $1 ); current->addChild( newData ); }
 ;

declarations
 : declaration
 | /*empty*/
 ;
 
declaration
 : DOCTYPE debut NAME VALUE CLOSE { dtd_name=$4; }
 ;
debut
: NAME
|NSNAME
;
element
 : start
   empty_or_content
 ;
start
 : START
    {
        if (current == NULL )
        {
            root = new XMLTag($1->second);
            current = root;
        }
        else
        {
            XMLTag * newTag = new XMLTag($1->second);
            current->addChild( newTag );
            current = newTag;
        }
    }
 | NSSTART
    {
        if (current == NULL )
        {
            root = new XMLTag($1->second, $1->first.c_str());
            current = root;
        }
        else
        {
            XMLTag * newTag = new XMLTag($1->second, $1->first.c_str());
            current->addChild( newTag );
            current = newTag;
        }
    };
empty_or_content
 : SLASH CLOSE { current = current->getParent(); }
 | attributes 
   close_content_and_end 
   name_or_nsname_opt CLOSE 
 ;
attributes
: attributes single_attribute
| /*empty*/
;
single_attribute
: debut EQ VALUE
    {
        XMLAttr * newAttr = new XMLAttr( $1, $3 );
        current->addAttr( newAttr );
    };
name_or_nsname_opt 
 : NAME     
 | NSNAME  
 | /* empty */
 ;
close_content_and_end
 : CLOSE			
   content 
   END { current = current->getParent(); }
 ;
content 
 : content DATA	{ XMLPCDATA * newData = new XMLPCDATA( $2 ); current->addChild( newData ); }
 | content misc        
 | content element      
 | /*empty*/         
 ;
%%


