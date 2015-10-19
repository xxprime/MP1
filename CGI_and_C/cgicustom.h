#ifndef cgicustom_H
#define cgicustom_H

#include "/usr/include/mysql/mysql.h" //CHANGE THIS TO PROPER DIRECTORY

void cgi_init(char *title);//
void cgi_term(void);//
char* post_init(unsigned long int lenstr, int flag);//
char* parse_data(char *data, char *key, char *enctype);//
void load(char** line, char** input);

//SQL

char *create_db(MYSQL *mysql, char *db_name, int flag);


#endif

#define MAXLEN 1000000
#define DEBUG_MODE 1
#define USE_MODE 0
