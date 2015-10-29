#ifndef cgicustom_H
#define cgicustom_H

#include <mysql/mysql.h> //CHANGE THIS TO PROPER DIRECTORY

void cgi_init(char *title);//
void cgi_init_beforecss(char *title);
void cgi_init_aftercss();
void cgi_term(void);//
char* post_init(unsigned long int lenstr, int flag);//
char* parse_data(char *data, char *key, char *enctype);//
void load(char** line, char** input);

//SQL
char *cgi_mysql_getvalue(char *db_name, char *table_name, int row, int column, int flag);
int cgi_mysql_check_db(char *db_name, int flag);
int cgi_mysql_statement(char* db_name, char *statement, int flag);
char *cgi_mysql_create_db(char *db_name, int flag);


#endif

#define MAXLEN 1000000
#define DEBUG_MODE 1
#define USE_MODE 0
