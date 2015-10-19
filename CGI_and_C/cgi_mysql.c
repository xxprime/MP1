#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "/usr/include/mysql/mysql.h" //CHANGE THIS TO PROPER DIRECTORY


char *create_db(MYSQL *mysql, char *db_name, int flag)
{
	char *statement = NULL;

	statement = (char *) malloc(sizeof(char) * (strlen(db_name)+17));
	strcpy(statement,"CREATE DATABASE ");
	strncat(statement,db_name,strlen(db_name));

	if(mysql_query(mysql, statement)) {
		if(flag){
			printf("ERROR %u (%s): %s", mysql_errno(mysql), mysql_sqlstate(mysql), mysql_error(mysql));
		}
		return NULL;
	}
	return db_name;
}