/** Copyright Shane Betz, Year 2020 **/

//System Headers
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include "/usr/local/include/xcb/xcb.h"

//Non-System Headers
#include "/home/shanebetz/dahlia_suite/nanosecondresolution_timekeeper/nanosecondresolution_timekeeper.h"
#include "/home/shanebetz/dahlia_suite/data_manipulation/total_digits_within_integer/total_digits_within_integer.h"
#include "/home/shanebetz/dahlia_suite/data_manipulation/data_consume_assist/data_consume_assist.h"
#include "/home/shanebetz/dahlia_suite/data_manipulation/string_to_integer/string_to_integer.h"
#include "/home/shanebetz/dahlia_suite/dahlia_image/dahlia_image.h"
#include "/home/shanebetz/dahlia_suite/dahlia_font/dahlia_font_english.h"
#include "/home/shanebetz/dahlia_suite/xcb/convenience_xcb.h"
#include "/home/shanebetz/dahlia_suite/xcb/xcb_draw/xcb_draw.h"
#include "/home/shanebetz/dahlia_suite/xcb/xcb_threaded_redraw/xcb_threaded_redraw.h"
#include "/home/shanebetz/dahlia_suite/xcb/convenience_xcb_events.h"

//Globals
struct dahlia_image * grid_image;
struct dahlia_image * canvas_surface_image;

#include "/home/shanebetz/dahlia_suite/nanosecondresolution_timekeeper/nanosecondresolution_timekeeper.c"
#include "/home/shanebetz/dahlia_suite/data_manipulation/total_digits_within_integer/total_digits_within_integer.c"
#include "/home/shanebetz/dahlia_suite/data_manipulation/data_consume_assist/data_consume_assist.c"
#include "/home/shanebetz/dahlia_suite/data_manipulation/string_to_integer/string_to_integer.c"
#include "/home/shanebetz/dahlia_suite/dahlia_image/dahlia_image.c"
#include "/home/shanebetz/dahlia_suite/dahlia_font/dahlia_font_english.c"
#include "/home/shanebetz/dahlia_suite/xcb/convenience_xcb.c"
#include "/home/shanebetz/dahlia_suite/xcb/xcb_draw/xcb_draw.c"
#include "/home/shanebetz/dahlia_suite/xcb/xcb_threaded_redraw/xcb_threaded_redraw.c"
#include "/home/shanebetz/dahlia_suite/xcb/convenience_xcb_events.c"

//Begin Execution of Application.
int main(){
	uint16_t windowWidth = 200;
	uint16_t windowHeight = 200;

	/** Create and Map(Show) Window **/
		//Create Window, using convenience xcb function.
		convenience_xcb_create_window(windowWidth, windowHeight);

	/** Initialize Convenience XCB Events Manager **/
		//Zero XCB events variables.
		convenience_xcb_events_initialize();

	/** Initialize Dahlias PerPixel FrameBuffer Management System **/
		//Create a useable dahlia image to be the framebuffer that is copied to the display upon redraw request.
		dahlia_perpixel_framebuffer_initialize(windowWidth, windowHeight);

	/** Initialize Layers **/
		//Initialize Dahlia Images
		grid_image =  dahlia_image_initialize(windowWidth, windowHeight);
		canvas_surface_image =  dahlia_image_initialize(windowWidth, windowHeight);
			//Make canvas surface transparent (transparency turns off when painted).
			uint32_t currentIndex = 0;
			while(currentIndex < canvas_surface_image->totalColorsInGrid){
				canvas_surface_image->transparencyGrid[currentIndex] = 100;

				//Next
				currentIndex = currentIndex + 1;
			}

	/** Define Grid Information **/
	uint32_t gridSpaceBetweenLines = 10;
	uint32_t x = 1;
	uint32_t y = 1;
	uint32_t keepCreatingGrid = 1;
	while(keepCreatingGrid == 1){
		//Draw pixel for this area of the grid.
		dahlia_image_define_pixel_information_by_square_area(grid_image, x, y, 1, 1, 3158064, 0);
		//Mark for redraw update
		convenience_xcb_threaded_perpixel_framebuffer_mark_for_redraw(x, y);		

		//Next
		x = x + 1;
		if(x > grid_image->width){
			x = 1;
			y = y + gridSpaceBetweenLines;
		}
		if(y > grid_image->height){
			keepCreatingGrid = 0;
		}
	}
	x = 1;
	y = 1;
	keepCreatingGrid = 1;
	while(keepCreatingGrid == 1){
		dahlia_image_define_pixel_information_by_square_area(grid_image, x, y, 1, 1, 3158064, 0);
		//Mark for redraw update
		convenience_xcb_threaded_perpixel_framebuffer_mark_for_redraw(x, y);		

		//Next
		y = y + 1;
		if(y > grid_image->height){
			y = 1;
			x = x + gridSpaceBetweenLines;
		}
		if(x > grid_image->width){
			keepCreatingGrid = 0;
		}
	}

	/** Initialize Dahlia Font English **/
	dahlia_font_english_letter_initialize();

	//uint8_t letterIndex = dahlia_font_english_get_index_by_letter("c");
	//printf("%u\n", letterIndex);

	/** Create Thread for Redraw To Display Function **/
		//Initialize xcb threaded function that redraws to display upon request.
		convenience_xcb_threaded_function_draw_to_display_initialize();

		//Start xcb threaded function that redraws to display upon request.
		convenience_xcb_threaded_function_draw_to_display_start_thread();

		
	//Begin Main Thread
	while(1) {
		/** Poll Keyboard, Mouse, GamePad events using Convenience XCB. **/
		convenience_xcb_events_poll();

		/** Begin "Drawing Application" Logic **/
			if(xcb_event_keyboard_s_state == 2){
				printf("BEGIN SAVING....\n");
				//Initiate storage of this image.
				dahlia_image_save_file("./saved_drawing.dahlia_rgba", canvas_surface_image);
				printf("END SAVING....\n");
			}
			//Upon mouse down, draw to canvas surface image
			//Permit if window is focused.
			if(xcb_event_window_focus == 1){
				if(xcb_event_mouse_leftbutton_down == 1){
					uint32_t brush_width = 10;
					uint32_t brush_height = 10;
					dahlia_image_define_pixel_information_by_square_area(canvas_surface_image, xcb_event_mouse_x, xcb_event_mouse_y, brush_width, brush_height, 0xAD800000, 0);
					uint32_t keepMarkingForRedraw = 1;
					uint32_t x = xcb_event_mouse_x;
					uint32_t stopX = xcb_event_mouse_x + brush_width;
					uint32_t y = xcb_event_mouse_y;
					uint32_t stopY = xcb_event_mouse_y + brush_height;
					while(keepMarkingForRedraw == 1){
						convenience_xcb_threaded_perpixel_framebuffer_mark_for_redraw(x, y);
						//Next
						x = x + 1;
						if(x > stopX){
							x = xcb_event_mouse_x;
							y = y + 1;
						}
						if(y > stopY){
							keepMarkingForRedraw = 0;
						}
					}
				}
			}
		/** End "Drawing Application" Logic **/

		/** Reset Released XCB States **/
		convenience_xcb_events_reset_released_states();

		/** Redraw requester. **/
		convenience_xcb_threaded_function_determine_if_redraw_should_be_requested(30);		
	} 

	return 0;
}
//End of Execution of Application.
