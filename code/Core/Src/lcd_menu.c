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
  menu_t menu2_1 = { "..", &menu2_2, NULL, NULL, &menu2, menu_back };
  menu_t menu2_2 = { "Proporcje", NULL, &menu2_1, NULL, &menu2, NULL }; // TODO
menu_t menu3 = { "Debug", NULL, &menu2, NULL, NULL, NULL }; // TODO

menu_t *currentPointer = &menu1;

void menu_init(uint8_t padding, uint8_t fontSize) {
  LCD_SCAN_DIR Lcd_ScanDir = SCAN_DIR_DFT;
  LCD_Init( Lcd_ScanDir );

  menu_item_padding = padding;
  menu_item_height = fontSize;

  menu_rows = LCD_HEIGHT / (menu_item_padding + menu_item_height);

  LCD_Clear(BLACK);
  menu_refresh();
}

void menu_update(void) {

  encoder_position_current = __HAL_TIM_GET_COUNTER(&htim1) / 2;

  if(encoder_position_current == 0 && encoder_position_previous == 19)
    menu_prev();
  else if(encoder_position_current == 19 && encoder_position_previous == 0)
    menu_next();
  else if(encoder_position_current > encoder_position_previous)
    menu_prev();
  else if(encoder_position_current < encoder_position_previous)
    menu_next();

  encoder_position_previous = encoder_position_current;
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

  LCD_SetArealColor(0, 0, 15, LCD_HEIGHT, BLACK);
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
