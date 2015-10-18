#include <stdio.h>
#include "cgicustom.h"

void print_form(char *name, int str, int intel, int vit, int agi, int dex);

int main()
{
	char name[10]={'\0'};
	int str = 0, intel = 0, vit = 0, agi = 0, dex = 0;

	cgi_init("MP1 Title_newgame");


	post_init(atoi(getenv("CONTENT_LENGTH",0)));
	parse_data();

	cgi_term();
	return 0;
}

void print_form()
{

}