#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h> //CHANGE THIS TO PROPER DIRECTORY
#include "cgicustom.h"
#include "randomizer.h"
#define STATEMENT_LEN 100
#define db_name "db_RPG"
#define db_name_temp "db_RPG_temp"
#define USER "root"
#define PASS "root"

void print_css();
void print_map(coordinate_t pos);
void print_arrows(int flag, coordinate_t pos);

int main()
{
	int spawn = 0;
    char name[10]={'\0'};
    char *data = NULL;
    coordinate_t prev;
    coordinate_t pos;
    pos.x = 0;
    pos.y = 0;

	cgi_init_beforecss("MP1 Title_Map");
	print_css();
	cgi_init_aftercss();

	if(getenv("CONTENT_LENGTH")) {
        data = post_init(atoi(getenv("CONTENT_LENGTH")),0);
        strncpy(name,parse_data(data, "name", "multipart/form-data"),9);
        if(parse_data(data, "ihat", "multipart/form-data")) {
  
        	pos.x = atoi(parse_data(data, "ihat", "multipart/form-data")) + atoi(parse_data(data, "xprev", "multipart/form-data"));
        	pos.y = atoi(parse_data(data, "yprev", "multipart/form-data"));
        }
        else if(parse_data(data, "jhat", "multipart/form-data")) {
        	pos.y = atoi(parse_data(data, "jhat", "multipart/form-data")) + atoi(parse_data(data, "yprev", "multipart/form-data"));
        	pos.x = atoi(parse_data(data, "xprev", "multipart/form-data"));
        }
    }

    if(pos.x == 0 && pos.y == 0) {
    	pos = rand_location();
    	spawn = 0;    	
    }

    else {
    	spawn = 1;
    }

    print_map(pos);
    print_arrows(1, pos);
    /*if(!rand_spawn(70) || !spawn) {
    	print_arrows(1, pos);
    }
    else {
    	print_arrows(0, pos);
    }*/

	cgi_term();
	free(data);
	return 0;
}

void print_arrows(int flag, coordinate_t pos)
{
	if(flag) {
	    puts("<div class=\"container\">");
	      	puts("<div class=\"row\">");
		        puts("<div class=\"col-md-7 arrow\">");
					puts("<form class=\"form-inline\" role=\"form\" action=\"/cgi-bin/MP1/map_handler.cgi\" method=\"post\" enctype=\"multipart/form-data\">");
					    puts("<div class=\"form-group\">");
							printf("<input type=\"hidden\" class=\"form-control\" name=\"yprev\" value=\"%d\">",pos.y);
							printf("<input type=\"hidden\" class=\"form-control\" name=\"xprev\" value=\"%d\">",pos.x);
							puts("<button type=\"submit hidden\" name=\"jhat\" value=\"-1\" class=\"btn\"><span class=\"glyphicon glyphicon-arrow-up\"></span></button>");
							puts("<button type=\"submit hidden\" name=\"jhat\" value=\"1\" class=\"btn\"><span class=\"glyphicon glyphicon-arrow-down\"></span></button>");
							puts("<button type=\"submit hidden\" name=\"ihat\" value=\"1\" class=\"btn\"><span class=\"glyphicon glyphicon-arrow-right\"></span></button>");
							puts("<button type=\"submit hidden\" name=\"ihat\" value=\"-1\" class=\"btn\"><span class=\"glyphicon glyphicon-arrow-left\"></span></button>");
					    puts("</div>");
					puts("</form>");
	        	puts("</div>");
			puts("<iframe name=\"result\" style=\"height:90px; width:30%%\"></iframe>");
			puts("</div>");
	    puts("</div>");
	}
}

void print_map(coordinate_t pos)
{
    puts("<div class=\"container map\">");
      printf("<div style=\"position: relative; left: %dpx; top: %dpx\">",(76+107*(pos.x)),(56*(pos.y)));
        puts("<img src=\"/MP1/Images/mlg_sanic.png\" alt=\"SANIC\" height=\"77\", width\"116\">");
      puts("</div>");
    puts("</div>");

    puts("<script src=\"bootstrap-3.3.5-dist/js/jquery.min.js\"></script>");     
    puts("<script src=\"bootstrap-3.3.5-dist/js/bootstrap.min.js\"></script>");
}

void print_css()
{
	puts("* {");
		puts("box-sizing: border-box;");
	  	puts("}");
    puts(".map {");
      	puts("width: 100%%;");
      	puts("height:600px;");
      	puts("padding: 1%%;");
		puts("border: 5px solid gray;");
		puts("margin: 0;");
		puts("background-image: url(/MP1/Images/map_bg.jpg);");
		puts("background-repeat: no-repeat;");
		puts("background-position: center;");
    puts("}");
}

