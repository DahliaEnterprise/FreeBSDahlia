//System Headers
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include "/usr/local/include/xcb/xcb.h"

#include "/root/dahlia_suite/data_manipulation/total_digits_within_integer/total_digits_within_integer.h"
#include "/root/dahlia_suite/data_manipulation/data_consume_assist/data_consume_assist.h"
#include "/root/dahlia_suite/data_manipulation/string_to_integer/string_to_integer.h"
#include "/root/dahlia_suite/dahlia_image/dahlia_image.h"

#include "/root/dahlia_suite/data_manipulation/total_digits_within_integer/total_digits_within_integer.c"
#include "/root/dahlia_suite/data_manipulation/data_consume_assist/data_consume_assist.c"
#include "/root/dahlia_suite/data_manipulation/string_to_integer/string_to_integer.c"
#include "/root/dahlia_suite/dahlia_image/dahlia_image.c"

void convenience_xcb_threaded_get_overlay_image_xy(struct dahlia_image * overlay_image, 
											      int32_t overlay_image_topLeft_x,
											      int32_t overlay_image_topLeft_y,
											      uint32_t perpixel_framebuffer_target_x,
											      uint32_t perpixel_framebuffer_target_y){
	//Begin x calculation.
		int64_t leftmost_x_plane = 0;
		int64_t canvas_image_leftmost_x = 1;
		int64_t overlay_image_leftmost_x = overlay_image_topLeft_x;

		//Define leftmost x plane based on which image is most left.
		uint8_t overlay_is_leftmost = 0;
		if(overlay_image_leftmost_x < canvas_image_leftmost_x){
			leftmost_x_plane = overlay_image_leftmost_x;
			overlay_is_leftmost = 1;
		}else if(canvas_image_leftmost_x <= overlay_image_leftmost_x){
			leftmost_x_plane = canvas_image_leftmost_x;
		}

		//Begin Iteration.
		int64_t x_plane_iterator = leftmost_x_plane;
		int64_t canvas_x_iterator = canvas_image_leftmost_x;
		int64_t overlay_x_iterator = overlay_image_leftmost_x;

		uint8_t keepIterating = 1;
		while(keepIterating == 1){
			//Determine if we have reached our destination.
			if(x_plane_iterator == perpixel_framebuffer_target_x){
				//Search found target aligned.
				keepIterating = 0;
			}else if(x_plane_iterator != perpixel_framebuffer_target_x){
				//Next.
				x_plane_iterator = x_plane_iterator + 1;
				canvas_x_iterator = canvas_x_iterator + 1;
				overlay_x_iterator = overlay_x_iterator + 1;
			}
		}

		int64_t overlay_x_aligned_with_x_plane_target = overlay_x_iterator;
		printf("OVERLAY X FOUND: %ld\n", overlay_x_aligned_with_x_plane_target);

	//End x calculation.

	//Begin y calculation.
		int64_t topmost_y_plane = 0;
		int64_t canvas_image_topmost_y = 1;
		int64_t overlay_image_topmost_y = overlay_image_topLeft_y;

		//Define topmost y plane based on which image is most top.
		uint8_t overlay_is_topmost = 0;
		if(overlay_image_topmost_y < canvas_image_topmost_y){
			topmost_y_plane = overlay_image_topmost_y;
			overlay_is_topmost = 1;
		}else if(canvas_image_topmost_y <= overlay_image_topmost_y){
			topmost_y_plane = canvas_image_topmost_y;
		}
	
		//Begin Iteration
		int64_t y_plane_iterator = topmost_y_plane;
		int64_t canvas_y_iterator = canvas_image_topmost_y;
		int64_t overlay_y_iterator = overlay_image_topmost_y;

		keepIterating = 1;
		while(keepIterating == 1){
			//Determine if we have reached our destination.
			if(y_plane_iterator == perpixel_framebuffer_target_y){
				//Search found target aligned.
				keepIterating = 0;
			}else if(y_plane_iterator != perpixel_framebuffer_target_y){
				//Next.
				y_plane_iterator = y_plane_iterator + 1;
				canvas_y_iterator = canvas_y_iterator + 1;
				overlay_y_iterator = overlay_y_iterator + 1;
			}
		}

		int64_t overlay_y_aligned_with_y_plane_target = y_plane_iterator;
		printf("OVERLAY Y FOUND: %ld\n", overlay_y_aligned_with_y_plane_target);
	//End y calculation.
}


int main(){

	printf("Begin aquire overlay x,y based on the canvas x,y\n");
	//Initialize canvas and overlay image with 500 width and 500 height.
	struct dahlia_image * canvas_image = dahlia_image_initialize(10, 10);
	struct dahlia_image * overlay_image = dahlia_image_initialize(10, 10);
	//Define the overlay topleft X,Y over the canvas image.
	int32_t overlay_image_topleft_x = -4;
	int32_t overlay_image_topleft_y = -4;
	//Test Notes: Canvas image topleft X,Y is always 1,1
	convenience_xcb_threaded_get_overlay_image_xy(overlay_image, overlay_image_topleft_x, overlay_image_topleft_y, 5, 5);	

	printf("End of Test\n");
	return 0;
}



