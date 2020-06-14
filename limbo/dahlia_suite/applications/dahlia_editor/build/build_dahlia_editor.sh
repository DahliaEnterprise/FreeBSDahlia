rm ./dahlia_draw_editor
cc -std=c17 -g -O0 -Wall -L/usr/local/lib/ -lxcb -lpthread -I/usr/local/include/ /root/dahlia_suite/applications/dahlia_editor/dahlia_editor_main.c -o dahlia_editor_main

