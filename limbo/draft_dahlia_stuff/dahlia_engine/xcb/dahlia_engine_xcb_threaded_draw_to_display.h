pthread_t xcb_draw_to_display_thread_id;
unsigned int xcb_ready_for_redraw;

void *dahlia_engine_xcb_threaded_draw_to_display(void *multipleArgumentHandler);
