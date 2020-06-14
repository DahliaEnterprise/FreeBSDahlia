//Threaded XCB Globals
//Threaded Id
pthread_t xcb_draw_to_display_thread_id;
//Request to redraw to display
unsigned int request_to_xcb_redraw_to_display;
//Timestamp since last redraw
uint64_t xcb_timestamp_since_last_redraw_to_display;

//Dahlia Image Redraw Frame buffer
struct dahlia_image * dahlia_perpixel_framebuffer_image;
	//Matrix for determining which pixels should be redrawn.
uint8_t * dahlia_perpixel_framebuffer_colorGrid_redraw;

void dahlia_perpixel_framebuffer_initialize(uint16_t windowWidth, uint16_t windowHeight);

void convenience_xcb_threaded_function_draw_to_display_initialize();
void convenience_xcb_threaded_function_draw_to_display_start_thread();
void convenience_xcb_threaded_perpixel_framebuffer_mark_for_redraw(uint32_t x, uint32_t y);
void *convenience_xcb_threaded_function_draw_to_display(void *multipleArgumentHandler);
void convenience_xcb_threaded_function_determine_if_redraw_should_be_requested(uint16_t target_frames_per_second);

