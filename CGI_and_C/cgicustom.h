#ifndef cgicustom_H
#define cgicustom_H

void cgi_init(char *title);//
void cgi_term(void);//
char* post_init(unsigned long int lenstr, int flag);//
char* parse_data(char *data, char *key, char *enctype);//
void load(char** line, char** input);


#endif

#define MAXLEN 1000000
#define DEBUG_MODE 1
#define USE_MODE 0
