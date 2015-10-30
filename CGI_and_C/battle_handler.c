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
stats_t get_stats(char *db, char *tablename);

int main()
{
	cgi_init_beforecss("MP1 Title_Map");
	cgi_init_aftercss();

	print_battle();

	cgi_term();
	return 0;
}

stats_t get_stats(char *db, char *tablename)
{
	stats_t stats;

	stats.level = atoi(cgi_mysql_getvalue(db, tablename, 1, 2, 1));
	stats.strength = atoi(cgi_mysql_getvalue(db, tablename, 1, 3, 1));
	stats.intelligence = atoi(cgi_mysql_getvalue(db, tablename, 1, 4, 1));
	stats.vitality = atoi(cgi_mysql_getvalue(db, tablename, 1, 5, 1));
	stats.agility = atoi(cgi_mysql_getvalue(db, tablename, 1, 6, 1));
	stats.dexterity = atoi(cgi_mysql_getvalue(db, tablename, 1, 7, 1));
	stats.health = atoi(cgi_mysql_getvalue(db, tablename, 1, 9, 1));

  return stats;
}

void print_battle()
{
	char playerName[10];
	char monsterName[10];
	stats_t player;
	stats_t monster;

	strcpy(playerName,cgi_mysql_getvalue(db_name_temp, "Player", 1, 1, 1));
	strcpy(monsterName,cgi_mysql_getvalue(db_name, "Monster", 1, 1, 1));

	player = get_stats(db_name_temp, "Player");
	monster = get_stats(db_name, "Monster");

	puts("<div class=\"container\" style=\"margin:20px\">");
		puts("<div class=\"row\">");
		printf("<div class=\"col-md-6 text-center\">%s</div>", playerName);
		printf("<div class=\"col-md-6 text-center\">%s</div>", monsterName);
		puts("</div>");
		puts("<div class=\"row\">");
		puts("<div class=\"col-md-6 text-center\"><img src=\"/MP1/Images/mlg_sanic.png\" alt=\"SANIC\" style=\"width:200px; height:200px;\"></div>");
		printf("<div class=\"col-md-6 text-center\"><img src=\"/MP1/Images/%s.png\" alt=\"%s\" style=\"width:200px; height:200px;\"></div>", monsterName, monsterName);
		puts("</div>");
		puts("<div class=\"row\">");
		printf("<div class=\"col-md-6 text-center\">HP:%d</div>", player.health);
		printf("<div class=\"col-md-6 text-center\">HP:%d</div>", monster.health);
		puts("</div>");
		puts("<div class=\"row\">");
		printf("<div class=\"col-md-6 text-center\">Level:%d</div>", player.level);
		printf("<div class=\"col-md-6 text-center\">Level:%d</div>", monster.level);
		puts("</div>");
		puts("<div class=\"row\">");
			puts("<div class=\"col-md-6 text-center\">");
				puts("<div class=\"row\">");
					printf("<div class=\"col-md-12 text-left\">STR:%d</div>", player.strength);
				puts("</div>");
				puts("<div class=\"row\">");
					printf("<div class=\"col-md-6 text-left\">INT:%d</div>", player.intelligence);
					printf("<div class=\"col-md-6 text-center\">VIT:%d</div>", player.vitality);
				puts("</div>");
				puts("<div class=\"row\">");
					printf("<div class=\"col-md-6 text-left\">AGI:%d</div>", player.agility);
					printf("<div class=\"col-md-6 text-center\">DEX:%d</div>", player.dexterity);
				puts("</div>");
			puts("</div>");
			puts("<div class=\"col-md-6 text-center\">");
				puts("<div class=\"row\">");
					printf("<div class=\"col-md-12 text-left\">STR:%d</div>", monster.strength);
				puts("</div>");
				puts("<div class=\"row\">");
					printf("<div class=\"col-md-6 text-left\">INT:%d</div>", monster.intelligence);
					printf("<div class=\"col-md-6 text-center\">VIT:%d</div>", monster.vitality);
				puts("</div>");
				puts("<div class=\"row\">");
					printf("<div class=\"col-md-6 text-left\">AGI:%d</div>", monster.agility);
					printf("<div class=\"col-md-6 text-center\">DEX:%d</div>", monster.dexterity);
				puts("</div>");
			puts("</div>");
		puts("</div>");		
		puts("<div class=\"container\">");
			puts("<form role=\"form\" action=\"\" method=\"post\" enctype=\"multipart/form-data\">");
				puts("<label class=\"radio-inline\">");
			  		puts("<input type=\"radio\" name=\"Action\" value=\"Attack\" checked>Attack");
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
