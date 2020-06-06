/*
 * lcd.menu.c
 *
 *  Created on: Jun 6, 2020
 *      Author: tymon
 */

#include "tim.h"
#include "ST7735S_dev_config.h"
#include "lcd_menu.h"

// definition of menu's components: (*name, *next, *prev, *child, *parent, (*menu_function))
menu_t menu1 = { "Nalewanie", &menu2, &menu3, NULL, NULL, NULL };
menu_t menu2 = { "Opcje", &menu3, &menu1, &menu2_1, NULL, NULL };
  menu_t menu2_1 = { "..", &menu2_2, &menu2_2, NULL, &menu2, menu_back };
  menu_t menu2_2 = { "Proporcje", NULL, &menu2_1, NULL, &menu2, NULL }; // TODO
menu_t menu3 = { "Debug", NULL, &menu2, NULL, NULL, NULL }; // TODO

menu_t *currentPointer = &menu1;

void menu_init(uint8_t padding, uint8_t fontSize) {
  LCD_SCAN_DIR Lcd_ScanDir = SCAN_DIR_DFT;
  LCD_Init( Lcd_ScanDir );

  menu_item_padding = padding;
  menu_item_height = fontSize;
  lcd_height = LCD_WIDTH;
  lcd_width = LCD_HEIGHT;

  menu_rows = lcd_height / (menu_item_padding + menu_item_height);

  menu_state = MENU_STATE_OK;

  LCD_Clear(BLACK);
  menu_refresh();
}

void menu_update(void) {
  update_encoder_direction();
  encoder_handle_rotate();
}

void menu_go_home(void) {
  menu_index = 0;
  lcd_row_pos = 0;
  currentPointer = &menu1;

  menu_state = MENU_STATE_OK;
  LCD_Clear(BLACK);
  menu_refresh();
}

void menu_show_error(const char * error_message) {
  menu_state = MENU_STATE_ERROR;
  LCD_Clear(BLACK);
  LCD_DisplayString( 5, (lcd_height - menu_item_height) / 2, error_message, & Font12, BLACK, RED);
  LCD_DisplayString( lcd_width / 2 - 14, lcd_height - menu_item_height - menu_item_padding, "> OK", & Font12, BLACK, WHITE);
}

void menu_next(void) {

  if (currentPointer->next)
  {
    currentPointer = currentPointer->next;
    menu_index++;
    if (++lcd_row_pos > menu_rows - 1)
      lcd_row_pos = menu_rows - 1;
  }
  else
  {
    menu_index = 0;
    lcd_row_pos = 0;

    if (currentPointer->parent)
      currentPointer = (currentPointer->parent)->child;
    else
      currentPointer = &menu1;
  }

  menu_refresh();

}

void menu_prev(void) {

  currentPointer = currentPointer->prev;

  if (menu_index)
  {
    menu_index--;

    if (lcd_row_pos > 0)
      lcd_row_pos--;
  }
  else
  {
    menu_index = menu_get_index(currentPointer);

    if (menu_index >= menu_rows - 1)
      lcd_row_pos = menu_rows - 1;
    else
      lcd_row_pos = menu_index;
  }

  menu_refresh();
}

void menu_enter(void) {

  if (currentPointer->menu_function) {
    currentPointer->menu_function();
    return;
  }

  if (currentPointer->child)
  {

    switch (menu_get_level(currentPointer)) {
      case 0:
        lcd_row_pos_level_1 = lcd_row_pos;
        break;

      case 1:
        lcd_row_pos_level_2 = lcd_row_pos;
        break;
    }

    menu_index = 0;
    lcd_row_pos = 0;

    currentPointer = currentPointer->child;

    LCD_Clear(BLACK);
    menu_refresh();
  }
}

void menu_back(void) {

  if (currentPointer->parent) {

    switch (menu_get_level(currentPointer)) {
      case 1:
        lcd_row_pos = lcd_row_pos_level_1;
        break;

      case 2:
        lcd_row_pos = lcd_row_pos_level_2;
        break;
      }

    currentPointer = currentPointer->parent;
    menu_index = menu_get_index(currentPointer);

    LCD_Clear(BLACK);
    menu_refresh();

  }
}

void menu_refresh(void) {

  menu_t *temp;
  uint8_t i;

  if (currentPointer->parent)
    temp = (currentPointer->parent)->child;
  else
    temp = &menu1;

  for (i = 0; i != menu_index - lcd_row_pos; i++) {
    temp = temp->next;
  }

  LCD_SetArealColor(0, 0, 15, lcd_height, BLACK);
  for (i = 0; i < menu_rows; i++) {
    LCD_DisplayString(
        15,
        (i + 1) * menu_item_padding + i * menu_item_height,
        temp->name,
        & Font12,
        BLACK,
        temp == currentPointer ? WHITE : LIGHTGRAY
            );

    if(temp == currentPointer)
      LCD_DisplayString( 5, (i + 1) * menu_item_padding + i * menu_item_height, ">", & Font12, BLACK, WHITE);

    temp = temp->next;
    if (!temp)
      break;
  }
}

uint8_t menu_get_level(menu_t *q) {

  menu_t *temp = q;
  uint8_t i = 0;

  if (!q->parent)
    return 0;

  while (temp->parent != NULL) {
    temp = temp->parent;
    i++;
  }

  return i;
}

uint8_t menu_get_index(menu_t *q) {

  menu_t *temp;
  uint8_t i = 0;

  if (q->parent)
    temp = (q->parent)->child;
  else
    temp = &menu1;

  while (temp != q) {
    temp = temp->next;
    i++;
  }

  return i;
}

void update_encoder_direction(void) {

  encoder_position_current = __HAL_TIM_GET_COUNTER(&htim1) / 2;

  encoder_direction = ENCODER_STOP;

  if(encoder_position_current == 0 && encoder_position_previous == 19)
    encoder_direction = ENCODER_LEFT;
  else if(encoder_position_current == 19 && encoder_position_previous == 0)
    encoder_direction = ENCODER_RIGHT;
  else if(encoder_position_current > encoder_position_previous)
    encoder_direction = ENCODER_LEFT;
  else if(encoder_position_current < encoder_position_previous)
    encoder_direction = ENCODER_RIGHT;

  encoder_position_previous = encoder_position_current;
}

void encoder_handle_click(void) {
  switch(menu_state) {
    case MENU_STATE_OK:
      menu_enter(); break;
    case MENU_STATE_ERROR:
      menu_go_home(); break;
  }
}

void encoder_handle_rotate(void) {
  if(encoder_direction == ENCODER_STOP)
    return;

  if(menu_state == MENU_STATE_OK) {
    if(encoder_direction == ENCODER_LEFT)
      menu_prev();
    if(encoder_direction == ENCODER_RIGHT)
      menu_next();
  }

}
