/** NOTE: PRINTING TO CONSOLE (FOR UNKNOWN REASONS) PREVENTS RENDERING TO SCREEN **/
//System Headers
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "/usr/local/include/xcb/xcb.h"
#include <pthread.h>


//Program Headers
	//Dahlia Engine Functions.
		//Assistance, Functions.
		#include "/home/shanebetz/dahlia_engine/data_consume_assist/data_consume_assist.h"
		#include "/home/shanebetz/dahlia_engine/string_to_integer/string_to_integer.h"
		#include "/home/shanebetz/dahlia_engine/total_digits_within_integer/total_digits_within_integer.h"
		#include "/home/shanebetz/dahlia_engine/time_keeper/time_keeper.h"
		
		//Associated with XCB, Functions.
		#include "/home/shanebetz/dahlia_engine/xcb/dahlia_engine_xcb.h"
		#include "/home/shanebetz/dahlia_engine/xcb/dahlia_engine_xcb_threaded_draw_to_display.h"
		#include "/home/shanebetz/dahlia_engine/dahlia_font_engine/dahlia_font_engine.h"
		#include "/home/shanebetz/dahlia_engine/xcb/dahlia_engine_xcb_events.h"

		//Image, Functions
		#include "/home/shanebetz/dahlia_engine/dahlia_image/dahlia_image.h"
		#include "/home/shanebetz/dahlia_engine/dahlia_resize_image/dahlia_resize_image.h"

	//Dahlia Editor Functions.
		//Document, Functions.
		#include "/home/shanebetz/dahlia_editor/dahlia_editor_document.h"


//Global Variables (Unitialized)
struct dahlia_image * grid_image;
struct dahlia_image * displaySurface;
uint32_t canvasWidth;
uint32_t canvasHeight;

//Program Definitions
#include "/home/shanebetz/dahlia_engine/xcb/dahlia_engine_xcb.c"
#include "/home/shanebetz/dahlia_engine/data_consume_assist/data_consume_assist.c"
#include "/home/shanebetz/dahlia_engine/string_to_integer/string_to_integer.c"
#include "/home/shanebetz/dahlia_engine/dahlia_image/dahlia_image.c"
#include "/home/shanebetz/dahlia_engine/time_keeper/time_keeper.c"
#include "/home/shanebetz/dahlia_engine/xcb/dahlia_engine_xcb_threaded_draw_to_display.c"
#include "/home/shanebetz/dahlia_engine/total_digits_within_integer/total_digits_within_integer.c"
#include "/home/shanebetz/dahlia_engine/dahlia_font_engine/dahlia_font_engine.c"
#include "/home/shanebetz/dahlia_editor/dahlia_editor_document.c"
#include "/home/shanebetz/dahlia_engine/xcb/dahlia_engine_xcb_events.c"
#include "/home/shanebetz/dahlia_engine/dahlia_resize_image/dahlia_resize_image.c"


//Begin Main Program
int main(int argc, char** argv){
	canvasWidth = 1024;
	canvasHeight = 768;

	int16_t mouseX = 1;
	int16_t mouseY = 1;

	if(argc > 1){ //Greater than one means the user has inputted a setting
		//argv[1] is width
		canvasWidth = dahlia_string_to_unsigned_integer_thirtytwo(argv[1]);	

		//argv[2] is height
		canvasHeight = dahlia_string_to_unsigned_integer_thirtytwo(argv[2]);
	}

	//Print Welcome message to the console.
	printf("Starting Dahlia Editor.\n");

	//Create X11 Window with XCB.
	dahlia_engine_editor_xcb_create_window(canvasWidth, canvasHeight);
	xcb_flush(dahlia_editor_engine_xcb_connection);


	//Manage window redraw using time.
	timekeeper_initialize();
	timekeeper_update();
	dahlia_editor_engine_xcb_timestamp_last_frame_rendered = timekeeper_currentTime_nanoseconds;

	//Mouse State.
	unsigned int leftMouseDown = 0;
	unsigned int rightMouseDown = 0;

	/** Prerender grid. **/
		//Initialize dahlias' XCB layer.
		 grid_image = dahlia_image_initialize(canvasWidth, canvasHeight);

		uint32_t gridColor = 3100495;
		uint32_t spaceBetweenGridLines = 10; 

		//Horizontal Grid
		uint32_t horizontalGridX= spaceBetweenGridLines;
		uint32_t horizontalGridY = 1;
		uint32_t keepDrawingHorizontalGrid = 1;
		while(keepDrawingHorizontalGrid == 1){
			dahlia_image_define_pixel_information_by_square_area(grid_image, horizontalGridX, horizontalGridY, 1, canvasHeight, gridColor, 0);

			horizontalGridX = horizontalGridX + spaceBetweenGridLines;
			if(horizontalGridX >= canvasWidth){ keepDrawingHorizontalGrid = 0; }
		}

		//Vertical Grid
		uint32_t verticalGridX = 1;
		uint32_t verticalGridY = spaceBetweenGridLines;
		uint32_t keepDrawingVerticalGrid = 1;
		while(keepDrawingVerticalGrid == 1){
			dahlia_image_define_pixel_information_by_square_area(grid_image, verticalGridX, verticalGridY, canvasWidth, 1, gridColor, 0);

			verticalGridY = verticalGridY + spaceBetweenGridLines;
			if(verticalGridY >= canvasHeight){ keepDrawingVerticalGrid = 0; }
		}
	/** End Prerender Grid **/

	//Initialize dahlia image to be used for the single layer drawing surface.
	 displaySurface = dahlia_image_initialize(canvasWidth, canvasHeight);
	dahlia_image_define_pixel_information_by_square_area(displaySurface, 1, 1, canvasWidth, canvasHeight, 0x000000, 1000000);

	//Begin Engine
		//PThread Initialize.
		xcb_ready_for_redraw = 0;
		pthread_create(&xcb_draw_to_display_thread_id, 0, dahlia_engine_xcb_threaded_draw_to_display, 0);
		//End PThread Initialize.
	dahlia_editor_engine_event = 0;
	while(1){ 
		//Begin Events Polling
		dahlia_editor_engine_event = xcb_poll_for_event (dahlia_editor_engine_xcb_connection);
		if(dahlia_editor_engine_event != 0){
			if(dahlia_editor_engine_event->response_type == XCB_KEY_PRESS){
				xcb_key_press_event_t * keyPressEvent = (xcb_key_press_event_t*)dahlia_editor_engine_event;
				if(keyPressEvent->detail == 39){
					dahlia_image_save_file("./dahlia_draw_image.rgb", displaySurface);
				}
				printf("KEY PRESS\n");
			}else if(dahlia_editor_engine_event->response_type == XCB_KEY_RELEASE){
				//printf("KEY RELEASE\n");
			}else if(dahlia_editor_engine_event->response_type == XCB_MOTION_NOTIFY){
				 xcb_motion_notify_event_t * mouseMoveEvent = (xcb_motion_notify_event_t*)dahlia_editor_engine_event;
				//printf("mouse move\n");
				//printf("%i   %i     ,    %i     %i\n", mouseMoveEvent->root_x, mouseMoveEvent->root_y, mouseMoveEvent->event_x, mouseMoveEvent->event_y);
				//Event XY is window coordinates.
				mouseX = mouseMoveEvent->event_x;
				mouseY = mouseMoveEvent->event_y;
	
			}else if(dahlia_editor_engine_event->response_type == XCB_BUTTON_PRESS){
				printf("button press\n");
				xcb_button_press_event_t* mouseDownEvent = (xcb_button_press_event_t*)dahlia_editor_engine_event;
				//printf("event:%d\n", mouseDownEvent->detail);
				if(mouseDownEvent->detail == 1){ leftMouseDown = 1; }else
				if(mouseDownEvent->detail == 3){ rightMouseDown = 1;}
			}else if(dahlia_editor_engine_event->response_type == XCB_BUTTON_RELEASE){
				printf("button release\n");
				xcb_button_release_event_t* mouseUpEvent = (xcb_button_release_event_t*)dahlia_editor_engine_event;
				//printf("event:%d\n", mouseUpEvent->detail);
				if(mouseUpEvent->detail == 1){ leftMouseDown = 0; }else
				if(mouseUpEvent->detail == 3){ rightMouseDown = 0; }
			}else if(dahlia_editor_engine_event->response_type == XCB_EXPOSE){
				//printf("expose\n");
			}
			free(dahlia_editor_engine_event);
			dahlia_editor_engine_event = 0;
		}
		//End Events Polling

		//on mouse left down, draw pixels((white)); on mouse right down, erase pixels(black)
		if(leftMouseDown == 1){
			//dahlia_engine_editor_xcb_draw_rectangle(mouseX, mouseY, 10, 10, 0xFFFFFFFF);
			dahlia_image_define_pixel_information_by_square_area(displaySurface, mouseX, mouseY, 10, 10, 0xFFFFFFFF, 0);
		}else if(rightMouseDown == 1){
			//dahlia_engine_editor_xcb_draw_rectangle(mouseX, mouseY, 5, 5, 0x00000000);
			dahlia_image_define_pixel_information_by_square_area(displaySurface, 1, 1, 10, 10, 0x00000000, 1000000);
		}


		/** Begin Redraw screen. **/
		timekeeper_update();
		uint64_t timesincelastRedraw = timekeeper_currentTime_nanoseconds - dahlia_editor_engine_xcb_timestamp_last_frame_rendered;
		if(timesincelastRedraw > (uint64_t)((1000*1000))){
			if(xcb_ready_for_redraw == 0){
				xcb_ready_for_redraw = 1;
				printf("REDRAW\n");
			}
		}
		/** End Redraw Screen **/
	}
	//End Engine

	//Print Shutdown message to the console.
	printf("Ending Dahlia Editor.\n");

	//Exit Main Program
	return 0;
}
//End of Dahlia Editor Engine

