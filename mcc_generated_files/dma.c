/*******************************************************************************
  DMA Generated Driver File

  Company:
    Microchip Technology Inc.

  File Name:
    dma.c

  Summary:
    This is the generated driver implementation file for the DMA driver using PIC24 / dsPIC33 / PIC32MM MCUs

  Description:
    This source file provides implementations for driver APIs for DMA.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - pic24-dspic-pic32mm : 1.75.1
        Device            :  PIC24FJ128GC006
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.35
        MPLAB             :  MPLAB X v5.05
 *******************************************************************************/

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
 */

#include <xc.h>
#include "dma.h"
#include "system.h"
#include "tmr1.h"
/**
  Prototype:        void DMA_Initialize(void)
  Input:            none
  Output:           none
  Description:      DMA_Initialize is an
                    initialization routine that takes inputs from the GUI.
  Comment:          
  Usage:            DMA_Initialize();
 */

extern int16_t allch_result[10];


extern int16_t volt_ch1[SIZE - 1];
extern int16_t volt_ch2[SIZE - 1];
extern int16_t volt_ch3[SIZE - 1];
extern int16_t volt_ch4[SIZE - 1];
extern int16_t volt_ch5[SIZE - 1];
extern int16_t volt_ch6[SIZE - 1];
extern int16_t volt_ch7[SIZE - 1];
extern int16_t volt_ch8[SIZE - 1];
extern int16_t volt_ch9[SIZE - 1];
extern int16_t volt_ch10[SIZE - 1];
extern int16_t volt_SD[SIZE - 1];
extern void DMAtoADC_calc(void);
extern void DMAtoADC_SDcalc(void);
int n = 0;


void DMA_Initialize(void) {
    // DMAEN enabled; PRSSEL Fixed priority; 
    DMACON = (0x8000 | 0x01) & 0x7FFF; //Enable DMA later
    // HADDR 65535; 
    DMAH = 0xFFFF;
    // LADDR 2048; 
    DMAL = 0x0800;

    // CHEN enabled; DAMODE Incremented; TRMODE Repeated Continuous; CHREQ enabled; RELOAD enabled; SIZE 16 bit; NULLW disabled; SAMODE Incremented; 
    DMACH0 = 0x035D & 0xFFFE; //Enable DMA Channel later;
    // HALFIF disabled; LOWIF disabled; HALFEN disabled; DONEIF disabled; OVRUNIF disabled; CHSEL Pipeline ADC; HIGHIF disabled; 
    DMAINT0 = 0x2F00;
    // SADDR 832; 
    DMASRC0 = 0x0340;
    // DADDR 8193; 
    DMADST0 = (int) allch_result; //0x2001;
    // CNT 128; 
    DMACNT0 = 10; //0x0080;
    // Clearing Channel 0 Interrupt Flag;
    IFS0bits.DMA0IF = false;
    // Enabling Channel 0 Interrupt
    IEC0bits.DMA0IE = true;

    // CHEN enabled; SAMODE Unchanged; SIZE 16 bit; DAMODE Incremented; CHREQ enabled; RELOAD enabled; TRMODE Repeated Continuous; NULLW disabled; 
    DMACH1 = 0x031D & 0xFFFE; //Enable DMA Channel later;
    // HALFIF disabled; LOWIF disabled; HALFEN disabled; DONEIF disabled; OVRUNIF disabled; HIGHIF disabled; CHSEL SD-ADC; 
    DMAINT1 = 0x3F00;
    // SADDR 1238; 
    DMASRC1 = 0x04D6;
    // DADDR 0; 
    DMADST1 = (int) volt_SD;
    // CNT 128; 
    DMACNT1 = 0x0080;
    // Clearing Channel 1 Interrupt Flag;
    IFS0bits.DMA1IF = false;
    // Enabling Channel 1 Interrupt
    IEC0bits.DMA1IE = true;

    // SAMODE Incremented; CHEN enabled; SIZE 16 bit; DAMODE Unchanged; CHREQ enabled; RELOAD disabled; NULLW disabled; TRMODE Repeated One-Shot; 
   /* DMACH2= 0x0145 & 0xFFFE; //Enable DMA Channel later;
    // HALFIF disabled; LOWIF disabled; HALFEN disabled; DONEIF disabled; OVRUNIF disabled; HIGHIF disabled; CHSEL TMR1; 
    DMAINT2= 0x3900;
    // SADDR 771; 
    DMASRC2= sintable;
    // DADDR 1090; 
    DMADST2= 0x0442;
    // CNT 125; 
    DMACNT2= 0x0001;
    // Clearing Channel 2 Interrupt Flag;
    IFS1bits.DMA2IF = false;*/

    // SAMODE Unchanged; CHEN disabled; SIZE 16 bit; DAMODE Unchanged; TRMODE One-Shot; NULLW disabled; CHREQ disabled; RELOAD disabled; 
    DMACH3 = 0x0000 & 0xFFFE; //Enable DMA Channel later;
    // HALFIF disabled; LOWIF disabled; HALFEN disabled; DONEIF disabled; OVRUNIF disabled; CHSEL None; HIGHIF disabled; 
    DMAINT3 = 0x0000;
    // SADDR 0; 
    DMASRC3 = 0x0000;
    // DADDR 0; 
    DMADST3 = 0x0000;
    // CNT 0; 
    DMACNT3 = 0x0000;
    // Clearing Channel 3 Interrupt Flag;
    IFS2bits.DMA3IF = false;

    // DAMODE Unchanged; SAMODE Unchanged; CHEN disabled; SIZE 16 bit; TRMODE One-Shot; CHREQ disabled; RELOAD disabled; NULLW disabled; 
    DMACH4 = 0x0000 & 0xFFFE; //Enable DMA Channel later;
    // HALFIF disabled; LOWIF disabled; HALFEN disabled; DONEIF disabled; OVRUNIF disabled; HIGHIF disabled; CHSEL None; 
    DMAINT4 = 0x0000;
    // SADDR 0; 
    DMASRC4 = 0x0000;
    // DADDR 0; 
    DMADST4 = 0x0000;
    // CNT 0; 
    DMACNT4 = 0x0000;
    // Clearing Channel 4 Interrupt Flag;
    IFS2bits.DMA4IF = false;

    // SIZE 16 bit; DAMODE Unchanged; CHEN disabled; SAMODE Unchanged; CHREQ disabled; RELOAD disabled; TRMODE One-Shot; NULLW disabled; 
    DMACH5 = 0x0000 & 0xFFFE; //Enable DMA Channel later;
    // CHSEL None; HALFIF disabled; LOWIF disabled; HALFEN disabled; DONEIF disabled; OVRUNIF disabled; HIGHIF disabled; 
    DMAINT5 = 0x0000;
    // SADDR 0; 
    DMASRC5 = 0x0000;
    // DADDR 0; 
    DMADST5 = 0x0000;
    // CNT 0; 
    DMACNT5 = 0x0000;
    // Clearing Channel 5 Interrupt Flag;
    IFS3bits.DMA5IF = false;

    //Enable DMA
    DMACONbits.DMAEN = 1;

    //Enable DMA Channel 0
    DMACH0bits.CHEN = 1;
    //Enable DMA Channel 1
    DMACH1bits.CHEN = 1;
    //Enable DMA Channel 2
    DMACH2bits.CHEN = 1;
     
  
    }


void __attribute__((interrupt, no_auto_psv)) _DMA0Interrupt(void) {

    volt_ch1[n] = allch_result[0];
    volt_ch2[n] = allch_result[1];
    volt_ch3[n] = allch_result[2];
    volt_ch4[n] = allch_result[3];
    volt_ch5[n] = allch_result[4];
    volt_ch6[n] = allch_result[5];
    volt_ch7[n] = allch_result[6];
    volt_ch8[n] = allch_result[7];
    volt_ch9[n] = allch_result[8];
    volt_ch10[n] = allch_result[9];

    n++;
    if (n == 128) {
        DMAtoADC_calc();
        n = 0;
        //USB_led = ~USB_led;
    }
    IFS0bits.DMA0IF = 0;
}

void __attribute__((interrupt, no_auto_psv)) _DMA1Interrupt(void) {
    DMAtoADC_SDcalc();
    IFS0bits.DMA1IF = 0;
}

void DMA_ChannelEnable(DMA_CHANNEL channel) {
    switch (channel) {
        case DMA_CHANNEL_0:
            DMACH0bits.CHEN = 1;
            break;
        case DMA_CHANNEL_1:
            DMACH1bits.CHEN = 1;
            break;
        case DMA_CHANNEL_2:
            DMACH2bits.CHEN = 1;
            break;
        case DMA_CHANNEL_3:
            DMACH3bits.CHEN = 1;
            break;
        case DMA_CHANNEL_4:
            DMACH4bits.CHEN = 1;
            break;
        case DMA_CHANNEL_5:
            DMACH5bits.CHEN = 1;
            break;
        default: break;
    }
}

void DMA_ChannelDisable(DMA_CHANNEL channel) {
    switch (channel) {
        case DMA_CHANNEL_0:
            DMACH0bits.CHEN = 0;
            break;
        case DMA_CHANNEL_1:
            DMACH1bits.CHEN = 0;
            break;
        case DMA_CHANNEL_2:
            DMACH2bits.CHEN = 0;
            break;
        case DMA_CHANNEL_3:
            DMACH3bits.CHEN = 0;
            break;
        case DMA_CHANNEL_4:
            DMACH4bits.CHEN = 0;
            break;
        case DMA_CHANNEL_5:
            DMACH5bits.CHEN = 0;
            break;
        default: break;
    }
}

void DMA_TransferCountSet(DMA_CHANNEL channel, uint16_t transferCount) {
    switch (channel) {
        case DMA_CHANNEL_0:
            DMACNT0 = transferCount;
            break;
        case DMA_CHANNEL_1:
            DMACNT1 = transferCount;
            break;
        case DMA_CHANNEL_2:
            DMACNT2 = transferCount;
            break;
        case DMA_CHANNEL_3:
            DMACNT3 = transferCount;
            break;
        case DMA_CHANNEL_4:
            DMACNT4 = transferCount;
            break;
        case DMA_CHANNEL_5:
            DMACNT5 = transferCount;
            break;
        default: break;
    }
}

uint16_t DMA_TransferCountGet(DMA_CHANNEL channel) {
    switch (channel) {
        case DMA_CHANNEL_0:
            return (DMACNT0);
        case DMA_CHANNEL_1:
            return (DMACNT1);
        case DMA_CHANNEL_2:
            return (DMACNT2);
        case DMA_CHANNEL_3:
            return (DMACNT3);
        case DMA_CHANNEL_4:
            return (DMACNT4);
        case DMA_CHANNEL_5:
            return (DMACNT5);
        default: return 0;
    }
}

void DMA_SoftwareTriggerEnable(DMA_CHANNEL channel) {
    switch (channel) {
        case DMA_CHANNEL_0:
            DMACH0bits.CHREQ = 1;
            break;
        case DMA_CHANNEL_1:
            DMACH1bits.CHREQ = 1;
            break;
        case DMA_CHANNEL_2:
            DMACH2bits.CHREQ = 1;
            break;
        case DMA_CHANNEL_3:
            DMACH3bits.CHREQ = 1;
            break;
        case DMA_CHANNEL_4:
            DMACH4bits.CHREQ = 1;
            break;
        case DMA_CHANNEL_5:
            DMACH5bits.CHREQ = 1;
            break;
        default: break;
    }
}

void DMA_SourceAddressSet(DMA_CHANNEL channel, uint16_t address) {
    switch (channel) {
        case DMA_CHANNEL_0:
            DMASRC0 = address;
            break;
        case DMA_CHANNEL_1:
            DMASRC1 = address;
            break;
        case DMA_CHANNEL_2:
            DMASRC2 = address;
            break;
        case DMA_CHANNEL_3:
            DMASRC3 = address;
            break;
        case DMA_CHANNEL_4:
            DMASRC4 = address;
            break;
        case DMA_CHANNEL_5:
            DMASRC5 = address;
            break;
        default: break;
    }
}

void DMA_DestinationAddressSet(DMA_CHANNEL channel, uint16_t address) {
    switch (channel) {
        case DMA_CHANNEL_0:
            DMADST0 = address;
            break;
        case DMA_CHANNEL_1:
            DMADST1 = address;
            break;
        case DMA_CHANNEL_2:
            DMADST2 = address;
            break;
        case DMA_CHANNEL_3:
            DMADST3 = address;
            break;
        case DMA_CHANNEL_4:
            DMADST4 = address;
            break;
        case DMA_CHANNEL_5:
            DMADST5 = address;
            break;
        default: break;
    }
}

bool DMA_IsSoftwareRequestPending(DMA_CHANNEL channel) {
    switch (channel) {
        case DMA_CHANNEL_0:
            return (DMACH0bits.CHREQ);
        case DMA_CHANNEL_1:
            return (DMACH1bits.CHREQ);
        case DMA_CHANNEL_2:
            return (DMACH2bits.CHREQ);
        case DMA_CHANNEL_3:
            return (DMACH3bits.CHREQ);
        case DMA_CHANNEL_4:
            return (DMACH4bits.CHREQ);
        case DMA_CHANNEL_5:
            return (DMACH5bits.CHREQ);
        default: return 0;
    }
}

bool DMA_IsBufferedWriteComplete(DMA_CHANNEL channel) {
    switch (channel) {
        case DMA_CHANNEL_0:
            return (DMAINT0bits.DBUFWF);
        case DMA_CHANNEL_1:
            return (DMAINT1bits.DBUFWF);
        case DMA_CHANNEL_2:
            return (DMAINT2bits.DBUFWF);
        case DMA_CHANNEL_3:
            return (DMAINT3bits.DBUFWF);
        case DMA_CHANNEL_4:
            return (DMAINT4bits.DBUFWF);
        case DMA_CHANNEL_5:
            return (DMAINT5bits.DBUFWF);
        default: return 0;
    }
}

bool DMA_IsHighAddressLimitFlagSet(DMA_CHANNEL channel) {
    switch (channel) {
        case DMA_CHANNEL_0:
            return (DMAINT0bits.HIGHIF);
        case DMA_CHANNEL_1:
            return (DMAINT1bits.HIGHIF);
        case DMA_CHANNEL_2:
            return (DMAINT2bits.HIGHIF);
        case DMA_CHANNEL_3:
            return (DMAINT3bits.HIGHIF);
        case DMA_CHANNEL_4:
            return (DMAINT4bits.HIGHIF);
        case DMA_CHANNEL_5:
            return (DMAINT5bits.HIGHIF);
        default: return 0;
    }
}

bool DMA_IsLowAddressLimitFlagSet(DMA_CHANNEL channel) {
    switch (channel) {
        case DMA_CHANNEL_0:
            return (DMAINT0bits.LOWIF);
        case DMA_CHANNEL_1:
            return (DMAINT1bits.LOWIF);
        case DMA_CHANNEL_2:
            return (DMAINT2bits.LOWIF);
        case DMA_CHANNEL_3:
            return (DMAINT3bits.LOWIF);
        case DMA_CHANNEL_4:
            return (DMAINT4bits.LOWIF);
        case DMA_CHANNEL_5:
            return (DMAINT5bits.LOWIF);
        default: return 0;
    }
}

bool DMA_IsOperationDone(DMA_CHANNEL channel) {
    switch (channel) {
        case DMA_CHANNEL_0:
            return (DMAINT0bits.DONEIF);
        case DMA_CHANNEL_1:
            return (DMAINT1bits.DONEIF);
        case DMA_CHANNEL_2:
            return (DMAINT2bits.DONEIF);
        case DMA_CHANNEL_3:
            return (DMAINT3bits.DONEIF);
        case DMA_CHANNEL_4:
            return (DMAINT4bits.DONEIF);
        case DMA_CHANNEL_5:
            return (DMAINT5bits.DONEIF);
        default: return 0;
    }
}

bool DMA_IsOverrunFlagSet(DMA_CHANNEL channel) {
    switch (channel) {
        case DMA_CHANNEL_0:
            return (DMAINT0bits.OVRUNIF);
        case DMA_CHANNEL_1:
            return (DMAINT1bits.OVRUNIF);
        case DMA_CHANNEL_2:
            return (DMAINT2bits.OVRUNIF);
        case DMA_CHANNEL_3:
            return (DMAINT3bits.OVRUNIF);
        case DMA_CHANNEL_4:
            return (DMAINT4bits.OVRUNIF);
        case DMA_CHANNEL_5:
            return (DMAINT5bits.OVRUNIF);
        default: return 0;
    }
}

bool DMA_IsOperationHalfComplete(DMA_CHANNEL channel) {
    switch (channel) {
        case DMA_CHANNEL_0:
            return (DMAINT0bits.HALFIF);
        case DMA_CHANNEL_1:
            return (DMAINT1bits.HALFIF);
        case DMA_CHANNEL_2:
            return (DMAINT2bits.HALFIF);
        case DMA_CHANNEL_3:
            return (DMAINT3bits.HALFIF);
        case DMA_CHANNEL_4:
            return (DMAINT4bits.HALFIF);
        case DMA_CHANNEL_5:
            return (DMAINT5bits.HALFIF);
        default: return 0;
    }
}
