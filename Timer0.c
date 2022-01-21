/*
 * File:   Timer0.c
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
#include "Timers.h"
#include "ControlALFEJ.h"



/* FUNCTIONS IMPLEMENTATION */

/*************************Description**************************/
/* Timer 0 is set on a 16 bits mode, also is configurated to  */
/* make a interruption every .25 secund, to achieve this it is*/
/* set the Timer0 with the next features                      */
/* FlagInt = (4/FresOsc)*Preescaler(65534-(TMROH:TMROL))      */
/* FresOsc = 64MHz                                            */
/* Preescaler = 256                                           */
/* TMROH:TMROL = 49909                                         */
/**************************************************************/

void Timer_init(void){
    
    TMR0H = Timer0_Int_Count << 8;  // TMR0H 255; 
    TMR0L = Timer0_Int_Count;       // TMR0L 121; 
    T0CON = 0x97;                   // T0PS 1:256; T08BIT 16-bit; T0SE Increment_hi_lo; T0CS FOSC/4; TMR0ON enabled; PSA assigned; 
    
    T0CONbits.T08BIT = Clear;          // Set Timer0 as 16bits mode
    T0CONbits.T0CS = Clear;            // Working with the internal clock
    T0CONbits.T0SE = Set;              // Increment on high-to-low transition on T0CKI pin
    T0CONbits.PSA = Clear;             // Timer0 prescaler is assigned
    T0CONbits.T0PS = Timer0_Prescale;  // Prescaler
    T0CONbits.TMR0ON = Set;            // Enables Timer0
}
