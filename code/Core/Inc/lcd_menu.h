/*
 * lcd_menu.h
 *
 *  Created on: Jun 6, 2020
 *      Author: tymon
 */

#ifndef INC_LCD_MENU_H_
#define INC_LCD_MENU_H_

#endif /* INC_LCD_MENU_H_ */


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
menu_t menu3;

uint8_t menu_index;
uint8_t lcd_row_pos;
uint8_t lcd_row_pos_level_1, lcd_row_pos_level_2;

uint8_t menu_item_padding;
uint8_t menu_item_height;
uint8_t menu_rows;

uint8_t encoder_position_previous;
uint8_t encoder_position_current;

void menu_init(uint8_t padding, uint8_t fontSize);
void menu_update(void);
void menu_next(void);
void menu_prev(void);
void menu_enter(void);
void menu_back(void);
void menu_refresh(void);
uint8_t menu_get_index(menu_t *q);
uint8_t menu_get_level(menu_t *q);



