using namespace std;

#include <cstring>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <stack>
#include <list>
#include <iostream>

#include <XMLAttr.h>
#include <XMLPCDATA.h>
#include <XMLVisitor.h>
#include <XMLPrintVisitor.h>
#include <XMLNode.h>
#include <XMLTag.h>
#include "commun.h"
#include "yy.tab_xml.h"
#include "analyse.h"

// globals
extern FILE   * xml_in;
extern FILE   * xsl_in;
extern FILE   * dtd_in;
extern char   * xml_dtd_name;
extern char   * xsl_dtd_name;
extern char   * xsl_name;
extern XMLTag * xml_root;
extern XMLTag * xsl_root;

// some useful functions
void pretty_print(XMLNode* node);
void check_xml(char * file_name);
void check_xsl();

////////////////////////////////////////////////////////////////////////////////
//                              main
////////////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv)
{
  // only one argument : xml file name
  if ( argc != 2 ) {
    printf("Please enter the name of the XML file only\n");
    return 1;
  }

  check_xml(argv[1]);
  check_xsl();
 
  pretty_print(xml_root);
  pretty_print(xsl_root);
  
  return 0;
}

////////////////////////////////////////////////////////////////////////////////
//                              check_xml
////////////////////////////////////////////////////////////////////////////////
void check_xml( char * file_name )
{
  int    xml_err;
  int    dtd_err;

  //////////// XML PARSING
  printf("Your XML file : %s\n", file_name);
  xml_in = fopen(file_name, "r");
  if ( xml_in == 0 )
  {
    printf("Can't open XML file\n");
  }
  xml_err = xml_parse();
  if (xml_err != 0)
  {
    printf("XML Parse ended with %d error(s)\n\n", xml_err);
  }
  else
  {
    printf("XML Parse ended with success\n\n");
  }
  
  //////////// DTD PARSING
  dtd_in = fopen(xml_dtd_name, "r");
  if ( dtd_in == 0 )
  {
    printf("Can't open DTD file : %s\n", xml_dtd_name);
  }
  
  dtd_err = dtd_parse();
  if (dtd_err != 0)
  {
    printf("DTD Parse ended with %d error(s)\n\n", dtd_err);
  }
  else
  {
    printf("DTD Parse ended with success\n\n");
  }
  
  //////////// XML VALIDITY CHECK
  // TODO
}

////////////////////////////////////////////////////////////////////////////////
//                              check_xsl
////////////////////////////////////////////////////////////////////////////////
void check_xsl()
{
  int    xsl_err;
  int    dtd_err;
  
  //////////// XSL PARSING
  printf("Your XSL file : %s\n", xsl_name);
  xsl_in = fopen(xsl_name, "r");
  if ( xsl_in == 0 )
  {
    printf("Can't open XSL file\n");
  }
  xsl_err = xsl_parse();
  if (xsl_err != 0)
  {
    printf("XSL Parse ended with %d error(s)\n\n", xsl_err);
  }
  else
  {
    printf("XSL Parse ended with success\n\n");
  }
  
  //////////// DTD PARSING
  dtd_in = fopen(xsl_dtd_name, "r");
  if ( dtd_in == 0 )
  {
    printf("Can't open DTD file : %s\n", xsl_dtd_name);
  }
  
  dtd_err = dtd_parse();
  if (dtd_err != 0)
  {
    printf("DTD Parse ended with %d error(s)\n\n", dtd_err);
  }
  else
  {
    printf("DTD Parse ended with success\n\n");
  }
  //////////// XML VALIDITY CHECK
  // TODO
}

////////////////////////////////////////////////////////////////////////////////
//                              pretty_print
////////////////////////////////////////////////////////////////////////////////
void pretty_print(XMLNode* node) {
	XMLPrintVisitor* visitor = new XMLPrintVisitor();
	XMLTag *tag;
	XMLPCDATA *pcdata;
	list<XMLNode *> children;
	list<XMLNode *>::iterator iter;
	if ( node == NULL )
	    return;
	switch (node->get_type()) {
		case NODE_XMLTAG:
			tag = static_cast<XMLTag*> (node);
			children = *(tag->get_children());
			tag->accept(visitor);
			if (!children.empty())
			{
				for (iter = children.begin(); iter != children.end(); iter++)
					pretty_print(*iter);
			}
			tag->accept(visitor);
			break;
		case NODE_XMLPCDATA:
			pcdata = static_cast<XMLPCDATA*>(node);
			pcdata->accept(visitor);
			break;
		default:
			break;
	}
}

////////////////////////////////////////////////////////////////////////////////
//                              xml_error
////////////////////////////////////////////////////////////////////////////////
void xml_error(char *msg)
{
  fprintf(stderr, "%s\n", msg);
}

////////////////////////////////////////////////////////////////////////////////
//                              dtd_error
////////////////////////////////////////////////////////////////////////////////
void dtd_error(char *msg)
{
  fprintf(stderr, "%s\n", msg);
}

////////////////////////////////////////////////////////////////////////////////
//                              xsl_error
////////////////////////////////////////////////////////////////////////////////
void xsl_error(char *msg)
{
  fprintf(stderr, "%s\n", msg);
}

