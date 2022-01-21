/*
 * File:   main.c (Conmutador ALFEJ SLG)
 * Author: TCB Mexico
 * Version:     4.1
 *
 * Designed by: Jorge Cervantes Alatorre
 * Checked by:  Jorge Cervantes Alatorre
 * 
 * Created on 19 de octubre de 2021, 08:53 AM
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
#include "UART.h"
#include "Interruptions.h"
#include "ControlALFEJ.h"

/* PRAGMA Settings */
#pragma config XINST = OFF      // PERMITE DEBUGEAR 
#pragma config SOSCSEL = DIG    // PUERTO C COMO DIGITAL

#pragma config MCLRE = OFF      // MASTER CLEAR
#pragma config FOSC = INTIO2    // Use Internal internal RC oscillator
#pragma config SOSCSEL = DIG    // Set RC0 and RC1 as GPIOs
#pragma config INTOSCSEL = HIGH // Set MCU to be at High-Power mode
#pragma config PWRTEN = OFF     // Power-up Timer disable

#pragma config WDTEN = SWDTDIS       // Watchdog Timer (WDT controlled by SWDTEN bit setting)°-°
#pragma config WDTPS = 256        // Watchdog Postscaler (1:8) °_°

/* MAIN FUNCTION */
void main(void){
    WDTCONbits.SWDTEN = 1;      /* enable software controlled watchdog timer*/
    
    OSCCONbits.IRCF = 0b111;    // Multiplexor for internal clock 16MHz
    OSCCONbits.SCS1 = 0;        // Default primary oscillator as HF-INTOSC with PLL
    OSCTUNEbits.PLLEN = 1;      // Enable PLL
    
    GPIO_init();                //  Pin configuration
    Timer_init ();              //  TMR0 and TMR2 configuration
    Interrupt_init();           //  Interrupt_init
    UART_init();                //  TX and RX configuration
    
    Relay_L1 = Disable;     // LED
    Relay_L2 = Disable;     // Second Line
    Relay_UPS = Disable;     // GE
    Relay_GE = Disable;     // Line CFE
    Buzzer = Set;           // Set buzzer
        
    Reset_Con = Set;        // Due to restart clear consumption 
    PIE1bits.TX1IE = Set;   // Start UART communication for energy reset

    do{
        CLRWDT();
    }while(ON);
}



