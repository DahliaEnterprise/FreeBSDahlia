void dahlia_engine_xcb_events_initialize(){
	/** Initialize Dahlia Event System **/
	dahlia_editor_engine_event = 0;
	dahlia_editor_engine_event_keyboard_a_state = 0;
	dahlia_editor_engine_event_keyboard_b_state = 0;
	dahlia_editor_engine_event_keyboard_c_state = 0;
	dahlia_editor_engine_event_keyboard_d_state = 0;
	dahlia_editor_engine_event_keyboard_e_state = 0;
	dahlia_editor_engine_event_keyboard_f_state = 0;
	dahlia_editor_engine_event_keyboard_g_state = 0;
	dahlia_editor_engine_event_keyboard_h_state = 0;
	dahlia_editor_engine_event_keyboard_i_state = 0;
	dahlia_editor_engine_event_keyboard_j_state = 0;
	dahlia_editor_engine_event_keyboard_k_state = 0;
	dahlia_editor_engine_event_keyboard_l_state = 0;
	dahlia_editor_engine_event_keyboard_m_state = 0;
	dahlia_editor_engine_event_keyboard_n_state = 0;
	dahlia_editor_engine_event_keyboard_o_state = 0;
	dahlia_editor_engine_event_keyboard_p_state = 0;
	dahlia_editor_engine_event_keyboard_q_state = 0;
	dahlia_editor_engine_event_keyboard_r_state = 0;
	dahlia_editor_engine_event_keyboard_s_state = 0;
	dahlia_editor_engine_event_keyboard_t_state = 0;
	dahlia_editor_engine_event_keyboard_u_state = 0;
	dahlia_editor_engine_event_keyboard_v_state = 0;
	dahlia_editor_engine_event_keyboard_w_state = 0;
	dahlia_editor_engine_event_keyboard_x_state = 0;
	dahlia_editor_engine_event_keyboard_y_state = 0;
	dahlia_editor_engine_event_keyboard_z_state = 0;
	dahlia_editor_engine_event_keyboard_leftarrow_state = 0;
	dahlia_editor_engine_event_keyboard_rightarrow_state = 0;

	//Mouse Event States
	dahlia_editor_engine_event_mouse_x = 1;
	dahlia_editor_engine_event_mouse_y = 1;
	dahlia_editor_engine_event_mouse_leftbutton_down = 0;
	dahlia_editor_engine_event_mouse_rightbutton_down = 0;

	//Redraw Time Keeper.
	dahlia_editor_engine_xcb_timestamp_last_frame_rendered = 0;
}

void dahlia_engine_xcb_events_poll(){
	//Reset event handle.
	dahlia_editor_engine_event = 0;

	//Do Poll For Event.
	dahlia_editor_engine_event = xcb_poll_for_event (dahlia_editor_engine_xcb_connection);

	//Manage Event.
	if(dahlia_editor_engine_event != 0){
		if(dahlia_editor_engine_event->response_type == XCB_KEY_PRESS){
			xcb_key_press_event_t * keyPressEvent = (xcb_key_press_event_t*)dahlia_editor_engine_event;
			/*if(keyPressEvent->detail == 39){
				//KEYPRESS
			}*/
			printf("KEY PRESS, %d\n", keyPressEvent->detail);
			if(keyPressEvent->detail == 38){
				dahlia_editor_engine_event_keyboard_a_state = 1;
			}else if(keyPressEvent->detail == 56){
				dahlia_editor_engine_event_keyboard_b_state = 1;
			}else if(keyPressEvent->detail == 54){
				dahlia_editor_engine_event_keyboard_c_state = 1;
			}else if(keyPressEvent->detail == 40){
				dahlia_editor_engine_event_keyboard_d_state = 1;
			}else if(keyPressEvent->detail == 26){
				dahlia_editor_engine_event_keyboard_e_state = 1;
			}else if(keyPressEvent->detail == 41){
				dahlia_editor_engine_event_keyboard_f_state = 1;
			}else if(keyPressEvent->detail == 42){
				dahlia_editor_engine_event_keyboard_g_state = 1;
			}else if(keyPressEvent->detail == 43){
				dahlia_editor_engine_event_keyboard_h_state = 1;
			}else if(keyPressEvent->detail == 31){
				dahlia_editor_engine_event_keyboard_i_state = 1;
			}else if(keyPressEvent->detail == 44){
				dahlia_editor_engine_event_keyboard_j_state = 1;
			}else if(keyPressEvent->detail == 45){
				dahlia_editor_engine_event_keyboard_k_state = 1;
			}else if(keyPressEvent->detail == 46){
				dahlia_editor_engine_event_keyboard_l_state = 1;
			}else if(keyPressEvent->detail == 58){
				dahlia_editor_engine_event_keyboard_m_state = 1;
			}else if(keyPressEvent->detail == 57){
				dahlia_editor_engine_event_keyboard_n_state = 1;
			}else if(keyPressEvent->detail == 32){
				dahlia_editor_engine_event_keyboard_o_state = 1;
			}else if(keyPressEvent->detail == 33){
				dahlia_editor_engine_event_keyboard_p_state = 1;
			}else if(keyPressEvent->detail == 24){
				dahlia_editor_engine_event_keyboard_q_state = 1;
			}else if(keyPressEvent->detail == 27){
				dahlia_editor_engine_event_keyboard_r_state = 1;
			}else if(keyPressEvent->detail == 39){
				dahlia_editor_engine_event_keyboard_s_state = 1;
			}else if(keyPressEvent->detail == 28){
				dahlia_editor_engine_event_keyboard_t_state = 1;
			}else if(keyPressEvent->detail == 30){
				dahlia_editor_engine_event_keyboard_u_state = 1;
			}else if(keyPressEvent->detail == 55){
				dahlia_editor_engine_event_keyboard_v_state = 1;
			}else if(keyPressEvent->detail == 25){
				dahlia_editor_engine_event_keyboard_w_state = 1;
			}else if(keyPressEvent->detail == 53){
				dahlia_editor_engine_event_keyboard_x_state = 1;
			}else if(keyPressEvent->detail == 29){
				dahlia_editor_engine_event_keyboard_y_state = 1;
			}else if(keyPressEvent->detail == 52){
				dahlia_editor_engine_event_keyboard_z_state = 1;
			}else if(keyPressEvent->detail == 100){
				dahlia_editor_engine_event_keyboard_leftarrow_state = 1;
			}else if(keyPressEvent->detail == 102){
				dahlia_editor_engine_event_keyboard_rightarrow_state = 1;
			}



		}else if(dahlia_editor_engine_event->response_type == XCB_KEY_RELEASE){
			xcb_key_release_event_t * keyReleaseEvent = (xcb_key_release_event_t*)dahlia_editor_engine_event;
			if(keyReleaseEvent->detail == 38){
				dahlia_editor_engine_event_keyboard_a_state = 2;
			}else if(keyReleaseEvent->detail == 56){
				dahlia_editor_engine_event_keyboard_b_state = 2;
			}else if(keyReleaseEvent->detail == 54){
				dahlia_editor_engine_event_keyboard_c_state = 2;
			}else if(keyReleaseEvent->detail == 40){
				dahlia_editor_engine_event_keyboard_d_state = 2;
			}else if(keyReleaseEvent->detail == 26){
				dahlia_editor_engine_event_keyboard_e_state = 2;
			}else if(keyReleaseEvent->detail == 41){
				dahlia_editor_engine_event_keyboard_f_state = 2;
			}else if(keyReleaseEvent->detail == 42){
				dahlia_editor_engine_event_keyboard_g_state = 2;
			}else if(keyReleaseEvent->detail == 43){
				dahlia_editor_engine_event_keyboard_h_state = 2;
			}else if(keyReleaseEvent->detail == 31){
				dahlia_editor_engine_event_keyboard_i_state = 2;
			}else if(keyReleaseEvent->detail == 44){
				dahlia_editor_engine_event_keyboard_j_state = 2;
			}else if(keyReleaseEvent->detail == 45){
				dahlia_editor_engine_event_keyboard_k_state = 2;
			}else if(keyReleaseEvent->detail == 46){
				dahlia_editor_engine_event_keyboard_l_state = 2;
			}else if(keyReleaseEvent->detail == 58){
				dahlia_editor_engine_event_keyboard_m_state = 2;
			}else if(keyReleaseEvent->detail == 57){
				dahlia_editor_engine_event_keyboard_n_state = 2;
			}else if(keyReleaseEvent->detail == 32){
				dahlia_editor_engine_event_keyboard_o_state = 2;
			}else if(keyReleaseEvent->detail == 33){
				dahlia_editor_engine_event_keyboard_p_state = 2;
			}else if(keyReleaseEvent->detail == 24){
				dahlia_editor_engine_event_keyboard_q_state = 2;
			}else if(keyReleaseEvent->detail == 27){
				dahlia_editor_engine_event_keyboard_r_state = 2;
			}else if(keyReleaseEvent->detail == 39){
				dahlia_editor_engine_event_keyboard_s_state = 2;
			}else if(keyReleaseEvent->detail == 28){
				dahlia_editor_engine_event_keyboard_t_state = 2;
			}else if(keyReleaseEvent->detail == 30){
				dahlia_editor_engine_event_keyboard_u_state = 2;
			}else if(keyReleaseEvent->detail == 55){
				dahlia_editor_engine_event_keyboard_v_state = 2;
			}else if(keyReleaseEvent->detail == 25){
				dahlia_editor_engine_event_keyboard_w_state = 2;
			}else if(keyReleaseEvent->detail == 53){
				dahlia_editor_engine_event_keyboard_x_state = 2;
			}else if(keyReleaseEvent->detail == 29){
				dahlia_editor_engine_event_keyboard_y_state = 2;
			}else if(keyReleaseEvent->detail == 52){
				dahlia_editor_engine_event_keyboard_z_state = 2;
			}else if(keyReleaseEvent->detail == 100){
				dahlia_editor_engine_event_keyboard_leftarrow_state = 2;
			}else if(keyReleaseEvent->detail == 102){
				dahlia_editor_engine_event_keyboard_rightarrow_state = 2;
			}

			//printf("KEY RELEASE\n");
		}else if(dahlia_editor_engine_event->response_type == XCB_MOTION_NOTIFY){
			 xcb_motion_notify_event_t * mouseMoveEvent = (xcb_motion_notify_event_t*)dahlia_editor_engine_event;
			//printf("%i   %i     ,    %i     %i\n", mouseMoveEvent->root_x, mouseMoveEvent->root_y, mouseMoveEvent->event_x, mouseMoveEvent->event_y);
			//Event XY is window coordinates.
			dahlia_editor_engine_event_mouse_x = mouseMoveEvent->event_x;
			dahlia_editor_engine_event_mouse_y = mouseMoveEvent->event_y;
		
		}else if(dahlia_editor_engine_event->response_type == XCB_BUTTON_PRESS){
			printf("button press\n");
			xcb_button_press_event_t* mouseDownEvent = (xcb_button_press_event_t*)dahlia_editor_engine_event;
			//printf("event:%d\n", mouseDownEvent->detail);
			if(mouseDownEvent->detail == 1){ dahlia_editor_engine_event_mouse_leftbutton_down = 1; }else
			if(mouseDownEvent->detail == 3){ dahlia_editor_engine_event_mouse_rightbutton_down = 1;}
			
		}else if(dahlia_editor_engine_event->response_type == XCB_BUTTON_RELEASE){
			printf("button release\n");
			xcb_button_release_event_t* mouseUpEvent = (xcb_button_release_event_t*)dahlia_editor_engine_event;
			//printf("event:%d\n", mouseUpEvent->detail);
			if(mouseUpEvent->detail == 1){ dahlia_editor_engine_event_mouse_leftbutton_down = 0; }else
			if(mouseUpEvent->detail == 3){ dahlia_editor_engine_event_mouse_rightbutton_down = 0; }

		}else if(dahlia_editor_engine_event->response_type == XCB_EXPOSE){
			//printf("expose\n");
		}

		//Free Event.
		free(dahlia_editor_engine_event);
	}
}

void dahlia_engine_xcb_events_reset_released_states(){
	if(dahlia_editor_engine_event_keyboard_a_state == 2){
		dahlia_editor_engine_event_keyboard_a_state = 0;
	}

	if(dahlia_editor_engine_event_keyboard_b_state == 2){
		dahlia_editor_engine_event_keyboard_b_state = 0;
	}

	if(dahlia_editor_engine_event_keyboard_c_state == 2){
		dahlia_editor_engine_event_keyboard_c_state = 0;
	}

	if(dahlia_editor_engine_event_keyboard_d_state == 2){
		dahlia_editor_engine_event_keyboard_d_state = 0;
	}

	if(dahlia_editor_engine_event_keyboard_e_state == 2){
		dahlia_editor_engine_event_keyboard_e_state = 0;
	}

	if(dahlia_editor_engine_event_keyboard_f_state == 2){
		dahlia_editor_engine_event_keyboard_f_state = 0;
	}

	if(dahlia_editor_engine_event_keyboard_g_state == 2){
		dahlia_editor_engine_event_keyboard_g_state = 0;
	}

	if(dahlia_editor_engine_event_keyboard_h_state == 2){
		dahlia_editor_engine_event_keyboard_h_state = 0;
	}

	if(dahlia_editor_engine_event_keyboard_i_state == 2){
		dahlia_editor_engine_event_keyboard_i_state = 0;
	}

	if(dahlia_editor_engine_event_keyboard_j_state == 2){
		dahlia_editor_engine_event_keyboard_j_state = 0;
	}

	if(dahlia_editor_engine_event_keyboard_k_state == 2){
		dahlia_editor_engine_event_keyboard_k_state = 0;
	}
	
	if(dahlia_editor_engine_event_keyboard_l_state == 2){
		dahlia_editor_engine_event_keyboard_l_state = 0;
	}

	if(dahlia_editor_engine_event_keyboard_m_state == 2){
		dahlia_editor_engine_event_keyboard_m_state = 0;
	}

	if(dahlia_editor_engine_event_keyboard_n_state == 2){
		dahlia_editor_engine_event_keyboard_n_state = 0;
	}

	if(dahlia_editor_engine_event_keyboard_o_state == 2){
		dahlia_editor_engine_event_keyboard_o_state = 0;
	}

	if(dahlia_editor_engine_event_keyboard_p_state == 2){
		dahlia_editor_engine_event_keyboard_p_state = 0;
	}

	if(dahlia_editor_engine_event_keyboard_q_state == 2){
		dahlia_editor_engine_event_keyboard_q_state = 0;
	}

	if(dahlia_editor_engine_event_keyboard_r_state == 2){
		dahlia_editor_engine_event_keyboard_r_state = 0;
	}

	if(dahlia_editor_engine_event_keyboard_s_state == 2){
		dahlia_editor_engine_event_keyboard_s_state = 0;
	}

	if(dahlia_editor_engine_event_keyboard_t_state == 2){
		dahlia_editor_engine_event_keyboard_t_state = 0;
	}

	if(dahlia_editor_engine_event_keyboard_u_state == 2){
		dahlia_editor_engine_event_keyboard_u_state = 0;
	}

	if(dahlia_editor_engine_event_keyboard_v_state == 2){
		dahlia_editor_engine_event_keyboard_v_state = 0;
	}

	if(dahlia_editor_engine_event_keyboard_w_state == 2){
		dahlia_editor_engine_event_keyboard_w_state = 0;
	}

	if(dahlia_editor_engine_event_keyboard_x_state == 2){
		dahlia_editor_engine_event_keyboard_x_state = 0;
	}

	if(dahlia_editor_engine_event_keyboard_y_state == 2){
		dahlia_editor_engine_event_keyboard_y_state = 0;
	}

	if(dahlia_editor_engine_event_keyboard_z_state == 2){
		dahlia_editor_engine_event_keyboard_z_state = 0;
	}

	if(dahlia_editor_engine_event_keyboard_leftarrow_state == 2){
		dahlia_editor_engine_event_keyboard_leftarrow_state = 0;
	}

	if(dahlia_editor_engine_event_keyboard_rightarrow_state == 2){
		dahlia_editor_engine_event_keyboard_rightarrow_state = 0;
	}
}

