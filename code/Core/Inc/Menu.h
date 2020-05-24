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

void setToEncdrSW(void);

void startingScreen(void);

void pourJuiceScreen(void);

void pourWaterScreen(void);

void mixScreen(void);

void mixScreen2(void);

void setFillPercentageScreen(void);

void makeingMixScreen(void);

void setConcentrationScreen(void);

void movedCupErrorScreen(void);

void emptyTankScreen(void);

void programistScreen(void);

void settingsScreen(void);

uint8_t get_activeMenu();

uint8_t get_activeListItem();

void motivesScreen(void);

void errorControl(void);

void returnToStartingScreen(void);

void menu_display(void);

uint16_t getConcentration_percentage();

uint16_t getFill_percentage();

#endif /* INC_MENU_H_ */
