/*
 * File:   GPIO.c
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

/* Project's INCLUDES */
#include "GPIO.h"
#include "ControlALFEJ.h"



/* FUNCTIONS IMPLEMENTATION */
void GPIO_init(void)
{
        /*PORT A configuration*/
    TRISA0 = Output;           // Set RA0 to GPIO output for control of the pin
    Relay_L1 = Low;        // Pin is set to low for int configuration avoiding accidents
            ANSEL0 = Disable;  // Disable the analog configuration for PTB0
    
    TRISA1 = Output;           // Set RA1 to GPIO output for control of the pin
        Relay_L2 = Low;        // Pin is set to low for int configuration avoiding accidents
            ANSEL1 = Disable;  // Disable the analog configuration for PTB0
    
    TRISA2 = Output;           // Set RA2 to GPIO output for control of the pin
        RA2 = Low;             // Pin is set to low for int configuration avoiding accidents
            ANSEL2 = Disable;  // Disable the analog configuration for PTB0
    
    TRISA3 = Output;           // Set RA3 to GPIO output for control of the pin
        RA3 = Low;             // Pin is set to low for int configuration avoiding accidents
            ANSEL3 = Disable;  // Disable the analog configuration for PTB0
    
    TRISA5 = Input;            // Set RA5 to GPIO input for control of the pin. HLVDIN
    
    TRISA6 = Output;           // Set RA6 to GPIO output for control of the pin. FREE
        RA6_Pwr_Ctl = Low;     // Pin is set to low for int configuration avoiding accidents
    
    TRISA7 = Output;           // Set RA7 to GPIO output for control of the pin. FREE
        RA7_Pwr_Ctl = Low;     // Pin is set to low for int configuration avoiding accidents
    
    /*PORT B configuration*/
    TRISB0 = Input;            // Set RB0 to GPIO input for control of the pin. Button 1
        ANSEL10 = Low;         // Disable the analog configuration for PTB0
    
    TRISB1 = Input;            //Free
            ANSEL8 = Low;      // Disable the analog configuration for PTB0
    
    TRISB2 = Output;           // Enable L2.2        // Pin is set to low for int configuration avoiding accidents
        EN_L2_2 = Low;
        
    TRISB3 = Output;           // Enable L1.2
        EN_L1_2 = Low;         // Pin is set to low for int configuration avoiding accidents
    
    TRISB4 = Output;           // Enable L2.1
        EN_L2_1 = Low;         // Pin is set to low for int configuration avoiding accidents
            ANSEL9 = Disable;  // Disable the analog configuration for PTB0
            
    //TRISB6 = INPUT;          // Pickit
    //TRISB7 = INPUT;          // Pickit
    
    /*PORT C configuration*/
    TRISC0 = Output;           // Free
        Free_RC0 = Low;
    TRISC1 = Input;            // Free
    
    TRISC2 = Output;           // Buzzer
        Buzzer = Low;            // Pin is set to low for int configuration avoiding accidents
    
    TRISC3 = Input;            // Free
    
    TRISC4 = Output;           // Enable Generator 2
        RC4 = Low;             // Pin is set to low for int configuration avoiding accidents
    
    TRISC5 = Output;           // Enable Generator 1
        EN_GE1 = Low;              // Pin is set to low for int configuration avoiding accidents
    
    TRISB5 = Output;           // Enable L1.1
    EN_L1_1 = Low;         // Pin is set to low for int configuration avoiding accidents
    
    TRISC4 = Output;
    EN_GE2 = Low;
    
    TRISC6 = Output;           // Free (Tx UART)
    TRISC7 = Input;            // Free (Rx UART) 
}

