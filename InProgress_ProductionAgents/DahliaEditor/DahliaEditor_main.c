/** Copyright Shane Betz, Year 2020 **/

//Include System Headrs
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include "/usr/local/include/xcb/xcb.h"

//Include DahliaEditor Headers
    //XCB Handles
    xcb_connection_t * xcb_connection;
    xcb_screen_t * xcb_screen;
    xcb_drawable_t xcb_pid;
    xcb_gcontext_t xcb_fill;
    xcb_drawable_t xcb_window;

    /** Keyboard State Definition: 0 = key up, 1 = key down, 2 = key released(reset to key up at end of cycle) **/
    uint8_t xcb_event_keyboard_a_state;
    uint8_t xcb_event_keyboard_b_state;
    uint8_t xcb_event_keyboard_c_state;
    uint8_t xcb_event_keyboard_d_state;
    uint8_t xcb_event_keyboard_e_state;
    uint8_t xcb_event_keyboard_f_state;
    uint8_t xcb_event_keyboard_g_state;
    uint8_t xcb_event_keyboard_h_state;
    uint8_t xcb_event_keyboard_i_state;
    uint8_t xcb_event_keyboard_j_state;
    uint8_t xcb_event_keyboard_k_state;
    uint8_t xcb_event_keyboard_l_state;
    uint8_t xcb_event_keyboard_m_state;
    uint8_t xcb_event_keyboard_n_state;
    uint8_t xcb_event_keyboard_o_state;
    uint8_t xcb_event_keyboard_p_state;
    uint8_t xcb_event_keyboard_q_state;
    uint8_t xcb_event_keyboard_r_state;
    uint8_t xcb_event_keyboard_s_state;
    uint8_t xcb_event_keyboard_t_state;
    uint8_t xcb_event_keyboard_u_state;
    uint8_t xcb_event_keyboard_v_state;
    uint8_t xcb_event_keyboard_w_state;
    uint8_t xcb_event_keyboard_x_state;
    uint8_t xcb_event_keyboard_y_state;
    uint8_t xcb_event_keyboard_z_state;
    uint8_t xcb_event_keyboard_leftarrow_state;
    uint8_t xcb_event_keyboard_rightarrow_state;

    //Mouse Event States
    int16_t xcb_event_mouse_x ;
    int16_t xcb_event_mouse_y ;
    uint8_t xcb_event_mouse_leftbutton_down;
    uint8_t xcb_event_mouse_rightbutton_down;

    //Window Event States
    uint8_t xcb_event_window_focus;

    //Redraw Time Keeper.
    //MUTED:uint64_t xcb_xcb_timestamp_last_frame_rendered;

    //XCB Event Handle
    xcb_generic_event_t * xcb_event;
    
    //Dahlia Images Paradigm
        //Pre-requisite to Dahlia Images
        #include "/root/DahliaEditor/data_consume_assist/data_consume_assist.h"
        #include "/root/DahliaEditor/string_to_integer/string_to_integer.h"
        #include "/root/DahliaEditor/total_digits_within_integer/total_digits_within_integer.h"
    #include "/root/DahliaEditor/dahlia_image/dahlia_image.h"
    
    //English Font - Utilizes Dahlia Images paradigm
    char * font_english_letter_index;
    struct dahlia_image ** font_english_images;


//Include DahliaEditor Definitions - (Temporarily Contains Header Format Function Declarations)
void dahliaeditor_create_window(uint16_t width, uint16_t height);
void dahliaeditor_initialize_events();
void dahliaeditor_poll_events();
void dahliaeditor_define_released_events();
#include "/root/DahliaEditor/data_consume_assist/data_consume_assist.c"
#include "/root/DahliaEditor/string_to_integer/string_to_integer.c"
#include "/root/DahliaEditor/total_digits_within_integer/total_digits_within_integer.c"
#include "/root/DahliaEditor/dahlia_image/dahlia_image.c"
void dahliaeditor_initialize_font_english();
uint8_t dahliaeditor_font_english_get_index_by_letter(char* letter);

//Begin Program
int main()
{
    //Create DahliaEditor Window
    uint16_t initial_window_width = (uint16_t)800;
    uint16_t initial_window_height = (uint16_t)400;
    dahliaeditor_create_window(initial_window_width, initial_window_height);
    
    //Initialize Events (Using XCB events that are already integrated into the window)
    dahliaeditor_initialize_events();
    
    //Begin Window Sustain Life Loop.
    while(1==1){
        //Poll(Detect) events from Keyboard, Mouse, GamePad events
        dahliaeditor_poll_events();
        
        
        //Begin Application Logic
        
        //End Application Logic
        
        //Define Events That Have Been Released
        dahliaeditor_define_released_events();
        
    }
}
//End Program

void dahliaeditor_create_window(uint16_t width, uint16_t height){
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

void dahliaeditor_initialize_events()
{
    /** Initialize Dahlia Event System **/
	xcb_event = 0;
	xcb_event_keyboard_a_state = 0;
	xcb_event_keyboard_b_state = 0;
	xcb_event_keyboard_c_state = 0;
	xcb_event_keyboard_d_state = 0;
	xcb_event_keyboard_e_state = 0;
	xcb_event_keyboard_f_state = 0;
	xcb_event_keyboard_g_state = 0;
	xcb_event_keyboard_h_state = 0;
	xcb_event_keyboard_i_state = 0;
	xcb_event_keyboard_j_state = 0;
	xcb_event_keyboard_k_state = 0;
	xcb_event_keyboard_l_state = 0;
	xcb_event_keyboard_m_state = 0;
	xcb_event_keyboard_n_state = 0;
	xcb_event_keyboard_o_state = 0;
	xcb_event_keyboard_p_state = 0;
	xcb_event_keyboard_q_state = 0;
	xcb_event_keyboard_r_state = 0;
	xcb_event_keyboard_s_state = 0;
	xcb_event_keyboard_t_state = 0;
	xcb_event_keyboard_u_state = 0;
	xcb_event_keyboard_v_state = 0;
	xcb_event_keyboard_w_state = 0;
	xcb_event_keyboard_x_state = 0;
	xcb_event_keyboard_y_state = 0;
	xcb_event_keyboard_z_state = 0;
	xcb_event_keyboard_leftarrow_state = 0;
	xcb_event_keyboard_rightarrow_state = 0;

	//Mouse Event States
	xcb_event_mouse_x = 1;
	xcb_event_mouse_y = 1;
	xcb_event_mouse_leftbutton_down = 0;
	xcb_event_mouse_rightbutton_down = 0;

	//Window Event States
	xcb_event_window_focus = 0;

	//Redraw Time Keeper.
	//MUTED:xcb_xcb_timestamp_last_frame_rendered = 0;
}

void dahliaeditor_poll_events()
{
    //Reset event handle.
	xcb_event = 0;

	//Do Poll For Event.
	xcb_event = xcb_poll_for_event (xcb_connection);

	//Manage Event.
	if(xcb_event != 0){
		if(xcb_event->response_type == XCB_KEY_PRESS){
			xcb_key_press_event_t * keyPressEvent = (xcb_key_press_event_t*)xcb_event;
			/*if(keyPressEvent->detail == 39){
				//KEYPRESS
			}*/
			if(keyPressEvent->detail == 38){
				xcb_event_keyboard_a_state = 1;
			}else if(keyPressEvent->detail == 56){
				xcb_event_keyboard_b_state = 1;
			}else if(keyPressEvent->detail == 54){
				xcb_event_keyboard_c_state = 1;
			}else if(keyPressEvent->detail == 40){
				xcb_event_keyboard_d_state = 1;
			}else if(keyPressEvent->detail == 26){
				xcb_event_keyboard_e_state = 1;
			}else if(keyPressEvent->detail == 41){
				xcb_event_keyboard_f_state = 1;
			}else if(keyPressEvent->detail == 42){
				xcb_event_keyboard_g_state = 1;
			}else if(keyPressEvent->detail == 43){
				xcb_event_keyboard_h_state = 1;
			}else if(keyPressEvent->detail == 31){
				xcb_event_keyboard_i_state = 1;
			}else if(keyPressEvent->detail == 44){
				xcb_event_keyboard_j_state = 1;
			}else if(keyPressEvent->detail == 45){
				xcb_event_keyboard_k_state = 1;
			}else if(keyPressEvent->detail == 46){
				xcb_event_keyboard_l_state = 1;
			}else if(keyPressEvent->detail == 58){
				xcb_event_keyboard_m_state = 1;
			}else if(keyPressEvent->detail == 57){
				xcb_event_keyboard_n_state = 1;
			}else if(keyPressEvent->detail == 32){
				xcb_event_keyboard_o_state = 1;
			}else if(keyPressEvent->detail == 33){
				xcb_event_keyboard_p_state = 1;
			}else if(keyPressEvent->detail == 24){
				xcb_event_keyboard_q_state = 1;
			}else if(keyPressEvent->detail == 27){
				xcb_event_keyboard_r_state = 1;
			}else if(keyPressEvent->detail == 39){
				xcb_event_keyboard_s_state = 1;
			}else if(keyPressEvent->detail == 28){
				xcb_event_keyboard_t_state = 1;
			}else if(keyPressEvent->detail == 30){
				xcb_event_keyboard_u_state = 1;
			}else if(keyPressEvent->detail == 55){
				xcb_event_keyboard_v_state = 1;
			}else if(keyPressEvent->detail == 25){
				xcb_event_keyboard_w_state = 1;
			}else if(keyPressEvent->detail == 53){
				xcb_event_keyboard_x_state = 1;
			}else if(keyPressEvent->detail == 29){
				xcb_event_keyboard_y_state = 1;
			}else if(keyPressEvent->detail == 52){
				xcb_event_keyboard_z_state = 1;
			}else if(keyPressEvent->detail == 100){
				xcb_event_keyboard_leftarrow_state = 1;
			}else if(keyPressEvent->detail == 102){
				xcb_event_keyboard_rightarrow_state = 1;
			}

		}else if(xcb_event->response_type == XCB_KEY_RELEASE){
			xcb_key_release_event_t * keyReleaseEvent = (xcb_key_release_event_t*)xcb_event;
			if(keyReleaseEvent->detail == 38){
				xcb_event_keyboard_a_state = 2;
			}else if(keyReleaseEvent->detail == 56){
				xcb_event_keyboard_b_state = 2;
			}else if(keyReleaseEvent->detail == 54){
				xcb_event_keyboard_c_state = 2;
			}else if(keyReleaseEvent->detail == 40){
				xcb_event_keyboard_d_state = 2;
			}else if(keyReleaseEvent->detail == 26){
				xcb_event_keyboard_e_state = 2;
			}else if(keyReleaseEvent->detail == 41){
				xcb_event_keyboard_f_state = 2;
			}else if(keyReleaseEvent->detail == 42){
				xcb_event_keyboard_g_state = 2;
			}else if(keyReleaseEvent->detail == 43){
				xcb_event_keyboard_h_state = 2;
			}else if(keyReleaseEvent->detail == 31){
				xcb_event_keyboard_i_state = 2;
			}else if(keyReleaseEvent->detail == 44){
				xcb_event_keyboard_j_state = 2;
			}else if(keyReleaseEvent->detail == 45){
				xcb_event_keyboard_k_state = 2;
			}else if(keyReleaseEvent->detail == 46){
				xcb_event_keyboard_l_state = 2;
			}else if(keyReleaseEvent->detail == 58){
				xcb_event_keyboard_m_state = 2;
			}else if(keyReleaseEvent->detail == 57){
				xcb_event_keyboard_n_state = 2;
			}else if(keyReleaseEvent->detail == 32){
				xcb_event_keyboard_o_state = 2;
			}else if(keyReleaseEvent->detail == 33){
				xcb_event_keyboard_p_state = 2;
			}else if(keyReleaseEvent->detail == 24){
				xcb_event_keyboard_q_state = 2;
			}else if(keyReleaseEvent->detail == 27){
				xcb_event_keyboard_r_state = 2;
			}else if(keyReleaseEvent->detail == 39){
				xcb_event_keyboard_s_state = 2;
			}else if(keyReleaseEvent->detail == 28){
				xcb_event_keyboard_t_state = 2;
			}else if(keyReleaseEvent->detail == 30){
				xcb_event_keyboard_u_state = 2;
			}else if(keyReleaseEvent->detail == 55){
				xcb_event_keyboard_v_state = 2;
			}else if(keyReleaseEvent->detail == 25){
				xcb_event_keyboard_w_state = 2;
			}else if(keyReleaseEvent->detail == 53){
				xcb_event_keyboard_x_state = 2;
			}else if(keyReleaseEvent->detail == 29){
				xcb_event_keyboard_y_state = 2;
			}else if(keyReleaseEvent->detail == 52){
				xcb_event_keyboard_z_state = 2;
			}else if(keyReleaseEvent->detail == 100){
				xcb_event_keyboard_leftarrow_state = 2;
			}else if(keyReleaseEvent->detail == 102){
				xcb_event_keyboard_rightarrow_state = 2;
			}
			//printf("KEY RELEASE\n");
		}else if(xcb_event->response_type == XCB_MOTION_NOTIFY){
			 xcb_motion_notify_event_t * mouseMoveEvent = (xcb_motion_notify_event_t*)xcb_event;
			//printf("%i   %i     ,    %i     %i\n", mouseMoveEvent->root_x, mouseMoveEvent->root_y, mouseMoveEvent->event_x, mouseMoveEvent->event_y);
			//Event XY is window coordinates.
			xcb_event_mouse_x = mouseMoveEvent->event_x;
			xcb_event_mouse_y = mouseMoveEvent->event_y;
		
		}else if(xcb_event->response_type == XCB_BUTTON_PRESS){
			xcb_button_press_event_t* mouseDownEvent = (xcb_button_press_event_t*)xcb_event;
			//printf("event:%d\n", mouseDownEvent->detail);

			if(mouseDownEvent->detail == 1){
				xcb_event_mouse_leftbutton_down = 1;
				xcb_event_mouse_x = mouseDownEvent->event_x;
				xcb_event_mouse_y = mouseDownEvent->event_y;
			}else if(mouseDownEvent->detail == 3){		
				xcb_event_mouse_rightbutton_down = 1;
				xcb_event_mouse_x = mouseDownEvent->event_x;
				xcb_event_mouse_y = mouseDownEvent->event_y;
			}
			
		}else if(xcb_event->response_type == XCB_BUTTON_RELEASE){
			xcb_button_release_event_t* mouseUpEvent = (xcb_button_release_event_t*)xcb_event;
			//printf("event:%d\n", mouseUpEvent->detail);
			if(mouseUpEvent->detail == 1){ 
				xcb_event_mouse_leftbutton_down = 0; 
			}else if(mouseUpEvent->detail == 3){
				xcb_event_mouse_rightbutton_down = 0; 
			}

		}else if(xcb_event->response_type == XCB_EXPOSE){
		}else if(xcb_event->response_type == XCB_ENTER_NOTIFY){
			xcb_enter_notify_event_t* windowEnterEvent = (xcb_enter_notify_event_t*)xcb_event;
			xcb_event_mouse_x = windowEnterEvent->event_x;
			xcb_event_mouse_y = windowEnterEvent->event_y;
			xcb_event_window_focus = 1;
		}else if(xcb_event->response_type == XCB_LEAVE_NOTIFY ){
				xcb_leave_notify_event_t* windowLeaveEvent = (xcb_leave_notify_event_t*)xcb_event;
			xcb_event_mouse_x = windowLeaveEvent->event_x;
			xcb_event_mouse_y = windowLeaveEvent->event_y;
			xcb_event_window_focus = 0;
			xcb_event_mouse_leftbutton_down = 0;
			xcb_event_mouse_rightbutton_down = 0;
		}

		//Free Event.
		free(xcb_event);
	}
}

void dahliaeditor_define_released_events()
{
    if(xcb_event_keyboard_a_state == 2){
		xcb_event_keyboard_a_state = 0;
	}

	if(xcb_event_keyboard_b_state == 2){
		xcb_event_keyboard_b_state = 0;
	}

	if(xcb_event_keyboard_c_state == 2){
		xcb_event_keyboard_c_state = 0;
	}

	if(xcb_event_keyboard_d_state == 2){
		xcb_event_keyboard_d_state = 0;
	}

	if(xcb_event_keyboard_e_state == 2){
		xcb_event_keyboard_e_state = 0;
	}

	if(xcb_event_keyboard_f_state == 2){
		xcb_event_keyboard_f_state = 0;
	}

	if(xcb_event_keyboard_g_state == 2){
		xcb_event_keyboard_g_state = 0;
	}

	if(xcb_event_keyboard_h_state == 2){
		xcb_event_keyboard_h_state = 0;
	}

	if(xcb_event_keyboard_i_state == 2){
		xcb_event_keyboard_i_state = 0;
	}

	if(xcb_event_keyboard_j_state == 2){
		xcb_event_keyboard_j_state = 0;
	}

	if(xcb_event_keyboard_k_state == 2){
		xcb_event_keyboard_k_state = 0;
	}
	
	if(xcb_event_keyboard_l_state == 2){
		xcb_event_keyboard_l_state = 0;
	}

	if(xcb_event_keyboard_m_state == 2){
		xcb_event_keyboard_m_state = 0;
	}

	if(xcb_event_keyboard_n_state == 2){
		xcb_event_keyboard_n_state = 0;
	}

	if(xcb_event_keyboard_o_state == 2){
		xcb_event_keyboard_o_state = 0;
	}

	if(xcb_event_keyboard_p_state == 2){
		xcb_event_keyboard_p_state = 0;
	}

	if(xcb_event_keyboard_q_state == 2){
		xcb_event_keyboard_q_state = 0;
	}

	if(xcb_event_keyboard_r_state == 2){
		xcb_event_keyboard_r_state = 0;
	}

	if(xcb_event_keyboard_s_state == 2){
		xcb_event_keyboard_s_state = 0;
	}

	if(xcb_event_keyboard_t_state == 2){
		xcb_event_keyboard_t_state = 0;
	}

	if(xcb_event_keyboard_u_state == 2){
		xcb_event_keyboard_u_state = 0;
	}

	if(xcb_event_keyboard_v_state == 2){
		xcb_event_keyboard_v_state = 0;
	}

	if(xcb_event_keyboard_w_state == 2){
		xcb_event_keyboard_w_state = 0;
	}

	if(xcb_event_keyboard_x_state == 2){
		xcb_event_keyboard_x_state = 0;
	}

	if(xcb_event_keyboard_y_state == 2){
		xcb_event_keyboard_y_state = 0;
	}

	if(xcb_event_keyboard_z_state == 2){
		xcb_event_keyboard_z_state = 0;
	}

	if(xcb_event_keyboard_leftarrow_state == 2){
		xcb_event_keyboard_leftarrow_state = 0;
	}

	if(xcb_event_keyboard_rightarrow_state == 2){
		xcb_event_keyboard_rightarrow_state = 0;
	}
}

void dahliaeditor_initialize_font_english()
{
    //Allocate memory for letter index map.
	font_english_letter_index = 0; while( font_english_letter_index == 0 ){ font_english_letter_index = (char*)malloc( 26 * sizeof(char) ); }
	
	//Map index numbers to letters.
	font_english_letter_index[0] = 'a';
	font_english_letter_index[1] = 'b';
	font_english_letter_index[2] = 'c';
	font_english_letter_index[3] = 'd';
	font_english_letter_index[4] = 'e';
	font_english_letter_index[5] = 'f';
	font_english_letter_index[6] = 'g';
	font_english_letter_index[7] = 'h';
	font_english_letter_index[8] = 'i';
	font_english_letter_index[9] = 'j';
	font_english_letter_index[10] = 'k';
	font_english_letter_index[11] = 'l';
	font_english_letter_index[12]= 'm';
	font_english_letter_index[13] = 'n';
	font_english_letter_index[14] = 'o';
	font_english_letter_index[15] = 'p';
	font_english_letter_index[16] = 'q';
	font_english_letter_index[17] = 'r';
	font_english_letter_index[18] = 's';
	font_english_letter_index[19] = 't';
	font_english_letter_index[20] = 'u';
	font_english_letter_index[21] = 'v';
	font_english_letter_index[22] = 'w';
	font_english_letter_index[23] = 'x';
	font_english_letter_index[24] = 'y';
	font_english_letter_index[25] = 'z';

	//Allocate memory for array images.
	font_english_images = 0; while( font_english_images == 0){ font_english_images = (struct dahlia_image**)malloc(26 * sizeof(struct dahlia_image)); }
	
	//loop through each letter index and load that image.
	char letterImages_fileLocationAndName[] = "/root/DahliaEditor/dahlia_alphabet_english/letter_a.dahlia_rgba";
	uint8_t letterReplacementIndex = 72; //position of the letterImage_fileLocationAndName to be automated for letter-replacement.///
	uint8_t currentIndex = 0;
	while(currentIndex < 26){
		//Update file location string.
		letterImages_fileLocationAndName[letterReplacementIndex] = font_english_letter_index[currentIndex];

		//Load image into array of images memory.
		font_english_images[currentIndex] = dahlia_image_load_file(letterImages_fileLocationAndName);

		//Next
		currentIndex = currentIndex + 1;
	}
}

uint8_t dahliaedtor_font_english_get_index_by_letter(char* letter){
	uint8_t output = 0;

	uint8_t currentIndex = 0;
	while(currentIndex < 26){
		if(strncmp(letter, &font_english_letter_index[currentIndex], 1) == 0){
			output = currentIndex;
			//Stop search
			currentIndex = 26;
		}

		//Next
		currentIndex = currentIndex + 1;
	}	

	return output;
}


