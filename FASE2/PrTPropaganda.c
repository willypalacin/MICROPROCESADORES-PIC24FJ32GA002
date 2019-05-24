#include "PrTPropaganda.h"
#include "controlTAD.h"
#include "servoTAD.h"


static int timestamp;
static char timerPropaganda, estatPropaganda;
static char temp[50], opcio;


#define     MAXCOLUMNES 16
static char estatLCD = 0, handle, tempChar[4], fitxesChar[4], anna[4], temperatura[4];
unsigned char cadena1[]={"MENU PRINCIPAL-000-00 C  " }; //HI HA 24 CARACTERS
unsigned char cadena2[]={"ESPERANT APOSTA-000-   C " };
unsigned char cadena3[]={"JUGANT... -000-   C      "};
static unsigned char timerLCD, caracterInici, i,j, m = 17, n = 0, tics;
static unsigned int mostra;
static unsigned char segonaLinia[MAXCOLUMNES];
static unsigned char esperaTemps[] = {255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255};
static int temps = 0, opcion = 0, tempsNostre = 0, flag = 1;


void initMotorLCD(void){
    //Pre: El LCD està inicialitzat
    timerLCD = TiGetTimer();
    tics = TiGetTimer();
    caracterInici = 0;
    LcClear();
}


void MotorLCD(void){
    
    TRISBbits.TRISB6 = 1;
    TRISBbits.TRISB7 = 1;
    TRISBbits.TRISB8 = 1;
    TRISBbits.TRISB9 = 1;
    
   switch (estatLCD){
       case 0:
          
           getFichas(anna);
           if(TiGetTics(tics) >= 20000){
               getTemperatura(temperatura);
               TiResetTics(tics);
           }
           
           cadena1[15] = anna[0];
           cadena1[16] = anna[1];
           cadena1[17] = anna[2];
           cadena1[19] = temperatura[1];
           cadena1[20] = temperatura[2];
           cadena1[21] = 223;
           LcPutChar(cadena1[j++]); 
            if (j==24) j= 0;
            if (i++ > MAXCOLUMNES) {
                estatLCD = 3;
                TiResetTics(timerLCD);
                EscriuPrimeraOrdre('a');
                LcGotoXY(0,1);
            }
           
           if (getOpcio() == '1'){
               //resetOpcio();
               estatLCD = 1;
           }
           else if(getStart() == 1){
               
               estatLCD = 2;
                
           }

           break;

       case 1: //Preparo el string
          
           getFichas(anna);
           if(TiGetTics(tics) >= 20000){
               getTemperatura(temperatura);
               TiResetTics(tics);
           }
           cadena2[16] = anna[0];
           cadena2[17] = anna[1];
           cadena2[18] = anna[2];
           cadena2[20] = temperatura[1];
           cadena2[21] = temperatura[2];
           cadena2[22] = 223;
           LcPutChar(cadena2[j++]);
           if (j==24) j= 0;
            if (i++ > MAXCOLUMNES) {
                estatLCD = 3;
                TiResetTics(timerLCD);
                EscriuPrimeraOrdre('a');
                LcGotoXY(0,1);
            }
           
           break;

       case 2: //Aquí faig l?itoa, que deu trigar una bona estona el pobre...
           
           getFichas(anna);
           if(TiGetTics(tics) >= 20000){
               getTemperatura(temperatura);
               TiResetTics(tics);
           }
           cadena3[11] = anna[0];
           cadena3[12] = anna[1];
           cadena3[13] = anna[2];
           cadena3[15] = temperatura[1];
           cadena3[16] = temperatura[2];
           cadena3[17] = 223;
           LcPutChar(cadena3[j++]);
           
           if (j==24) j= 0;
            if (i++ > MAXCOLUMNES) {
                estatLCD = 3;
                TiResetTics(timerLCD);
                EscriuPrimeraOrdre('a');
                LcGotoXY(0,1);
            }
           
           break;
           
       case 3:
           if (TiGetTics(timerLCD)>500){
               //Observo que si estresso molt al LCD arriba un punt que alguna
               //vegada pinta malament un caràcter. Deu tenir una cua interna?
               //si la té, aposto a que és de 24 posicions (mal número)...
               //Cap problema, donem 50 ms. de calma entre ràfega i ràfega i gas
               TiResetTics(timerLCD);
               i=0;
               estatLCD = 4;
           }
           break;
           
       case 4:
          
           m = getTemps();
           esperaTemps[m - 1] = 32;
           LcPutChar(esperaTemps[i++]);
           if (i > MAXCOLUMNES) {
               estatLCD = 5;
               TiResetTics(timerLCD);
           }
           
           if(m <= 0){
               resetTemps();
           }
           break;

       case 5:
           if (TiGetTics(timerLCD)>= 2500){
               //Alerta, ja porto 50 ms. des de l?últim refresc
               caracterInici++;
               if (caracterInici==24)
                   caracterInici=0;
               estatLCD = 0;
               LcGotoXY(0,0);
               j = caracterInici;
               i=0;
           }
           break;
           
        case 6:
            
            break;
               
   }
}

void resetTemps(void){
    i = 0;
    while(i <= 16){
        esperaTemps[i] = 255;
        i++;
    }
}

void itoaa3(char * temp, int num){
   //Post: escriu el valor ascii de num a tmp;
   
    temp[0] = (char)(num/1000);
    num = num - (temp[0]*1000);
    temp[1] = (char)(num /100);
    num = num - (temp[1]*100);
    temp[2] = (char) (num /10);
    num = num - (temp[2]*10);
    temp[3] = num+'0';
    temp[4] = '\0';
    temp[2]+='0';
    temp[1]+='0';
    temp[0] =' ';
}
