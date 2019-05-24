/*
 * File:   melodiaTAD.c
 * Author: annaaguareles
 *
 * Created on May 14, 2019, 9:16 AM
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
#include "melodiaTAD.h"

static int estat = 0, partida = 0, partida2 = 0, count = 0, MAXCOUNT = 5000;
static int var = 2, T1 = 8, T2 = 4, flag = 0;
static char t;
static int espera = 0;

void initMelodia (){
    t = TiGetTimer();
    TRISAbits.TRISA1 = 0;
    LATAbits.LATA1 = 0;
}

void motorMelodia (void){
    
    static char estat = 0;

	switch(estat) {
		case 0:
			if (partida > 0) {
				TiResetTics(t);
				count = 0;
				var = 0;
                LATAbits.LATA1 = 1;
				estat = 2;
			}
		
		break;
		case 2:
			if (TiGetTics(t) > T1) {
				count++;
                LATAbits.LATA1 = 0;
                TiResetTics(t);
				estat = 3;
			}
		break;
		case 3:
			if (TiGetTics(t) > T1) {
                LATAbits.LATA1 = 1;
                TiResetTics(t);
                compruebaTono();
				estat = 6;
			}
		break;
        case 6:
            if (count >= MAXCOUNT) {
				partida = 0;
				estat = 0;
			}
            if (count < MAXCOUNT){
                estat = 2;
            }
            break;
            
        
	}
}

void motorMelodia2 (void){
    
    static char estat2 = 0;

	switch(estat2) {
		case 0:
			if (partida2 > 0) {
                
				TiResetTics(t);
				count = 0;
				var = 0;
                LATAbits.LATA1 = 1;
				estat2 = 2;
			}
		
		break;
		case 2:
			if (TiGetTics(t) > 5) {
				count++;
                LATAbits.LATA1 = 0;
                TiResetTics(t);
				estat2 = 3;
			}
		break;
		case 3:
			if (TiGetTics(t) > 10) {
                LATAbits.LATA1 = 1;
                TiResetTics(t);
                compruebaTono();
				estat2 = 6;
			}
		break;
        case 6:
            estat2 = 0;
            break;
            
        
	}
}

void setPartida (int part) {
    int var = AdGetMostra();
    MAXCOUNT =  map(var);
    partida = part;
     
    if (part == 1) {
        T1 = 1;
    
    } else T1 = 3;
}

int getPartida () {
    return partida;

}

void setPartida2 (int part) {
    MAXCOUNT =  map(var);
    partida2 = part;
    
}

void compruebaTono() {
    int var = AdGetMostra();
    //MAXCOUNT =  map(var);
    
    
    if (partida == 1) {
        
        if (count < MAXCOUNT/3) {
            T1 = 5;
        } else if(count >= MAXCOUNT/3 && count <= MAXCOUNT/3 * 2) {
            T1 = 4;
        } else if (count > MAXCOUNT/3 * 2 && count < MAXCOUNT) {
            T1 = 3;
        }
    } else if (partida == 2) {
        if (count < MAXCOUNT/3) {
            T1 = 1;
        } else if(count >= MAXCOUNT/3 && count <= MAXCOUNT/3 * 2) {
            T1 = 3;
        } else if (count > MAXCOUNT/3 * 2 && count < MAXCOUNT) {
            T1 = 5;
        }
    
    } else if (partida == 4) {
        if (count < MAXCOUNT/3) {
            T1 = 5;
        } else if(count >= MAXCOUNT/3 && count <= MAXCOUNT/3 * 2) {
            T1 = 7;
        } else if (count > MAXCOUNT/3 * 2 && count < MAXCOUNT) {
            T1 = 9;
        } 
        
    
    }
}