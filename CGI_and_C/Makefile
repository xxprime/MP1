all:
	gcc -Wall -o main_menu.cgi main_menu.c cgi_init_term.c -lmysqlclient
	sudo cp ../HTML/index.html /var/www/html/MP1/
	sudo cp -r ../HTML/bootstrap-3.3.5-dist /var/www/html/MP1/
	sudo cp ../HTML/jquery.min.js /var/www/html/MP1/
	sudo cp main_menu.cgi /usr/lib/cgi-bin/MP1/