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
 * File:                GPIO.h
 * Author:              TCB Mexico
 * Comments:            Rev. 2.0
 * Revision history:    20/10/2021
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
//#ifndef XC_HEADER_TEMPLATE_H
//#define	XC_HEADER_TEMPLATE_H

/* General INCLUDES */
#include <stdio.h>
#include <stdlib.h>
#include "pic18f25k80.h"


/* Project's INCLUDES */

/*********************General Definitions**********************/
#define Relay_L1 LATA0   // Output enable for the relay control Line 1
#define Relay_L2 LATA1   // Output enable for the relay control Line 2
#define Relay_UPS LATA2   // Output enable for the relay control Line 3
#define Relay_GE LATA3   // Output enable for the relay control Line 4

#define RA5_Pwr_Ctl RA5  // Free for UPS use.
#define RA6_Pwr_Ctl RA6  // Free for UPS use.
#define RA7_Pwr_Ctl RA7  // Free for UPS use.

#define EN_GE1  LATC5   // Enable mux for UART Comunication
#define EN_GE2  LATC4   // Enable mux for UART Comunication
#define EN_L1_2  LATB3   // Enable mux for UART Comunication
#define EN_L2_1  LATB4   // Enable mux for UART Comunication
#define EN_L1_1  LATB5   // Enable mux for UART Comunication
#define EN_L2_2  LATB2   // Enable mux for UART Comunication

#define Button RB0       // Button control input
#define Buzzer LATC2     // Buzzer output control
#define Free_RC0 RC1     // Free pin

/**************************************************************/
/*********************** Variables ****************************/
/**************************************************************/

void GPIO_init(void);   //  Pin configuration


//#endif	/* XC_HEADER_TEMPLATE_H */

