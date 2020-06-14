void convenience_xcb_draw_rectangle_to_display(int16_t x, int16_t y, uint16_t width, uint16_t height, uint32_t colorToDraw ){
	uint32_t color[2]; 
	color[0] = colorToDraw;
	color[1] = 0;
	xcb_change_gc(xcb_connection, xcb_fill, XCB_GC_FOREGROUND | XCB_GC_BACKGROUND, color);
	xcb_poly_fill_rectangle(xcb_connection, xcb_pid, xcb_fill, 1, (xcb_rectangle_t[]){{ x, y, width, height}});
}


