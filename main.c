/* 
 * File:   main.c
 * Author: andrey
 *
 * Created on 30 ?????? 2013, 9:31
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <xc.h>

#include "globals.h"
#include "MainLibrary.h"
#include "Timer.h"
#include "Spi.h"
#include "FRAM.h"
#include "Fat.h"
#include "Can.h"
#include "CanOpen.h"
#include "WriteParameters.h"
#include "PathComands.h"
#include "InOutSignals.h"
#include "ADC.h"

// FOSC
#pragma config FOSFPR = XT_PLL16             // Oscillator (XT)
#pragma config FCKSMEN = CSW_FSCM_OFF   // Clock Switching and Monitor (Sw Disabled, Mon Disabled)

// FWDT
#pragma config FWPSB = WDTPSB_16        // WDT Prescaler B (1:16)
#pragma config FWPSA = WDTPSA_512      // WDT Prescaler A (1:512)
#pragma config WDT = WDT_ON            // Watchdog Timer (Disabled)

// FBORPOR
#pragma config FPWRT = PWRT_64          // POR Timer Value (64ms)
#pragma config BODENV = BORV_45            // Brown Out Voltage (4.5)
#pragma config BOREN = PBOR_OFF         // PBOR Enable (Disable)
#pragma config MCLRE = MCLR_EN         // Master Clear Enable (Enable)

// FBS
#pragma config BWRP = WR_PROTECT_BOOT_OFF// Boot Segment Program Memory Write Protect (Boot Segment Program Memory may be written)
#pragma config BSS = NO_BOOT_CODE       // Boot Segment Program Flash Memory Code Protection (No Boot Segment)
#pragma config EBS = NO_BOOT_EEPROM     // Boot Segment Data EEPROM Protection (No Boot EEPROM)
#pragma config RBS = NO_BOOT_RAM        // Boot Segment Data RAM Protection (No Boot RAM)

// FSS
#pragma config SWRP = WR_PROT_SEC_OFF   // Secure Segment Program Write Protect (Disabled)
#pragma config SSS = NO_SEC_CODE        // Secure Segment Program Flash Memory Code Protection (No Secure Segment)
#pragma config ESS = NO_SEC_EEPROM      // Secure Segment Data EEPROM Protection (No Segment Data EEPROM)
#pragma config RSS = NO_SEC_RAM         // Secure Segment Data RAM Protection (No Secure RAM)

// FGS
#pragma config GWRP = GWRP_OFF          // General Code Segment Write Protect (Disabled)
#pragma config GCP = GSS_OFF            // General Segment Code Protection (Disabled)

// FICD
#pragma config ICS = ICS_PGD            // Comm Channel Select (Use PGC/EMUC and PGD/EMUD)

//global vars
extern int _nodeId;

unsigned int maj_i = 0;

//clear WDT timer
void __attribute__((__interrupt__, __auto_psv__)) _T1Interrupt(void);
//write to can bus
void __attribute__((__interrupt__, __auto_psv__)) _T2Interrupt(void);
//write to can queue
void __attribute__((__interrupt__, __auto_psv__)) _T4Interrupt(void);
// Can1 Receive Parameter
void __attribute__ ((__interrupt__, __auto_psv__)) _C1Interrupt (void);
// Can2 Receive Parameter
void __attribute__ ((__interrupt__, __auto_psv__)) _C2Interrupt (void);

int main(int argc, char** argv) {
    ClrWdt();
    //StartTimer1();// start timer for WDT clearing
    InitADC();
    FramInitialization();
    WriteAllParameters();
    ReadConfig();//read global vars from FRAM
    Can1Initialization();
    Can2Initialization();
    StartTimer2();
    StartTimer4();
    TurnOnRelay();

    while(1)
    {
        ClrWdt();
        delay(1000000);
    }
    return (EXIT_SUCCESS);
}
void __attribute__((__interrupt__, __auto_psv__)) _T1Interrupt(void)
{
    // Clear Timer 1 interrupt flag
    _T1IF = 0;
    
}
void __attribute__((__interrupt__, __auto_psv__)) _T2Interrupt(void)
{
    // Clear Timer 2 interrupt flag
    _T2IF = 0;
    Can1Execute();
    Can2Execute();
}
void __attribute__((__interrupt__, __auto_psv__)) _T4Interrupt(void)
{
    // Clear Timer 4 interrupt flag
    // Write to can bus
    _T4IF = 0;
     //TurnOnOrOffRelay(GetPathComandsDown());
    char relayData[8] = {0,0,0,0,0,0,0,0};
    relayData[0] = ~ReadInSignals();
    relayData[1] = ~ReadOutSignals();
    relayData[2] = GetPathComandsUpDown();
    relayData[3] = GetPathComandsUpDown();
    relayData[4] = GetAnalogSignal(0);
    relayData[5] = GetAnalogSignal(1);
    relayData[6] = GetAnalogSignal(2);
    relayData[7] = GetAnalogSignal(3);
    unsigned int sId;
    sId = 0x480;
    sId += _nodeId;
    Can1SendData(sId, relayData, 2);
    //Can2SendData(sId, relayData, 1);
   // CanOpenSendCurrentObjectState(50000,800000,5000,0);
}
void __attribute__ ((__interrupt__, __auto_psv__)) _C1Interrupt (void){
    IFS1bits.C1IF = 0; //Clear CAN1 interrupt flag
    C1INTFbits.RX0IF = 0; //Clear CAN1 RX interrupt flag
    C1INTFbits.RX1IF = 0; //Clear CAN1 RX interrupt flag
    char rxData[8];
    if(C1CTRLbits.ICODE == 7) //check filters
    {
        C1INTFbits.WAKIF = 0;
        return;
    }
    unsigned int sId = C1RX0SIDbits.SID;
    Can1ReceiveData(rxData);
    if(sId == 0x600 + _nodeId)
        CanOpenParseRSDO(sId, rxData, 1); //parse RSDO message and send response
    ParseTPDO1(sId, rxData);//parse TPDO message
    maj_i++;
    if(maj_i == 18)
    {
         Majorization();
         maj_i = 0;
    }
    C1RX0CONbits.RXFUL = 0;
    C1RX1CONbits.RXFUL = 0;
  }
void __attribute__ ((__interrupt__, __auto_psv__)) _C2Interrupt (void){
    IFS2bits.C2IF = 0; //Clear CAN2 interrupt flag
    C2INTFbits.RX0IF = 0; //Clear CAN2 RX interrupt flag
    C2INTFbits.RX1IF = 0; //Clear CAN2 RX interrupt flag
    char rxData[8];
    if(C2CTRLbits.ICODE == 7) //check filters
    {
        C2INTFbits.WAKIF = 0;
        return;
    }
    unsigned int sId = C2RX0SIDbits.SID;
    Can2ReceiveData(rxData);
    if(sId == 0x600 + _nodeId)
        CanOpenParseRSDO(sId, rxData, 2); //parse RSDO message and send response
    C2RX0CONbits.RXFUL = 0;
    C2RX1CONbits.RXFUL = 0;
  }
