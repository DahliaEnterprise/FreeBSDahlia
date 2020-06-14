#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>


#include "/home/shanebetz/dahlia_engine/dahlia_image/dahlia_image.h"
#include "/home/shanebetz/dahlia_engine/data_consume_assist/data_consume_assist.h"
#include "/home/shanebetz/dahlia_engine/string_to_integer/string_to_integer.h"
#include "/home/shanebetz/dahlia_engine/total_digits_within_integer/total_digits_within_integer.h"

#include "/home/shanebetz/dahlia_engine/dahlia_image/dahlia_image.c"
#include "/home/shanebetz/dahlia_engine/data_consume_assist/data_consume_assist.c"
#include "/home/shanebetz/dahlia_engine/string_to_integer/string_to_integer.c"
#include "/home/shanebetz/dahlia_engine/total_digits_within_integer/total_digits_within_integer.c"

int main(){

	//Begin Initialization Of Save and Load Test.
	printf("BEGIN INITIALIZATION OF INTENDED TEST\n");
		//Create a (verifyable) dahlia image
			//Initialize a 3 by 3 empty image.
			struct dahlia_image * image = dahlia_image_initialize(3, 3);
			
			//Verify width and height was defined correctly.
			assert(image->width == 3);
			assert(image->height == 3);
			
			//Define Pixel Color and Transparency Information
				//Rgb Color
				uint32_t rgbColor = 1234567890;

				//Transparency Value (Completly Visible).
				uint32_t transparencyValue = 0;

				//X1 Y1
				dahlia_image_define_pixel_information(image, 1, 1, rgbColor, transparencyValue);
				//X2 Y1
				dahlia_image_define_pixel_information(image, 2, 1, rgbColor, transparencyValue);
				//X3 Y1
				dahlia_image_define_pixel_information(image, 3, 1, rgbColor, transparencyValue);

				//X1 Y2
				dahlia_image_define_pixel_information(image, 1, 2, rgbColor, transparencyValue);
				//X2 Y2
				dahlia_image_define_pixel_information(image, 2, 2, rgbColor, transparencyValue);
				//X3 Y2
				dahlia_image_define_pixel_information(image, 3, 2, rgbColor, transparencyValue);

				//X1 Y3
				dahlia_image_define_pixel_information(image, 1, 3, rgbColor, transparencyValue);
				//X2 Y3
				dahlia_image_define_pixel_information(image, 2, 3, rgbColor, transparencyValue);
				//X3 Y3
				dahlia_image_define_pixel_information(image, 3, 3, rgbColor, transparencyValue);

			//Verify dahlia_image_define_pixel_information was defined correctly before the intented test begins.
			//printf("Asserting colorGrid integrity.\n");
			assert(image->colorGrid[0] == rgbColor);
			assert(image->colorGrid[1] == rgbColor);
			assert(image->colorGrid[2] == rgbColor);
			assert(image->colorGrid[3] == rgbColor);
			assert(image->colorGrid[4] == rgbColor);
			assert(image->colorGrid[5] == rgbColor);
			assert(image->colorGrid[6] == rgbColor);
			assert(image->colorGrid[7] == rgbColor);
			assert(image->colorGrid[8] == rgbColor);
	
			//printf("Asserting transparencyGrid integrity.\n");
			assert(image->transparencyGrid[0] == transparencyValue);
			assert(image->transparencyGrid[1] == transparencyValue);
			assert(image->transparencyGrid[2] == transparencyValue);
			assert(image->transparencyGrid[3] == transparencyValue);
			assert(image->transparencyGrid[4] == transparencyValue);
			assert(image->transparencyGrid[5] == transparencyValue);
			assert(image->transparencyGrid[6] == transparencyValue);
			assert(image->transparencyGrid[7] == transparencyValue);
			assert(image->transparencyGrid[8] == transparencyValue);
			
	//Begin Test
		//Saving file.
		dahlia_image_save_file("./test_dahlia_image.rgba", image);

 		//Load file.
		struct dahlia_image * loadedImage = dahlia_image_load_file("./test_dahlia_image.rgba");
	
		//Determine quality of functions.
			//Verify dahlia_image_define_pixel_information was defined correctly before the intented test begins.
			//printf("Asserting colorGrid integrity.\n");
			assert(loadedImage->colorGrid[0] == rgbColor);
			assert(loadedImage->colorGrid[1] == rgbColor);
			assert(loadedImage->colorGrid[2] == rgbColor);
			assert(loadedImage->colorGrid[3] == rgbColor);
			assert(loadedImage->colorGrid[4] == rgbColor);
			assert(loadedImage->colorGrid[5] == rgbColor);
			assert(loadedImage->colorGrid[6] == rgbColor);
			assert(loadedImage->colorGrid[7] == rgbColor);
			assert(loadedImage->colorGrid[8] == rgbColor);
	
			//printf("Asserting transparencyGrid integrity.\n");
			assert(loadedImage->transparencyGrid[0] == transparencyValue);
			assert(loadedImage->transparencyGrid[1] == transparencyValue);
			assert(loadedImage->transparencyGrid[2] == transparencyValue);
			assert(loadedImage->transparencyGrid[3] == transparencyValue);
			assert(loadedImage->transparencyGrid[4] == transparencyValue);
			assert(loadedImage->transparencyGrid[5] == transparencyValue);
			assert(loadedImage->transparencyGrid[6] == transparencyValue);
			assert(loadedImage->transparencyGrid[7] == transparencyValue);
			assert(loadedImage->transparencyGrid[8] == transparencyValue);
			
	//End Test
	
	//Free
	free(image);
	free(loadedImage);
	return 0;
}
