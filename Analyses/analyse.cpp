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
extern FILE   * dtd_in;
extern char   * dtd_name;
extern char   * xsl_name;
extern XMLTag * root;

// some useful functions
void pretty_print(XMLNode* node);
int  check_xml(char * file_name);

////////////////////////////////////////////////////////////////////////////////
//                              main
////////////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv)
{
  XMLTag * xml_root;
  XMLTag * xsl_root;
  int      parse_error;
  
  // only one argument allowed : xml file name
  if ( argc != 2 ) {
    printf("Please enter the name of the XML file only\n");
    return 1;
  }

  // Parsing XML
  parse_error = check_xml(argv[1]);
  if ( parse_error == 1 )
  {
    return 1;
  }
  xml_root = root;
  // Parsing XSL
  parse_error = check_xml(xsl_name);
  if ( parse_error == 1 )
  {
    return 1;
  }
  xsl_root = root;
 
  /*pretty_print(xml_root);
  pretty_print(xsl_root);*/
  
  delete(xml_root);
  delete(xsl_root);
  
  return 0;
}

////////////////////////////////////////////////////////////////////////////////
//                              check_xml
////////////////////////////////////////////////////////////////////////////////
int check_xml( char * file_name )
{
  int    xml_err;
  int    dtd_err;

  //////////// XML PARSING
  printf("Your XML file : %s\n", file_name);
  xml_in = fopen(file_name, "r");
  if ( xml_in == 0 )
  {
    printf("Can't open XML file\n");
    return 1;
  }
  xml_err = xml_parse();
  if (xml_err != 0)
  {
    printf("XML Parse ended with %d error(s)\n\n", xml_err);
    return 1;
  }
  else
  {
    printf("XML Parse ended with success\n\n");
  }
  
  //////////// DTD PARSING
  dtd_in = fopen(dtd_name, "r");
  if ( dtd_in == 0 )
  {
    printf("Can't open DTD file : %s\n", dtd_name);
    return 1;
  }
  
  dtd_err = dtd_parse();
  if (dtd_err != 0)
  {
    printf("DTD Parse ended with %d error(s)\n\n", dtd_err);
    return 1;
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
	delete( visitor );
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

