#cc -Wall -g -o0 -L/usr/local/lib/ -lxcb -I/usr/local/include/ /home/shanebetz/dahlia_editor/dahlia_editor_main.c -o dahlia_editor_main
rm ./dahlia_image_viewer
cc -Wall -g -O0 -std=c11 -L/usr/local/lib/ -lxcb -lpthread -I/usr/local/include/ /home/shanebetz/dahlia_image_viewer/dahlia_image_viewer_main.c -o dahlia_image_viewer
