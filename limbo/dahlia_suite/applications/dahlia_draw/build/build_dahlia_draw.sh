rm ./dahlia_draw_main
cc -std=c17 -g -O0 -Wall -L/usr/local/lib/ -lxcb -lpthread -I/usr/local/include/ /home/shanebetz/dahlia_suite/applications/dahlia_draw/dahlia_draw_main.c -o dahlia_draw_main

