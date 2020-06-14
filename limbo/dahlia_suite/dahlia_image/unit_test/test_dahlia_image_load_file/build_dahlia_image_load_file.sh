rm ./dahlia_image_unit_test_load_file
cc -std=c11 -Wall -g -static  -L/usr/local/lib/ -lxcb -I/usr/local/include/ /home/shanebetz/dahlia_engine/dahlia_image/unit_test/test_dahlia_image_load_file/dahlia_image_unit_test_load_file.c -o dahlia_image_unit_test_load_file
