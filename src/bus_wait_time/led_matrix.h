#ifndef WAITING_TIME_LED_MATRIX_H
#define WAITING_TIME_LED_MATRIX_H

extern void resetMatrix(byte *matrix);
extern void plotFigureToMatrix( byte *matrix, 
                            byte *figure, 
                            byte pos);
                            
extern void drawProgress(byte *image,int pos);
extern void drawImage(byte *image);
extern void draw_number(int number);
extern void initDisplay();
extern void displayWiFi();
extern void displayErr();
extern void displayProgress(int tick);
extern void updateDisplay();

#endif

