#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h> //CHANGE THIS TO PROPER DIRECTORY
#include "cgicustom.h"
#include "stats.h"
#define STATEMENT_LEN 100
#define db_name "db_RPG"
#define db_name_temp "db_RPG_temp"
#define USER "root"
#define PASS "root"

void print_battle();

int main()
{
	char *data = NULL;
	cgi_init_beforecss("MP1 Title_Map");
	cgi_init_aftercss();

	if(getenv("CONTENT_LENGTH")) {
        data = post_init(atoi(getenv("CONTENT_LENGTH")),0);

        free(data);
    }

	print_battle();

	cgi_term();
	return 0;
}

void print_battle()
{
	puts("<div class=\"container\" style=\"margin:20px\">");
		puts("<div class=\"row\">");
		puts("<div class=\"col-md-6 text-center\">YOU</div>");
		puts("<div class=\"col-md-6 text-center\">MONSTER</div>");
		puts("</div>");
		puts("<div class=\"row\">");
		puts("<div class=\"col-md-6 text-center\"><img src=\"/MP1/Images/mlg_sanic.png\" alt=\"SANIC\" style=\"width:200px; height:200px;\"></div>");
		puts("<div class=\"col-md-6 text-center\"><img src=\"/MP1/Images/dark_sanic.png\" alt=\"DARK SANIC\" style=\"width:200px; height:200px;\"></div>");
		puts("</div>");
		puts("<div class=\"row\">");
		puts("<div class=\"col-md-6 text-center\">HP:%d</div>");
		puts("<div class=\"col-md-6 text-center\">HP:%d</div>");
		puts("</div>");
		puts("<div class=\"row\">");
		puts("<div class=\"col-md-6 text-center\">Level:%d</div>");
		puts("<div class=\"col-md-6 text-center\">Level:%d</div>");
		puts("</div>");
		puts("<div class=\"row\">");
			puts("<div class=\"col-md-6 text-center\">");
				puts("<div class=\"row\">");
					puts("<div class=\"col-md-12 text-left\">STR:</div>");
				puts("</div>");
				puts("<div class=\"row\">");
					puts("<div class=\"col-md-6 text-left\">INT:</div>");
					puts("<div class=\"col-md-6 text-center\">VIT:</div>");
				puts("</div>");
				puts("<div class=\"row\">");
					puts("<div class=\"col-md-6 text-left\">AGI:</div>");
					puts("<div class=\"col-md-6 text-center\">DEX:</div>");
				puts("</div>");
			puts("</div>");
		puts("</div>");
		puts("<div class=\"container\">");
			puts("<form role=\"form\" action=\"\" method=\"post\" enctype=\"multipart/form-data\">");
				puts("<label class=\"radio-inline\">");
			  		puts("<input type=\"radio\" name=\"Action\" value=\"Attack\">Attack");
				puts("</label>");
				puts("<label class=\"radio-inline\">");
			  		puts("<input type=\"radio\" name=\"Action\" value=\"Defend\">Defend");
				puts("</label>");
				puts("<label class=\"radio-inline\">");
			  		puts("<input type=\"radio\" name=\"Action\" value=\"Skill\">Skill");
				puts("</label>");
				puts("<label class=\"radio-inline\">");
			  		puts("<input type=\"radio\" name=\"Action\" value=\"Run\">Run");
				puts("</label>");
				puts("<button type=\"submit\" class=\"btn btn-default\">Submit</button>");
			puts("</form>");
		puts("</div>");
		puts("<div class=\"container\">");
			puts("<iframe name=\"gameover\" style=\"height:90px; width:30%%\"></iframe>");
		puts("</div>");
	puts("</div>");
}
