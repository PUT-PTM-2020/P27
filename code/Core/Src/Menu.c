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

//Menu
volatile uint8_t activeMenu = 0;
volatile uint8_t activeListItem = 0;

volatile COLOR backgroundColour = WHITE; //kolor tła
volatile COLOR markedItemColour = RED; // kolor wybranej opcji
volatile COLOR otherItemColour = BLACK; //kolor pozostałych opcji

// Drink
volatile uint16_t concentration_percentage = 0;
volatile uint16_t fill_percentage = 0;

// Encoder
volatile uint16_t pulse_count; // impulse counter
volatile uint16_t encoder_position; // position counter licznik przekreconych pozycji
volatile uint8_t ToEncdrSW;

void encoder() {
  pulse_count = TIM1 -> CNT; // przepisanie wartosci z rejestru timera
  encoder_position = pulse_count / 2; // zeskalowanie impulsow do liczby stabilnych pozycji walu enkodera
}

void setToEncdrSW() {
  ToEncdrSW = 1;
}

/**
 * starting menu
 * open when activeMenu==0
 */
void startingScreen() {

  if (encoder_position < 10 || (encoder_position >= 50 && encoder_position < 60)) {
    LCD_DisplayString(10, 20, "POUR JUICE", & Font12, LCD_BACKGROUND, markedItemColour);
    LCD_DisplayString(10, 40, "POUR WATER", & Font12, LCD_BACKGROUND, otherItemColour);
    LCD_DisplayString(10, 60, "MIX", & Font12, LCD_BACKGROUND, otherItemColour);
    LCD_DisplayString(10, 80, "SETTINGS", & Font12, LCD_BACKGROUND, otherItemColour);
    LCD_DisplayString(10, 100, "PROGRAMIST", & Font12, LCD_BACKGROUND, otherItemColour);
    if (ToEncdrSW == 1) {
      ToEncdrSW = 0;
      LCD_Clear(backgroundColour);
      activeMenu = 1;
    }
  } else if ((encoder_position >= 10 && encoder_position < 20) ||
    (encoder_position >= 60 && encoder_position < 70)) {
    LCD_DisplayString(10, 20, "POUR JUICE", & Font12, LCD_BACKGROUND, otherItemColour);
    LCD_DisplayString(10, 40, "POUR WATER", & Font12, LCD_BACKGROUND, markedItemColour);
    LCD_DisplayString(10, 60, "MIX", & Font12, LCD_BACKGROUND, otherItemColour);
    LCD_DisplayString(10, 80, "SETTINGS", & Font12, LCD_BACKGROUND, otherItemColour);
    LCD_DisplayString(10, 100, "PROGRAMIST", & Font12, LCD_BACKGROUND, otherItemColour);
    if (ToEncdrSW == 1) {
      ToEncdrSW = 0;
      LCD_Clear(backgroundColour);
      activeMenu = 2;
    }

  } else if ((encoder_position >= 20 && encoder_position < 30) ||
    (encoder_position >= 70 && encoder_position < 80)) {

    LCD_DisplayString(10, 20, "POUR JUICE", & Font12, LCD_BACKGROUND, otherItemColour);
    LCD_DisplayString(10, 40, "POUR WATER", & Font12, LCD_BACKGROUND, otherItemColour);
    LCD_DisplayString(10, 60, "MIX", & Font12, LCD_BACKGROUND, markedItemColour);
    LCD_DisplayString(10, 80, "SETTINGS", & Font12, LCD_BACKGROUND, otherItemColour);
    LCD_DisplayString(10, 100, "PROGRAMIST", & Font12, LCD_BACKGROUND, otherItemColour);
    if (ToEncdrSW == 1) {
      ToEncdrSW = 0;
      LCD_Clear(backgroundColour);
      activeMenu = 3;
    }

  } else if ((encoder_position >= 30 && encoder_position < 40) ||
    (encoder_position >= 80 && encoder_position < 90)) {
    LCD_DisplayString(10, 20, "POUR JUICE", & Font12, LCD_BACKGROUND, otherItemColour);
    LCD_DisplayString(10, 40, "POUR WATER", & Font12, LCD_BACKGROUND, otherItemColour);
    LCD_DisplayString(10, 60, "MIX", & Font12, LCD_BACKGROUND, otherItemColour);
    LCD_DisplayString(10, 80, "SETTINGS", & Font12, LCD_BACKGROUND, markedItemColour);
    LCD_DisplayString(10, 100, "PROGRAMIST", & Font12, LCD_BACKGROUND, otherItemColour);
    if (ToEncdrSW == 1) {
      ToEncdrSW = 0;
      LCD_Clear(backgroundColour);
      activeMenu = 4;
    }

  } else {
    LCD_DisplayString(10, 20, "POUR JUICE", & Font12, LCD_BACKGROUND, otherItemColour);
    LCD_DisplayString(10, 40, "POUR WATER", & Font12, LCD_BACKGROUND, otherItemColour);
    LCD_DisplayString(10, 60, "MIX", & Font12, LCD_BACKGROUND, otherItemColour);
    LCD_DisplayString(10, 80, "SETTINGS", & Font12, LCD_BACKGROUND, otherItemColour);
    LCD_DisplayString(10, 100, "PROGRAMIST", & Font12, LCD_BACKGROUND, markedItemColour);
    if (ToEncdrSW == 1) {
      ToEncdrSW = 0;
      LCD_Clear(backgroundColour);
      activeMenu = 6;
    }
  }
}

/**
 * pouring juice screen
 * open when activeMenu==1
 */
void pourJuiceScreen() {
  LCD_DisplayString(10, 20, "POURING JUICE", & Font12, LCD_BACKGROUND, otherItemColour);
  LCD_DisplayString(10, 40, "PRESS BUTTON", & Font12, LCD_BACKGROUND, otherItemColour);
  LCD_DisplayString(10, 60, "TO STOP", & Font12, LCD_BACKGROUND, otherItemColour);
  if (ToEncdrSW == 1) {
    //add function to stop pouring juice
    LCD_Clear(backgroundColour);
    activeMenu = 0;
    ToEncdrSW = 0;
  }

  errorControl();

}
/**
 * pouring juice screen
 * open when activeMenu==2
 */
void pourWaterScreen() {
  LCD_DisplayString(10, 20, "POURING WATER", & Font12, LCD_BACKGROUND, otherItemColour);
  LCD_DisplayString(10, 40, "PRESS BUTTON", & Font12, LCD_BACKGROUND, otherItemColour);
  LCD_DisplayString(10, 60, "TO STOP", & Font12, LCD_BACKGROUND, otherItemColour);
  if (ToEncdrSW == 1) {
    //add function to stop pouring water
    LCD_Clear(backgroundColour);
    activeMenu = 0;
    ToEncdrSW = 0;
  }
  errorControl();

}
/**
 * pouring juice screen
 * open when activeMenu==3
 */
void mixScreen() {
  if (encoder_position < 10 || (encoder_position >= 30 && encoder_position < 40) ||
    (encoder_position >= 60 && encoder_position < 70) || encoder_position > 90) {
    LCD_DisplayString(10, 20, "     SET   ", & Font12, LCD_BACKGROUND, markedItemColour);
    LCD_DisplayString(10, 30, " CONCENTRATION", & Font12, LCD_BACKGROUND, markedItemColour);
    LCD_DisplayString(10, 60, "     NEXT", & Font12, LCD_BACKGROUND, otherItemColour);
    LCD_DisplayString(10, 80, "     BACK", & Font12, LCD_BACKGROUND, otherItemColour);
    if (ToEncdrSW == 1) {
      LCD_Clear(backgroundColour);
      activeMenu = 9;
      ToEncdrSW = 0;
    }
  } else if ((encoder_position >= 10 && encoder_position < 20) || (encoder_position >= 40 && encoder_position < 50) ||
    (encoder_position >= 70 && encoder_position < 80)) {
    LCD_DisplayString(10, 20, "     SET   ", & Font12, LCD_BACKGROUND, otherItemColour);
    LCD_DisplayString(10, 30, " CONCENTRATION", & Font12, LCD_BACKGROUND, otherItemColour);
    LCD_DisplayString(10, 60, "     NEXT", & Font12, LCD_BACKGROUND, markedItemColour);
    LCD_DisplayString(10, 80, "     BACK", & Font12, LCD_BACKGROUND, otherItemColour);
    if (ToEncdrSW == 1) {
      LCD_Clear(backgroundColour);
      activeMenu = 10;
      ToEncdrSW = 0;
    }
  } else {
    LCD_DisplayString(10, 20, "     SET   ", & Font12, LCD_BACKGROUND, otherItemColour);
    LCD_DisplayString(10, 30, " CONCENTRATION", & Font12, LCD_BACKGROUND, otherItemColour);
    LCD_DisplayString(10, 60, "     NEXT", & Font12, LCD_BACKGROUND, otherItemColour);
    LCD_DisplayString(10, 80, "     BACK", & Font12, LCD_BACKGROUND, markedItemColour);
    returnToStartingScreen();
  }

}
/**
 * activeMenu==10
 */
void mixScreen2() {
  if (encoder_position < 10 || (encoder_position >= 30 && encoder_position < 40) ||
    (encoder_position >= 60 && encoder_position < 70) || encoder_position > 90) {
    LCD_DisplayString(10, 20, "   SET FILL", & Font12, LCD_BACKGROUND, markedItemColour);
    LCD_DisplayString(10, 40, "  PERCENTAGE", & Font12, LCD_BACKGROUND, markedItemColour);
    LCD_DisplayString(10, 60, "     NEXT", & Font12, LCD_BACKGROUND, otherItemColour);
    LCD_DisplayString(10, 80, "     BACK", & Font12, LCD_BACKGROUND, otherItemColour);
    if (ToEncdrSW == 1) {
      LCD_Clear(backgroundColour);
      activeMenu = 11;
      ToEncdrSW = 0;
    }
  } else if ((encoder_position >= 10 && encoder_position < 20) || (encoder_position >= 40 && encoder_position < 50) ||
    (encoder_position >= 70 && encoder_position < 80)) {
    LCD_DisplayString(10, 20, "   SET FILL", & Font12, LCD_BACKGROUND, otherItemColour);
    LCD_DisplayString(10, 40, "  PERCENTAGE", & Font12, LCD_BACKGROUND, otherItemColour);
    LCD_DisplayString(10, 60, "     NEXT", & Font12, LCD_BACKGROUND, markedItemColour);
    LCD_DisplayString(10, 80, "     BACK", & Font12, LCD_BACKGROUND, otherItemColour);
    if (ToEncdrSW == 1) {
      LCD_Clear(backgroundColour);
      activeMenu = 12;
      ToEncdrSW = 0;
    }
  } else {
    LCD_DisplayString(10, 20, "   SET FILL", & Font12, LCD_BACKGROUND, otherItemColour);
    LCD_DisplayString(10, 40, "  PERCENTAGE", & Font12, LCD_BACKGROUND, otherItemColour);
    LCD_DisplayString(10, 60, "     NEXT", & Font12, LCD_BACKGROUND, otherItemColour);
    LCD_DisplayString(10, 80, "     BACK", & Font12, LCD_BACKGROUND, markedItemColour);
    if (ToEncdrSW == 1) {
      LCD_Clear(backgroundColour);
      activeMenu = 3;
      ToEncdrSW = 0;
    }
  }

}

/**
 * activeMenu==9
 */
void setConcentrationScreen() {

  char str[16];
  itoa(encoder_position, str, 10);
  LCD_Clear(backgroundColour);
  LCD_DisplayString(40, 65, str, & Font24, LCD_BACKGROUND, markedItemColour);
  LCD_DisplayString(85, 65, "%", & Font24, LCD_BACKGROUND, markedItemColour);
  if (ToEncdrSW == 1) {
    concentration_percentage = encoder_position;
    LCD_Clear(backgroundColour);
    activeMenu = 3;
    ToEncdrSW = 0;
  }

  HAL_Delay(500);
}
/**
 * activeMenu==11
 */
void setFillPercentageScreen() {

  char str[16];
  itoa(encoder_position, str, 10);
  LCD_Clear(backgroundColour);
  LCD_DisplayString(40, 65, str, & Font24, LCD_BACKGROUND, markedItemColour);
  LCD_DisplayString(85, 65, "%", & Font24, LCD_BACKGROUND, markedItemColour);
  if (ToEncdrSW == 1) {
    fill_percentage = encoder_position;
    LCD_Clear(backgroundColour);
    activeMenu = 10;
    ToEncdrSW = 0;
  }

  HAL_Delay(500);
}
/**
 * activeMenu==12
 */
void makeingMixScreen() {
  LCD_DisplayString(10, 20, "MAKEING YOUR", & Font12, LCD_BACKGROUND, otherItemColour);
  LCD_DisplayString(10, 40, "  DRINK", & Font12, LCD_BACKGROUND, otherItemColour);
  errorControl();
  //dodac funkcje do nalewania
  HAL_Delay(5000);
  LCD_Clear(backgroundColour);
  activeMenu = 0;

}

/**
 * activeMenu==7
 */
void movedCupErrorScreen() {
  LCD_DisplayString(10, 20, "THERE IS", & Font12, LCD_BACKGROUND, markedItemColour);
  LCD_DisplayString(10, 35, "NO CUP", & Font12, LCD_BACKGROUND, markedItemColour);
  returnToStartingScreen();
}
/**
 * activeMenu==8
 */
void emptyTankScreen() {
  LCD_DisplayString(10, 20, "THERE IS", & Font12, LCD_BACKGROUND, markedItemColour);
  LCD_DisplayString(10, 40, "NO LIQUID ", & Font12, LCD_BACKGROUND, markedItemColour);
  returnToStartingScreen();
}
/**
 * function to control if there is any interruption
 */
void errorControl() {
  //movedCupErrorScreen();
  //emptyTankScreen();
}

/**
 * active menu==6
 */
void programistScreen() {
  LCD_DisplayString(10, 20, "SERVO 70", & Font12, LCD_BACKGROUND, otherItemColour);
  LCD_DisplayString(10, 40, "CUP DISTANCE 14", & Font12, LCD_BACKGROUND, otherItemColour);
  LCD_DisplayString(10, 60, "ENGINE 1 TRUE", & Font12, LCD_BACKGROUND, otherItemColour);
  LCD_DisplayString(10, 80, "ENGINE 2 FALSE", & Font12, LCD_BACKGROUND, otherItemColour);
  returnToStartingScreen();
}
/**
 * when activeMenu==4
 */
void settingsScreen() {
  if (encoder_position < 10 || (encoder_position >= 20 && encoder_position < 30) ||
    (encoder_position >= 40 && encoder_position < 50) ||
    (encoder_position >= 60 && encoder_position < 70) ||
    (encoder_position >= 80 && encoder_position < 90)) {
    LCD_DisplayString(10, 20, "MOTIVES", & Font12, LCD_BACKGROUND, markedItemColour);
    LCD_DisplayString(10, 40, "BACK ", & Font12, LCD_BACKGROUND, otherItemColour);
    if (ToEncdrSW == 1) {
      LCD_Clear(backgroundColour);
      activeMenu = 5;
      ToEncdrSW = 0;
    }
  } else {
    LCD_DisplayString(10, 20, "MOTIVES", & Font12, LCD_BACKGROUND, otherItemColour);
    LCD_DisplayString(10, 40, "BACK ", & Font12, LCD_BACKGROUND, markedItemColour);
    returnToStartingScreen();
  }
}
/**
 * when activeMenu==5
 */
void motivesScreen() {
  if (encoder_position < 10 || (encoder_position >= 50 && encoder_position < 60)) {
    LCD_DisplayString(10, 20, "STYLE 1", & Font12, LCD_BACKGROUND, markedItemColour);
    LCD_DisplayString(10, 40, "STYLE 2", & Font12, LCD_BACKGROUND, otherItemColour);
    LCD_DisplayString(10, 60, "STYLE 3", & Font12, LCD_BACKGROUND, otherItemColour);
    LCD_DisplayString(10, 80, "STYLE 4", & Font12, LCD_BACKGROUND, otherItemColour);
    LCD_DisplayString(10, 100, "     BACK", & Font12, LCD_BACKGROUND, otherItemColour);
    if (ToEncdrSW == 1) {
      backgroundColour = BLACK;
      markedItemColour = RED;
      otherItemColour = WHITE;
      ToEncdrSW = 0;
      LCD_Clear(backgroundColour);

    }
  } else if ((encoder_position >= 10 && encoder_position < 20) ||
    (encoder_position >= 60 && encoder_position < 70)) {
    LCD_DisplayString(10, 20, "STYLE 1", & Font12, LCD_BACKGROUND, otherItemColour);
    LCD_DisplayString(10, 40, "STYLE 2", & Font12, LCD_BACKGROUND, markedItemColour);
    LCD_DisplayString(10, 60, "STYLE 3", & Font12, LCD_BACKGROUND, otherItemColour);
    LCD_DisplayString(10, 80, "STYLE 4", & Font12, LCD_BACKGROUND, otherItemColour);
    LCD_DisplayString(10, 100, "     BACK", & Font12, LCD_BACKGROUND, otherItemColour);
    if (ToEncdrSW == 1) {
      backgroundColour = WHITE;
      markedItemColour = GREEN;
      otherItemColour = BLACK;
      ToEncdrSW = 0;
      LCD_Clear(backgroundColour);
    }

  } else if ((encoder_position >= 20 && encoder_position < 30) ||
    (encoder_position >= 70 && encoder_position < 80)) {

    LCD_DisplayString(10, 20, "STYLE 1", & Font12, LCD_BACKGROUND, otherItemColour);
    LCD_DisplayString(10, 40, "STYLE 2", & Font12, LCD_BACKGROUND, otherItemColour);
    LCD_DisplayString(10, 60, "STYLE 3", & Font12, LCD_BACKGROUND, markedItemColour);
    LCD_DisplayString(10, 80, "STYLE 4", & Font12, LCD_BACKGROUND, otherItemColour);
    LCD_DisplayString(10, 100, "     BACK", & Font12, LCD_BACKGROUND, otherItemColour);
    if (ToEncdrSW == 1) {
      backgroundColour = BLUE;
      markedItemColour = RED;
      otherItemColour = YELLOW;
      ToEncdrSW = 0;
      LCD_Clear(backgroundColour);

    }

  } else if ((encoder_position >= 30 && encoder_position < 40) ||
    (encoder_position >= 80 && encoder_position < 90)) {
    LCD_DisplayString(10, 20, "STYLE 1", & Font12, LCD_BACKGROUND, otherItemColour);
    LCD_DisplayString(10, 40, "STYLE 2", & Font12, LCD_BACKGROUND, otherItemColour);
    LCD_DisplayString(10, 60, "STYLE 3", & Font12, LCD_BACKGROUND, otherItemColour);
    LCD_DisplayString(10, 80, "STYLE 4", & Font12, LCD_BACKGROUND, markedItemColour);
    LCD_DisplayString(10, 100, "     BACK", & Font12, LCD_BACKGROUND, otherItemColour);
    if (ToEncdrSW == 1) {
      backgroundColour = WHITE;
      markedItemColour = RED;
      otherItemColour = BLACK;
      ToEncdrSW = 0;
      LCD_Clear(backgroundColour);

    }

  } else {
    LCD_DisplayString(10, 20, "STYLE 1", & Font12, LCD_BACKGROUND, otherItemColour);
    LCD_DisplayString(10, 40, "STYLE 2", & Font12, LCD_BACKGROUND, otherItemColour);
    LCD_DisplayString(10, 60, "STYLE 3", & Font12, LCD_BACKGROUND, otherItemColour);
    LCD_DisplayString(10, 80, "STYLE 4", & Font12, LCD_BACKGROUND, otherItemColour);
    LCD_DisplayString(10, 100, "     BACK", & Font12, LCD_BACKGROUND, markedItemColour);
    returnToStartingScreen();
  }
}

uint8_t get_activeMenu() {
  return activeMenu;
}

uint8_t get_activeListItem() {
  return activeListItem;
}

/**
 * function to control menu states
 */
void menu_display() {

  encoder();

  switch (activeMenu) {
  case 0:
    startingScreen();
    break;
  case 1:
    pourJuiceScreen();
    break;
  case 2:
    pourWaterScreen();
    break;
  case 3:
    mixScreen();
    break;
  case 4:
    settingsScreen();
    break;
  case 5:
    motivesScreen();
    break;
  case 6:
    programistScreen();
    break;
  case 7:
    emptyTankScreen();
    break;
  case 8:
    movedCupErrorScreen();
    break;
  case 9:
    setConcentrationScreen();
    break;
  case 10:
    mixScreen2();
    break;
  case 11:
    setFillPercentageScreen();
    break;
  case 12:
    makeingMixScreen();
    break;
  default:

    break;
  }
}

/**
 * if button is pressed -> activeMenu=0
 */
void returnToStartingScreen() {
  if (ToEncdrSW == 1) {
    LCD_Clear(backgroundColour);
    activeMenu = 0;
    ToEncdrSW = 0;
  }
}

uint16_t getConcentration_percentage() {
  return concentration_percentage;
}

uint16_t getFill_percentage() {
  return fill_percentage;
}
