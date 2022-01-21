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
 * File:   ControlALFEJ
 * Author: TCB Mexico
 * Comments: Rev. 2.0
 * Revision history: 20/10/2021
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
//#ifndef XC_HEADER_TEMPLATE_H
//#define XC_HEADER_TEMPLATE_H

/******************************************************************************/
/* #include <> */
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
//#include "pic18f25k80"
/******************************************************************************/

/******************************************************************************/
/* Definitions */
#define Input 1         // Pin configuration
#define Output 0        // Pin configuration
#define ON 1            // Set logic High
#define OFF 0           // Set logic Low
#define Enable 1        // Set 1
#define Disable 0       // Set 0
#define Clear 0         // Set 0
#define Set 1           // Set 1
#define Low 0           // Set 0
#define High 1          // Set 1

#define MaxEnergyConsumption 0x0A    // Control of consumption is set to -> 1KWh
#define FullDay 65854                // Day = 86400 segs. Day+delay = 86100  //error - 1.312s per module. 65854 counts per 24hours.
#define WaitSwitchingTime 0xD055     // Wait switching time for conmutation 
#define OneSeg 4                     // Tries for reciving request
                        

#define module1 0   //Line 1 fase 1 module
#define module2 1   //Line 1 fase 2 module
#define module3 2   //Line 2 fase 1 module
#define module4 3   //Line 2 fase 2 module
#define module5 4   //Electric Generator fase 1 module
#define module6 5   //Electric Generator fase 2 module

#define mlength 8   // Maximum length of values sent for status request
#define RElength 4  // Maximum length of values sent for consumption reset
#define vlength 25  // Length of values received from status request
#define maxmodule 4 // Maximum number of modules
//MCL : 107 - 146
#define conditionA      ((voltage1[0] < 150 && voltage1[0] > 100) && (frequency1[0] > 48 && frequency1[0] < 72))    // Tolerance up to 20%
#define conditionB      1                                                                                          // Tolerance up to 20%
#define conditionC      0                                                                                          // Tolerance up to 20%
#define conditionD      (energy1[0] >= MaxEnergyConsumption)                                                        // Consumption condition
#define conditionE      (Hrs24 < FullDay)                                                                           // Daly status
#define conditionF      (Hrs24 >= FullDay)                                                                          // Daly status

/******************************************************************************/

/******************************************************************************/
/* Variables */
const unsigned char measure[mlength] = {0xF8, 0x04, 0x00, 0x00, 0x00, 0x0A, 0x64, 0x64};  // Command for measurement result 
const unsigned char Reset_Energy[RElength] = {0xF8, 0x42, 0xC2, 0x41};                    // Command for reset energy

unsigned char values[maxmodule][vlength];   // Array for data received
unsigned char dataRecive = 0;               // Data counter received
unsigned char Modulo = 0;                   // Module counter
unsigned char Reset_Con = 0;                // Reset consumption request
unsigned char MilisegundosCounter = 0;      // Counter for compleat a Seg.

unsigned int voltage1[maxmodule];   // Voltage array
unsigned int current1[maxmodule];   // Current array
unsigned int power1[maxmodule];     // Power array
unsigned int energy1[maxmodule];    // Energy array
unsigned int frequency1[maxmodule]; // Frequency array
unsigned int alarm1[maxmodule];     // Alarm Array
unsigned int PF1[maxmodule];        // Power factor array

unsigned long Hrs24 = 0;    // Seconds counter 

unsigned char isGenLast = 0, isFuente2Last = 0, isCFELast = 0;
/******************************************************************************/

/******************************************************************************/
/* Funtions */

//#endif  /* XC_HEADER_TEMPLATE_H */
