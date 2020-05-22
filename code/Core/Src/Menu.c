/*
 * Menu.c
 *
 *  Created on: 12 maj 2020
 *      Author: kamil
 */


#include "ST7735S_dev_config.h"
#include "ST7735S.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "main.h"


volatile uint8_t activeMenu = 0;
volatile uint8_t activeListItem = 0;

// Encoder
volatile uint16_t pulse_count; // impulse counter
volatile uint16_t encoder_position; // position counter licznik przekreconych pozycji
volatile uint8_t ToEncdrSW;

void encoder(){
    pulse_count = TIM1->CNT; // przepisanie wartosci z rejestru timera
    encoder_position = pulse_count/2; // zeskalowanie impulsow do liczby stabilnych pozycji walu enkodera
}

void setToEncdrSW(){
	 ToEncdrSW=1;
}

/**
 * starting menu
 * open when activeMenu==0
 */
void startingScreen(){

	if(encoder_position<=20){
	LCD_DisplayString(10,20,"Pour juice",&Font12,LCD_BACKGROUND,RED);
	LCD_DisplayString(10,40,"Pour water",&Font12,LCD_BACKGROUND,BLUE);
	LCD_DisplayString(10,60,"Mix",&Font12,LCD_BACKGROUND,BLUE);
	LCD_DisplayString(10,80,"Settings",&Font12,LCD_BACKGROUND,BLUE);
	LCD_DisplayString(10,100,"Programist",&Font12,LCD_BACKGROUND,BLUE);
	if(ToEncdrSW==1){
		ToEncdrSW=0;
		LCD_Clear(WHITE);
		activeMenu=1;
	}
	}else if(encoder_position>20 && encoder_position<=40){
		LCD_DisplayString(10,20,"Pour juice",&Font12,LCD_BACKGROUND,BLUE);
		LCD_DisplayString(10,40,"Pour water",&Font12,LCD_BACKGROUND,RED);
		LCD_DisplayString(10,60,"Mix",&Font12,LCD_BACKGROUND,BLUE);
		LCD_DisplayString(10,80,"Settings",&Font12,LCD_BACKGROUND,BLUE);
		LCD_DisplayString(10,100,"Programist",&Font12,LCD_BACKGROUND,BLUE);
		if(ToEncdrSW==1){
						ToEncdrSW=0;
						LCD_Clear(WHITE);
						activeMenu=2;
			}

		}else if(encoder_position>40 && encoder_position<=60){

	LCD_DisplayString(10,20,"Pour juice",&Font12,LCD_BACKGROUND,BLUE);
	LCD_DisplayString(10,40,"Pour water",&Font12,LCD_BACKGROUND,BLUE);
	LCD_DisplayString(10,60,"Mix",&Font12,LCD_BACKGROUND,RED);
	LCD_DisplayString(10,80,"Settings",&Font12,LCD_BACKGROUND,BLUE);
	LCD_DisplayString(10,100,"Programist",&Font12,LCD_BACKGROUND,BLUE);
	if(ToEncdrSW==1){
		ToEncdrSW=0;
		LCD_Clear(WHITE);
		activeMenu=3;
		}

		}else if(encoder_position>60 && encoder_position<=80){
	LCD_DisplayString(10,20,"Pour juice",&Font12,LCD_BACKGROUND,BLUE);
	LCD_DisplayString(10,40,"Pour water",&Font12,LCD_BACKGROUND,BLUE);
	LCD_DisplayString(10,60,"Mix",&Font12,LCD_BACKGROUND,BLUE);
	LCD_DisplayString(10,80,"Settings",&Font12,LCD_BACKGROUND,RED);
	LCD_DisplayString(10,100,"Programist",&Font12,LCD_BACKGROUND,BLUE);
	if(ToEncdrSW==1){
		ToEncdrSW=0;
					LCD_Clear(WHITE);
					activeMenu=4;
		}

		}else if(encoder_position>80){
	LCD_DisplayString(10,20,"Pour juice",&Font12,LCD_BACKGROUND,BLUE);
	LCD_DisplayString(10,40,"Pour water",&Font12,LCD_BACKGROUND,BLUE);
	LCD_DisplayString(10,60,"Mix",&Font12,LCD_BACKGROUND,BLUE);
	LCD_DisplayString(10,80,"Settings",&Font12,LCD_BACKGROUND,BLUE);
	LCD_DisplayString(10,100,"Programist",&Font12,LCD_BACKGROUND,RED);
	if(ToEncdrSW==1){
			ToEncdrSW=0;
			LCD_Clear(WHITE);
			activeMenu=5;
		}
}
}

/**
 * pouring juice screen
 * open when activeMenu==1
 */
void pourJuiceScreen(){
	LCD_DisplayString(10,20,"POURING JUICE",&Font12,LCD_BACKGROUND,BLUE);
	LCD_DisplayString(10,40,"PRESS BUTTON",&Font12,LCD_BACKGROUND,BLUE);
	LCD_DisplayString(10,60,"TO STOP",&Font12,LCD_BACKGROUND,BLUE);
	if(ToEncdrSW==1){
			LCD_Clear(WHITE);
			activeMenu=0;
			ToEncdrSW=0;
		}

}

void pourWaterScreen(){
	LCD_DisplayString(10,20,"POURING WATER",&Font12,LCD_BACKGROUND,BLUE);
	LCD_DisplayString(10,40,"PRESS BUTTON",&Font12,LCD_BACKGROUND,BLUE);
	LCD_DisplayString(10,60,"TO STOP",&Font12,LCD_BACKGROUND,BLUE);
	if(ToEncdrSW==1){
			LCD_Clear(WHITE);
			activeMenu=0;
			ToEncdrSW=0;
		}

}

void setConcentrationScreen(){
	LCD_DisplayString(10,20,"Set concentration",&Font8,LCD_BACKGROUND,BLUE);
	LCD_DrawRectangle(0,40,sLCD_DIS.LCD_Dis_Column/2,60,BLUE, DRAW_FULL, DOT_PIXEL_1X1);
	LCD_DrawRectangle(0,40,sLCD_DIS.LCD_Dis_Column,60,BLUE, DRAW_EMPTY, DOT_PIXEL_1X1);
	LCD_DisplayString(10,80,"50%",&Font12,LCD_BACKGROUND,BLUE);
}

void setCupFillScreen(){
	LCD_DisplayString(10,20,"Set fill percentage",&Font8,LCD_BACKGROUND,BLUE);
	LCD_DrawRectangle(0,40,sLCD_DIS.LCD_Dis_Column/5,60,BLUE, DRAW_FULL, DOT_PIXEL_1X1);
	LCD_DrawRectangle(0,40,sLCD_DIS.LCD_Dis_Column,60,BLUE, DRAW_EMPTY, DOT_PIXEL_1X1);
	LCD_DisplayString(10,80,"20%",&Font12,LCD_BACKGROUND,BLUE);
}

void movedCupErrorScreen(){
	LCD_DisplayString(10,20,"THERE IS",&Font16,LCD_BACKGROUND,RED);
	LCD_DisplayString(10,35,"NO CUP",&Font16,LCD_BACKGROUND,RED);
}

void emptyTankScreen(){
	LCD_DisplayString(10,20,"THERE IS",&Font16,LCD_BACKGROUND,RED);
	LCD_DisplayString(10,40,"NO LIQUID ",&Font16,LCD_BACKGROUND,RED);
}

void programistScreen(){
		LCD_DisplayString(10,20,"servo 70",&Font12,LCD_BACKGROUND,BLUE);
		LCD_DisplayString(10,40,"cup distance 14",&Font12,LCD_BACKGROUND,BLUE);
		LCD_DisplayString(10,60,"engine 1 true",&Font12,LCD_BACKGROUND,BLUE);
		LCD_DisplayString(10,80,"engine 2 false",&Font12,LCD_BACKGROUND,BLUE);
	}

uint8_t get_activeMenu(){
	return activeMenu;
}

uint8_t get_activeListItem(){
	return activeListItem;
}
