/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef CTAD_H
#define	CTAD_H

#include <xc.h> 
#define MENU1 "  \r\n--------------- \r\n Menu principal \r\n---------------  \r\n Tria una opcion: \r\n 1. Nova aposta \r\n 2. Afegir o retirar fitxes \r\n 3. Veure estadistiques \r\n Opcion: \0"
#define MENU2 "\r\n\r\nBenvingut a LSCasino \r\n Prem '*' per retornar al menu principal \r\n Prem '#' per apostar fitxes\r\n\0"
#define FICHASMENU "\r\nFitxes disponibles: \0"
#define TEMPSRESTANT "\r[Temps restant: \0"
#define FICHASAPOSTAR "Introdueix numero de fitxes a apostar: \r\n\0"
#define CELDAAPOSTAR "\r\nIntrodueix cel.la [0-36 = Individual || 100 - Red || 200 - Black]\r\n\0"
#define AFEGIRRETIRAR "\r\nIntrodueix un valor i prem '#' per afegir fitxes o '*' per retirar fitxes.\r\n\0"
#define FITXES "\r\nFitxes: \0"
#define ESTADISTIQUES "\r\nPanell d'estadistiques: \0"
#define FICHAS4  "\r\nS'han apostat \0"
#define CELDAGANADORA  "\r\nLa cel.la guanyadora es la \0"
#define FICHASPERDIDAS "\r\nHo sentim molt, has perdut.\0"
#define SEGS16TICS 200
#define CELDAJUGADOR "\r\nCelda apostada por el jugador: \0"
#define CELDAGANADORA "Celda ganadora: \0"
#define GANADOR "\r\nENHORABUENA, has ganado \0"
#define PERDEDOR "\r\nLO SENTIMOS, has perdido \0"
#define CORXETE "] \0"
#define FICHASHAPPY " fichas! :)\0"
#define FICHASTRISTE " fichas! :(\0"
#define FACTUALS "\r\n\r\nFitxes actuals:\t\t\t\0"
#define PGUANYADES "\r\nPartides guanyades:\t\t\0"
#define PJUGADES "\r\nPartides jugades:\t\t\0"
#define FGUANYADES "\r\nFitxes guanyades en total:\t\0"
#define FPERDUDES "\r\nFitxes perdudes en total:\t\0"
#define TSISTEMA "\rTemps del sistema:\t\t\0"


// include processor files - each processor file is guarded.  

// TODO Insert appropriate #include <>

// TODO Insert C++ class definitions if appropriate

// TODO Insert declarations

// Comment a function and leverage automatic documentation with slash star star
/**
    <p><b>Function prototype:</b></p>
  
    <p><b>Summary:</b></p>

    <p><b>Description:</b></p>

    <p><b>Precondition:</b></p>

    <p><b>Parameters:</b></p>

    <p><b>Returns:</b></p>

    <p><b>Example:</b></p>
    <code>
 
    </code>

    <p><b>Remarks:</b></p>
 */
// TODO Insert declarations or function prototypes (right here) to leverage 
// live documentation

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

//void itoaa(char cas[3], int i);

char getOpcio();

int getTemps();

int getFlag();

void getFichas(char nFitxesChar[4]);