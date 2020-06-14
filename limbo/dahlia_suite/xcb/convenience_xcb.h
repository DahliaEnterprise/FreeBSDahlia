//Convenience XCB Globals.
//XCB Handles
xcb_connection_t * xcb_connection;
xcb_screen_t * xcb_screen;
xcb_drawable_t xcb_pid;
xcb_gcontext_t xcb_fill;
xcb_drawable_t xcb_window;



//Convenience XCB Functions.
void convenience_xcb_create_window(uint16_t width, uint16_t height);

