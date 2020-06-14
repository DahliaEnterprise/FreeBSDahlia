//Dahlia Editor Engine XCB, Global Variables.
xcb_connection_t * dahlia_editor_engine_xcb_connection;
xcb_screen_t * dahlia_editor_engine_xcb_screen;
xcb_drawable_t dahlia_editor_engine_xcb_pid;
xcb_gcontext_t dahlia_editor_engine_xcb_fill;
xcb_drawable_t dahlia_editor_engine_xcb_window;
xcb_gcontext_t foreground;

//Dahlia Editor Engine XCB, Function Headers
void dahlia_engine_editor_xcb_create_window(uint16_t width, uint16_t height);
void dahlia_engine_editor_xcb_draw_rectangle(int16_t x, int16_t y, uint16_t width, uint16_t height, uint32_t colorToDraw);
