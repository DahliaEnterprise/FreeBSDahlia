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
	canvasWidth = 1000;
	canvasHeight = 700;

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
	
	//XCB Event State.
	//dahlia_engine_xcb_events_initialize();

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

	//Initialize dahlia image to be used for the single layer display surface.
	 displaySurface = dahlia_image_initialize(canvasWidth, canvasHeight);
	dahlia_image_define_pixel_information_by_square_area(displaySurface, 1, 1, canvasWidth, canvasHeight, 0x000000, 1000000);

	//Begin Engine
		//PThread Initialize.
		xcb_ready_for_redraw = 0;
		pthread_create(&xcb_draw_to_display_thread_id, 0, dahlia_engine_xcb_threaded_draw_to_display, 0);
		//End PThread Initialize.
	while(1){}
/*
	while(1){

		/** Begin Redraw screen. **
		timekeeper_update();
		uint64_t timesincelastRedraw = timekeeper_currentTime_nanoseconds - dahlia_editor_engine_xcb_timestamp_last_frame_rendered;
		uint64_t timeToWait_nanoSeconds = 1000 * 1000;
		if(timesincelastRedraw >= timeToWait_nanoSeconds){
			if(xcb_ready_for_redraw == 0){
				xcb_ready_for_redraw = 1;
				printf("redraw,");
			}
		}
		/** End Redraw Screen **
	}*/

	return 0 ;
}
