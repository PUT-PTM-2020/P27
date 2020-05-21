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
//activeMenu
// activeListItem
/*void LCD_DisplayString (	POINT Xstart, POINT Ystart, const char * pString,
							sFONT* Font,COLOR Color_Background, COLOR Color_Foreground ) */
/*void LCD_DrawCircle ( 	POINT X_Center, POINT Y_Center, LENGTH Radius,
						COLOR Color,
						DRAW_FILL  Draw_Fill ,
						DOT_PIXEL Dot_Pixel )
LCD_DrawCircle( Cx1, Cy1, Cr, BLUE, DRAW_EMPTY, DOT_PIXEL_DFT);
*/
/**
 * starting menu
 * state 00
 */
void startingScreen(uint16_t encoder_position){

	if(encoder_position<=20){
	LCD_DisplayString(10,20,"Pour juice",&Font12,LCD_BACKGROUND,RED);
	LCD_DisplayString(10,40,"Pour water",&Font12,LCD_BACKGROUND,BLUE);
	LCD_DisplayString(10,60,"Mix",&Font12,LCD_BACKGROUND,BLUE);
	LCD_DisplayString(10,80,"Settings",&Font12,LCD_BACKGROUND,BLUE);
	LCD_DisplayString(10,100,"Programist",&Font12,LCD_BACKGROUND,BLUE);

	}else if(encoder_position>20 && encoder_position<=40){
		LCD_DisplayString(10,20,"Pour juice",&Font12,LCD_BACKGROUND,BLUE);
		LCD_DisplayString(10,40,"Pour water",&Font12,LCD_BACKGROUND,RED);
		LCD_DisplayString(10,60,"Mix",&Font12,LCD_BACKGROUND,BLUE);
		LCD_DisplayString(10,80,"Settings",&Font12,LCD_BACKGROUND,BLUE);
		LCD_DisplayString(10,100,"Programist",&Font12,LCD_BACKGROUND,BLUE);

		}else if(encoder_position>40 && encoder_position<=60){

	LCD_DisplayString(10,20,"Pour juice",&Font12,LCD_BACKGROUND,BLUE);
	LCD_DisplayString(10,40,"Pour water",&Font12,LCD_BACKGROUND,BLUE);
	LCD_DisplayString(10,60,"Mix",&Font12,LCD_BACKGROUND,RED);
	LCD_DisplayString(10,80,"Settings",&Font12,LCD_BACKGROUND,BLUE);
	LCD_DisplayString(10,100,"Programist",&Font12,LCD_BACKGROUND,BLUE);
		}else if(encoder_position>60 && encoder_position<=80){
	LCD_DisplayString(10,20,"Pour juice",&Font12,LCD_BACKGROUND,BLUE);
	LCD_DisplayString(10,40,"Pour water",&Font12,LCD_BACKGROUND,BLUE);
	LCD_DisplayString(10,60,"Mix",&Font12,LCD_BACKGROUND,BLUE);
	LCD_DisplayString(10,80,"Settings",&Font12,LCD_BACKGROUND,RED);
	LCD_DisplayString(10,100,"Programist",&Font12,LCD_BACKGROUND,BLUE);

		}else if(encoder_position>80){
	LCD_DisplayString(10,20,"Pour juice",&Font12,LCD_BACKGROUND,BLUE);
	LCD_DisplayString(10,40,"Pour water",&Font12,LCD_BACKGROUND,BLUE);
	LCD_DisplayString(10,60,"Mix",&Font12,LCD_BACKGROUND,BLUE);
	LCD_DisplayString(10,80,"Settings",&Font12,LCD_BACKGROUND,BLUE);
	LCD_DisplayString(10,100,"Programist",&Font12,LCD_BACKGROUND,RED);
}
}
//void LCD_DrawRectangle ( POINT Xstart, POINT Ystart, POINT Xend, POINT Yend, COLOR Color, DRAW_FILL Filled , DOT_PIXEL Dot_Pixel );
/**
 * set concentration screen
 * state 21
 */
void setConcentrationScreen(){
	LCD_DisplayString(10,20,"Set concentration",&Font8,LCD_BACKGROUND,BLUE);
	LCD_DrawRectangle(0,40,sLCD_DIS.LCD_Dis_Column/2,60,BLUE, DRAW_FULL, DOT_PIXEL_1X1);
	LCD_DrawRectangle(0,40,sLCD_DIS.LCD_Dis_Column,60,BLUE, DRAW_EMPTY, DOT_PIXEL_1X1);
	LCD_DisplayString(10,80,"50%",&Font12,LCD_BACKGROUND,BLUE);
}
/**
 * seting cup fill
 * state 22
 */
void setCupFillScreen(){
	LCD_DisplayString(10,20,"Set fill percentage",&Font8,LCD_BACKGROUND,BLUE);
	LCD_DrawRectangle(0,40,sLCD_DIS.LCD_Dis_Column/5,60,BLUE, DRAW_FULL, DOT_PIXEL_1X1);
	LCD_DrawRectangle(0,40,sLCD_DIS.LCD_Dis_Column,60,BLUE, DRAW_EMPTY, DOT_PIXEL_1X1);
	LCD_DisplayString(10,80,"20%",&Font12,LCD_BACKGROUND,BLUE);
}
/**
 * error screen when somebody moved the cup
 * state 25
 */
void movedCupErrorScreen(){
	LCD_DisplayString(10,20,"THERE IS",&Font16,LCD_BACKGROUND,RED);
	LCD_DisplayString(10,35,"NO CUP",&Font16,LCD_BACKGROUND,RED);
}
/**
 * error screen when there is no liquid in the tank
 * state 25
 */
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
