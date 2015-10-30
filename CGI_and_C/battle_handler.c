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

void print_battle(int gameover);
int resolve_action(char *action);
stats_t get_stats(char *db, char *tablename);
void put_stats(char *db, char *tablename, stats_t stats, int advantageorexp);

int main()
{
	int gameover = 0;
	char *data = NULL;
	char action[7];
	cgi_init_beforecss("MP1 Title_Battle");
	cgi_init_aftercss();

    if(getenv("CONTENT_LENGTH")) {
        data = post_init(atoi(getenv("CONTENT_LENGTH")),0);
        strcpy(action,parse_data(data,"Action","multipart/form-data"));
        gameover = resolve_action(action);
    }

	print_battle(gameover);
	cgi_term();
	return 0;
}

void put_stats(char *db, char *tablename, stats_t stats, int advantageorexp)
{
	char name[10];
	strcpy(name,cgi_mysql_getvalue(db, tablename, 1, 1, 1));

	char statement[STATEMENT_LEN];
	sprintf(statement, "TRUNCATE TABLE %s",tablename);
	cgi_mysql_statement(db, statement, 1);
	sprintf(statement,"INSERT INTO %s VALUES(\"%s\", %d, %d, %d, %d, %d, %d, %d, %d)",tablename, name, stats.level, stats.strength, stats.intelligence, stats.vitality, stats.agility, stats.dexterity, advantageorexp, stats.health);
	cgi_mysql_statement(db, statement, 1);
}

int resolve_action(char *action) 
{
	stats_t player;
	stats_t monster;
	player = get_stats(db_name_temp, "Player");
	monster = get_stats(db_name, "Monster");
	int gameover = 0;

	int advantage = atoi(cgi_mysql_getvalue(db_name,"Monster",1,8,1));
	int playerexp = atoi(cgi_mysql_getvalue(db_name_temp, "Player",1,8,1));
    if(!strcmp(action,"Attack")) {
    	if(advantage) {
    		//MONSTER FIRST
    		if(hit_success(monster.dexterity, player.agility)) {
    			player.health = cur_health(player.health, dmg_attack(monster.strength, monster.level)/3, 0);
    		}
    		if(player.health == 0) {
    			gameover = 1;
    		}

    		//PLAYER'S TURN
    		if(hit_success(player.dexterity, monster.agility) && !gameover) {
    			monster.health = cur_health(monster.health, dmg_attack(player.strength, player.level)/3, 0);
    		}
    		if(monster.health == 0) {
    			player.health = player.vitality;
    			playerexp = playerexp + 1;
    			if(playerexp == player.level) {
    				//allocation then back to map
    			}
    			else {
    				put_stats(db_name_temp, "Player", player, playerexp);
    				puts("<meta http-equiv=\"refresh\" content=\"0; url=/cgi-bin/MP1/map_handler.cgi\"/>");
    			}
    		}
    	}
    	else {
    		//PLAYER FIRST
    		if(hit_success(player.dexterity, monster.agility)) {
    			monster.health = cur_health(monster.health, dmg_attack(player.strength, player.level)/3, 0);
    		}
    		if(monster.health == 0) {
    			player.health = player.vitality;
    			playerexp = playerexp + 1;
    			if(playerexp == player.level) {
    				//allocation then back to map
    			}
    			else {
    				put_stats(db_name_temp, "Player", player, playerexp);
    				puts("<meta http-equiv=\"refresh\" content=\"0; url=/cgi-bin/MP1/map_handler.cgi\"/>");
    			}
    		}

    		//MONSTER'S TURN
    		if(hit_success(monster.dexterity, player.agility)) {
    			player.health = cur_health(player.health, dmg_attack(monster.strength, monster.level)/3, 0);
    		}
    		if(player.health == 0) {
    			gameover = 1;
    		}
    	}
    }
    else if(!strcmp(action,"Defend")) {
    	if(advantage) {
    		//MONSTER FIRST
    		if(hit_success(monster.dexterity, player.agility)) {
    			player.health = cur_health(player.health, dmg_attack(monster.strength, monster.level)/2, dmg_reduction(player.vitality, player.level));
    		}
    		if(player.health == 0) {
    			gameover = 1;
    		}

    		//PLAYER'S TURN
    		if(hit_success(player.dexterity, monster.agility) && !gameover) {
    			monster.health = cur_health(monster.health, dmg_attack(player.strength, player.level)/6, 0);
    		}
    		if(monster.health == 0) {
    			player.health = player.vitality;
    			playerexp = playerexp + 1;
    			if(playerexp == player.level) {
    				//allocation then back to map
    			}
    			else {
    				put_stats(db_name_temp, "Player", player, playerexp);
    				puts("<meta http-equiv=\"refresh\" content=\"0; url=/cgi-bin/MP1/map_handler.cgi\"/>");
    			}
    		}
    	}
    	else {
    		//PLAYER FIRST
    		if(hit_success(player.dexterity, monster.agility)) {
    			monster.health = cur_health(monster.health, dmg_attack(player.strength, player.level)/6, 0);
    		}
    		if(monster.health == 0) {
    			player.health = player.vitality;
    			playerexp = playerexp + 1;
    			if(playerexp == player.level) {
    				//allocation then back to map
    			}
    			else {
    				put_stats(db_name_temp, "Player", player, playerexp);
    				puts("<meta http-equiv=\"refresh\" content=\"0; url=/cgi-bin/MP1/map_handler.cgi\"/>");
    			}
    		}

    		//MONSTER'S TURN
    		if(hit_success(monster.dexterity, player.agility)) {
    			player.health = cur_health(player.health, dmg_attack(monster.strength, monster.level)/2, dmg_reduction(player.vitality, player.level));
    		}
    		if(player.health == 0) {
    			gameover = 1;
    		}
    	}
    }
    else if(!strcmp(action,"Skill")) {
    	if(advantage) {
    		//MONSTER FIRST
    		if(hit_success(monster.dexterity, player.agility)) {
    			player.health = cur_health(player.health, dmg_attack(monster.strength, monster.level)/3, 0);
    		}
    		if(player.health == 0) {
    			gameover = 1;
    		}

    		//PLAYER'S TURN
    		if(hit_success(player.dexterity, monster.agility) && !gameover) {
    			monster.health = cur_health(monster.health, dmg_skill(player.intelligence, player.level)/3, 0);
    			player.health = cur_health(player.health, dmg_skill(player.intelligence, player.level)/6, 0);
    			if(player.health == 0) {
    				player.health = 1;
    			}
    		}
    		if(monster.health == 0) {
    			player.health = player.vitality;
    			playerexp = playerexp + 1;
    			if(playerexp == player.level) {
    				//allocation then back to map
    			}
    			else {
    				put_stats(db_name_temp, "Player", player, playerexp);
    				puts("<meta http-equiv=\"refresh\" content=\"0; url=/cgi-bin/MP1/map_handler.cgi\"/>");
    			}
    		}
    	}
    	else {
    		//PLAYER FIRST
    		if(hit_success(player.dexterity, monster.agility)) {
    			monster.health = cur_health(monster.health, dmg_skill(player.intelligence, player.level)/3, 0);
    			player.health = cur_health(player.health, dmg_skill(player.intelligence, player.level)/6, 0);
    			if(player.health == 0) {
    				player.health = 1;
    			}
    		}
    		if(monster.health == 0) {
    			player.health = player.vitality;
    			playerexp = playerexp + 1;
    			if(playerexp == player.level) {
    				//allocation then back to map
    			}
    			else {
					put_stats(db_name_temp, "Player", player, playerexp);
    				puts("<meta http-equiv=\"refresh\" content=\"0; url=/cgi-bin/MP1/map_handler.cgi\"/>");
    			}
    		}

    		//MONSTER'S TURN
    		if(hit_success(monster.dexterity, player.agility) && !gameover) {
    			player.health = cur_health(player.health, dmg_attack(monster.strength, monster.level)/3, 0);
    		}
    		if(player.health == 0) {
    			gameover = 1;
    		}
    	}
    }
    else if(!strcmp(action,"Run")) {
    	if(advantage) {
    		//MONSTER FIRST
    		if(hit_success(monster.dexterity, player.agility)) {
    			player.health = cur_health(player.health, dmg_attack(monster.strength, monster.level)/3, 0);
    		}
    		if(player.health == 0) {
    			gameover = 1;
    		}

    		//PLAYER'S TURN
	    	if(flee_success(player.agility, player.level, monster.level) && !gameover) {
	    		player.health = player.vitality;
	    		put_stats(db_name_temp, "Player", player, playerexp);
	    	    puts("<meta http-equiv=\"refresh\" content=\"0; url=/cgi-bin/MP1/map_handler.cgi\"/>");
	    	}
    	}
    	else {
    		//PLAYER FIRST
	    	if(flee_success(player.agility, player.level, monster.level)) {
	    		player.health = player.vitality;
	    		put_stats(db_name_temp, "Player", player, playerexp);
	    	    puts("<meta http-equiv=\"refresh\" content=\"0; url=/cgi-bin/MP1/map_handler.cgi\"/>");
	    	}

    		//MONSTER'S TURN
    		if(hit_success(monster.dexterity, player.agility)) {
    			player.health = cur_health(player.health, dmg_attack(monster.strength, monster.level)/3, 0);
    		}
    		if(player.health == 0) {
    			gameover = 1;
    		}
    	}
    }
	put_stats(db_name_temp, "Player", player, playerexp);
	put_stats(db_name, "Monster", monster, advantage);
	return gameover;
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

void print_battle(int gameover)
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
			if(!gameover) {
				puts("<button type=\"submit\" class=\"btn btn-default\">Submit</button>");
			}
			else if(gameover) {
				puts("<button type=\"submit\" class=\"btn btn-default disabled\" disabled>Submit</button>");
			}
			puts("</form>");
		puts("</div>");
	if(!gameover) {
		puts("<div class=\"container\">");
			puts("<iframe name=\"gameover\" style=\"height:90px; width:30%%\"></iframe>");
		puts("</div>");
	}
	else if(gameover) {
		puts("<div class=\"container\">");
			puts("<iframe name=\"gameover\" src =\"/MP1/iframegameover.html\" style=\"height:90px; width:30%%\"></iframe>");
		puts("</div>");
	}
		puts("<div class=\"container\">");
			puts("<button class=\"btn dropdown-toggle disabled\" type=\"button\" data-toggle=\"dropdown\" disabled>");
				puts("<h4 class=\"list-group-item-heading text-left\">Save Game</h4>");
			puts("</button>");
			puts("<a href=\"/cgi-bin/MP1/main_menu.cgi\">EXIT GAME</a>");
		puts("</div>");
	puts("</div>");
}
