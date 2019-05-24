/*
 * File:   sensorTAD.c
 * Author: annaaguareles
 *
 * Created on May 14, 2019, 4:06 PM
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
#include "TecladoTAD.h"
#include "servoTAD.h"
#include "melodiaTAD.h"
#include "sensorTAD.h"
#include <math.h>

static int estat = 0, nserie = 0, segons = 10000;
static char tTemp, tics1m;
static char  tempChar[4];
static int nBits, bitLlegit, temp;
static int potencia = 0;


void initSensor(void){
    AD1PCFGbits.PCFG12 = 1; //No vull entrada analògica (AN12)!!
    tTemp = TiGetTimer();
    tics1m = TiGetTimer();
    TRISBbits.TRISB11 = 0; //pin 22 pic clock sensor
    TRISBbits.TRISB12 = 1; //valor serie entrada sensor
    TRISBbits.TRISB10 = 0; //bit de CS
    LATBbits.LATB10 = 0;
    TiResetTics(tTemp);
    
    temp = 0;
    nBits = 0;
    bitLlegit = 0;
}

void motorSensor(void) {
	static char estat = 0;
    
    switch(estat) {
		case 0:
            LATBbits.LATB10 = 0;
            temp = 0;
            nBits = 0;
            estat = 1;
            TiResetTics(tTemp);
           break;
           
        case 1:
            LATBbits.LATB11 = 0;
            TiResetTics(tics1m);
            estat = 2;
            break;
            
        case 2:
            if(TiGetTics(tics1m) >= 2){
                estat = 3;
                TiResetTics(tics1m);
                temp += PORTBbits.RB12;
            }
            break;
            
        case 3:
            if(TiGetTics(tics1m) >= 2){
                estat = 4;
                TiResetTics(tics1m);
            }
            
        case 4:
            LATBbits.LATB11 = 1;
            nBits++;
            estat = 5;
            break;
            
        case 5:
            if(TiGetTics(tics1m) >= 4){
                if (nBits < 9) {
                    temp = temp << 1;
                    temp = temp & 0xFE;
                    estat = 1;
                }
                else{
                    estat = 6;
                }
            }
            break;
            
        case 6:
            LATBbits.LATB10 = 1;
            temp = temp & 0x3FF;
            estat = 7;
            break;
            
        case 7:
            LATBbits.LATB11 = 1;
            if(TiGetTics(tTemp) > 30000){
                estat = 0;
            }
            break;
			
	}
}

void acumTemperatura(int bitLlegit, int nBits){
    
    switch(nBits){
        case 0:
            
            //temp = temp + bitLlegit*4096;
            temp = temp + bitLlegit*256;
            break;
            
        case 1:
            //temp = temp + bitLlegit*2048;
            temp = temp + bitLlegit*128;
            break;
            
        case 2:
            //temp = temp + bitLlegit*1024;
            temp = temp + bitLlegit*64;
            break;
            
        case 3:
            //temp = temp + bitLlegit*512;
            temp = temp + bitLlegit*32;
            break;
            
        case 4:
            //temp = temp + bitLlegit*256;
            temp = temp + bitLlegit*16;
            break;
            
        case 5:
            //temp = temp + bitLlegit*128;
            temp = temp + bitLlegit*8;
            break;
            
        case 6:
            //temp = temp + bitLlegit*64;
            temp = temp + bitLlegit*4;
            break;
            
        case 7:
            //temp = temp + bitLlegit*32;
            temp = temp + bitLlegit*2;
            break;
            
        case 8:
            //temp = temp + bitLlegit*16;
            temp = temp + bitLlegit*1;
            break;
            
        case 9:
            temp = temp + bitLlegit*8;
            break;
            
        case 10:
            temp = temp + bitLlegit*4;
            break;
            
        case 11:
            temp = temp + bitLlegit*2;
            break;
            
        case 12:
            temp = temp + bitLlegit*1;
            break;
             
    }
}

void itoaa2(char * temp, int num){
   
   temp[0] = (char)(num/100);
   num = num - (temp[0]*100);
   temp[1] = (char)(num /10);
   num = num - (temp[1]*10);
   temp[2] = (char) (num /1);
   num = num - (temp[2]*1);
   temp[3] = '\0';
   temp[4] = '\0';
   temp[2]+='0';
   temp[1]+='0';
   temp[0]+='0';
    
}

void getTemperatura (char tempChar[4]){
    
    itoaa2(tempChar,temp);
    return tempChar;
}
