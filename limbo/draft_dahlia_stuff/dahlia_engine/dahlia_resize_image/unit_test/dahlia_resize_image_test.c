#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>


#include "/home/shanebetz/dahlia_engine/dahlia_image/dahlia_image.h"
#include "/home/shanebetz/dahlia_engine/data_consume_assist/data_consume_assist.h"
#include "/home/shanebetz/dahlia_engine/string_to_integer/string_to_integer.h"
#include "/home/shanebetz/dahlia_engine/total_digits_within_integer/total_digits_within_integer.h"
#include "/home/shanebetz/dahlia_engine/dahlia_resize_image/dahlia_resize_image.h"

#include "/home/shanebetz/dahlia_engine/dahlia_image/dahlia_image.c"
#include "/home/shanebetz/dahlia_engine/data_consume_assist/data_consume_assist.c"
#include "/home/shanebetz/dahlia_engine/string_to_integer/string_to_integer.c"
#include "/home/shanebetz/dahlia_engine/total_digits_within_integer/total_digits_within_integer.c"
#include "/home/shanebetz/dahlia_engine/dahlia_resize_image/dahlia_resize_image.c"

int main(){

	//Begin Initialization Of Resize Image Test.
	printf("BEGIN INITIALIZATION OF INTENDED TEST\n");
		//Create a (verifyable) dahlia image
			//Initialize a 8 by 8 empty image.
			struct dahlia_image * image = dahlia_image_initialize(8, 8);
			
			//Verify width and height was defined correctly.
			assert(image->width == 8);
			assert(image->height == 8);
			
			//Define Pixel Color and Transparency Information
				//Fill Rgb Color
				uint32_t rgbColor = 1234567890;

				//Fill Alternative Rgb Color
				uint32_t rgbColor2= 0;

				//Transparency Value (0 is Completly Visible).
				uint32_t transparencyValue = 0;

				//WWWWBBBB
				//WWWWBBBB
				//WWWWBBBB
				//WWWWBBBB
				//BBBBWWWW
				//BBBBWWWW
				//BBBBWWWW
				//BBBBWWWW
				//Stream:  WWWWBBBB WWWWBBBB WWWWBBBB WWWWBBBB BBBBWWWW BBBBWWWW BBBBWWWW BBBBWWWW
				//Resized
				//WB
				//BW
				//Stream: WB BW
				
				//X1 Y1
				dahlia_image_define_pixel_information(image, 1, 1, rgbColor, transparencyValue);
				//X2 Y1
				dahlia_image_define_pixel_information(image, 2, 1, rgbColor, transparencyValue);
				//X3 Y1
				dahlia_image_define_pixel_information(image, 3, 1, rgbColor, transparencyValue);
				//X4 Y1
				dahlia_image_define_pixel_information(image, 4, 1, rgbColor, transparencyValue);
				//X5 Y1
				dahlia_image_define_pixel_information(image, 5, 1, rgbColor2, transparencyValue);
				//X6 Y1
				dahlia_image_define_pixel_information(image, 6, 1, rgbColor2, transparencyValue);
				//X7 Y1
				dahlia_image_define_pixel_information(image, 7, 1, rgbColor2, transparencyValue);
				//X8 Y1
				dahlia_image_define_pixel_information(image, 8, 1, rgbColor2, transparencyValue);

				//X1 Y2
				dahlia_image_define_pixel_information(image, 1, 2, rgbColor, transparencyValue);
				//X2 Y2
				dahlia_image_define_pixel_information(image, 2, 2, rgbColor, transparencyValue);
				//X3 Y2
				dahlia_image_define_pixel_information(image, 3, 2, rgbColor, transparencyValue);
				//X4 Y2
				dahlia_image_define_pixel_information(image, 4, 2, rgbColor, transparencyValue);
				//X5 Y2
				dahlia_image_define_pixel_information(image, 5, 2, rgbColor2, transparencyValue);
				//X6 Y2
				dahlia_image_define_pixel_information(image, 6, 2, rgbColor2, transparencyValue);
				//X7 Y2
				dahlia_image_define_pixel_information(image, 7, 2, rgbColor2, transparencyValue);
				//X8 Y2
				dahlia_image_define_pixel_information(image, 8, 2, rgbColor2, transparencyValue);

				//X1 Y3
				dahlia_image_define_pixel_information(image, 1, 3, rgbColor, transparencyValue);
				//X2 Y3
				dahlia_image_define_pixel_information(image, 2, 3, rgbColor, transparencyValue);
				//X3 Y3
				dahlia_image_define_pixel_information(image, 3, 3, rgbColor, transparencyValue);
				//X4 Y3
				dahlia_image_define_pixel_information(image, 4, 3, rgbColor, transparencyValue);
				//X5 Y3
				dahlia_image_define_pixel_information(image, 5, 3, rgbColor2, transparencyValue);
				//X6 Y3
				dahlia_image_define_pixel_information(image, 6, 3, rgbColor2, transparencyValue);
				//X7 Y3
				dahlia_image_define_pixel_information(image, 7, 3, rgbColor2, transparencyValue);
				//X8 Y3
				dahlia_image_define_pixel_information(image, 8, 3, rgbColor2, transparencyValue);

				//X1 Y4
				dahlia_image_define_pixel_information(image, 1, 4, rgbColor, transparencyValue);
				//X2 Y4
				dahlia_image_define_pixel_information(image, 2, 4, rgbColor, transparencyValue);
				//X3 Y4
				dahlia_image_define_pixel_information(image, 3, 4, rgbColor, transparencyValue);
				//X4 Y4
				dahlia_image_define_pixel_information(image, 4, 4, rgbColor, transparencyValue);
				//X5 Y4
				dahlia_image_define_pixel_information(image, 5, 4, rgbColor2, transparencyValue);
				//X6 Y4
				dahlia_image_define_pixel_information(image, 6, 4, rgbColor2, transparencyValue);
				//X7 Y4
				dahlia_image_define_pixel_information(image, 7, 4, rgbColor2, transparencyValue);
				//X8 Y4
				dahlia_image_define_pixel_information(image, 8, 4, rgbColor2, transparencyValue);

				//X1 Y5
				dahlia_image_define_pixel_information(image, 1, 5, rgbColor2, transparencyValue);
				//X2 Y5
				dahlia_image_define_pixel_information(image, 2, 5, rgbColor2, transparencyValue);
				//X3 Y5
				dahlia_image_define_pixel_information(image, 3, 5, rgbColor2, transparencyValue);
				//X4 Y5
				dahlia_image_define_pixel_information(image, 4, 5, rgbColor2, transparencyValue);
				//X5 Y5
				dahlia_image_define_pixel_information(image, 5, 5, rgbColor, transparencyValue);
				//X6 Y5
				dahlia_image_define_pixel_information(image, 6, 5, rgbColor, transparencyValue);
				//X7 Y5
				dahlia_image_define_pixel_information(image, 7, 5, rgbColor, transparencyValue);
				//X8 Y5
				dahlia_image_define_pixel_information(image, 8, 5, rgbColor, transparencyValue);

				//X1 Y6
				dahlia_image_define_pixel_information(image, 1, 6, rgbColor2, transparencyValue);
				//X2 Y6
				dahlia_image_define_pixel_information(image, 2, 6, rgbColor2, transparencyValue);
				//X3 Y6
				dahlia_image_define_pixel_information(image, 3, 6, rgbColor2, transparencyValue);
				//X4 Y6
				dahlia_image_define_pixel_information(image, 4, 6, rgbColor2, transparencyValue);
				//X5 Y6
				dahlia_image_define_pixel_information(image, 5, 6, rgbColor, transparencyValue);
				//X6 Y6
				dahlia_image_define_pixel_information(image, 6, 6, rgbColor, transparencyValue);
				//X7 Y6
				dahlia_image_define_pixel_information(image, 7, 6, rgbColor, transparencyValue);
				//X8 Y6
				dahlia_image_define_pixel_information(image, 8, 6, rgbColor, transparencyValue);

				//X1 Y7
				dahlia_image_define_pixel_information(image, 1, 7, rgbColor2, transparencyValue);
				//X2 Y7
				dahlia_image_define_pixel_information(image, 2, 7, rgbColor2, transparencyValue);
				//X3 Y7
				dahlia_image_define_pixel_information(image, 3, 7, rgbColor2, transparencyValue);
				//X4 Y7
				dahlia_image_define_pixel_information(image, 4, 7, rgbColor2, transparencyValue);
				//X5 Y7
				dahlia_image_define_pixel_information(image, 5, 7, rgbColor, transparencyValue);
				//X6 Y7
				dahlia_image_define_pixel_information(image, 6, 7, rgbColor, transparencyValue);
				//X7 Y7
				dahlia_image_define_pixel_information(image, 7, 7, rgbColor, transparencyValue);
				//X8 Y7
				dahlia_image_define_pixel_information(image, 8, 7, rgbColor, transparencyValue);

				//X1 Y8
				dahlia_image_define_pixel_information(image, 1, 8, rgbColor2, transparencyValue);
				//X2 Y8
				dahlia_image_define_pixel_information(image, 2, 8, rgbColor2, transparencyValue);
				//X3 Y8
				dahlia_image_define_pixel_information(image, 3, 8, rgbColor2, transparencyValue);
				//X4 Y8
				dahlia_image_define_pixel_information(image, 4, 8, rgbColor2, transparencyValue);
				//X5 Y8
				dahlia_image_define_pixel_information(image, 5, 8, rgbColor, transparencyValue);
				//X6 Y8
				dahlia_image_define_pixel_information(image, 6, 8, rgbColor, transparencyValue);
				//X7 Y8
				dahlia_image_define_pixel_information(image, 7, 8, rgbColor, transparencyValue);
				//X8 Y8
				dahlia_image_define_pixel_information(image, 8, 8, rgbColor, transparencyValue);

		

		//Begin Test
			struct dahlia_image * resizedImage = dahlia_resize_image(image, 2, 2);
			
			//Assert colors
			printf("Asserting Colors\n");			
			assert(resizedImage->colorGrid[0] == 1234567890);
			assert(resizedImage->colorGrid[1] == 0);
			assert(resizedImage->colorGrid[2] == 0);
			assert(resizedImage->colorGrid[3] == 1234567890);
			
		//End Test
		printf("Finished Test\n");

	//Free
	printf("Freeing Memory\n");
	free(image);

	while(1){ free(image); }
	
	return 0;
}
