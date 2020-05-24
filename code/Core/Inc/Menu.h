/*
 * Menu.h
 *
 *  Created on: 12 maj 2020
 *      Author: kamil
 */

#ifndef INC_MENU_H_
#define INC_MENU_H_





//////////////////////////////////////////////////////////////////////////////////////////////
void encoder(void);

void setToEncdrSW();

void startingScreen();

void pourJuiceScreen();

void pourWaterScreen();

void mixScreen(void);

void setCupFillScreen(void);

void movedCupErrorScreen(void);

void emptyTankScreen(void);

void programistScreen(void);

uint8_t get_activeMenu();

uint8_t get_activeListItem();

void menu_display();

#endif /* INC_MENU_H_ */
