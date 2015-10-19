//test

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cgicustom.h"

void print_form(char *name, int str, int intel, int vit, int agi, int dex);
void update_stat(char* mode, int *str, int *intel, int *vit, int *agi, int *dex);

int main()
{
    char name[10]={'\0'};
    char *data = NULL;
    char *mode = NULL;
    int str = 0, intel = 0, vit = 0, agi = 0, dex = 0;

    cgi_init("MP1 Title_newgame");

    if(getenv("CONTENT_LENGTH")) {
        data = post_init(atoi(getenv("CONTENT_LENGTH")),1);
        strncpy(name,parse_data(data, "name", "multipart/form-data"),9);
        mode = parse_data(data, "mode", "multipart/form-data");
        str = atoi(parse_data(data, "str", "multipart/form-data"));
        intel = atoi(parse_data(data, "intel", "multipart/form-data"));
        vit = atoi(parse_data(data, "vit", "multipart/form-data"));
        agi = atoi(parse_data(data, "agi", "multipart/form-data"));
        dex = atoi(parse_data(data, "dex", "multipart/form-data"));
        update_stat(mode, &str, &intel, &vit, &agi, &dex);    
    }
    print_form(name, str, intel, vit, agi, dex);

    cgi_term();
    return 0;
}

void print_form(char *name, int str, int intel, int vit, int agi, int dex)
{
    puts("<div class=\"container\">");
        puts("<h2>Create a new character</h2>");
        puts("<form class =\"form-horizontal\" role=\"form\" action=\"/cgi-bin/MP1/new_game.cgi\" method=\"post\" enctype=\"multipart/form-data\">");
            puts("<div class=\"form-group\">");
                puts("<label class=\"control-label col-md-2\" for=\"name\">Name: </label>");
                puts("<div class=\"col-md-4\">");
    if(name[0] != '\0') {
                    printf("<input type=\"text\" class=\"form-control\" id=\"name\" name=\"name\" value=\"%s\" required>", name);
    }
    else {
                    printf("<input type=\"text\" class=\"form-control\" id=\"name\" name=\"name\" required>");
    }
                puts("</div>");
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
                puts("<div class=\"row\">");
                    puts("<div class=\"col-md-offset-1 col-md-10\">");
                        puts("<button type=\"submit hidden\" name=\"mode\" value=\"s-up\" class=\"btn\"><span class=\"glyphicon glyphicon-chevron-up\"></span></button>");
                    puts("</div>");
                puts("</div>");
                puts("<div class=\"row\">");
                    printf("<div class=\"col-md-offset-1 col-md-1\" style=\"margin-left: 125\">%d</div>", str);
                    puts("<div class=\"col-md-9\">Strength</div>");
                puts("</div>");
                puts("<div class=\"row\">");
                    puts("<div class=\"col-md-offset-1 col-md-10\">");
                        puts("<button type=\"submit hidden\" name=\"mode\" value=\"s-down\" class=\"btn\"><span class=\"glyphicon glyphicon-chevron-down\"></span></button>");
                    puts("</div>");
                puts("</div>");
            puts("</div>");
            puts("<div class=\"form-group\">");
                puts("<div class=\"row\">");
                    puts("<div class=\"col-md-offset-1 col-md-10\">");
                        puts("<button type=\"submit hidden\" name=\"mode\" value=\"i-up\" class=\"btn\"><span class=\"glyphicon glyphicon-chevron-up\"></span></button>");
                    puts("</div>");
                puts("</div>");
                puts("<div class=\"row\">");
                    printf("<div class=\"col-md-offset-1 col-md-1\" style=\"margin-left: 125\">%d</div>", intel);
                    puts("<div class=\"col-md-9\">Intelligence</div>");
                puts("</div>");
                puts("<div class=\"row\">");
                    puts("<div class=\"col-md-offset-1 col-md-10\">");
                        puts("<button type=\"submit hidden\" name=\"mode\" value=\"i-down\" class=\"btn\"><span class=\"glyphicon glyphicon-chevron-down\"></span></button>");
                    puts("</div>");
                puts("</div>");
            puts("</div>");
            puts("<div class=\"form-group\">");
                puts("<div class=\"row\">");
                    puts("<div class=\"col-md-offset-1 col-md-10\">");
                        puts("<button type=\"submit hidden\" name=\"mode\" value=\"v-up\" class=\"btn\"><span class=\"glyphicon glyphicon-chevron-up\"></span></button>");
                    puts("</div>");
                puts("</div>");
                puts("<div class=\"row\">");
                    printf("<div class=\"col-md-offset-1 col-md-1\" style=\"margin-left: 125\">%d</div>", vit);
                    puts("<div class=\"col-md-9\">Vitality</div>");
                puts("</div>");
                puts("<div class=\"row\">");
                    puts("<div class=\"col-md-offset-1 col-md-10\">");
                        puts("<button type=\"submit hidden\" name=\"mode\" value=\"v-down\" class=\"btn\"><span class=\"glyphicon glyphicon-chevron-down\"></span></button>");
                    puts("</div>");
                puts("</div>");
            puts("</div>");
            puts("<div class=\"form-group\">");
                puts("<div class=\"row\">");
                    puts("<div class=\"col-md-offset-1 col-md-10\">");
                        puts("<button type=\"submit hidden\" name=\"mode\" value=\"a-up\" class=\"btn\"><span class=\"glyphicon glyphicon-chevron-up\"></span></button>");
                    puts("</div>");
                puts("</div>");
                puts("<div class=\"row\">");
                    printf("<div class=\"col-md-offset-1 col-md-1\" style=\"margin-left: 125\">%d</div>", agi);
                    puts("<div class=\"col-md-9\">Agility</div>");
                puts("</div>");
                puts("<div class=\"row\">");
                    puts("<div class=\"col-md-offset-1 col-md-10\">");
                        puts("<button type=\"submit hidden\" name=\"mode\" value=\"a-down\" class=\"btn\"><span class=\"glyphicon glyphicon-chevron-down\"></span></button>");
                    puts("</div>");
                puts("</div>");
            puts("</div>");
            puts("<div class=\"form-group\">");
                puts("<div class=\"row\">");
                    puts("<div class=\"col-md-offset-1 col-md-10\">");
                        puts("<button type=\"submit hidden\" name=\"mode\" value=\"d-up\" class=\"btn\"><span class=\"glyphicon glyphicon-chevron-up\"></span></button>");
                    puts("</div>");
                puts("</div>");
                puts("<div class=\"row\">");
                    printf("<div class=\"col-md-offset-1 col-md-1\" style=\"margin-left: 125\">%d</div>",dex);
                    puts("<div class=\"col-md-9\">Dexterity</div>");
                puts("</div>");
                puts("<div class=\"row\">");
                    puts("<div class=\"col-md-offset-1 col-md-10\">");
                        puts("<button type=\"submit hidden\" name=\"mode\" value=\"d-down\" class=\"btn\"><span class=\"glyphicon glyphicon-chevron-down\"></span></button>");
                    puts("</div>");
                puts("</div>");
            puts("</div>");
            puts("<div class=\"row\">");
                printf("<div class=\"col-md-offset-1 col-md-11\">%d stat point/s left</div>", (10-str-intel-vit-agi-dex));
            puts("</div>");
            puts("<div class=\"form-group\">");
                puts("<div class=\"control-label col-md-2\">");
    if(10-str-intel-vit-agi-dex) {
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

void update_stat(char* mode, int *str, int *intel, int *vit, int *agi, int *dex)
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
        case 'g': break;
        default: break;
    }
}