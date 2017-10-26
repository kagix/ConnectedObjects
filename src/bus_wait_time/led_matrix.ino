#include <LedControl.h>
#include "led_matrix.h"
#include "binary.h"

LedControl lc=LedControl(pinDIN,pinCLK,pinCS,shieldCount);


// Our drawing buffer. Everything goes here, eventually. 8x8 bit array
byte led_matrix[8]= {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000
};

// bitmap Err for the display
byte led_err[8]= {
  B11000000,
  B10000000,
  B11011011,
  B10010010,
  B11010010,
  B00000000,
  B00000000,
  B00000000
};

// bitmap WF for the display
byte led_wifi[8]= {
  B10101011,
  B10101010,
  B10101011,
  B10101010,
  B01010010,
  B00000000,
  B00000000,
  B00000000
};


//  5x3 LED figures from 0 to 9
byte figures[10][5]={
  { 0x07, 0x05, 0x05, 0x05, 0x07 }, //  0
  { 0x01, 0x01, 0x01, 0x01, 0x01 }, //  1
  { 0x07, 0x01, 0x07, 0x04, 0x07 }, //  2
  { 0x07, 0x01, 0x07, 0x01, 0x07 }, //  3
  { 0x05, 0x05, 0x07, 0x01, 0x01 }, //  4
  { 0x07, 0x04, 0x07, 0x01, 0x07 }, //  5
  { 0x07, 0x04, 0x07, 0x05, 0x07 }, //  6
  { 0x07, 0x01, 0x01, 0x01, 0x01 }, //  7
  { 0x07, 0x05, 0x07, 0x05, 0x07 }, //  8
  { 0x07, 0x05, 0x07, 0x01, 0x07 }  //  9
};

// Not sure if memset(matrix, ..) exists on Arduino
void resetMatrix(byte *matrix){
  for (int row = 0; row < 7; row++){
    matrix[row] = 0x00;
  }
}

// bitblt equivalent for the 8x8 display
void plotFigureToMatrix( byte *matrix, 
                            byte *figure, 
                            byte pos){
  for (int row = 0; row < 5; row ++){
    byte buf = figure[row];
    if (pos > 0)
      buf=buf*0x10;
    matrix[row] += buf;
  }
}

// Simple progress bar on the lowest row (7) of LEDs
void drawProgress(byte *image,int pos){
  byte val = 0;
  switch(pos){
    case 1: val=2; break;
    case 2: val=4; break;
    case 3: val=8; break;
    case 4: val=16; break;
    case 5: val=32; break;
    case 6: val=64; break;
    default:
      val = 0;
  }

  image[7] = val;
  
}

// A pitty LED library has no buffer copy.
void drawImage(byte *image){
  for ( int row = 0; row < 8; row ++){
    lc.setRow(shieldID,row,image[row]);
  }
}




// Draw a 1-figure  or 2-figure number on the 8x8 display with 5x3 figures 
void draw_number(int number){
  
  resetMatrix(led_matrix);

  int unitsFigure = number % 10;
  int tensFigure = ((number - unitsFigure) / 10 ) % 10;
  if ( number >= 0){
    plotFigureToMatrix(led_matrix,figures[unitsFigure],0);
  if (number >= 10)      
     plotFigureToMatrix(led_matrix,figures[tensFigure],1);
  }
    
  drawImage(led_matrix);
}

// Let's separate the code for devices: LEDS ..
void initDisplay(){
  lc.shutdown(shieldID,false);
  lc.setIntensity(shieldID,1);
  lc.clearDisplay(shieldID);  
  drawImage(led_err);
  delay(ONE_SECOND);

}

void displayWiFi(){
    drawImage(led_wifi);
}

void displayErr(){
  drawImage(led_err);
}

void displayProgress(int tick){
         drawProgress(led_matrix,tick);
}

void updateDisplay(){
     drawImage(led_matrix);
}



