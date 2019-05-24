/*
 * File:   servoTAD.c
 * Author: annaaguareles
 *
 * Created on May 13, 2019, 10:05 AM
 */

#include "xc.h"
#include "time.h"
#include "LeTLeds.h"
#include "LcTLCD.h"
#include "AuTAudio.h"
#include "SwTSwitch.h"
#include "PbTPushbutton.h"
#include "AdTADC.h"
#include "BlTBacklight.h"
#include "SiTSio.h"
#include "PrTPropaganda.h"
#include "controlTAD.h"
#include "TecladoTAD.h"
#include "servoTAD.h"

#define VUELTAS8 1530;


static int start = 0, estat = 0, count = 0;
static char t, tVolta;
int PERIODOS = 160;
int NTICSP  = 40; 
int NTICS1 = 1;
static int done;
unsigned char ruleta[] = {0, 26, 3, 35, 12, 28, 7, 29, 18, 22, 9, 31, 14, 20, 1, 33, 16, 24, 5, 10, 23, 8, 30, 11, 36, 13, 27, 6, 34, 17, 25, 2, 21, 4, 19, 15, 32};
unsigned char colRuleta[] = {0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1};
//unsigned char msRuleta[] = {23500, 23627, 23754, 23881, 24008, 24135, 24262, 24389, 24516, 24643, 24770, 24897, 25024, 25151, 25278, 25405, 25532, 25659, 25786, 25913, 26040, 26167, 26294, 26421, 26548, 26675, 26802, 26929, 27056, 27183, 27310, 27437, 27564, 27691, 27818, 27945, 28072, 28199};
static int numReal, rand2, rand3;
static int msRuleta[37];
static int tCincVoltes = 23500;

void initServo(void){
    t = TiGetTimer();
    TRISAbits.TRISA4 = 0;
    LATAbits.LATA4 = 1;
    done = 0;
    rand2 = 0;
    int i = 0;
    while (i <= 36){
        msRuleta[i]=  1453  + (int)((1453/8/37)*i);
        i++;
    }
}

void motorServo(void){
    
    switch (estat) {
        
        case 0:
            if (start == 1) {
                //SiPuts("ENTRA AL MOTOR SERVO");
                TiResetTics(t);
                LATAbits.LATA4 = 1;
                count = 0;
                estat = 1;
            }
            break;
        
        case 1:
            if (TiGetTics(t) >= NTICS1) {
                count++;
                TiResetTics(t);
                LATAbits.LATA4 = 0;
                estat = 2;
            }
            break;
        
        case 2:
            if (TiGetTics(t) >(NTICSP)) {
                LATAbits.LATA4 = 1;
                TiResetTics(t);
                estat = 3;
            }
            break;
            
        case 3:
            if (count >= PERIODOS) {
                start = 0;
                done = 0;
                estat = 0;
            }
            else if (count < PERIODOS) {
                LATAbits.LATA4 = 1;
                TiResetTics(t);
                estat = 1;
            }
            break;
    }
}

int setStart(int rand) {
    numReal =  ruleta[(rand+rand2-1)%37];
    PERIODOS =  msRuleta[rand];
    start = 1;
    done = 1;
    rand2 = (rand + rand2)%37;
    return numReal;
}

int getStart() {
    return start;
}