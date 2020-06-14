rm ./dahlia_editor
cc -std=c17 -g -Wall -L/usr/local/lib/ -lxcb -lpthread -I/usr/local/include/ /root/DahliaEditor/DahliaEditor_main.c -o dahlia_editor

