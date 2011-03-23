#ifndef _ANALYSE_
#define _ANALYSE_

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

#endif
