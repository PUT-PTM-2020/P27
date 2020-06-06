/*
 * lcd_menu.h
 *
 *  Created on: Jun 6, 2020
 *      Author: tymon
 */

#ifndef INC_LCD_MENU_H_
#define INC_LCD_MENU_H_

#endif /* INC_LCD_MENU_H_ */

#include "tim.h"
#include <shared.h>
#include "pumps.h"
#include "ST7735S_dev_config.h"
#include <stdio.h>

typedef enum {
  MENU_STATE_OK,
  MENU_STATE_ERROR,
  MENU_STATE_LIQUIDS
} MENU_STATE;

typedef enum { ENCODER_LEFT, ENCODER_STOP, ENCODER_RIGHT } ENCODER_DIRECTION;

MENU_STATE menu_state;
ENCODER_DIRECTION encoder_direction;

typedef struct menu_struct menu_t;

struct menu_struct {

  const char * name;
  menu_t * next;
  menu_t * prev;
  menu_t * child;
  menu_t * parent;
  void (*menu_function)(void);

};

menu_t menu1;
menu_t menu2;
  menu_t menu2_1;
  menu_t menu2_2;
    menu_t menu2_2_1;
    menu_t menu2_2_2;
    menu_t menu2_2_3;
menu_t menu3;
  menu_t menu3_1;
  menu_t menu3_2;
  menu_t menu3_3;

uint8_t menu_index;
uint8_t lcd_row_pos;
uint8_t lcd_row_pos_level_1, lcd_row_pos_level_2;

uint8_t menu_item_padding;
uint8_t menu_item_height;
uint8_t menu_rows;

uint8_t lcd_height;
uint8_t lcd_width;

uint8_t encoder_position_previous;
uint8_t encoder_position_current;

void menu_init(uint8_t padding, uint8_t fontSize);
void menu_update(void);
void menu_go_home(void);
void menu_display_error(const char * error_message);
void menu_next(void);
void menu_prev(void);
void menu_enter(void);
void menu_back(void);
void menu_refresh(void);
uint8_t menu_get_index(menu_t *q);
uint8_t menu_get_level(menu_t *q);



void menu_screen_proportion(void);
void menu_update_proportion(void);
void menu_set_liquid_1(void);
void menu_set_liquid_2(void);

void menu_screen_debug(void);
void menu_update_debug(void);
void menu_toggle_pump_1(void);
void menu_toggle_pump_2(void);

void update_encoder_direction(void);
void encoder_handle_click(void);
void encoder_handle_rotate(void);



