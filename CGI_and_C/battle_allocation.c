#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h> //CHANGE THIS TO PROPER DIRECTORY
#include "cgicustom.h"
#define STATEMENT_LEN 100
#define db_name "db_RPG"
#define db_name_temp "db_RPG_temp"
#define USER "root"
#define PASS "root"

void print_form(char *name, int str, int intel, int vit, int agi, int dex, int max);
int update_stat(char *mode, int *str, int *intel, int *vit, int *agi, int *dex);
void goto_map(char *name, int str, int intel, int vit, int agi, int dex);

int main()
{
    char name[10]={'\0'};
    char *data = NULL;
    char *mode = NULL;
    int str, intel, vit, agi, dex, max;
    strcpy(name, cgi_mysql_getvalue(db_name_temp, "Player", 1, 1, 1));
    str = atoi(cgi_mysql_getvalue(db_name_temp, "Player", 1, 3, 1));
    intel = atoi(cgi_mysql_getvalue(db_name_temp, "Player", 1, 4, 1));
    vit = atoi(cgi_mysql_getvalue(db_name_temp, "Player", 1, 5, 1));
    agi = atoi(cgi_mysql_getvalue(db_name_temp, "Player", 1, 6, 1));
    dex = atoi(cgi_mysql_getvalue(db_name_temp, "Player", 1, 7, 1));
    max = str + intel + vit + agi + dex + 5;
    cgi_init("SANIC_Allocation");

    if(getenv("CONTENT_LENGTH")) {
        data = post_init(atoi(getenv("CONTENT_LENGTH")),0);
        strncpy(name,parse_data(data, "name", "multipart/form-data"),9);
        mode = parse_data(data, "mode", "multipart/form-data");
        str = atoi(parse_data(data, "str", "multipart/form-data"));
        intel = atoi(parse_data(data, "intel", "multipart/form-data"));
        vit = atoi(parse_data(data, "vit", "multipart/form-data"));
        agi = atoi(parse_data(data, "agi", "multipart/form-data"));
        dex = atoi(parse_data(data, "dex", "multipart/form-data"));
        max = atoi(parse_data(data, "max", "multipart/form-data"));
        if(update_stat(mode, &str, &intel, &vit, &agi, &dex)) {
            goto_map(name, str, intel, vit, agi, dex);
        }    
    }
    print_form(name, str, intel, vit, agi, dex, max);

    cgi_term();
    return 0;
}

void goto_map(char *name, int str, int intel, int vit, int agi, int dex)
{
    int lvl = atoi(cgi_mysql_getvalue(db_name_temp, "Player", 1, 2, 1));
    char statement[STATEMENT_LEN];
    sprintf(statement,"DELETE FROM Player WHERE PlayerName=\"%s\"", name);
    cgi_mysql_statement(db_name_temp, statement, 1);
    sprintf(statement,"INSERT INTO Player VALUES(\"%s\", %d, %d, %d, %d, %d, %d, 0, %d)", name, lvl+1, str, intel, vit, agi, dex, vit);
    cgi_mysql_statement(db_name_temp,statement,1);
    puts("<meta http-equiv=\"refresh\" content=\"0; url=/cgi-bin/MP1/map_handler.cgi\"/>");
}

void print_form(char *name, int str, int intel, int vit, int agi, int dex, int max)
{
    puts("<div class=\"container\">");
        puts("<h2>LEVEL UP! Allocate Stats!</h2>");
        puts("<form class =\"form-horizontal\" role=\"form\" action=\"/cgi-bin/MP1/battle_allocation.cgi\" method=\"post\" enctype=\"multipart/form-data\">");
            puts("<div class=\"form-group\">");
                puts("<label class=\"control-label col-md-2\" for=\"name\">Name: </label>");
                puts("<div class=\"col-md-4\">");
                    printf("<input type=\"text\" class=\"form-control disabled\" id=\"name\" name=\"name\" value=\"%s\" disabled>", name);
                puts("</div>");
            puts("</div>");
            puts("<div class=\"form-group\">");
                printf("<input type=\"hidden\" class=\"form-control\" name=\"name\" value=\"%s\" ",name);
            puts("</div>");
            puts("<div class=\"form-group\">");
                printf("<input type=\"hidden\" class=\"form-control\" name=\"str\" value=\"%d\" ",str);
            puts("</div>");
            puts("<div class=\"form-group\">");
                printf("<input type=\"hidden\" class=\"form-control\" name=\"intel\" value=\"%d\" ",intel);
            puts("</div>");
            puts("<div class=\"form-group\">");
                printf("<input type=\"hidden\" class=\"form-control\" name=\"vit\" value=\"%d\" ",vit);
            puts("</div>");
            puts("<div class=\"form-group\">");
                printf("<input type=\"hidden\" class=\"form-control\" name=\"agi\" value=\"%d\" ",agi);
            puts("</div>");
            puts("<div class=\"form-group\">");
                printf("<input type=\"hidden\" class=\"form-control\" name=\"dex\" value=\"%d\" ",dex);
            puts("</div>");
            puts("<div class=\"form-group\">");
                printf("<input type=\"hidden\" class=\"form-control\" name=\"max\" value=\"%d\" ",max);
            puts("</div>");
            puts("<div class=\"form-group\">");
                puts("<div class=\"row\">");
                    puts("<div class=\"col-md-offset-1 col-md-10\">");
    if(!(max-str-intel-vit-agi-dex)) {
                        puts("<button type=\"submit hidden\" name=\"mode\" value=\"s-up\" class=\"btn disabled\" disabled><span class=\"glyphicon glyphicon-chevron-up\"></span></button>");
    }
    else {
                        puts("<button type=\"submit hidden\" name=\"mode\" value=\"s-up\" class=\"btn\"><span class=\"glyphicon glyphicon-chevron-up\"></span></button>");
    }
                    puts("</div>");
                puts("</div>");
                puts("<div class=\"row\">");
                    printf("<div class=\"col-md-offset-1 col-md-1\" style=\"margin-left: 125\">%d</div>", str);
                    puts("<div class=\"col-md-9\">Strength</div>");
                puts("</div>");
            puts("</div>");
            puts("<div class=\"form-group\">");
                puts("<div class=\"row\">");
                    puts("<div class=\"col-md-offset-1 col-md-10\">");
    if(!(max-str-intel-vit-agi-dex)) {
                        puts("<button type=\"submit hidden\" name=\"mode\" value=\"i-up\" class=\"btn disabled\" disabled><span class=\"glyphicon glyphicon-chevron-up\"></span></button>");
    }
    else {
                        puts("<button type=\"submit hidden\" name=\"mode\" value=\"i-up\" class=\"btn\"><span class=\"glyphicon glyphicon-chevron-up\"></span></button>");
    }
                    puts("</div>");
                puts("</div>");
                puts("<div class=\"row\">");
                    printf("<div class=\"col-md-offset-1 col-md-1\" style=\"margin-left: 125\">%d</div>", intel);
                    puts("<div class=\"col-md-9\">Intelligence</div>");
                puts("</div>");
            puts("</div>");
            puts("<div class=\"form-group\">");
                puts("<div class=\"row\">");
                    puts("<div class=\"col-md-offset-1 col-md-10\">");
    if(!(max-str-intel-vit-agi-dex)) {
                        puts("<button type=\"submit hidden\" name=\"mode\" value=\"v-up\" class=\"btn disabled\" disabled><span class=\"glyphicon glyphicon-chevron-up\"></span></button>");
    }
    else {
                        puts("<button type=\"submit hidden\" name=\"mode\" value=\"v-up\" class=\"btn\"><span class=\"glyphicon glyphicon-chevron-up\"></span></button>");
    }
                    puts("</div>");
                puts("</div>");
                puts("<div class=\"row\">");
                    printf("<div class=\"col-md-offset-1 col-md-1\" style=\"margin-left: 125\">%d</div>", vit);
                    puts("<div class=\"col-md-9\">Vitality</div>");
                puts("</div>");
            puts("</div>");
            puts("<div class=\"form-group\">");
                puts("<div class=\"row\">");
                    puts("<div class=\"col-md-offset-1 col-md-10\">");
    if(!(max-str-intel-vit-agi-dex)) {
                        puts("<button type=\"submit hidden\" name=\"mode\" value=\"a-up\" class=\"btn disabled\" disabled><span class=\"glyphicon glyphicon-chevron-up\"></span></button>");
    }
    else {
                        puts("<button type=\"submit hidden\" name=\"mode\" value=\"a-up\" class=\"btn\"><span class=\"glyphicon glyphicon-chevron-up\"></span></button>");
    }
                    puts("</div>");
                puts("</div>");
                puts("<div class=\"row\">");
                    printf("<div class=\"col-md-offset-1 col-md-1\" style=\"margin-left: 125\">%d</div>", agi);
                    puts("<div class=\"col-md-9\">Agility</div>");
                puts("</div>");
            puts("</div>");
            puts("<div class=\"form-group\">");
                puts("<div class=\"row\">");
                    puts("<div class=\"col-md-offset-1 col-md-10\">");
    if(!(max-str-intel-vit-agi-dex)) {
                        puts("<button type=\"submit hidden\" name=\"mode\" value=\"d-up\" class=\"btn disabled\" disabled><span class=\"glyphicon glyphicon-chevron-up\"></span></button>");
    }
    else {
                        puts("<button type=\"submit hidden\" name=\"mode\" value=\"d-up\" class=\"btn\"><span class=\"glyphicon glyphicon-chevron-up\"></span></button>");
    }
                    puts("</div>");
                puts("</div>");
                puts("<div class=\"row\">");
                    printf("<div class=\"col-md-offset-1 col-md-1\" style=\"margin-left: 125\">%d</div>",dex);
                    puts("<div class=\"col-md-9\">Dexterity</div>");
                puts("</div>");
            puts("</div>");
            puts("<div class=\"row\">");
                printf("<div class=\"col-md-offset-1 col-md-11\">%d stat point/s left</div>", (max-str-intel-vit-agi-dex));
            puts("</div>");
            puts("<div class=\"form-group\">");
                puts("<div class=\"control-label col-md-2\">");
    if(max-str-intel-vit-agi-dex) {
                    puts("<button type=\"submit hidden\" name=\"mode\" value=\"g-go\" class=\"btn btn-default disabled\" disabled>Go</button>");
    }
    else {
                    puts("<button type=\"submit hidden\" name=\"mode\" value=\"g-go\" class=\"btn btn-default\">Go</button>");
    }
                puts("</div>");
            puts("</div>");
        puts("</form>");
    puts("</div>");
}

int update_stat(char* mode, int *str, int *intel, int *vit, int *agi, int *dex)
{
    char stat = 'x';
    char change[5];
    int increment = 0;

    sscanf(mode,"%c-%s",&stat,change);

    if(!strcmp(change, "up")) {
        increment = 1;
    }
    else {
        increment = -1;
    }

    switch(stat) {
        case 's': *str = *str + increment; break;
        case 'i': *intel = *intel + increment; break;
        case 'v': *vit = *vit + increment; break;
        case 'a': *agi = *agi + increment; break;
        case 'd': *dex = *dex + increment; break;
        case 'g': return 1; break;
        default: break;
    }
    return 0;
}