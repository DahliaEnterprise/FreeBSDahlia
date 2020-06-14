void convenience_xcb_create_window(uint16_t width, uint16_t height){
	//Create X11 Connection Handle
	xcb_connection = xcb_connect(0, 0);
	//Create X11 Screen Handle
	xcb_screen = xcb_setup_roots_iterator( xcb_get_setup( xcb_connection ) ).data;

	/** Clear screen as the Initial Frame **/
	uint32_t mask = 0;
	uint32_t values[2];

	//Initial Black Screen - (Dosn't Visually Paint to Screen, However is a required part of the initalization process)
	xcb_gcontext_t foreground = xcb_generate_id(xcb_connection);
	mask = XCB_GC_FOREGROUND | XCB_GC_GRAPHICS_EXPOSURES;
	values[0] = xcb_screen->black_pixel;
	values[1] = 0;
	xcb_create_gc(xcb_connection, foreground, xcb_screen->root, mask, values);

	xcb_pid = xcb_generate_id(xcb_connection);
	xcb_create_pixmap(xcb_connection, xcb_screen->root_depth, xcb_pid, xcb_screen->root, width, height);

	//Initial Solid Color Screen
	xcb_fill = xcb_generate_id(xcb_connection);
	mask = XCB_GC_FOREGROUND | XCB_GC_BACKGROUND;
	values[0] = 0x000000; //0xD2F262D0;
	values[1] = 0;
	xcb_create_gc(xcb_connection, xcb_fill, xcb_pid, mask, values);

	//Create Window
	xcb_window = xcb_generate_id(xcb_connection);
	mask = XCB_CW_BACK_PIXMAP | XCB_CW_EVENT_MASK;
	values[0] = xcb_pid;
	values[1] = XCB_EVENT_MASK_EXPOSURE | XCB_EVENT_MASK_BUTTON_PRESS | XCB_EVENT_MASK_BUTTON_MOTION | XCB_EVENT_MASK_KEY_PRESS | XCB_EVENT_MASK_KEY_RELEASE | XCB_EVENT_MASK_ENTER_WINDOW | XCB_EVENT_MASK_LEAVE_WINDOW;

	xcb_create_window(xcb_connection, xcb_screen->root_depth, xcb_window, xcb_screen->root, 0, 0, width, height, 1, XCB_WINDOW_CLASS_INPUT_OUTPUT, xcb_screen->root_visual, mask, values);

	/* map window to screen */
	xcb_map_window(xcb_connection, xcb_window);
	/* Flush Queued Commands */
	xcb_flush(xcb_connection);	

	/* Clear  window */
	xcb_poly_fill_rectangle(xcb_connection, xcb_pid, xcb_fill, 1, (xcb_rectangle_t[]){{ 0, 0, width, height}});

	/* Flush Queued Commands */
	xcb_flush(xcb_connection);	
}


