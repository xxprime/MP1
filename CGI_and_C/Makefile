all:
	gcc -Wall -o main_menu.cgi main_menu.c cgi_init_term.c cgi_mysql.c -lmysqlclient
	gcc -Wall -o new_game.cgi new_game.c cgi_init_term.c cgi_parser.c cgi_mysql.c -lmysqlclient
	gcc -Wall -o map_handler.cgi map_handler.c cgi_init_term.c cgi_parser.c cgi_mysql.c randomizer.c stats.c -lmysqlclient
	gcc -Wall -o battle_handler.cgi battle_handler.c cgi_init_term.c cgi_parser.c cgi_mysql.c stats.c -lmysqlclient
	gcc -Wall -o battle_allocation.cgi battle_allocation.c cgi_init_term.c cgi_parser.c cgi_mysql.c -lmysqlclient
	sudo cp -r ../HTML/* /var/www/html/MP1/
	sudo cp  -r ../CGI_and_C/* /usr/lib/cgi-bin/MP1/
	sudo cp -r ../Images /var/www/html/MP1/
	sudo chown -R www-data /var/www