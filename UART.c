/*
 * File:   UART1.c
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
#include "UART.h"
#include "ControlALFEJ.h"

/* FUNCTIONS IMPLEMENTATION */

/*************************Description**************************/
/* The UART is working at 9600bps, at 8BITS, NO FERMING ERROR */
/* NO OVER RUN ERROR and the TX is set on RC6 and             */
/* Rx is on RC7                                               */
/* Baud Rate =  FOSC/[64 (n + 1)]                             */
/**************************************************************/
void UART_init (void)
{
    
    TXSTA1bits.CSRC = Clear;  // Clock Source Select bit don´t care
    TXSTA1bits.TX9 = Clear;   // Set 8-bit transmission
    TXSTA1bits.TXEN = Set;    // Transmit is set
    TXSTA1bits.SYNC = Clear;  // Asynchronous mode
    TXSTA1bits.SENDB = Clear; // Send Break Character bit don´t  care
    TXSTA1bits.BRGH = Clear;  // Low Baud Rate Selected
    TXSTA1bits.TRMT = Clear;  // Transmit Shift is full
    TXSTA1bits.BRGH = Clear;  // 9th bit of Transmit Data disable

    RCSTA1bits.SPEN = Set;    // Serial port is enabled
    RCSTA1bits.RX9 = Clear;   // 8-bit reception selected
    RCSTA1bits.SREN = Clear;  // Single Receive disable
    RCSTA1bits.CREN = Set;    // Continuous Receive set
    RCSTA1bits.ADDEN = Clear; // Address Detect don´t care
    RCSTA1bits.FERR = Clear;  // No framing error
    RCSTA1bits.OERR = Clear;  // No overrun error
    RCSTA1bits.RX9D = Clear;  // 9th bit of Received Data Disable

    BAUDCON1bits.BRG16 = Clear;   // 8-bit Baud Rate Generator
    SPBRG1 = 0x68;      // For Baud Rate Formula go to page 343
    
}
