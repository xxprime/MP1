#include <stdio.h>
#include "cgicustom.h"
#include <mysql/mysql.h>
#define db_name "db_RPG"

void print_menu();

int main()
{

  cgi_init("MP1 Title_menu");

  /*CHECKS FOR DATABASE, CREATES DATABASE IF DATABASE IS NONEXISTENT (ALSO CREATES THE TABLES)*/
  if(!cgi_mysql_check_db(db_name, 1)) {
    if(cgi_mysql_create_db(db_name, 1)) {
        cgi_mysql_statement(db_name, "CREATE TABLE Player(PlayerName varchar(10), PlayerLvl int, PlayerStr int, PlayerInt int, PlayerVit int, PlayerAgi int, PlayerDex int, PlayerExp int)", 1);
        cgi_mysql_statement(db_name, "CREATE TABLE Monster(MonsterName varchar(10), MonsterLvl int, MonsterStr int, MonsterInt int, MonsterVit int, MonsterAgi int, MonsterDex int)", 1);
    }
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
                  puts("<a href=\"#\" class=\"list-group-item\">");
                      puts("<h4 class \"list-group-item-heading\">How to Play</h4>");
                      puts("<p class=\"list-group-item-text\">Teaches you the basics of the game. It also teaches you how to win.</p>");
                  puts("</a>");
                  puts("<a href=\"/cgi-bin/MP1/new_game.cgi\" class=\"list-group-item\">");
                      puts("<h4 class=\"list-group-item-heading\">New Game</h4>");
                      puts("<p class=\"list-group-item-text\">Create a brand new game. Start from scratch.</p>");
                  puts("</a>");
                  puts("<a href=\"#\" class=\"list-group-item\">");
                      puts("<h4 class=\"list-group-item-heading\">Load Game</h4>");
                      puts("<p class=\"list-group-item-text\">Load a saved game. Continue your adventure.</p>");
                  puts("</a>");
              puts("</div>");
          puts("</div>");
      puts("</div>");
  puts("</div>");  
}