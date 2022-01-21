/*
 * File:   High_Priority_Interruption.c
 * Author: Ing. Jorge Cervantes
 *
 * Created on October 20, 2021, 9:19 AM
 *
 * Copyright 2020, Tecnologías Cervantes Baez, (TCB México)
 * All rights reserved.
 * 
 * This software is developed by TCB México.
 * 
 * Redistribution and use in source and binary forms, with or without modification, are
 * permitted provided that the following conditions are met:
 * 
 *     1. Redistributions of source code must retain the above copyright notice, this list of
 *        conditions and the following disclaimer.
 * 
 *     2. Redistributions in binary form must reproduce the above copyright notice, this list
 *        of conditions and the following disclaimer in the documentation and/or other
 *        materials provided with the distribution.
 * 
 *     3. TCB México name may not be used to endorse or promote products derived from this
 *        software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY TCB México "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL TCB México BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING BUT NOT LIMITED TO
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWSOEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* General INCLUDES */
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "pic18f25k80.h"

/* Project's INCLUDES */
#include "GPIO.h"
#include "Timers.h"
#include "Interruptions.h"
#include "ControlALFEJ.h"


/* FUNCTIONS IMPLEMENTATION */

/*************************Description**************************/
/* Initializated all the interruption tha the projet required */                                               
/**************************************************************/

void Interrupt_init(void)
{
    IPEN = Set;   //Interrupt Priority Enable bit = ON          
    GIEH = Set;   //Enables all high-priority interrupts
    GIEL = Set;   //Enables all low-priority peripheral interrupts
    
    /*Timer0*/
    TMR0IE = Set; // Enable the interruption for Timer0
    TMR0IP = Low; // Set timer 0 to low priority

    /*Int Pin*/
    INT0IF = Clear; // Cleared the flag from Pin
    INT0IE = Set;   // Enable the interruption for RB0
    INTEDG0 = Clear;// Interruption when there is a falling edge
    
    /*UART*/
    PIE1bits.TX1IE = Clear;  // Disable the interruption for Tx UART 
    TX1IP = Set;             // Set Tx to low priority
    PIE1bits.RC1IE = Set;    // Enable the interruption for Rx UART
    RC1IP = Set;             // Set Rx to High priority
}

__interrupt(low_priority) void ISC_Low(void){                                                                                                   
    if((TMR0IF == Enable)&&(TMR0IE == Enable)){ // Time interruption
        if(MilisegundosCounter++ < OneSeg){
            if((dataRecive == vlength) || (dataRecive == RElength)){
                if(Reset_Con == Set){
                    if(values[Modulo][3] == Reset_Energy[2] && values[Modulo][4] == Reset_Energy[3]){
                        Reset_Con = Clear;
                    }
                }
                else{
                    if(dataRecive == vlength){
                        //Read Sensors
                        voltage1[Modulo] = (unsigned int)(values[Modulo][4] << 8 | values[Modulo][5]) / 10;
                        current1[Modulo] = (unsigned int)(values[Modulo][6] << 8 | values[Modulo][7]);/* | 
                            values[Modulo][8] << 24 | (unsigned int)values[Modulo][9] << 16) / 1000;*/
                        power1[Modulo] = (unsigned int)(values[Modulo][10] << 8 | values[Modulo][11] | 
                           values[Modulo][12] << 24 | values[Modulo][13] << 16) / 10;
                        energy1[Modulo] = (unsigned int)(values[Modulo][14] << 8 | values[Modulo][15]);/* | 
                            values[Modulo][16] << 24 | (unsigned int)values[Modulo][17] << 16) / 1000; */
                        frequency1[Modulo] = (unsigned int)(values[Modulo][18] << 8 | values[Modulo][19]) / 10;
                        PF1[Modulo] = (unsigned int)(values[Modulo][20] << 8 | values[Modulo][21]) / 100;
                            alarm1[Modulo] = (unsigned int)(values[Modulo][22] << 8 | values[Modulo][23]);
                    }
                }

            }
            else{
                dataRecive = Clear;
                PIE1bits.TX1IE = Set;
            }
        }
        else{          
            /*if(++Modulo > module4){ //Para cuando hay más módulos; en MCL sólo hay 1
                Modulo = module1;
            }*/
            
            /////FUENTE 1
            if((conditionA && !conditionC && conditionB && conditionD && (conditionF || !conditionE)) || (conditionA && !conditionC && (!conditionD || !conditionB))){
                
                /*RESET CUANDO LA PLANTA FUE LA ACCION PASADA*/
                if(isGenLast){
                    Reset_Con = Set;
                    isGenLast = 0;
                }
                
               Buzzer = OFF;
               Relay_L2 = Disable;        // Second Line
               Relay_UPS = Disable;        // GE
               Relay_GE = Disable;        // Free
               for(unsigned int i = 0; i <= 1; i++){
                   asm("nop");
               }
               Relay_L1 = Set;        // CFE
               Buzzer = OFF;
           }
            
            /////FUENTE 2
           if(conditionA && conditionB && !conditionC && conditionD && conditionE && !conditionF){
               Buzzer = OFF;
               Relay_UPS = Disable;        // GE
               Relay_GE = Disable;        // Line CFE
               Relay_L1 = Disable;        // LED
               
               isFuente2Last = 1;
               
               if(isGenLast){
                   for(unsigned int i = 0; i <= WaitSwitchingTime; i++){
                        asm("nop");asm("nop");
                    }
                   isGenLast = 0;
               }
               
               for(unsigned int i = 0; i <= 1; i++){
                   asm("nop");
               }
               Relay_L2 = Set;        // Second Line
               Buzzer = OFF;
           }
            
           /////PLANTA DE LUZ
           if(!conditionA || conditionC){
               if(!conditionA){//Activar variable de isGenLast cuando la planta sea la última y no haya luz
                    isGenLast = 1;
               }
               if(isFuente2Last){
                   for(unsigned int i = 0; i <= WaitSwitchingTime; i++){
                        asm("nop");asm("nop");
                    }
                   isFuente2Last = 0;
               }
               
               Relay_L1 = Disable;        // LED
               Relay_L2 = Disable;        // Second Line
               Relay_GE = Disable;        // Line CFE
               for(unsigned int i = 0; i <= 1; i++){
                   asm("nop");
               }
               Relay_UPS = Set;        // GE
               Buzzer = Set;
            }
            
            if(Hrs24++ >= FullDay){
                Reset_Con = Set;
            }
            
            PIE1bits.TX1IE = Set;
            MilisegundosCounter = Clear;
        }
        
        
        INTCONbits.TMR0IF = Disable;                // Clear the TMR0 interrupt flag         
        TMR0H = timer0ReloadVal >> 8;               // Reload TMR0
        TMR0L = (unsigned int) timer0ReloadVal;     // Reload TMR0  
    }
} 

__interrupt(high_priority) void ISC_High(void){

    if(!RCONbits.TO){            // check for WDT reset occurrence 
        Buzzer = ON;
        for(unsigned long i = 0; i <= WaitSwitchingTime; i++){asm("nop");}
        Buzzer = OFF;
        for(unsigned long i = 0; i <= WaitSwitchingTime; i++){asm("nop");}
        Buzzer = ON;
        for(unsigned long i = 0; i <= WaitSwitchingTime; i++){asm("nop");}
        Buzzer = OFF;
        for(unsigned long i = 0; i <= WaitSwitchingTime; i++){asm("nop");}
        Relay_L1 = Disable;        // LED
        Relay_L2 = Disable;        // Second Line
        Relay_UPS = Disable;        // GE
        Relay_GE = Disable;        // Line CFE
        Buzzer = ON;
        for(unsigned long i = 0; i <= WaitSwitchingTime; i++){asm("nop");}
        Buzzer = OFF;
        for(unsigned long i = 0; i <= WaitSwitchingTime; i++){asm("nop");}
    }
    
    if( PIR1bits.RCIF && PIE1bits.RC1IE ){     //Interrupcion de Entrada Serial
        values[Modulo][++dataRecive] = RCREG1;
        PIR1bits.RCIF = Clear;
    }
    
    if( PIR1bits.TX1IF && PIE1bits.TX1IE ){   //Interrupcion de Salida Serial
        
        if(Modulo == module1){
            EN_L2_1 = Clear;
            EN_L1_2 = Clear;
            EN_GE1 = Clear;
            EN_L1_1 = Set;
        }
        if(Modulo == module2){
            EN_L1_1 = Clear;
            EN_L2_1 = Clear;
            EN_GE1 = Clear;
            EN_L1_2 = Set;
        }
        if(Modulo == module3){
            EN_L1_1 = Clear;
            EN_L2_1 = Clear;
            EN_L1_2 = Clear;
            EN_GE1 = Set;
        }
        if(Modulo == module4){
            EN_L1_2 = Clear;
            EN_L1_1 = Clear;
            EN_GE1 = Clear;
            EN_L2_1 = Set;
        }
        
        if(Reset_Con == Set){
            EN_L2_1 = Clear;
            EN_L1_2 = Clear;
            EN_GE1 = Clear;
            EN_L1_1 = Set;
            Hrs24 = Clear;
            
            for(unsigned char count = 0; count < RElength; count++){
                TXREG1 = Reset_Energy[count];
                do{}while(!TXSTA1bits.TRMT);
            }
        }
        else{
            for(unsigned char i = Clear; i <= vlength; i++){
                values[Modulo][i]    = Clear;
            }
            voltage1[Modulo]    = Clear;
            current1[Modulo]    = Clear;
            power1[Modulo]      = Clear;
            energy1[Modulo]     = Clear; 
            frequency1[Modulo]  = Clear;
            PF1[Modulo]         = Clear;
            alarm1[Modulo]      = Clear;

            for(unsigned char count = Clear; count < mlength; count++){
                TXREG1 = measure[count];
                do{}while(TXSTA1bits.TRMT == Clear); 
            }
            asm("nop");
        }
        PIE1bits.TX1IE = Clear;
        PIR1bits.TX1IF = Clear;
        PIR1bits.RCIF = Clear;
    }
    
    if( INT0IE && INT0IF ){                   //Control Button
        Buzzer = ON;
        for(unsigned long i = 0; i <= WaitSwitchingTime; i++){asm("nop");}
        Buzzer = OFF;
        for(unsigned long i = 0; i <= WaitSwitchingTime; i++){asm("nop");}
        Buzzer = ON;
        for(unsigned long i = 0; i <= WaitSwitchingTime; i++){asm("nop");}
        Buzzer = OFF;
        for(unsigned long i = 0; i <= WaitSwitchingTime; i++){asm("nop");}
        Relay_L1 = Disable;        // LED
        Relay_L2 = Disable;        // Second Line
        Relay_UPS = Disable;        // GE
        Relay_GE = Disable;        // Line CFE
        Buzzer = ON;
        for(unsigned long i = 0; i <= WaitSwitchingTime; i++){asm("nop");}
        Buzzer = OFF;
        for(unsigned long i = 0; i <= WaitSwitchingTime; i++){asm("nop");}

        asm("reset");
        INT0IF = 0;
    }
}

