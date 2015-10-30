#include <stdio.h>
#include <stdlib.h>
#include "cgicustom.h"
#include <mysql/mysql.h>
#define db_name "db_RPG"
#define db_name_temp "db_RPG_temp"

void print_menu();

int main()
{

  cgi_init("MP1 Title_menu");

  /*CHECKS FOR DATABASE, CREATES DATABASE IF DATABASE IS NONEXISTENT (ALSO CREATES THE TABLES)*/
  if(!cgi_mysql_check_db(db_name, 0)) {
    if(cgi_mysql_create_db(db_name, 1)) {
        cgi_mysql_statement(db_name, "CREATE TABLE Player(PlayerName varchar(10), PlayerLvl int, PlayerStr int, PlayerInt int, PlayerVit int, PlayerAgi int, PlayerDex int, PlayerExp int)", 1);
        cgi_mysql_statement(db_name, "CREATE TABLE Monster(MonsterName varchar(10), MonsterLvl int, Advantage int)", 1);
    }
  }

  /*CHECKS FOR TEMP DATABASE, CREATES DATABASE IF DATABASE IS NONEXISTENT (ALSO CREATES THE TABLES)*/
  if(!cgi_mysql_check_db(db_name_temp, 0)) {
    if(cgi_mysql_create_db(db_name_temp, 1)) {
        cgi_mysql_statement(db_name_temp, "CREATE TABLE Player(PlayerName varchar(10), PlayerLvl int, PlayerStr int, PlayerInt int, PlayerVit int, PlayerAgi int, PlayerDex int, PlayerExp int)", 1);
    }
  }

  if(cgi_mysql_check_db(db_name_temp,0)) {
    cgi_mysql_statement(db_name_temp, "TRUNCATE TABLE Player", 1);
  }
  print_menu();

  cgi_term();

  return 0;
}

void print_menu()
{
  puts("<div class=\"container\">");
      puts("<div class=\"row\">");
          puts("<div class=\"col-md-offset-4 col-md-4 col-md-offset-4\">");
          puts("<h2 class=\"text-center\">TITLE</h2>");
          puts("</div>");
      puts("</div>");

      puts("<div class=\"row\">");
          puts("<div class=\"col-md-2\"></div>");
          puts("<div class=\"col-md-8\">");
              puts("<div class=\"list-group\"> <!--Add Badges, form for new/load, disable load if save files are non-existent-->");
                  puts("<a href=\"/cgi-bin/MP1/battle_handler.cgi\" class=\"list-group-item\">");
                      puts("<h4 class \"list-group-item-heading\">How to Play</h4>");
                      puts("<p class=\"list-group-item-text\">Teaches you the basics of the game. It also teaches you how to win.</p>");
                  puts("</a>");
                  puts("<a href=\"/cgi-bin/MP1/new_game.cgi\" class=\"list-group-item\">");
                      puts("<h4 class=\"list-group-item-heading\">New Game</h4>");
                      puts("<p class=\"list-group-item-text\">Create a brand new game. Start from scratch.</p>");
                  puts("</a>");
                  puts("<div class=\"list-group-item\">");
                      puts("<div class=\"dropdown\">");
                          puts("<button class=\"btn dropdown-toggle\" type=\"button\" data-toggle=\"dropdown\">");
                              puts("<h4 class=\"list-group-item-heading text-left\">Load Game</h4>");
                              puts("<p class=\"list-group-item-text\">Load a saved game. Continue your adventure.</p>");
                          puts("</button>");


                          puts("<ul class=\"dropdown-menu\">");
                              puts("<form role=\"form\" action=\"/cgi-bin/MP1/map_handler.cgi\" method=\"post\" enctype=\"multipart/form-data\">");
                              if(cgi_mysql_getvalue(db_name, "Player", 1, 1, 1)) {
                                printf("<li><button type=\"submit hidden\" name=\"name\" value=\"%s\" class=\"btn btn-default\">Name:%s Level:%d</button></li>", cgi_mysql_getvalue(db_name, "Player", 1, 1, 1), cgi_mysql_getvalue(db_name, "Player", 1, 1, 1), atoi(cgi_mysql_getvalue(db_name, "Player", 1, 2, 1)));
                              }
                              if(cgi_mysql_getvalue(db_name, "Player", 2, 1, 1)) {
                                printf("<li><button type=\"submit hidden\" name=\"name\" value=\"%s\" class=\"btn btn-default\">Name:%s Level:%d</button></li>", cgi_mysql_getvalue(db_name, "Player", 2, 1, 1), cgi_mysql_getvalue(db_name, "Player", 2, 1, 1), atoi(cgi_mysql_getvalue(db_name, "Player", 2, 2, 1)));
                              }
                              if(cgi_mysql_getvalue(db_name, "Player", 3, 1, 1)) {
                                printf("<li><button type=\"submit hidden\" name=\"name\" value=\"%s\" class=\"btn btn-default\">Name:%s Level:%d</button></li>", cgi_mysql_getvalue(db_name, "Player", 3, 1, 1), cgi_mysql_getvalue(db_name, "Player", 3, 1, 1), atoi(cgi_mysql_getvalue(db_name, "Player", 3, 2, 1)));
                              }
                              puts("</form>");
                          puts("</ul>");


                      puts("</div>");
                  puts("</div>");
              puts("</div>");
          puts("</div>");
      puts("</div>");
  puts("</div>");  
}