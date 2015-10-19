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
        data = post_init(atoi(getenv("CONTENT_LENGTH")),0);
        strncpy(name,parse_data(data, name, "multipart/form-data"),9);
        mode = parse_data(data, mode, "multipart/form-data");
    }

    printf("%s, %d",data, mode);

    //update_stat(mode, &str, &intel, &vit, &agi, &dex);
    //printf_form(name, str, intel, vit, agi, dex);

    cgi_term();
    return 0;
}

void print_form(char *name, int str, int intel, int vit, int agi, int dex)
{
    puts("<div class=\"container\">");
        puts("<h2>Create a new character</h2>");
        puts("<form class =\"form-horizontal\" role=\"form\">");
            puts("<div class=\"form-group\">");
                puts("<label class=\"control-label col-md-2\" for=\"name\">Name: </label>");
                puts("<div class=\"col-md-4\">");
                    puts("<input type=\"text\" class=\"form-control\" id=\"name\" name=\"name\" required>");
                puts("</div>");
            puts("</div>");
            puts("<div class=\"form-group\">");
                puts("<div class=\"row\">");
                    puts("<div class=\"col-md-offset-1 col-md-10\">");
                        puts("<button type=\"submit hidden\" name=\"mode\" value=\"str-up\" class=\"btn\"><span class=\"glyphicon glyphicon-chevron-up\"></span></button>");
                    puts("</div>");
                puts("</div>");
                puts("<div class=\"row\">");
                    puts("<div class=\"col-md-offset-1 col-md-1\" style=\"margin-left: 115\">0</div>");
                    puts("<div class=\"col-md-9\">Strength</div>");
                puts("</div>");
                puts("<div class=\"row\">");
                    puts("<div class=\"col-md-offset-1 col-md-10\">");
                        puts("<button type=\"submit hidden\" name=\"mode\" value=\"str-down\" class=\"btn\"><span class=\"glyphicon glyphicon-chevron-down\"></span></button>");
                    puts("</div>");
                puts("</div>");
            puts("</div>");
            puts("<div class=\"form-group\">");
                puts("<div class=\"row\">");
                    puts("<div class=\"col-md-offset-1 col-md-10\">");
                        puts("<button type=\"submit hidden\" name=\"mode\" value=\"int-up\" class=\"btn\"><span class=\"glyphicon glyphicon-chevron-up\"></span></button>");
                    puts("</div>");
                puts("</div>");
                puts("<div class=\"row\">");
                    puts("<div class=\"col-md-offset-1 col-md-1\" style=\"margin-left: 115\">0</div>");
                    puts("<div class=\"col-md-9\">Intelligence</div>");
                puts("</div>");
                puts("<div class=\"row\">");
                    puts("<div class=\"col-md-offset-1 col-md-10\">");
                        puts("<button type=\"submit hidden\" name=\"mode\" value=\"int-down\" class=\"btn\"><span class=\"glyphicon glyphicon-chevron-down\"></span></button>");
                    puts("</div>");
                puts("</div>");
            puts("</div>");
            puts("<div class=\"form-group\">");
                puts("<div class=\"row\">");
                    puts("<div class=\"col-md-offset-1 col-md-10\">");
                        puts("<button type=\"submit hidden\" name=\"mode\" value=\"vit-up\" class=\"btn\"><span class=\"glyphicon glyphicon-chevron-up\"></span></button>");
                    puts("</div>");
                puts("</div>");
                puts("<div class=\"row\">");
                    puts("<div class=\"col-md-offset-1 col-md-1\" style=\"margin-left: 115\">0</div>");
                    puts("<div class=\"col-md-9\">Vitality</div>");
                puts("</div>");
                puts("<div class=\"row\">");
                    puts("<div class=\"col-md-offset-1 col-md-10\">");
                        puts("<button type=\"submit hidden\" name=\"mode\" value=\"vit-down\" class=\"btn\"><span class=\"glyphicon glyphicon-chevron-down\"></span></button>");
                    puts("</div>");
                puts("</div>");
            puts("</div>");
            puts("<div class=\"form-group\">");
                puts("<div class=\"row\">");
                    puts("<div class=\"col-md-offset-1 col-md-10\">");
                        puts("<button type=\"submit hidden\" name=\"mode\" value=\"agi-up\" class=\"btn\"><span class=\"glyphicon glyphicon-chevron-up\"></span></button>");
                    puts("</div>");
                puts("</div>");
                puts("<div class=\"row\">");
                    puts("<div class=\"col-md-offset-1 col-md-1\" style=\"margin-left: 115\">0</div>");
                    puts("<div class=\"col-md-9\">Agility</div>");
                puts("</div>");
                puts("<div class=\"row\">");
                    puts("<div class=\"col-md-offset-1 col-md-10\">");
                        puts("<button type=\"submit hidden\" name=\"mode\" value=\"agi-down\" class=\"btn\"><span class=\"glyphicon glyphicon-chevron-down\"></span></button>");
                    puts("</div>");
                puts("</div>");
            puts("</div>");
            puts("<div class=\"form-group\">");
                puts("<div class=\"row\">");
                    puts("<div class=\"col-md-offset-1 col-md-10\">");
                        puts("<button type=\"submit hidden\" name=\"mode\" value=\"dex-up\" class=\"btn\"><span class=\"glyphicon glyphicon-chevron-up\"></span></button>");
                    puts("</div>");
                puts("</div>");
                puts("<div class=\"row\">");
                    puts("<div class=\"col-md-offset-1 col-md-1\" style=\"margin-left: 115\">0</div>");
                    puts("<div class=\"col-md-9\">Dexterity</div>");
                puts("</div>");
                puts("<div class=\"row\">");
                    puts("<div class=\"col-md-offset-1 col-md-10\">");
                        puts("<button type=\"submit hidden\" name=\"mode\" value=\"dex-down\" class=\"btn\"><span class=\"glyphicon glyphicon-chevron-down\"></span></button>");
                    puts("</div>");
                puts("</div>");
            puts("</div>");
            puts("<div class=\"row\">");
                puts("<div class=\"col-md-offset-1 col-md-11\">%d stat points left</div>");
            puts("</div>");
            puts("<div class=\"form-group\">");
                puts("<div class=\"control-label col-md-2\">");
                    puts("<button type=\"submit hidden\" name=\"mode\" value=\"go-go\" class=\"btn btn-default\">Go</button>");
                puts("</div>");
            puts("</div>");
        puts("</form>");
    puts("</div>");
}

void update_stat(char* mode, int *str, int *intel, int *vit, int *agi, int *dex)
{
    char stat = 'x';
    int change = 0;

    sscanf(mode,"%c-%d",&stat,&change);

    switch(stat) {
        case 's': *str = *str + change; break;
        case 'i': *intel = *intel + change; break;
        case 'v': *vit = *vit + change; break;
        case 'a': *agi = *agi + change; break;
        case 'd': *dex = *dex + change; break;
        case 'g': break;
        default: break;
    }
}