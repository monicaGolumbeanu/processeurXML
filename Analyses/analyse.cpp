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

// xml parsing functions
void xml_error(char *msg);
int  xml_lex(void);
int  xml_parse(void);

// dtd parsing functions
void dtd_error(char *msg);
int  dtd_lex(void);
int  dtd_parse(void);

// xml parsing functions
void xsl_error(char *msg);
int  xsl_lex(void);
int  xsl_parse(void);

// globals
extern FILE   * xml_in;
extern FILE   * xsl_in;
extern FILE   * dtd_in;
extern char   * dtd_name;
extern char   * xsl_name;
extern int      dtd_debug;
extern XMLTag * xml_root;
extern XMLTag * xsl_root;

////////////////////////////////////////////////////////////////////////////////
//                              pretty_print
////////////////////////////////////////////////////////////////////////////////
void pretty_print(XMLNode* node) {
	XMLPrintVisitor* visitor = new XMLPrintVisitor();
	XMLTag *tag;
	XMLPCDATA *pcdata;
	list<XMLNode *> children;
	list<XMLNode *>::iterator iter;
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
//                              main
////////////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv)
{
  int    xml_err;
  int    xsl_err;
  int    dtd_err;
  
//dtd_debug=1;
  // only one argument : xml file name
  if ( argc != 2 )
  {
    printf("Please enter the name of the XML file only\n");
    return 1;
  }
  else
  {
    printf("Your XML file : %s\n", argv[1]);
  }

  xml_in = fopen(argv[1], "r");
  if ( xml_in == 0 )
  {
    printf("Can't open XML file\n");
  }
  
// DEBUG
printf("Beginning of the XML parsing\n");

  xml_err = xml_parse();
  if (xml_err != 0)
  {
    printf("XML Parse ended with %d error(s)\n\n", xml_err);
  }
  else
  {
    printf("XML Parse ended with success\n\n");
  }
  printf("xsl_name : %s\n", xsl_name);
  xsl_in = fopen(xsl_name, "r");
  if ( xsl_in == 0 )
  {
    printf("Can't open XSL file\n");
  }
  else
  {
    printf("XSL file open\n");
  }
  xsl_err = xsl_parse();
  if (xsl_err != 0)
  {
    printf("SECOND XSL Parse ended with %d error(s)\n\n", xml_err);
  }
  else
  {
    printf("SECOND XSL Parse ended with success\n\n");
  }
  
  printf("Your DTD file : %s\n", dtd_name );
  
  // DEBUG
printf("Beginning of the DTD parsing\n");

  dtd_in = fopen(dtd_name, "r");
  if ( dtd_in == 0 )
  {
    printf("Can't open DTD file\n");
  }
  
  dtd_err = dtd_parse();
  if (dtd_err != 0)
  {
    printf("DTD Parse ended with %d error(s)\n", dtd_err);
  }
  else
  {
    printf("DTD Parse ended with success\n");
  }
 
  pretty_print(xml_root);
  pretty_print(xsl_root);
  return 0;
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

