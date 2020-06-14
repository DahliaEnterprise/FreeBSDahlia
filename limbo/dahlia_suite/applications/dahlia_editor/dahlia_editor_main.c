/** Copyright Shane Betz, Year 2020 **/

//System Headers
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include "/usr/local/include/xcb/xcb.h"

//Non-System Headers
#include "/root/dahlia_suite/nanosecondresolution_timekeeper/nanosecondresolution_timekeeper.h"
#include "/root/dahlia_suite/data_manipulation/total_digits_within_integer/total_digits_within_integer.h"
#include "/root/dahlia_suite/data_manipulation/data_consume_assist/data_consume_assist.h"
#include "/root/dahlia_suite/data_manipulation/string_to_integer/string_to_integer.h"
#include "/root/dahlia_suite/dahlia_image/dahlia_image.h"
#include "/root/dahlia_suite/dahlia_font/dahlia_font_english.h"
#include "/root/dahlia_suite/xcb/convenience_xcb.h"
#include "/root/dahlia_suite/xcb/xcb_draw/xcb_draw.h"
#include "/root/dahlia_suite/xcb/xcb_threaded_redraw/xcb_threaded_redraw.h"
#include "/root/dahlia_suite/xcb/convenience_xcb_events.h"

//Globals
struct dahlia_image * grid_image;
struct dahlia_image * canvas_surface_image;

#include "/root/dahlia_suite/nanosecondresolution_timekeeper/nanosecondresolution_timekeeper.c"
#include "/root/dahlia_suite/data_manipulation/total_digits_within_integer/total_digits_within_integer.c"
#include "/root/dahlia_suite/data_manipulation/data_consume_assist/data_consume_assist.c"
#include "/root/dahlia_suite/data_manipulation/string_to_integer/string_to_integer.c"
#include "/root/dahlia_suite/dahlia_image/dahlia_image.c"
#include "/root/dahlia_suite/dahlia_font/dahlia_font_english.c"
#include "/root/dahlia_suite/xcb/convenience_xcb.c"
#include "/root/dahlia_suite/xcb/xcb_draw/xcb_draw.c"
#include "/root/dahlia_suite/xcb/xcb_threaded_redraw/xcb_threaded_redraw.c"
#include "/root/dahlia_suite/xcb/convenience_xcb_events.c"

//Begin Execution of Application.
int main(){
	uint16_t canvasWidth = 200;
	uint16_t canvasHeight = 200;
	uint16_t toolsetWidth = 20;
	uint16_t toolsetHeight = canvasHeight;
	uint16_t windowWidth = canvasWidth + toolsetWidth;
	uint16_t windowHeight = canvasHeight;


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
		grid_image =  dahlia_image_initialize(canvasWidth, canvasHeight);
		canvas_surface_image =  dahlia_image_initialize(canvasWidth, canvasHeight);
			//Make canvas surface transparent (transparency turns off when painted).
			uint32_t currentIndex = 0;
			while(currentIndex < canvas_surface_image->totalColorsInGrid){
				canvas_surface_image->transparencyGrid[currentIndex] = 100;

				//Next
				currentIndex = currentIndex + 1;
			}


	/** Initialize Dahlia Font English **/
	//dahlia_font_english_letter_initialize();

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
