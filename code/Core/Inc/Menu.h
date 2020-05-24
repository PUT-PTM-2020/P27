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

void mixScreen2();

void setFillPercentageScreen();

void makeingMixScreen();

void setCupFillScreen(void);

void setConcentrationScreen();

void movedCupErrorScreen(void);

void emptyTankScreen(void);

void programistScreen(void);

void settingsScreen();

uint8_t get_activeMenu();

uint8_t get_activeListItem();

void motivesScreen();

void errorControl();

void returnToStartingScreen();

void menu_display();

#endif /* INC_MENU_H_ */
