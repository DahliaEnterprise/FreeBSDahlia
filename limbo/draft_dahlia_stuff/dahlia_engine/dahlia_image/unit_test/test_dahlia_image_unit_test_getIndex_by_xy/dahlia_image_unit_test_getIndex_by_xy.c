#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "/home/shanebetz/dahlia_engine/dahlia_image/dahlia_image.h"
#include "/home/shanebetz/dahlia_engine/data_consume_assist/data_consume_assist.h"
#include "/home/shanebetz/dahlia_engine/string_to_integer/string_to_integer.h"

#include "/home/shanebetz/dahlia_engine/dahlia_image/dahlia_image.c"
#include "/home/shanebetz/dahlia_engine/data_consume_assist/data_consume_assist.c"
#include "/home/shanebetz/dahlia_engine/string_to_integer/string_to_integer.c"

int main(){
	//Begin Test.
	struct dahlia_image * image = dahlia_image_initialize(100, 100);
	dahlia_image_define_pixel_information(image,  1, 2, 345678, 0);
	printf("Pixel Defined in X: 1, Y: 1, with color: %u, expecting color: %u\n", image->colorGrid[100], 345678);


	return 0;
}
