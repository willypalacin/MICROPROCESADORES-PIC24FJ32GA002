/*
 * File:   TecladoTAD.c
 * Author: MB
 *
 * Created on April 29, 2019, 8:19 PM
 */

#include "xc.h"
#include "TecladoTad.h"
#include "time.h"

#define MS20 500

static char estat = 0;
static int cols = -1, HiHaTecla = 0;
static unsigned int filas = 1;
static char teclaAUX = '-1', tecla = '-1', t;


void initTeclat(){
    t = TiGetTimer();
    TRISAbits.TRISA3 = 1;
    TRISAbits.TRISA2 = 1;
    TRISBbits.TRISB13 = 1;
    TRISBbits.TRISB6 = 0;
    TRISBbits.TRISB7 = 0;
    TRISBbits.TRISB8 = 0;
    TRISBbits.TRISB9 = 0;
    
}

void motorTeclado(void) { 
    TRISBbits.TRISB6 = 0;
    TRISBbits.TRISB7 = 0;
    TRISBbits.TRISB8 = 0;
    TRISBbits.TRISB9 = 0;
    
	switch(estat) {
        //sacarFilas();
		case 0:
			filas = 1;
			estat = 1;
		break;
		case 1:
			if (HayTecla() == 0) {
                sacarFilas();
				filas = filas << 1;
                
				estat = 2;
			}
			else if (HayTecla()) {
				TiResetTics(t);
				estat = 3;
			}
		break;
		case 2:
			if (filas <= 8) {
				estat = 1;
			}
			else if (filas > 8) {
				estat = 0;
			}
		break;
		case 3:
			if (TiGetTics(t) >= MS20 && HayTecla()) {
				teclaAUX = QueTecla();
				estat = 4;
			} 
            else if (TiGetTics(t) >= MS20 && !HayTecla()) {
				
				estat = 0;
			}
		break;
		case 4:
			if (!HayTecla()) {
				tecla = teclaAUX;
                HiHaTecla = 1;
				estat = 0;
                
			}
		break;
	}
}

int TECLADO_HayTecla() {
    
    return HiHaTecla;
}


char TECLADO_GetTecla() {
    HiHaTecla = 0;
    return tecla;

}

int HayTecla(){
    
    if (PORTAbits.RA2 == 1) {
        cols = 1;
        return 1;
    }
    else if(PORTBbits.RB13 == 1){
        cols = 2;
        return 1;
    }
    else if(PORTAbits.RA3 == 1){
        cols = 4;
        return 1;
    }
    return 0;
}

int QueTecla(){
    char tecla_AUX2;
    
    if(cols == 1){
        if(filas == 1){
            tecla_AUX2 = '*';
        }
        else if(filas == 2){
            tecla_AUX2 = '1';
        }
        else if(filas == 4){
            tecla_AUX2 = '4';
        }
        else if(filas == 8){
            tecla_AUX2 ='7';
        }
    }
    
    else if(cols == 2){
        if(filas == 1){
            tecla_AUX2 = '0';
        }
        else if(filas == 2){
            tecla_AUX2 = '2';
        }
        else if(filas == 4){
            tecla_AUX2 = '5';
        }
        else if(filas == 8){
            tecla_AUX2 = '8';
        }
    }
    
    else if(cols == 4){
        if(filas == 1){
            tecla_AUX2 = '#';
        }
        else if(filas == 2){
            tecla_AUX2 = '3';
        }
        else if(filas == 4){
            tecla_AUX2 = '6';
        }
        else if(filas == 8){
            tecla_AUX2 ='9';
        }
    }
    return tecla_AUX2;
}

void sacarFilas() {
    if(filas == 1) {
        LATBbits.LATB6 = 1;
        LATBbits.LATB7 = 0;
        LATBbits.LATB8 = 0;
        LATBbits.LATB9 = 0;
    }
    else if (filas == 2) {
       LATBbits.LATB6 = 0;
       LATBbits.LATB7 = 1;
       LATBbits.LATB8 = 0;
       LATBbits.LATB9 = 0;
    }
    else if (filas == 4) {
       LATBbits.LATB6 = 0;
       LATBbits.LATB7 = 0;
       LATBbits.LATB8 = 1;
       LATBbits.LATB9 = 0;
    }
    else if (filas == 8) {
       LATBbits.LATB6 = 0;
       LATBbits.LATB7 = 0;
       LATBbits.LATB8 = 0;
       LATBbits.LATB9 = 1;
    }
    //LATB = ((PORTB & 0xFC3F) | (filas << 6));
}