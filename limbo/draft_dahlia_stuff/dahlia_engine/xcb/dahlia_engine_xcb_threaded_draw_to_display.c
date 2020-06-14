void *dahlia_engine_xcb_threaded_draw_to_display(void *multipleArgumentHandler){
	unsigned int keepProcessing = 1;
	while(keepProcessing == 1){
		if(xcb_ready_for_redraw == 1){
			/** BEGIN COPYING TO XCB FRAME (FRONT TO BACK PROCESSING) **/
			/** Draw grid Dahlia Image to XCB frame. **/
			uint32_t iteratorX = 1;
			uint32_t iteratorY = 1;
			unsigned int keepCopying = 1;
		
			while(keepCopying == 1){
				uint32_t index = dahlia_image_getIndex_by_xy(grid_image, iteratorX, iteratorY);
				dahlia_engine_editor_xcb_draw_rectangle(iteratorX, iteratorY, 1, 1, grid_image->colorGrid[index]);
				
				//Next.
				iteratorX = iteratorX + 1;
				if(iteratorX > grid_image->width){
					iteratorX = 1;
					iteratorY = iteratorY + 1;
				}
				if(iteratorY > grid_image->height){
					keepCopying = 0;
				}
			}

			//Draw Dahlia Image to XCB frame.
			iteratorX = 1;
			iteratorY = 1;
			keepCopying = 1;
			while(keepCopying == 1){
				uint32_t index = dahlia_image_getIndex_by_xy(displaySurface, iteratorX, iteratorY);
				//Draw to XCB display only if this is a non-transparent.
				if(displaySurface->transparencyGrid[index] == 0){
					dahlia_engine_editor_xcb_draw_rectangle(iteratorX, iteratorY, 1, 1, displaySurface->colorGrid[index]);
				}

				//Next.
				iteratorX = iteratorX + 1;
				if(iteratorX > displaySurface->width){
					iteratorX = 1;
					iteratorY = iteratorY + 1;
				}
				if(iteratorY > displaySurface->height){
					keepCopying = 0;
				}
			}
	
			//Tell XCB to update frame.
			xcb_copy_area(dahlia_editor_engine_xcb_connection, dahlia_editor_engine_xcb_pid, dahlia_editor_engine_xcb_window, dahlia_editor_engine_xcb_fill, 1, 1, 1, 1, canvasWidth, canvasHeight);
			xcb_flush(dahlia_editor_engine_xcb_connection);

			//Update status.
			xcb_ready_for_redraw = 0;

			//Update last frame rendered.
			timekeeper_update();
			dahlia_editor_engine_xcb_timestamp_last_frame_rendered = timekeeper_currentTime_nanoseconds;
		}
	}

	return (void*)0;
}
