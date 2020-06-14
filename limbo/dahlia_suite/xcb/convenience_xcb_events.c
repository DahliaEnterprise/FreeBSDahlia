void convenience_xcb_events_initialize(){
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
	xcb_xcb_timestamp_last_frame_rendered = 0;
}

void convenience_xcb_events_poll(){
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

void convenience_xcb_events_reset_released_states(){
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

