using namespace std;
#include <cstring>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <stack>
#include <list>

#include "commun.h"
#include "yy.tab.h"

// xml parsing functions
int  xml_wrap(void);
void xml_error(char *msg);
int  xml_lex(void);

// dtd parsing functions
void dtd_error(char *msg);
int  dtd_wrap(void);
int  dtd_lex(void);

// globals
extern FILE   * xml_in;
extern FILE   * dtd_in;
extern string   nom_dtd;


////////////////////////////////////////////////////////////////////////////////
//                              main
////////////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv)
{
  int    xml_err;
  int    dtd_err;
  FILE * xml_file;
  FILE * dtd_file;
  
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
  
  xml_file = fopen(argv[1], "r");
  xml_in = xml_file;
  
// DEBUG
printf("Beginning of the XML parsing\n");

  xml_err = xml_parse();
  if (xml_err != 0)
  {
    printf("XML Parse ended with %d error(s)\n", xml_err);
  }
  else
  {
    printf("XML Parse ended with sucess\n", xml_err);
  }
  
  printf("Your DTD file : %s\n", nom_dtd);
  
  // DEBUG
printf("Beginning of the XML parsing\n");

  dtd_err = dtd_parse();
  if (dtd_err != 0)
  {
    printf("DTD Parse ended with %d error(s)\n", dtd_err);
  }
  else
  {
    printf("DTD Parse ended with sucess\n", dtd_err);
  }
  	
  return 0;
}

////////////////////////////////////////////////////////////////////////////////
//                              xml_wrap
////////////////////////////////////////////////////////////////////////////////
int xml_wrap(void)
{
  return 1;
}

////////////////////////////////////////////////////////////////////////////////
//                              xml_error
////////////////////////////////////////////////////////////////////////////////
void xml_error(char *msg)
{
  fprintf(stderr, "%s\n", msg);
}

////////////////////////////////////////////////////////////////////////////////
//                              dtd_wrap
////////////////////////////////////////////////////////////////////////////////
int dtd_wrap(void)
{
  return 1;
}

////////////////////////////////////////////////////////////////////////////////
//                              dtd_error
////////////////////////////////////////////////////////////////////////////////
void dtd_error(char *msg)
{
  fprintf(stderr, "%s\n", msg);
}

