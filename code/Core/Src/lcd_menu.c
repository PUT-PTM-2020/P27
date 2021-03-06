/*
 * lcd.menu.c
 *
 *  Created on: Jun 6, 2020
 *      Author: tymon
 */

#include "lcd_menu.h"

// definition of menu's components: (*name, *next, *prev, *child, *parent, (*menu_function))
menu_t menu1 = { "Nalewanie", &menu2, &menu3, NULL, NULL, menu_screen_pour };
menu_t menu2 = { "Opcje", &menu3, &menu1, &menu2_1, NULL, NULL };
  menu_t menu2_1 = { "..", &menu2_2, &menu2_2, NULL, &menu2, menu_back };
  menu_t menu2_2 = { "Proporcje", NULL, &menu2_1, &menu2_2_1, &menu2, menu_screen_proportion };
    menu_t menu2_2_1 = { "..", &menu2_2_2, &menu2_2_3, NULL, &menu2_2, menu_back };
    menu_t menu2_2_2 = { "Ciecz 1", &menu2_2_3, &menu2_2_1, NULL, &menu2_2, menu_set_liquid_1 };
    menu_t menu2_2_3 = { "Ciecz 2", NULL, &menu2_2_2, NULL, &menu2_2, menu_set_liquid_2 };
menu_t menu3 = { "Debug", NULL, &menu2, &menu3_1, NULL, menu_screen_debug };
  menu_t menu3_1 = { "..", &menu3_2, &menu3_5, NULL, &menu3, menu_back };
  menu_t menu3_2 = { "Pompa 1", &menu3_3, &menu3_1, NULL, &menu3, menu_toggle_pump_1 };
  menu_t menu3_3 = { "Pompa 2", &menu3_4, &menu3_2, NULL, &menu3, menu_toggle_pump_2 };
  menu_t menu3_4 = { "Serwo", &menu3_5, &menu3_3, NULL, &menu3, menu_set_servo };
  menu_t menu3_5 = { "Czujnik", NULL, &menu3_4, NULL, &menu3, menu_get_distance };

menu_t *currentPointer = &menu1;
uint8_t *currentLiquid = NULL;

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

  LCD_Clear(BLACK);
  menu_state = MENU_STATE_OK;
  menu_refresh();
}

void menu_display_error(const char * error_message) {
  menu_state = MENU_STATE_ERROR;
  LCD_Clear(BLACK);
  LCD_DisplayString( 5, (lcd_height - menu_item_height) / 2, error_message, & Font12, BLACK, RED);
  LCD_DisplayString( lcd_width / 2 - Font12.Width * 2, lcd_height - menu_item_height - menu_item_padding, "> OK", & Font12, BLACK, WHITE);
}

void menu_display_measurement(void) {
  char min_distance_string[5];
  sprintf(min_distance_string, "%dmm", min_distance);

  LCD_DisplayString( 5, (lcd_height - menu_item_height) / 2, "Pomiar...", & Font12, BLACK, WHITE);
  LCD_DisplayString( lcd_width / 2 - Font12.Width * 2, lcd_height - menu_item_height - menu_item_padding, min_distance_string, & Font12, BLACK, WHITE);
}

void menu_display_confirm_measurement(void) {
  char max_pouring_height_string[6];
  sprintf(max_pouring_height_string, "%dmm", max_pouring_height);

  LCD_DisplayString( 5, (lcd_height - menu_item_height) / 2, "Nalewac?", & Font12, BLACK, WHITE);
  LCD_DisplayString( lcd_width / 2 - Font12.Width * 2, lcd_height - (menu_item_height + menu_item_padding) * 3, max_pouring_height_string, & Font12, BLACK, WHITE);
  LCD_DisplayString( lcd_width / 2 - Font12.Width * 2, lcd_height - (menu_item_height + menu_item_padding) * 2, "TAK >", & Font12, BLACK, WHITE);
  LCD_DisplayString( lcd_width / 2 - Font12.Width * 2, lcd_height - menu_item_height - menu_item_padding, "< NIE", & Font12, BLACK, WHITE);
}

void menu_display_pouring(void) {
  char text[13];

  LCD_DisplayString( 5, (lcd_height - menu_item_height) / 2, "Nalewanie", & Font12, BLACK, WHITE);

  sprintf(text, "Ciecz %d", pumps_is_on(1) ? 1 : 2);
  LCD_DisplayString( 5, (lcd_height - menu_item_height) / 2 +  menu_item_height + menu_item_padding, text, & Font12, BLACK, WHITE);

  sprintf(text, "Pomiar %dmm  ", average_distance);
  LCD_DisplayString( 5, (lcd_height - menu_item_height) / 2 + (menu_item_height + menu_item_padding) * 2, text, & Font12, BLACK, WHITE);

  LCD_DisplayString( lcd_width / 2 - Font12.Width * 2, lcd_height - menu_item_height - menu_item_padding, "> STOP", & Font12, BLACK, WHITE);
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

void menu_screen_pour(void) {
  init_cup_height_measurement();
}

void menu_screen_proportion(void) {
  menu_enter();
  menu_update_proportion();
}

void menu_update_proportion(void) {
  uint8_t position_x = lcd_width - 4 * Font12.Width;
  char percent[4];

  sprintf(percent, "%d%%", liquid1);
  LCD_DisplayString(
      position_x,
      menu_item_padding * 2 + menu_item_height,
      percent,
      & Font12, BLACK, WHITE);

  sprintf(percent, "%d%%", liquid2);
  LCD_DisplayString(
      position_x,
      menu_item_padding * 3 + menu_item_height * 2,
      percent,
      & Font12, BLACK, WHITE);
}

void menu_set_liquid_1(void) {
  menu_state = MENU_STATE_LIQUIDS;
  currentLiquid = &liquid1;
}

void menu_set_servo(void) {
  menu_state = MENU_STATE_SERVO;
}

void menu_get_distance(void) {
  menu_update_debug();
}

void menu_set_liquid_2(void) {
  menu_state = MENU_STATE_LIQUIDS;
  currentLiquid = &liquid2;
}

void menu_screen_debug(void) {
  menu_state = MENU_STATE_DEBUG;
  menu_enter();
  menu_update_debug();
}

void menu_update_debug(void) {
  uint8_t position_x = lcd_width - 4 * Font12.Width;
  char percent[6];

  LCD_DisplayString(
      position_x,
      menu_item_padding * 2 + menu_item_height,
      pumps_is_on(1) ? "ON " : "OFF",
      & Font12, BLACK, WHITE);

  LCD_DisplayString(
      position_x,
      menu_item_padding * 3 + menu_item_height * 2,
      pumps_is_on(2) ? "ON " : "OFF",
      & Font12, BLACK, WHITE);

  sprintf(percent, "%d*  ", current_servo_angle / 10);
  LCD_DisplayString(
      position_x,
      menu_item_padding * 4 + menu_item_height * 3,
      percent,
      & Font12, BLACK, WHITE);

  sprintf(percent, "%d   ", distance_milimeters);
  LCD_DisplayString(
      position_x,
      menu_item_padding * 5 + menu_item_height * 4,
      percent,
      & Font12, BLACK, WHITE);
}

void menu_toggle_pump_1(void) {
  pumps_toggle(1);
  menu_update_debug();
}

void menu_toggle_pump_2(void) {
  pumps_toggle(2);
  menu_update_debug();
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

  if(menu_state == MENU_STATE_OK || menu_state == MENU_STATE_DEBUG) {
    if(currentPointer->menu_function)
      currentPointer->menu_function();
    else menu_enter();
  }

  else if(menu_state == MENU_STATE_POURING) {
    stop_pouring();
  }

  else if(menu_state == MENU_STATE_ERROR) {
    menu_go_home();
  }

  else if(menu_state == MENU_STATE_LIQUIDS) {
    menu_state = MENU_STATE_OK;
    currentLiquid = NULL;
  }

  else if(menu_state == MENU_STATE_SERVO) {
    menu_state = MENU_STATE_DEBUG;
    servo_set_angle(0, 0);
  }
}

void encoder_handle_rotate(void) {
  if(encoder_direction == ENCODER_STOP)
    return;

  if(menu_state == MENU_STATE_OK || menu_state == MENU_STATE_DEBUG) {
    if(encoder_direction == ENCODER_LEFT)
      menu_prev();
    else if(encoder_direction == ENCODER_RIGHT)
      menu_next();
  }

  else if(menu_state == MENU_STATE_CONFIRM_MEASUREMENT) {
    if(encoder_direction == ENCODER_LEFT)
      stop_pouring();
    else if(encoder_direction == ENCODER_RIGHT)
      init_pouring();
  }

  else if(menu_state == MENU_STATE_LIQUIDS) {
    if(encoder_direction == ENCODER_LEFT)
      liquid_add_percent(currentLiquid, -1);
    else if(encoder_direction == ENCODER_RIGHT)
      liquid_add_percent(currentLiquid, 1);
    menu_update_proportion();
  }

  else if(menu_state == MENU_STATE_SERVO) {
    if(encoder_direction == ENCODER_LEFT)
      servo_set_angle(current_servo_angle == 0 ? current_servo_angle : current_servo_angle - 10, 0);
    else if(encoder_direction == ENCODER_RIGHT)
      servo_set_angle(current_servo_angle == 900 ? current_servo_angle : current_servo_angle + 10, 0);
    menu_update_debug();
  }
}
