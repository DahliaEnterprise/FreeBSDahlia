rm ./dahlia_resize_image_test
cc -std=c11 -Wall -g -static  -L/usr/local/lib/ -lxcb -I/usr/local/include/ /home/shanebetz/dahlia_engine/dahlia_resize_image/unit_test/dahlia_resize_image_test.c -o dahlia_resize_image_test
