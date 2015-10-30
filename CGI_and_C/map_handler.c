#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h> //CHANGE THIS TO PROPER DIRECTORY
#include "cgicustom.h"
#include "randomizer.h"
#include "stats.h"
#define STATEMENT_LEN 100
#define db_name "db_RPG"
#define db_name_temp "db_RPG_temp"
#define USER "root"
#define PASS "root"

void print_css();
void print_map(coordinate_t pos);
void print_arrows(int flag, coordinate_t pos, char *name);
void save_state(char *playerName, char *saveName);
void loadto_temp(char *playerName);
int fightorflight(int flag);

int main()
{

	cgi_init_beforecss("MP1 Title_Map");
	print_css();
	cgi_init_aftercss();

	int increment = 0, same = 0, success = 0;
    char name[10]={'\0'};
    char *data = NULL;
    coordinate_t prev;
    prev.x = 0;
    prev.y = 0;
    coordinate_t pos;
    pos.x = 0;
    pos.y = 0;



	if(getenv("CONTENT_LENGTH")) {
        data = post_init(atoi(getenv("CONTENT_LENGTH")),0);
        if(parse_data(data, "name", "multipart/form-data")) {
       		strncpy(name,parse_data(data, "name", "multipart/form-data"),9);
        }
        if(parse_data(data, "xprev", "multipart/form-data")) {
        	prev.x = atoi(parse_data(data, "xprev", "multipart/form-data"));
        }
        if(parse_data(data, "yprev", "multipart/form-data")) {
        	prev.y = atoi(parse_data(data, "yprev", "multipart/form-data"));
        }
        if(parse_data(data, "ihat", "multipart/form-data")) {
        	increment = atoi(parse_data(data, "ihat", "multipart/form-data"));
        	if((prev.x == 1 && increment == -1)|| (prev.x == 9 && increment == 1)) {
        		pos.x = prev.x;
        		same = 1;
        	}
        	else {
        		pos.x = increment + prev.x;
        		same = 0;
        	}
        	pos.y = prev.y;
        }
        else if(parse_data(data, "jhat", "multipart/form-data")) {
        	increment = atoi(parse_data(data, "jhat", "multipart/form-data"));
        	if((prev.y == 1 && increment == -1)|| (prev.y == 9 && increment == 1)) {
        		pos.y = prev.y;
        		same = 1;
        	}
        	else {
        		pos.y = increment + prev.y;
        		same = 0;
        	}
        	pos.x = prev.x;
        }
        else {
        	pos.x = prev.x;
        	pos.y = prev.y;
        }
        if(parse_data(data, "sname", "multipart/form-data")) {
        	save_state(name,parse_data(data,"sname","multipart/form-data"));
        	same = 1;
        }
        if(parse_data(data, "Fight", "multipart/form-data")) {
        	success = fightorflight(atoi(parse_data(data, "Fight", "multipart/form-data")));
        }
        free(data);
    }

    if((prev.x == 0 && prev.y == 0)) {
    	pos = rand_location();
    	loadto_temp(name);
    }

    print_map(pos);
    if(success) {
    	print_arrows(-1, pos, name);
    }
    else if(!rand_spawn(50) || (prev.x == 0 && prev.y == 0) || same == 1) {
    	print_arrows(1, pos, name);
    }
    else {
    	print_arrows(0, pos, name);
    }

	cgi_term();
	return 0;
}

int fightorflight(int flag)
{
	int agi = 0;
	int t_level, s_level;
	char statement[STATEMENT_LEN];


	s_level = atoi(cgi_mysql_getvalue(db_name_temp, "Player", 1, 2, 1));
	t_level = rand_monster_lvl(s_level);

	cgi_mysql_statement(db_name, "TRUNCATE TABLE Monster", 1);
	if(flag) {
		agi = atoi(cgi_mysql_getvalue(db_name_temp, "Player", 1, 6, 1));
		if(flee_success(agi, s_level, t_level)) {
			return 1;
		}
		else {
			sprintf(statement,"INSERT INTO Monster VALUES(\"%s\", %d, 1)", "DRK SANIC", t_level);
			//cgi_mysql_statement(db_name, statement, 1);
			return 0;
		}
	}
	else {
		sprintf(statement,"INSERT INTO Monster VALUES(\"%s\", %d, 0)", "DRK SANIC", t_level);
		//cgi_mysql_statement(db_name, statement, 1);
		return 0;
	}
	return 0;
}

void loadto_temp(char *playerName)
{
	int lvl = 0, str = 0, intel = 0, vit = 0, agi = 0, dex = 0, expe = 0;
	int row = 0;
	char statement[STATEMENT_LEN];
	if(playerName[0] != '\0') {

		sprintf(statement,"DELETE FROM Player WHERE PlayerName=\"%s\"", playerName);
		cgi_mysql_statement(db_name_temp, statement, 1);


		row = cgi_mysql_getrow(db_name, "Player", playerName, 1);
		lvl = atoi(cgi_mysql_getvalue(db_name, "Player", row, 2, 1));
		str = atoi(cgi_mysql_getvalue(db_name, "Player", row, 3, 1));
		intel = atoi(cgi_mysql_getvalue(db_name, "Player", row, 4, 1));
		vit = atoi(cgi_mysql_getvalue(db_name, "Player", row, 5, 1));
		agi = atoi(cgi_mysql_getvalue(db_name, "Player", row, 6, 1));
		dex = atoi(cgi_mysql_getvalue(db_name, "Player", row, 7, 1));
		expe = atoi(cgi_mysql_getvalue(db_name, "Player", row, 8, 1));
		sprintf(statement,"INSERT INTO Player VALUES(\"%s\", %d, %d, %d, %d, %d, %d, %d)", playerName, lvl, str, intel, vit, agi, dex, expe);
	    cgi_mysql_statement(db_name_temp,statement,1);
	}

	else {
		strcpy(playerName,cgi_mysql_getvalue(db_name_temp, "Player", 1, 1, 1));
	}
}

void save_state(char *playerName, char* saveName)
{
    char statement[STATEMENT_LEN];
    int row = 0, lvl = 1, str = 0, intel = 0, vit = 0, agi = 0, dex = 0, expe = 0;
    row = cgi_mysql_getrow(db_name_temp, "Player", playerName, 1);
    lvl = atoi(cgi_mysql_getvalue(db_name_temp, "Player", row, 2, 1));
    str = atoi(cgi_mysql_getvalue(db_name_temp, "Player", row, 3, 1));
    intel = atoi(cgi_mysql_getvalue(db_name_temp, "Player", row, 4, 1));
   	vit = atoi(cgi_mysql_getvalue(db_name_temp, "Player", row, 5, 1));
    agi = atoi(cgi_mysql_getvalue(db_name_temp, "Player", row, 6, 1));
    dex = atoi(cgi_mysql_getvalue(db_name_temp, "Player", row, 7, 1));
    expe = atoi(cgi_mysql_getvalue(db_name_temp, "Player", row, 8, 1));
    if(!strcmp(saveName,"empty_save_state")) {
    	sprintf(statement,"INSERT INTO Player VALUES(\"%s\", %d, %d, %d, %d, %d, %d, %d)", playerName, lvl, str, intel, vit, agi, dex, expe);
    }
    else {
    	sprintf(statement,"DELETE FROM Player WHERE PlayerName=\"%s\"", saveName);
    	//printf("%s<br/>",statement);
    	cgi_mysql_statement(db_name, statement, 1);    	
    	sprintf(statement,"INSERT INTO Player VALUES(\"%s\", %d, %d, %d, %d, %d, %d, %d)", playerName, lvl, str, intel, vit, agi, dex, expe);

    }
    //printf("%s",statement);
    cgi_mysql_statement(db_name,statement,1);
}

void print_arrows(int flag, coordinate_t pos, char *name)
{
	if(flag == 1) {
	    puts("<div class=\"container\">");
	      	puts("<div class=\"row\">");
		        puts("<div class=\"container arrow\">");
					puts("<form class=\"form-inline\" role=\"form\" action=\"/cgi-bin/MP1/map_handler.cgi\" method=\"post\" enctype=\"multipart/form-data\">");
					    puts("<div class=\"form-group\">");
					    	printf("<input type=\"hidden\" class=\"form-control\" name=\"name\" value=\"%s\">",name);
							printf("<input type=\"hidden\" class=\"form-control\" name=\"yprev\" value=\"%d\">",pos.y);
							printf("<input type=\"hidden\" class=\"form-control\" name=\"xprev\" value=\"%d\">",pos.x);
							puts("<button type=\"submit hidden\" name=\"jhat\" value=\"-1\" class=\"btn\"><span class=\"glyphicon glyphicon-arrow-up\"></span></button>");
							puts("<button type=\"submit hidden\" name=\"jhat\" value=\"1\" class=\"btn\"><span class=\"glyphicon glyphicon-arrow-down\"></span></button>");
							puts("<button type=\"submit hidden\" name=\"ihat\" value=\"1\" class=\"btn\"><span class=\"glyphicon glyphicon-arrow-right\"></span></button>");
							puts("<button type=\"submit hidden\" name=\"ihat\" value=\"-1\" class=\"btn\"><span class=\"glyphicon glyphicon-arrow-left\"></span></button>");
					    puts("</div>");
					puts("</form>");
	        	puts("</div>");
		        puts("<div class=\"container\">");
					puts("<div class=\"dropdown\">");
						puts("<button class=\"btn dropdown-toggle\" type=\"button\" data-toggle=\"dropdown\">");
							puts("<h4 class=\"list-group-item-heading text-left\">Save Game</h4>");
						puts("</button>");
						puts("<ul class=\"dropdown-menu\">");
							puts("<form role=\"form\" action=\"/cgi-bin/MP1/map_handler.cgi\" method=\"post\" enctype=\"multipart/form-data\">");
								printf("<input type=\"hidden\" class=\"form-control\" name=\"name\" value=\"%s\">",name);
								printf("<input type=\"hidden\" class=\"form-control\" name=\"yprev\" value=\"%d\">",pos.y);
								printf("<input type=\"hidden\" class=\"form-control\" name=\"xprev\" value=\"%d\">",pos.x);
								if(cgi_mysql_getvalue(db_name, "Player", 1, 1, 1)) {
									printf("<li><button type=\"submit hidden\" name=\"sname\" value=\"%s\" class=\"btn btn-default\">Name:%s Level:%d</button></li>", cgi_mysql_getvalue(db_name, "Player", 1, 1, 1), cgi_mysql_getvalue(db_name, "Player", 1, 1, 1), atoi(cgi_mysql_getvalue(db_name, "Player", 1, 2, 1)));
								}
								else {
									printf("<li><button type=\"submit hidden\" name=\"sname\" value=\"empty_save_state\" class=\"btn btn-default\">empty_save_state</button></li>");
								}
								if(cgi_mysql_getvalue(db_name, "Player", 2, 1, 1)) {
									printf("<li><button type=\"submit hidden\" name=\"sname\" value=\"%s\" class=\"btn btn-default\">Name:%s Level:%d</button></li>", cgi_mysql_getvalue(db_name, "Player", 2, 1, 1), cgi_mysql_getvalue(db_name, "Player", 2, 1, 1), atoi(cgi_mysql_getvalue(db_name, "Player", 2, 2, 1)));
								}
								else {
									printf("<li><button type=\"submit hidden\" name=\"sname\" value=\"empty_save_state\" class=\"btn btn-default\">empty_save_state</button></li>");
								}
								if(cgi_mysql_getvalue(db_name, "Player", 3, 1, 1)) {
									printf("<li><button type=\"submit hidden\" name=\"sname\" value=\"%s\" class=\"btn btn-default\">Name:%s Level:%d</button></li>", cgi_mysql_getvalue(db_name, "Player", 3, 1, 1), cgi_mysql_getvalue(db_name, "Player", 3, 1, 1), atoi(cgi_mysql_getvalue(db_name, "Player", 3, 2, 1)));
								}
								else {
									printf("<li><button type=\"submit hidden\" name=\"sname\" value=\"empty_save_state\" class=\"btn btn-default\">empty_save_state</button></li>");
								}
							puts("</form>");
						puts("</ul>");
					puts("</div>");
					puts("<a href=\"/cgi-bin/MP1/main_menu.cgi\">EXIT</a>");
				puts("</div>");
			puts("<iframe name=\"result\" style=\"height:90px; width:30%%\"></iframe>");
			puts("</div>");
	    puts("</div>");
	}
	else if(flag == -1) {
	    puts("<div class=\"container\">");
	      	puts("<div class=\"row\">");
		        puts("<div class=\"container arrow\">");
					puts("<form class=\"form-inline\" role=\"form\" action=\"/cgi-bin/MP1/map_handler.cgi\" method=\"post\" enctype=\"multipart/form-data\">");
					    puts("<div class=\"form-group\">");
					    	printf("<input type=\"hidden\" class=\"form-control\" name=\"name\" value=\"%s\">",name);
							printf("<input type=\"hidden\" class=\"form-control\" name=\"yprev\" value=\"%d\">",pos.y);
							printf("<input type=\"hidden\" class=\"form-control\" name=\"xprev\" value=\"%d\">",pos.x);
							puts("<button type=\"submit hidden\" name=\"jhat\" value=\"-1\" class=\"btn\"><span class=\"glyphicon glyphicon-arrow-up\"></span></button>");
							puts("<button type=\"submit hidden\" name=\"jhat\" value=\"1\" class=\"btn\"><span class=\"glyphicon glyphicon-arrow-down\"></span></button>");
							puts("<button type=\"submit hidden\" name=\"ihat\" value=\"1\" class=\"btn\"><span class=\"glyphicon glyphicon-arrow-right\"></span></button>");
							puts("<button type=\"submit hidden\" name=\"ihat\" value=\"-1\" class=\"btn\"><span class=\"glyphicon glyphicon-arrow-left\"></span></button>");
					    puts("</div>");
					puts("</form>");
	        	puts("</div>");
		        puts("<div class=\"col-md-7 arrow\">");
					puts("<div class=\"dropdown\">");
						puts("<button class=\"btn dropdown-toggle\" type=\"button\" data-toggle=\"dropdown\">");
							puts("<h4 class=\"list-group-item-heading text-left\">Save Game</h4>");
						puts("</button>");
						puts("<ul class=\"dropdown-menu\">");
							puts("<form role=\"form\" action=\"/cgi-bin/MP1/map_handler.cgi\" method=\"post\" enctype=\"multipart/form-data\">");
								printf("<input type=\"hidden\" class=\"form-control\" name=\"name\" value=\"%s\">",name);
								printf("<input type=\"hidden\" class=\"form-control\" name=\"yprev\" value=\"%d\">",pos.y);
								printf("<input type=\"hidden\" class=\"form-control\" name=\"xprev\" value=\"%d\">",pos.x);
								if(cgi_mysql_getvalue(db_name, "Player", 1, 1, 1)) {
									printf("<li><button type=\"submit hidden\" name=\"sname\" value=\"%s\" class=\"btn btn-default\">Name:%s Level:%d</button></li>", cgi_mysql_getvalue(db_name, "Player", 1, 1, 1), cgi_mysql_getvalue(db_name, "Player", 1, 1, 1), atoi(cgi_mysql_getvalue(db_name, "Player", 1, 2, 1)));
								}
								else {
									printf("<li><button type=\"submit hidden\" name=\"sname\" value=\"empty_save_state\" class=\"btn btn-default\">empty_save_state</button></li>");
								}
								if(cgi_mysql_getvalue(db_name, "Player", 2, 1, 1)) {
									printf("<li><button type=\"submit hidden\" name=\"sname\" value=\"%s\" class=\"btn btn-default\">Name:%s Level:%d</button></li>", cgi_mysql_getvalue(db_name, "Player", 2, 1, 1), cgi_mysql_getvalue(db_name, "Player", 2, 1, 1), atoi(cgi_mysql_getvalue(db_name, "Player", 2, 2, 1)));
								}
								else {
									printf("<li><button type=\"submit hidden\" name=\"sname\" value=\"empty_save_state\" class=\"btn btn-default\">empty_save_state</button></li>");
								}
								if(cgi_mysql_getvalue(db_name, "Player", 3, 1, 1)) {
									printf("<li><button type=\"submit hidden\" name=\"sname\" value=\"%s\" class=\"btn btn-default\">Name:%s Level:%d</button></li>", cgi_mysql_getvalue(db_name, "Player", 3, 1, 1), cgi_mysql_getvalue(db_name, "Player", 3, 1, 1), atoi(cgi_mysql_getvalue(db_name, "Player", 3, 2, 1)));
								}
								else {
									printf("<li><button type=\"submit hidden\" name=\"sname\" value=\"empty_save_state\" class=\"btn btn-default\">empty_save_state</button></li>");
								}
							puts("</form>");
						puts("</ul>");
					puts("</div>");
					puts("<a href=\"/cgi-bin/MP1/main_menu.cgi\">EXIT</a>");
				puts("</div>");
			puts("<iframe name=\"result\" src=\"/MP1/iframesuccess.html\" style=\"height:90px; width:30%%\"></iframe>");
			puts("</div>");
	    puts("</div>");
	}
	else {
	    puts("<div class=\"container\">");
	      	puts("<div class=\"row\">");
		        puts("<div class=\"col-md-7 arrow\">");
					puts("<form class=\"form-inline\" role=\"form\" action=\"/cgi-bin/MP1/map_handler.cgi\" method=\"post\" enctype=\"multipart/form-data\">");
					    puts("<div class=\"form-group\">");
					    	printf("<input type=\"hidden\" class=\"form-control\" name=\"name\" value=\"%s\">",name);
							printf("<input type=\"hidden\" class=\"form-control\" name=\"yprev\" value=\"%d\">",pos.y);
							printf("<input type=\"hidden\" class=\"form-control\" name=\"xprev\" value=\"%d\">",pos.x);
							puts("<button type=\"submit hidden\" name=\"jhat\" value=\"-1\" class=\"btn disabled\" disabled><span class=\"glyphicon glyphicon-arrow-up\"></span></button>");
							puts("<button type=\"submit hidden\" name=\"jhat\" value=\"1\" class=\"btn disabled\" disabled><span class=\"glyphicon glyphicon-arrow-down\"></span></button>");
							puts("<button type=\"submit hidden\" name=\"ihat\" value=\"1\" class=\"btn disabled\" disabled><span class=\"glyphicon glyphicon-arrow-right\"></span></button>");
							puts("<button type=\"submit hidden\" name=\"ihat\" value=\"-1\" class=\"btn disabed\" disabled><span class=\"glyphicon glyphicon-arrow-left\"></span></button>");
					    puts("</div>");
					puts("</form>");
					puts("<form class=\"form-inline\" role=\"form\" action=\"/cgi-bin/MP1/map_handler.cgi\" method=\"post\" enctype=\"multipart/form-data\">");
					    puts("<div class=\"form-group\">");
					    	printf("<input type=\"hidden\" class=\"form-control\" name=\"name\" value=\"%s\">",name);
							printf("<input type=\"hidden\" class=\"form-control\" name=\"yprev\" value=\"%d\">",pos.y);
							printf("<input type=\"hidden\" class=\"form-control\" name=\"xprev\" value=\"%d\">",pos.x);
							puts("<button type=\"submit hidden\" name=\"Fight\" value=\"0\" class=\"btn\"><span class=\"glyphicon glyphicon-eye-open\">Fight</span></button>");
							puts("<button type=\"submit hidden\" name=\"Fight\" value=\"1\" class=\"btn\"><span class=\"glyphicon glyphicon-eye-close\"></span>Flight</button>");
					    puts("</div>");
					puts("</form>");
	        	puts("</div>");
	        	puts("<a href=\"/cgi-bin/MP1/main_menu.cgi\">EXIT</a>");
			puts("<iframe name=\"result\" src=\"/MP1/iframe.html\" style=\"height:90px; width:100%%\"></iframe>");
			puts("</div>");
	    puts("</div>");
	}
}

void print_map(coordinate_t pos)
{
    puts("<div class=\"container map\">");
      printf("<div style=\"position: relative; left: %dpx; top: %dpx\">",(107*(pos.x)),(56*(pos.y)));
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
		puts("margin-left: 25px;");
		puts("background-image: url(/MP1/Images/map_bg.jpg);");
		puts("background-repeat: no-repeat;");
		puts("background-position: center;");
    puts("}");
}

