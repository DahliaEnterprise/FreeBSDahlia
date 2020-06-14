void dahlia_engine_editor_xcb_create_window(uint16_t width, uint16_t height){
	
	//Create X11 Connection Handle
	dahlia_editor_engine_xcb_connection = xcb_connect("Dahlia Engine", 0);
	//Create X11 Screen Handle
	dahlia_editor_engine_xcb_screen = xcb_setup_roots_iterator( xcb_get_setup( dahlia_editor_engine_xcb_connection ) ).data;

	/** Clear screen as the Initial Frame **/
	uint32_t mask = 0;
	uint32_t values[2];

	//Initial Black Screen - (Dosn't Visually Paint to Screen, However is a required part of the initalization process)
	foreground = xcb_generate_id(dahlia_editor_engine_xcb_connection);
	mask = XCB_GC_FOREGROUND;/* | XCB_GC_GRAPHICS_EXPOSURES*/
	values[0] = dahlia_editor_engine_xcb_screen->black_pixel;
	values[1] = 0;
	xcb_create_gc(dahlia_editor_engine_xcb_connection, foreground, dahlia_editor_engine_xcb_screen->root, mask, values);

	dahlia_editor_engine_xcb_pid = xcb_generate_id(dahlia_editor_engine_xcb_connection);
	xcb_create_pixmap(dahlia_editor_engine_xcb_connection, dahlia_editor_engine_xcb_screen->root_depth, dahlia_editor_engine_xcb_pid, dahlia_editor_engine_xcb_screen->root, width, height);
	
	//Initial Solid Color Screen
	dahlia_editor_engine_xcb_fill = xcb_generate_id(dahlia_editor_engine_xcb_connection);
	mask = XCB_GC_FOREGROUND | XCB_GC_BACKGROUND;
	values[0] = 0x00000000; //0xD2F262D0;
	values[1] = 0;
	xcb_create_gc(dahlia_editor_engine_xcb_connection, dahlia_editor_engine_xcb_fill, dahlia_editor_engine_xcb_pid, mask, values);
	
	//Create Window
	dahlia_editor_engine_xcb_window = xcb_generate_id(dahlia_editor_engine_xcb_connection);
	mask = XCB_CW_BACK_PIXMAP | XCB_CW_EVENT_MASK;
	values[0] = dahlia_editor_engine_xcb_pid;
	values[1] = XCB_EVENT_MASK_EXPOSURE | XCB_EVENT_MASK_BUTTON_PRESS | XCB_EVENT_MASK_BUTTON_RELEASE | XCB_EVENT_MASK_POINTER_MOTION | XCB_EVENT_MASK_BUTTON_MOTION | XCB_EVENT_MASK_KEY_PRESS | XCB_EVENT_MASK_KEY_RELEASE;

	xcb_create_window(dahlia_editor_engine_xcb_connection, dahlia_editor_engine_xcb_screen->root_depth, dahlia_editor_engine_xcb_window, dahlia_editor_engine_xcb_screen->root, 0, 0, width, height, 10, XCB_WINDOW_CLASS_INPUT_OUTPUT, dahlia_editor_engine_xcb_screen->root_visual, mask, values);

	/* map window to screen */
	xcb_map_window(dahlia_editor_engine_xcb_connection, dahlia_editor_engine_xcb_window);

	xcb_poly_fill_rectangle(dahlia_editor_engine_xcb_connection, dahlia_editor_engine_xcb_pid, dahlia_editor_engine_xcb_fill, 1, (xcb_rectangle_t[]){{ 0, 0, width, height}});

	/* draw with a color 
	//Randomize positions and color
	printf("Random:%d\n", RAND_MAX);
	srand(time(0));
	printf("Random number:%d\n", (rand() % (65 + 1 - 0) + 0));
	int flushCounter = 0;
	uint32_t randomColor[2];
	randomColor[0] = (rand() % (255 + 1 - 0) + 0);
	randomColor[1] = 0;
	xcb_change_gc(dahlia_editor_engine_xcb_connection, dahlia_editor_engine_xcb_fill, XCB_GC_FOREGROUND, randomColor);
	xcb_poly_fill_rectangle(dahlia_editor_engine_xcb_connection, dahlia_editor_engine_xcb_pid, dahlia_editor_engine_xcb_fill, 1, (xcb_rectangle_t[]){{ 0, 0, 50, 50}});
	
	*/
	
	//printf("%d\n", flushCounter);
	xcb_flush(dahlia_editor_engine_xcb_connection);
		
}

void dahlia_engine_editor_xcb_draw_rectangle(int16_t x, int16_t y, uint16_t width, uint16_t height, uint32_t colorToDraw ){
	uint32_t color[2]; 
	color[0] = colorToDraw;
	color[1] = 0;
	xcb_change_gc(dahlia_editor_engine_xcb_connection, dahlia_editor_engine_xcb_fill, XCB_GC_FOREGROUND | XCB_GC_BACKGROUND, color);
	xcb_poly_fill_rectangle(dahlia_editor_engine_xcb_connection, dahlia_editor_engine_xcb_pid, dahlia_editor_engine_xcb_fill, 1, (xcb_rectangle_t[]){{ x, y, width, height}});
}



