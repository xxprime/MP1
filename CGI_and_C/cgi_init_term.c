#include <stdio.h>

void cgi_init(char *title)
{
  printf("Content-type:text/html\n\n");
  printf("<html><head>");
  printf("<title>%s</title>",title);
  printf("<script src=\"https://ajax.googleapis.com/ajax/libs/jquery/2.1.3/jquery.min.js\"></script>");
  printf("<link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.3.5/css/bootstrap.min.css\">");
  printf("<link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.3.5/css/bootstrap-theme.min.css\">");
  printf("<script src=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.3.5/js/bootstrap.min.js\"></script>");
  printf("</head><body>");
}

void cgi_term()
{
  printf("</body></html>");
}