/*
 * File:   controlTAD.c
 * Author: MB
 *
 * Created on April 29, 2019, 7:22 PM
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <xc.h>
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
#include <math.h>


typedef struct {
    
	char fichas[4]; //Fichas que apuesta el jugador
    int fichasInt;
    
    char celda[4];  //Celda a la que apuesta el jugador
    int celdaInt;
    
    char cas[4];   //Casilla aleatoria 
    int casInt;     
    
    int nFitxes;    //Fichas que dispone el jugador siempre
    
    int segundos;
    int fGuanyades;
    int fPerdudes;
    int pJugades;
    int pGuanyades;
    int tempsTotal;
} Jugador;

static Jugador jugador;

static char estat = 0;
static char tecla, tecla2 = 0, celdaJugador[50], celdaGanadora[50], ganador[50], perdedor[50];
static char fichas = 0, ficha_AUX = 0, celda_AUX = 0, nFitxesChar[4], liniaTempsAposta[100], tempsChar[4];
static int numero, temps = 17, flag1 = 1, flag2 = 1; 
static int cont = 0, nCelda, afegeix, retira, tempsTotal, error, numero_AUX;
static char handle, opcion, tSistema, tempsTotalChar[4], handle2, ticsReset;


 

void controlInit() {
    jugador.cas[3]= '\0';
    jugador.nFitxes = 125;
    jugador.fichas[0] = '0';
    jugador.tempsTotal = 0;
    jugador.fGuanyades = 0;
    jugador.fPerdudes = 0;
    jugador.pJugades = 0;
    jugador.pGuanyades = 0;
    jugador.casInt = 0;
    jugador.celdaInt = 0;
    jugador.fichasInt = 0;
    handle = TiGetTimer();
    tSistema = TiGetTimer();
    handle2 = TiGetTimer();
    ticsReset = TiGetTimer();
    TiResetTics(handle);
    TiResetTics(tSistema);
    TiResetTics(handle2);
    
    
    //itoaa(nFitxesChar, jugador.nFitxes);
    flag1 = 1;
    flag2 = 1;
    
    //a = atoii(aChar);
    //SiPutsCooperatiu("NUMERO CONVERTIDO");
    //SiSendChar(a);
}


void motorControl() {
    tempsSistema();
    
	switch(estat) {
		case 0:
            jugador.fichasInt = 0;
            jugador.celdaInt = 0;
            jugador.casInt = 0;
            jugador.cas[0] = '\0';
            jugador.celda[0] = '\0';
            jugador.fichas[0] = '\0';
            nFitxesChar[0] = '\0';
            ficha_AUX = '0';
            opcion = 0;
            cont = 0;
            
            //contaSegons();
            temps = 17;
            SiPutsCooperatiu(MENU1);
            
			estat = 1;
            break;
		
        case 1:
            
			if (SiCharAvail() > 0) {
				opcion = SiGetChar();
                SiSendChar(opcion);
                
				estat = 2;
			}
            else if(TECLADO_HayTecla() == 1){
                
                
                opcion = TECLADO_GetTecla();
                SiSendChar(opcion);     
                estat = 2;
            }
            
            
		break;
		
        case 2:
            
			if (opcion == '1') {
                
				TiResetTics(handle);
				TiGetTics(handle);
				SiPutsCooperatiu(MENU2);
                itoaa(nFitxesChar, jugador.nFitxes);
                SiPutsCooperatiu(FICHASMENU); SiPutsCooperatiu(nFitxesChar);
                SiPutsCooperatiu("\r\n");
                TiResetTics(handle);
				estat = 3;
			}
            else if(opcion == '2'){
                itoaa(nFitxesChar, jugador.nFitxes);
                nFitxesChar[3] = '\0';
                SiPutsCooperatiu(FICHASMENU); SiPutsCooperatiu(nFitxesChar);
                SiPutsCooperatiu(AFEGIRRETIRAR); SiPutsCooperatiu(FITXES);
                estat = 16;
            }
            else if(opcion == '3'){
                tempsTotalChar[0] = '\0';
                itoaa(tempsTotalChar, tempsTotal);
                SiPuts(ESTADISTIQUES); SiPuts(FACTUALS); tempsTotalChar[0] = '\0'; itoaa(tempsTotalChar,jugador.nFitxes); SiPuts(tempsTotalChar); SiPuts(PGUANYADES); tempsTotalChar[0] = '\0'; 
                itoaa(tempsTotalChar,jugador.pGuanyades); SiPuts(tempsTotalChar); SiPuts(PJUGADES); tempsTotalChar[0] = '\0';itoaa(tempsTotalChar,jugador.pJugades); SiPuts(tempsTotalChar); 
                SiPuts(FGUANYADES); tempsTotalChar[0] = '\0'; itoaa(tempsTotalChar,jugador.fGuanyades); SiPuts(tempsTotalChar); SiPuts(FPERDUDES); tempsTotalChar[0] = '\0'; 
                itoaa(tempsTotalChar,jugador.fPerdudes); SiPuts(tempsTotalChar); SiPuts("\n\n\0"); 
                estat = 28;
            }
		break;
		
        case 3:
            //SiPutsCooperatiu(opcion);
			if ((SiCharAvail() <= 0 && TECLADO_HayTecla() == 0)) {
                
                contaSegons();
				if(flag1 == 1){
                    liniaTempsAposta[0] = '\0';
                    itoaa(tempsChar, temps);
                    SiPutsCooperatiu(TEMPSRESTANT); SiPutsCooperatiu(tempsChar); SiPutsCooperatiu(CORXETE);
                    flag1 = 0;
                }
				estat = 4;
			}
			else if (SiCharAvail() > 0) {
				tecla = SiGetChar();  
                SiSendChar(tecla);
				estat = 5;
			}
            else if(TECLADO_HayTecla() == 1){
                tecla2 = TECLADO_GetTecla();
                SiSendChar(tecla2);
                estat = 5;
            }
		break;
		
        case 4:
            if (temps > 0){
                estat = 3;
            }
            else if(temps == 0){
                numero_AUX = TiGetTics(handle) % 37;
                numero = setStart(numero_AUX);
                jugador.casInt = numero;
                setPartida(4);
                itoaa(jugador.cas, numero);
                temps = 17;
                jugador.fichas[0] = '0'; jugador.fichas[1]= '0'; jugador.fichas[2] = '0'; jugador.fichas[3] = '\0';
                TiResetTics(handle2);
                estat = 25;
            }
			
		break;
		
        case 5:
            //temps = 0;
			if (tecla == 'x' || tecla2 == '#') {
				tecla = '#';
                SiSendChar('#');
                itoaa(tempsChar, temps);
                SiPutsCooperatiu(TEMPSRESTANT); SiPutsCooperatiu(tempsChar); SiPutsCooperatiu(CORXETE); SiPutsCooperatiu(FICHASAPOSTAR); SiPutsCooperatiu(nFitxesChar);
				estat = 6;
			}
			else if (tecla == '*' || tecla2 == '*') {
				tecla = '*';
                SiSendChar('*');
                temps = 17;
                estat = 0;
			} 
            
		break;
		
        case 6:
            if (SiCharAvail() <= 0 && TECLADO_HayTecla() == 0) {
                contaSegons();
				if(flag1 == 1){
                    liniaTempsAposta[0] = '\0';
                    itoaa(tempsChar, temps);
                    SiPutsCooperatiu(TEMPSRESTANT); SiPutsCooperatiu(tempsChar); SiPutsCooperatiu(CORXETE);
                    flag1 = 0;
                }
				estat = 15;
            }
            
			if (SiCharAvail() > 0) {
				ficha_AUX = SiGetChar();
				estat = 7;
			}
			else if (TECLADO_HayTecla()) {
				ficha_AUX = TECLADO_GetTecla();
                //comprovaFitxes2();
				estat = 11;
			}
		break;
		
        case 7:
			if (ficha_AUX == '\r' ) {
                comprovaFitxes2();
                
                estat = 24;
			}
			else if (ficha_AUX != '\r') {
				jugador.fichas[cont] = ficha_AUX;
                intAcum(&jugador.fichasInt, &ficha_AUX); //Funcion que pasa el caracter al int;
                SiSendChar(ficha_AUX);                
				cont++;
				estat = 6;
			}
            else if (temps > 0){
                estat = 6;
            }
            
		break;
		
        case 8:
			if (SiCharAvail() > 0) {
				celda_AUX = SiGetChar();
				estat = 9;
			}
            else if(TECLADO_HayTecla() == 1){
                celda_AUX = TECLADO_GetTecla();
                estat = 12;
            }
            else if(SiCharAvail() <= 0 && TECLADO_HayTecla() == 0){
                contaSegons();
				if(flag1 == 1){
                    liniaTempsAposta[0] = '\0';
                    itoaa(tempsChar, temps);
                    SiPutsCooperatiu(TEMPSRESTANT); SiPutsCooperatiu(tempsChar); SiPutsCooperatiu(CORXETE);
                    flag1 = 0;
                }
                estat = 30;
            }
		break;
		
        case 9:
            contaSegons();
			if (celda_AUX !='\r') {
                jugador.celda[cont] = celda_AUX;
                intAcum(&jugador.celdaInt, &celda_AUX); //Funcion que pasa el caracter al int;
				SiSendChar(celda_AUX);
				cont++;
				estat = 8;
			}
        break;
		
        case 10:
            
            if(getStart() == 0) {
                setPartida2 (0); 
                compararFichas();
                //temps = 0;
                temps = 17;
                estat = 13;
            }
            else if(getStart()!= 0) {
                
                estat = 14;
            }

		break;
        
        case 11:
            if(ficha_AUX != '*'){
                jugador.fichas[cont] = ficha_AUX;
                intAcum(&jugador.fichasInt, &ficha_AUX); //Funcion que pasa el caracter al int;
                SiSendChar(ficha_AUX);
                cont++;
                estat = 6;
            }
            else if(ficha_AUX == '*'){
                comprovaFitxes2();
				estat = 24;
            }
           
        break; 
        
        case 12:
            if(celda_AUX != '*'){
                jugador.celda[cont] = celda_AUX;
                intAcum(&jugador.celdaInt, &celda_AUX); //Funcion que pasa el caracter al int;
				SiSendChar(celda_AUX);
				cont++;
                estat = 8;
            }
            
            
        break;
        
        case 13:
            jugador.fichasInt = 0;
            jugador.celdaInt = 0;
            jugador.casInt = 0;
            jugador.cas[0] = '\0';
            jugador.celda[0] = '\0';
            jugador.fichas[0] = '\0';
            nFitxesChar[0] = '\0';
            ficha_AUX = '0';
            
            cont = 0;
            //contaSegons();
            temps = 17;
            //temps = 0;
            estat = 2;           
            break;
        
        case 14:
            estat = 10;
            break;
            
        case 15:
            if (temps > 0){
                estat = 6;
            }
            else if(temps == 0){
                
                setPartida(4);
                setPartida2(1);
                temps = 17;
                estat = 10;
            }
            break;
            
        case 16:
                cont = 0;
                estat = 17;
            break;
            
        case 17:
            if(TECLADO_HayTecla()){
                ficha_AUX = TECLADO_GetTecla(); 
                
                
                estat = 19;
            }
            else if(SiCharAvail() > 0){
                ficha_AUX = SiGetChar();
                
                //jugador.fichas[cont] = ficha_AUX;
                //SiSendChar(ficha_AUX);
                
                
                estat = 21;
            }
            break;
            
        case 18:
            estat = 16;
            break;
            
        case 19:
            if ( ficha_AUX != '*'){
                //jugador.fichas[cont] = ficha_AUX;
                //SiSendChar(ficha_AUX);
                //cont++;
                intAcum(&jugador.fichasInt, &ficha_AUX);
                SiSendChar(ficha_AUX);
                
                estat = 17;
            }
            else if(ficha_AUX == '*'){
                //comprovaFitxes2(); //aquesta uncio retornara un valor a 1 si es poden afegir o no les fitxes
                //retirarFitxes();
                estat = 22;
            }
            else if(ficha_AUX == '\r'){
               // comprovaFitxes1();
               // acumularFitxes();
                estat = 22;
            }
            break;
        
        case 20:
            
            
            if((jugador.nFitxes - jugador.fichasInt) > 0) {   
                jugador.nFitxes = jugador.nFitxes - jugador.fichasInt;
               
                
                itoaa(nFitxesChar, jugador.nFitxes);
                
                SiPutsCooperatiu(nFitxesChar);
                estat = 27;
            } else if ((jugador.nFitxes - jugador.fichasInt) < 0) {
                char a [4]; 
                itoaa(a, jugador.fichasInt);
                a[3] = '\0';
                SiPutsCooperatiu(a);
                SiPutsCooperatiu(" No puedes retirar mas fichas de las que dispones.\r\n\0");
                estat = 27;
            }
            break;
            
            
        case 21:
            if(ficha_AUX != '\r'){
                intAcum(&jugador.fichasInt, &ficha_AUX);
                SiSendChar(ficha_AUX);
                
                estat = 17;
            }
            else if(ficha_AUX == '*' || ficha_AUX == '\r'){
                //comprovaFitxes2(); //aquesta uncio retornara un valor a 1 si es poden afegir o no les fitxes
                //retirarFitxes();
              
                estat  = 22;
            }
            break;
            
        case 22:
            
            if (SiCharAvail() > 0){
                
                ficha_AUX = SiGetChar();
                estat = 23;
            }
            else if(TECLADO_HayTecla() == 1){
                
                
                
                estat = 23;
            }
            break;
            
        case 23:
            if(ficha_AUX == '*'){
                SiSendChar(ficha_AUX);
                estat = 20; 
            }
            else if(ficha_AUX == 'x' || ficha_AUX == '#'){
                SiSendChar(ficha_AUX);
                estat = 26;
            }
            break;
            
        case 24:
            if(retira == 1){
                itoaa(tempsChar, temps);
                SiPutsCooperatiu(TEMPSRESTANT); SiPutsCooperatiu(tempsChar); SiPutsCooperatiu(CORXETE); SiPutsCooperatiu(CELDAAPOSTAR); SiPutsCooperatiu(nFitxesChar);
                cont = 0;
                estat = 8;
            }
            else if(retira == 0){
                SiPutsCooperatiu("\r\nNo pots apostar fitxes que no tens. Afegeix-ne primer. (Opcio 2)\0");
                estat = 0;
            }
            break;
            case 25:
                
                if(TiGetTics(handle2) > 10000) {
                    setPartida2(1);
                    numero_AUX = TiGetTics(handle) % 37;
                    numero = setStart(numero_AUX);
                    //printf("NUM %d ", numero);
                    jugador.casInt = numero;
                    setPartida(4);
                    itoaa(jugador.cas, numero);
                    TiResetTics(handle2);
                    
                    estat = 10;
                }

            break;
            
        case 26:

             if((jugador.nFitxes + jugador.fichasInt) <= 999) {   
                jugador.nFitxes = jugador.nFitxes + jugador.fichasInt;
                
                itoaa(nFitxesChar, jugador.nFitxes);
                
                SiPutsCooperatiu(nFitxesChar);
                estat = 27;
            } else if ((jugador.nFitxes + jugador.fichasInt) > 999) {
                SiPutsCooperatiu("No puedes anadir mas de 999 fichas.\r\n\0");
                estat = 27;
            }
            break;
            
            
        case 27:
            if(TECLADO_HayTecla() == 1){
                TECLADO_GetTecla();
                estat = 0;
            }
            else if(SiCharAvail() > 0){
                SiGetChar();
                estat = 0;
            }
            break;
            
        case 28:
            if(SiCharAvail() <= 0 && TECLADO_HayTecla() <=0 && flag2 == 1 ){
                SiPuts(TSISTEMA);
                tempsTotalChar[0] = '\0';itoaa(tempsTotalChar,jugador.tempsTotal); SiPuts(tempsTotalChar); SiPuts("s");
                estat = 29;
            }
            else if(SiCharAvail() > 0 || TECLADO_HayTecla() ==1){
                estat = 0;
            }
            break;
            case 29:
                estat = 28; 
            
            break;
            
        case 30:
            if (temps > 0){
                estat = 8;
            }
            else if(temps <= 0){
                /*numero_AUX = TiGetTics(handle) % 37;
                numero = setStart(numero_AUX);
                printf("NUM %d ", numero);
                jugador.casInt = numero;
                setPartida(4);
                itoaa(jugador.cas, numero);
                TiResetTics(handle2);*/
     
                estat = 25;
            }
            break;
            
        case 31:
            //estat = 
            break;
                    
	}
}




void comprovaFitxes1(void){
    if ((jugador.nFitxes + jugador.fichasInt) <= 999){
        afegeix = 1;
    }else{
        afegeix = 0;
    }

}

void comprovaFitxes2(){
    
    if ((jugador.nFitxes - jugador.fichasInt) >= 0){
        retira = 1;
    }else{
        retira = 0;
    }
   
}


void acumularFitxes(void){
    
    
    if(afegeix == 1 && (jugador.celdaInt == 100 || jugador.celdaInt == 200)){
        jugador.nFitxes = (jugador.nFitxes - jugador.fichasInt) + (jugador.fichasInt * 2);
    }
    else if(afegeix == 1 && (jugador.celdaInt >= 0 && jugador.celdaInt <= 36)){
        jugador.nFitxes = (jugador.fichasInt - jugador.fichasInt ) + (jugador.fichasInt  * 36);
    }
    else if(afegeix == 0){
        jugador.nFitxes = 999;
    }
    
}

void retirarFitxes(void){
    if(retira == 1){
        jugador.nFitxes = jugador.nFitxes - jugador.fichasInt;
        char abc[4];
        abc[3] = '\0';
        itoaa(abc, jugador.nFitxes);
        SiPutsCooperatiu("             FICHAS RESTADAS:        \0");
        SiPutsCooperatiu(abc);
    }
    else if(retira == 0 && error == 1){
        SiPutsCooperatiu("\r\nNo pots retirar tantes fitxes.\0");
    }
    else if(retira == 0 && error == 0){
        SiPutsCooperatiu("\r\nNo pots apostar fitxes que no tens. Afegeix-ne primer. (Opcio 2)\0");
    }
}

void calculoCelda(char a[2]) {
     
     a = "44";
     
 }

char getEquivalencia(char fichas) {
    return fichas - '0';

}


void itoaa(char * temp, int num){
   
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

int atoii(char cas[4]) {
 int i, j, w, k;
 i = (cas[0] - '0');
 //SiSendChar(i + '0');
 j =  ((cas[1] - '0'));
 //SiSendChar(j + '0');
 w = ((cas[2] - '0'));
// SiSendChar(w + '0');
 k = i * 100 + j*10 + w;

 return k;
}

void contaSegons(void){
    flag1 = 0;
    if (TiGetTics(handle) >= 10000){
        flag1 = 1;
        temps = temps - 1;
        TiResetTics(handle);
    }
}

void tempsSistema(void){
    flag2 = 0;
    if (TiGetTics(tSistema) >= 10000){
        flag2 = 1;
        jugador.tempsTotal = jugador.tempsTotal + 1;
        TiResetTics(tSistema);
    }
}

void compararFichas(void) {
    
    SiPuts(CELDAJUGADOR); SiPuts(jugador.celda);
    SiPuts("\r\n\0");
    SiPuts("\r\n\0");
    SiPuts(CELDAGANADORA); SiPuts(jugador.cas);
    SiPuts("\r\n");
    if(jugador.fichasInt == 0) {
        SiPutsCooperatiu("\r\nNo has apostado fichas \0");
        
    
    }
    else if((jugador.casInt == jugador.celdaInt) || (jugador.celdaInt == 100 && numero_AUX%2 == 0 )|| (jugador.celdaInt == 200 && numero_AUX%2 != 0)) {
        SiPuts(GANADOR); SiPuts(jugador.fichas); SiPuts(FICHASHAPPY); 
        setPartida(1);
        afegeix = 1;
        jugador.pGuanyades ++;
        jugador.pJugades ++;
        jugador.fGuanyades = jugador.fGuanyades + jugador.fichasInt;
        comprovaFitxes1();
        acumularFitxes();
    } 
    else {
        SiPuts(PERDEDOR); SiPuts(jugador.fichas); SiPuts(FICHASTRISTE);
        setPartida(2);
        retira = 1;
        jugador.pJugades ++;
        jugador.fPerdudes = jugador.fPerdudes + jugador.fichasInt;
        
        retirarFitxes();
    }
}

char getOpcio(){
    return opcion;
}

void resetOpcio(){
    opcion = '0';
}

int getTemps(){
    return temps;
}

int getFlag(){
    return flag1;
}

void getFichas(char nFitxesChar[4]){
    itoaa(nFitxesChar, jugador.nFitxes);
    return nFitxesChar;
}

void intAcum(int * var, char *  car) {
    *var = *var * 10 + (*car - '0');
    SiSendChar(*var);

}