#include "tusb.h"

#include "actions.h"
#include "keys.h"

/*
Functions which are used as handlers inside the key_action_map, called during a key press.
*/
void action_none(void){}

//LAYER5
void action_volume_up(void)        { macro_key_press(HID_KEY_NONE, HID_KEY_F8); }
void action_volume_down(void)      { macro_key_press(HID_KEY_NONE, HID_KEY_F7); }
void action_mute(void)             { macro_key_press(HID_KEY_NONE, HID_KEY_F6); }
void action_play_pause(void)       { macro_key_press(HID_KEY_NONE, HID_KEY_F10); }
void action_brightness_up(void)    { macro_key_press(HID_KEY_NONE, HID_KEY_F3); }
void action_brightness_down(void)  { macro_key_press(HID_KEY_NONE, HID_KEY_F2); }

//LAYER4
void action_open_taskmanager(void) { macro_key_press(KEYBOARD_MODIFIER_LEFTCTRL | KEYBOARD_MODIFIER_LEFTSHIFT, HID_KEY_ESCAPE); }
void action_window_close(void)     { macro_key_press(KEYBOARD_MODIFIER_LEFTALT, HID_KEY_F4); }
void action_refresh(void)          { macro_key_press(KEYBOARD_MODIFIER_LEFTCTRL, HID_KEY_R); }
void action_find(void)             { macro_key_press(KEYBOARD_MODIFIER_LEFTCTRL, HID_KEY_F); }
void action_desktop_show(void)     { macro_key_press(KEYBOARD_MODIFIER_LEFTGUI, HID_KEY_D); }  
void action_lock_computer(void)    { macro_key_press(KEYBOARD_MODIFIER_LEFTGUI, HID_KEY_L); }  

//LAYER3
void action_zoom_in(void)  { macro_key_press(KEYBOARD_MODIFIER_LEFTCTRL, HID_KEY_EQUAL); }
void action_zoom_out(void) { macro_key_press(KEYBOARD_MODIFIER_LEFTCTRL, HID_KEY_MINUS); }
void action_save(void)     { macro_key_press(KEYBOARD_MODIFIER_LEFTCTRL, HID_KEY_S); }
void action_open(void)     { macro_key_press(KEYBOARD_MODIFIER_LEFTCTRL, HID_KEY_O); }
void action_tab_open(void) { macro_key_press(KEYBOARD_MODIFIER_LEFTCTRL, HID_KEY_T); }
void action_tab_close(void){ macro_key_press(KEYBOARD_MODIFIER_LEFTCTRL, HID_KEY_W); }

//LAYER2
void action_open_chatgpt(void)      { macro_type_url("https://chatgpt.com"); }
void action_open_youtube(void)      { macro_type_url("https://youtube.com"); }
void action_open_discord(void)      { macro_type_url("https://discord.com/channels/@me"); }
void action_open_google(void)       { macro_type_url("https://google.com"); }
void action_open_github(void)       { macro_type_url("https://github.com"); }
void action_open_google_drive(void) { macro_type_url("https://drive.google.com/drive/u/0/home"); }

//LAYER1
void action_undo(void)             { macro_key_press(KEYBOARD_MODIFIER_LEFTCTRL, HID_KEY_Z); }
void action_screenshot(void)       { macro_key_press(KEYBOARD_MODIFIER_LEFTGUI | KEYBOARD_MODIFIER_LEFTSHIFT, HID_KEY_S); }
void action_cut(void)              { macro_key_press(KEYBOARD_MODIFIER_LEFTCTRL, HID_KEY_X); }
void action_select(void)           { macro_key_press(KEYBOARD_MODIFIER_LEFTCTRL, HID_KEY_A); }
void action_copy(void)             { macro_key_press(KEYBOARD_MODIFIER_LEFTCTRL, HID_KEY_C); }
void action_paste(void)            { macro_key_press(KEYBOARD_MODIFIER_LEFTCTRL, HID_KEY_V); }