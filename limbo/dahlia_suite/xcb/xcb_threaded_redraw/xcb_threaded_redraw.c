void dahlia_perpixel_framebuffer_initialize(uint16_t windowWidth, uint16_t windowHeight){
	//Initialize FrameBuffer Image (The image that is copied to the display when a redraw request is active).
	dahlia_perpixel_framebuffer_image = dahlia_image_initialize(windowWidth, windowHeight);
	
	//Fill the entire framebuffer image with no transparency(0) with a solid color.
	uint32_t currentIndex = 0;
	while(currentIndex < dahlia_perpixel_framebuffer_image->totalColorsInGrid){
		dahlia_perpixel_framebuffer_image->colorGrid[currentIndex] = 0xFFFFFFFF;
		dahlia_perpixel_framebuffer_image->transparencyGrid[currentIndex] = 0;
		//Next
		currentIndex = currentIndex + 1;
	}

	//Allocate tracker that will know which pixels to update.
	dahlia_perpixel_framebuffer_colorGrid_redraw = 0; while(dahlia_perpixel_framebuffer_colorGrid_redraw == 0){ dahlia_perpixel_framebuffer_colorGrid_redraw = (uint8_t*)malloc(dahlia_perpixel_framebuffer_image->totalColorsInGrid * sizeof(uint8_t)); }
	//Define tracker initialized as redraw all upon start up(first draw).
	for(uint32_t a = 0; a <= dahlia_perpixel_framebuffer_image->totalColorsInGrid; a++){
		dahlia_perpixel_framebuffer_colorGrid_redraw[a] = 1;
	}
}

void convenience_xcb_threaded_function_draw_to_display_initialize(){
	//Initialize variables for threaded redrawing.
	request_to_xcb_redraw_to_display = 0;
	xcb_timestamp_since_last_redraw_to_display = nanosecondresolution_timekeeper_getCurrentTime();
}

void convenience_xcb_threaded_function_draw_to_display_start_thread(){
	pthread_create(&xcb_draw_to_display_thread_id, 0, convenience_xcb_threaded_function_draw_to_display, 0);
}

void convenience_xcb_threaded_perpixel_framebuffer_mark_for_redraw(uint32_t x, uint32_t y){
	//This function should be used during color changes in a layer that has updated.
	char * index_error_outofbounds = 0;
	uint32_t perpixel_framebuffer_image_pixel_index = dahlia_image_getIndex_by_xy(dahlia_perpixel_framebuffer_image, x, y, index_error_outofbounds);
	//If no errors occured, then mark the index for redraw.
	if(index_error_outofbounds == 0){	
		dahlia_perpixel_framebuffer_colorGrid_redraw[perpixel_framebuffer_image_pixel_index] = 1;
	}
}

void *convenience_xcb_threaded_function_draw_to_display(void *multipleArgumentHandler){
	while(1){
		if(request_to_xcb_redraw_to_display == 1){
			/** Redraw perpixel framebuffer image to Display**/
			uint32_t perpixel_framebuffer_index = 0;
			uint32_t perpixel_framebuffer_iteratorX = 1;
			uint32_t perpixel_framebuffer_iteratorY = 1;
			uint8_t keepCopying = 1;
			while(keepCopying == 1){
				//Determine if the perpixel framebuffer is indicating this index should be redrawn.
				if(dahlia_perpixel_framebuffer_colorGrid_redraw[index] == 1){
					//Combine rgbColors
					
					//Get X,Y of the grid image using perpixel framebuffer X,Y as the target.
					//TODO
				}
				//Next
				perpixel_framebuffer_index = perpixel_framebuffer_index + 1;
				perpixel_framebuffer_iteratorX = perpixel_framebuffer_iteratorX + 1;
				if(perpixel_framebuffer_iteratorX > dahlia_perpixel_framebuffer_image->width){
					perpixel_framebuffer_iteratorX = 1;
					perpixel_framebuffer_iteratorY = perpixel_framebuffer_iteratorY + 1;
				}
				if(perpixel_framebuffer_iteratorY > dahlia_perpixel_framebuffer_image->height){
					keepCopying = 0;
				}
			}

			/** MUTED DEPRECATED DUE TO HOW THE REDRAW SYSTEM WILL WORK NOW
			uint32_t index = 0;
			uint32_t iteratorX = 1;
			uint32_t iteratorY = 1;
			uint8_t keepCopying = 1;
			while(keepCopying == 1){
				//Determine if the perpixel framebuffer is indicating this index should be redrawn.
				if(dahlia_perpixel_framebuffer_colorGrid_redraw[index] == 1){
					uint32_t finalizedRgbColor = 0;
					//Get grid color for this pixel index
					uint32_t perpixel_framebuffer_index_in_regards_to_grid_image_xy_position = convenience_xcb_threaded_function_get_dahlia_image_index_by_perpixel_framebuffer_xy(grid_image, 1, 1, uint32_t targetX_within_image, uint32_t targetY_within_image);
					printf("%u\n", perpixel_framebuffer_index_in_regards_to_grid_image_xy_position);					
					uint32_t grid_rgbColor_at_index = grid_image->colorGrid[index];
					finalizedRgbColor = grid_rgbColor_at_index;
					if(canvas_surface_image->transparencyGrid[index] == 0){
						uint32_t canvas_surface_image_rgbColor_at_index = canvas_surface_image->colorGrid[index];
						finalizedRgbColor = canvas_surface_image_rgbColor_at_index;
					}

					//Draw pixel for this x,y position based on the finalized rgb color.
					convenience_xcb_draw_rectangle_to_display(iteratorX, iteratorY, 1, 1, finalizedRgbColor);

					//Mark as no redraw needed.
					dahlia_perpixel_framebuffer_colorGrid_redraw[index] = 0;
				}

				//Next.
				index = index + 1;
				iteratorX = iteratorX + 1;
				if(iteratorX > dahlia_perpixel_framebuffer_image->width){
					iteratorX = 1;
					iteratorY = iteratorY + 1;
				}
				if(iteratorY > dahlia_perpixel_framebuffer_image->height){
					keepCopying = 0;
				}
			}
			**/

			//Tell XCB its time to update frame to display.
			xcb_copy_area(xcb_connection, xcb_pid, xcb_window, xcb_fill, 1, 1, 1, 1, dahlia_perpixel_framebuffer_image->width, dahlia_perpixel_framebuffer_image->height);
			xcb_flush(xcb_connection);

			//Update last redraw timestamp.
			xcb_timestamp_since_last_redraw_to_display = nanosecondresolution_timekeeper_getCurrentTime();

			//Turn of status to redraw to display (To be turned on outside of thread).
			request_to_xcb_redraw_to_display = 0;
		}
	}
	return (void*)0;
}

void convenience_xcb_threaded_function_determine_if_redraw_should_be_requested(uint16_t target_frames_per_second){
	//Don't determine if a request to redraw should be made if the current request hasn't been fullfilled.
	if(request_to_xcb_redraw_to_display == 0){
		//Determine how many miliseconds is required to achieve the target frames per second.
		uint64_t nanoseconds_per_second = (1000 * 1000) * 1000; //1000 nanoseconds times 1000 is 1 milisecond, times 1000 is 1 second in the form of nanoseconds.
		//Divide nanoseconds per second by target frames per second.
		uint64_t nanoseconds_pause_between_frames = nanoseconds_per_second / target_frames_per_second;
		//Get current time in nanosecond space.
		uint64_t currentTime_nanoseconds = nanosecondresolution_timekeeper_getCurrentTime();
		//Get nanoseconds since last redraw.
		uint64_t time_since_last_redraw = currentTime_nanoseconds - xcb_timestamp_since_last_redraw_to_display;
		//If nanoseconds since last redraw is larger than the "wait till redraw" time, then request a redraw to display.
		if(time_since_last_redraw >= nanoseconds_pause_between_frames){
			request_to_xcb_redraw_to_display = 1;
		}
	}
}

void convenience_xcb_threaded_get_overlay_image_xy(struct dahlia_image * overlay_image, int32_t overlay_image_topLeft_x, int32_t overlay_image_topLeft_y, uint32_t perpixel_framebuffer_target_x, uint32_t perpixel_framebuffer_target_y){
	//Determine offset difference of overlay image in comparison to the perpixel framebuffer.
	//^^ offset difference is overlay image topLeft X Y
	
	//Determine the X Y of the overlay image based on the perpixel framebuffer X Y target as the aquirer.
		//Is the target beyond the bounds of the over lay image in regards to the overlay placement over the perpixel framebuffer image.
		uint8_t target_outOfBounds = 0;
		int64_t overlay_image_rightside_x = overlay_image_topLeft_x + overlay_image->width;
		printf("%ld\n", overlay_image_rightside_x);
		if(overlay_image_rightside_x <= 0){
			target_outOfBounds = 1;
		}
}




