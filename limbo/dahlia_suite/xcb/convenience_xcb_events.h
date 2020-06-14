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
uint64_t xcb_xcb_timestamp_last_frame_rendered;

//XCB Event Handle
xcb_generic_event_t * xcb_event;

//Header, Functions
void convenience_xcb_events_initialize();
void convenience_xcb_events_poll();
void convenience_xcb_events_reset_released_states();

