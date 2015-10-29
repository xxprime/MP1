#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h> //CHANGE THIS TO PROPER DIRECTORY
#define STATEMENT_LEN 100
#define USER "root"
#define PASS "root"

char *cgi_mysql_getvalue(char *db_name, char *table_name, int num_row, int num_column, int flag)
{
	MYSQL mysql;
	MYSQL_RES *result;
	MYSQL_ROW row;
	char statement[STATEMENT_LEN];

	if(!mysql_init(&mysql) && flag) {
		printf("getvalue:ERROR %u (%s): %s<br/>", mysql_errno(&mysql), mysql_sqlstate(&mysql), mysql_error(&mysql));
	}	

    sprintf(statement,"SELECT * FROM %s", table_name);

	if(mysql_real_connect(&mysql, "localhost", USER, PASS, db_name, 0, NULL, 0)) {
		if(mysql_query(&mysql, statement)) {
			if(flag){	
        		printf("getvalue:ERROR %u (%s): %s<br/>", mysql_errno(&mysql), mysql_sqlstate(&mysql), mysql_error(&mysql));
        	}
        }
        else {
        	result = mysql_store_result(&mysql);
        	while(num_row--) {
        		row = mysql_fetch_row(result);
        	}
        	if(row) {
        		return row[num_column-1];
        	}
        	else {
        		return NULL;
        	}
        }
	}

	else {
		if(flag) {
			printf("getvalue:ERROR %u (%s): %s<br/>", mysql_errno(&mysql), mysql_sqlstate(&mysql), mysql_error(&mysql));
		}
		mysql_close(&mysql);
		return NULL;
	}
	mysql_close(&mysql);
	return NULL;
}

int cgi_mysql_check_db(char *db_name, int flag)
{
	MYSQL mysql;

	if(!mysql_init(&mysql) && flag) {
		printf("check_db:ERROR %u (%s): %s<br/>", mysql_errno(&mysql), mysql_sqlstate(&mysql), mysql_error(&mysql));
	}

	if (mysql_real_connect(&mysql, "localhost", USER, PASS, db_name, 0, NULL, 0)) {
		if(flag) {
			printf("database found!<br/>");
		}
		mysql_close(&mysql);
		return 1;
	}
	else {
		if(flag) {
			printf("database not found!<br/>");
		}
		mysql_close(&mysql);
		return 0;
	}
}

int cgi_mysql_statement(char* db_name, char *statement, int flag)
{
	MYSQL mysql;

	if(!mysql_init(&mysql) && flag) {
		printf("statement:ERROR %u (%s): %s<br/>", mysql_errno(&mysql), mysql_sqlstate(&mysql), mysql_error(&mysql));
	}

	if(mysql_real_connect(&mysql, "localhost", USER, PASS, db_name, 0, NULL, 0)) {
		if(mysql_query(&mysql, statement)) {
			if(flag){	
        		printf("statement:ERROR %u (%s): %s<br/>", mysql_errno(&mysql), mysql_sqlstate(&mysql), mysql_error(&mysql));
        	}
        }
	}

	else {
		if(flag) {
			printf("statement:ERROR %u (%s): %s<br/>", mysql_errno(&mysql), mysql_sqlstate(&mysql), mysql_error(&mysql));
		}
		mysql_close(&mysql);
		return 0;
	}
	mysql_close(&mysql);
	return 1;
}

char *cgi_mysql_create_db(char *db_name, int flag)
{

	MYSQL mysql;

	if(!mysql_init(&mysql) && flag) {
		printf("create_db:ERROR %u (%s): %s<br/>", mysql_errno(&mysql), mysql_sqlstate(&mysql), mysql_error(&mysql));
	}

	char *statement = NULL;

	statement = (char *) malloc(sizeof(char) * (strlen(db_name)+17));
	strcpy(statement,"CREATE DATABASE ");
	strncat(statement,db_name,strlen(db_name));

	if(mysql_real_connect(&mysql, "localhost", USER, PASS, NULL, 0, NULL, 0)) {
		if(mysql_query(&mysql, statement)) {
			if(flag){
				printf("create_db:ERROR %u (%s): %s<br/>", mysql_errno(&mysql), mysql_sqlstate(&mysql), mysql_error(&mysql));
			}
			free(statement);
			mysql_close(&mysql);
			return NULL;
		}
	}

	else {
		if(flag){
			printf("create_db:ERROR %u (%s): %s<br/>", mysql_errno(&mysql), mysql_sqlstate(&mysql), mysql_error(&mysql));
		}
		free(statement);
		mysql_close(&mysql);
		return NULL;
	}
	free(statement);
	mysql_close(&mysql);
	return db_name;
}