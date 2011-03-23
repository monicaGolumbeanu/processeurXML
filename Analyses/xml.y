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
#include "analyse.h"

char   * xml_dtd_name;
char   * xsl_name;
XMLTag * xml_root;
XMLTag * xml_current;

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
 : refXSL declarations element misc_seq_opt 
 ;
refXSL
 : STARTSPECIAL NAME EQ VALUE NAME EQ VALUE CLOSESPECIAL { xsl_name=$4; }
|/*empty*/
;
misc_seq_opt
 : misc_seq_opt misc
 | /*empty*/
 ;
misc
 : COMMENT { XMLPCDATA * newData = new XMLPCDATA( $1 ); xml_current->add_child( newData ); }
 ;

declarations
 : declaration
 | /*empty*/
 ;
 
declaration
 : DOCTYPE debut NAME VALUE CLOSE { xml_dtd_name=$4; }
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
        if (xml_current == NULL )
        {
            xml_root = new XMLTag($1->second);
            xml_current = xml_root;
        }
        else
        {
            XMLTag * newTag = new XMLTag($1->second);
            xml_current->add_child( newTag );
            xml_current = newTag;
        }
    }
 | NSSTART
    {
        if (xml_current == NULL )
        {
            xml_root = new XMLTag($1->second, $1->first.c_str());
            xml_current = xml_root;
        }
        else
        {
            XMLTag * newTag = new XMLTag($1->second, $1->first.c_str());
            xml_current->add_child( newTag );
            xml_current = newTag;
        }
    };
empty_or_content
 : SLASH CLOSE { xml_current = xml_current->get_parent(); }
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
        xml_current->add_attr( newAttr );
    };
name_or_nsname_opt 
 : NAME     
 | NSNAME  
 | /* empty */
 ;
close_content_and_end
 : CLOSE			
   content 
   END { xml_current = xml_current->get_parent(); }
 ;
content 
 : content DATA	{ XMLPCDATA * newData = new XMLPCDATA( $2 ); xml_current->add_child( newData ); }
 | content misc        
 | content element      
 | /*empty*/         
 ;
%%


