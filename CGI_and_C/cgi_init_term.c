#include <stdio.h>

void cgi_init(char *title)
{
  printf("Content-type:text/html\n\n");
  printf("<html><head>");
  printf("<meta charset=\"UTF-8\">");
  printf("<title>%s</title>",title);
  printf("<link rel=\"stylesheet\" type=\"text/css\" href=\"/MP1/bootstrap-3.3.5-dist/css/bootstrap.min.css\">");
  printf("<link rel=\"stylesheet\" type=\"text/css\" href=\"/MP1/bootstrap-3.3.5-dist/css/bootstrap-theme.min.css\">");
  printf("</head><body>");
}

void cgi_init_beforecss(char *title)
{
  printf("Content-type:text/html\n\n");
  printf("<html><head>");
  printf("<meta charset=\"UTF-8\">");
  printf("<title>%s</title>",title);
  printf("<link rel=\"stylesheet\" type=\"text/css\" href=\"/MP1/bootstrap-3.3.5-dist/css/bootstrap.min.css\">");
  printf("<link rel=\"stylesheet\" type=\"text/css\" href=\"/MP1/bootstrap-3.3.5-dist/css/bootstrap-theme.min.css\">");
  printf("<style>");
}

void cgi_init_aftercss()
{
  printf("</style>");
  printf("</head><body>");
}

void cgi_term()
{
  printf("<script src=\"/MP1/bootstrap-3.3.5-dist/js/jquery.min.js\"></script>");
  printf("<script src=\"/MP1/bootstrap-3.3.5-dist/js/bootstrap.min.js\"></script>");
  printf("</body></html>");
}