using namespace std;

#include <cstring>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <stack>
#include <list>
#include <iostream>
#include <map>


#include "XMLAttr.h"
#include "XMLPCDATA.h"
#include "XMLVisitor.h"
#include "XMLPrintVisitor.h"
#include "XMLNode.h"
#include "XMLTag.h"
#include "commun.h"
#include "yy.tab_xml.h"
#include "analyse.h"

// globals
extern FILE   * xml_in;
extern FILE   * dtd_in;
extern char   * dtd_name;
extern char   * xsl_name;
extern XMLTag * root;

// some useful functions used inside this file
static void pretty_print(XMLNode* node);
static int  check_xml(char * file_name);
static void construct_XSLmap( XMLTag * xsl_root );
static void printMap();
static void transform( XMLTag * xml_root );
static void apply_xsl( XMLTag * xml_node, XMLTag * xsl_node, XMLTag * html_node );
static void add_to_html( XMLNode * xsl_node, XMLTag * html_node, XMLTag * xml_root );

static map<string, XMLTag*>   XSLmap;
static XMLTag               * html_root = NULL;

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
 
  //pretty_print(xml_root);
  //pretty_print(xsl_root);

  construct_XSLmap( xsl_root );
  // printMap();
  transform( xml_root ) ;
  
  // DEBUG : check if the html tree is conform
  cout << "pretty print transform" << endl;
  pretty_print( html_root );
    
  delete(xml_root);
  delete(xsl_root);
  
  return 0;
}

////////////////////////////////////////////////////////////////////////////////
//                              check_xml
////////////////////////////////////////////////////////////////////////////////
int check_xml( char * file_name )
// Function that parses a xml file and its dtd and then validate the xml file
// thanks to the dtd
// parameters : file_name : name of the file containing the xml
// return     : 1 if there is an  ERROR
//              0 if everything's OK
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
void pretty_print(XMLNode* node)
// This function prints a xml tree in its raw shape
{
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
//                              construct_XSLmap
////////////////////////////////////////////////////////////////////////////////
void construct_XSLmap( XMLTag * xsl_root )
// This function create a map<string, XMLTag*> linking the templates with the
// name of the attribute they match. The result is the global attribute XSLmap
// parameters : xsl_root : root of the xsl tree
{
	
	list<XMLNode *>::iterator iter;
	XMLTag *tag;
	list<XMLNode *> children;
	list<XMLAttr *> attrs;
	list<XMLAttr *>::iterator iterList;
	if (xsl_root!=NULL)
	{
		children = *(xsl_root->get_children());
		for (iter = children.begin(); iter != children.end(); iter++)
		{
			switch ((*iter)->get_type()) {
				case NODE_XMLTAG:
					tag = static_cast<XMLTag*> (*iter);
					attrs = *(tag->get_attrs());
					for (iterList = attrs.begin(); iterList != attrs.end(); iterList++)
					{
						if((*iterList)->get_name() == "match")
						{
							XSLmap[(*iterList)->get_value()] = tag;
						}
					}
					break;
				case NODE_XMLPCDATA:
					break;
				default:
					break;
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//                              print_map
////////////////////////////////////////////////////////////////////////////////
void printMap()
{
	map<string, XMLTag*>::iterator p;

	for(p = XSLmap.begin(); p != XSLmap.end(); p++) {
		cout << p->first << '\n';
		pretty_print(p->second);
  	}
}

////////////////////////////////////////////////////////////////////////////////
//                              transform
////////////////////////////////////////////////////////////////////////////////
void transform( XMLTag * xml_root )
// Function that transorm the xml tree into a html tree thanks to the xsl sheet
// Parameters : xml_root : root of the xml tree to transform
{
    // take the xsl template for the root
    XMLTag * xsl_root = XSLmap["/"];
    
    // Call add_to_html with the first child : "html" -> will be the root of the
    // new html tree
    list<XMLNode*>            * xsl_children = xsl_root->get_children();
	list<XMLNode *>::iterator   iter;
    iter = xsl_children->begin();
    add_to_html( *iter, html_root, xml_root );
}

////////////////////////////////////////////////////////////////////////////////
//                              add_to_html
////////////////////////////////////////////////////////////////////////////////
void add_to_html( XMLNode * xsl_node, XMLTag * html_node, XMLTag * xml_root )
// That function is a recursive function that add to html_node every node of the
// xsl_node and then call apply_xsl where it find it (this function is used for
// the xsl-template match '/' only
// parameters : xsl_node : node to add to the html_node
//              html_node : node to which is added the xsl (created if null)
//              xml_root : xml_root where are to be applied the xsl-templates
{
    XMLTag                    * tag;
    list<XMLNode *>           * children;
    list<XMLNode *>::iterator   iter;
    // If html_node doesn't exist : create it with xsl_node and be recursive
    if ( html_node == NULL )
    {
	    tag = static_cast<XMLTag*> (xsl_node);
        html_root = new XMLTag( tag->get_name() );
        html_node = html_root;
        children = tag->get_children();
        // be recursive with all the children
        for (iter = children->begin(); iter != children->end(); iter++)
        {
            add_to_html( *iter, html_node, xml_root );
        }
    }
    else // if html_node already exists
    {
        XMLPCDATA * pc_data;
        XMLTag    * html_child_tag;
        XMLPCDATA * html_child_pcdata;
        
        // Treatment is different if this is PCDATA or XMLTag
        switch ( xsl_node->get_type() )
        {
			case NODE_XMLTAG:
				tag = static_cast<XMLTag*> (xsl_node);
				// create a new pointer to duplicate the tree
				html_child_tag = new XMLTag( tag->get_name() );
				// If we found apply-templates then go to apply_xsl which makes
				// the treatment for the xml tree
				if(tag->get_name() == "apply-templates")
				{
				    apply_xsl( xml_root, tag, html_node );
				}
				else // if the tag is not "apply-templates"
				{
				    // add the XMLTag to the html tree
                    html_node->add_child( html_child_tag );
                    children = tag->get_children();
                    // be recursive with all the children
                    for (iter = children->begin(); iter != children->end(); iter++)
                    {
                        add_to_html( *iter, html_child_tag, xml_root );
                    }
				}
				break;
			case NODE_XMLPCDATA:
			    // Cast PCDATA and add it to the html tree
			    pc_data = static_cast<XMLPCDATA *> (xsl_node);
			    html_child_pcdata = new XMLPCDATA( pc_data->get_content() );
			    html_node->add_child( html_child_pcdata );
				break;
			default:
				break;
	    }
    }
}

////////////////////////////////////////////////////////////////////////////////
//                              apply_xsl
////////////////////////////////////////////////////////////////////////////////
void apply_xsl( XMLTag * xml_node, XMLTag * xsl_node, XMLTag * html_node )
// That function apply the xsl template described by xsl_node to xml_node and
// all the tree that is under.
// parameters : xml_node  : root of the xml tree to transform
//              xsl_node  : root of the modifications to do
//              html_node : node to which the result is added
{
    // TODO
    // if xml_node is XMLPCDATA : add to html_node the xsl_node and its children
    //                            and the xml_node when found "apply-templates"
    // if xml_node is not a PCDATA :
    // find if a template matches the xml_node
    // if not : recursive call with the children and 'xsl_node'
    // if yes : ???????
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

