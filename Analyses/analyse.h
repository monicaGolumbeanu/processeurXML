#ifndef _ANALYSE_
#define _ANALYSE_

/* XML Parsing functions */
void   xml_error(char *msg);
int    xml_lex(void);

/* DTD Parsing functions */
void   dtd_error(char *msg);
int    dtd_lex(void);

/* XSL Parsing functions */
void   xsl_error(char *msg);
int    xsl_lex(void);

#endif
