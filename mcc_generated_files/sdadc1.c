/*******************************************************************************
  SDADC1 Generated Driver File

  Company:
    Microchip Technology Inc.

  File Name:
    sdadc1.c

  Summary:
    This is the generated driver implementation file for the SDADC1 driver using PIC24 / dsPIC33 / PIC32MM MCUs

  Description:
    This source file provides implementations for driver APIs for SDADC1.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - pic24-dspic-pic32mm : 1.75.1
        Device            :  PIC24FJ128GC006
        Version           :  1.0
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

/**
  Section: Included Files
*/
#include <xc.h>
#include "sdadc1.h"

/**
  Section: Data Type Definitions
*/
#define SDADC1_WAIT_COUNT               (0x8)
#define SDADC1_EXPECTED_MAX_VALUE       (0x7FFF)
#define SDADC1_RESULT_ROUNDING          (0x2)
#define SDADC1_CHOPPING_ENABLED         (0x3)
#define SDADC1_CALIBRATION_CHANNEL      (0x3)

/**
  Section: Local data definition
*/
/* SD ADC Driver Offset Value

  @Summary
    Stores the Offset value computed during calibration.

  @Description
    This data variable stores the offset value during calibration.
	After conversion, this offset value will be used to apply offset correction.

 */
static int16_t sdadc1_offset;
/* SD ADC Driver Gain Value

  @Summary
    Stores the Gain value computed during calibration.

  @Description
    This data variable stores the gain value during calibration.
	After conversion, this gain value will be used to apply gain correction.

 */
static double sdadc1_gain;

/**
  Section: Local Function Declarations
*/
static void SDADC1_Calibrate(void);
static void SDADC1_WaitForSettling(void);

/**
  Section: Driver Interface
*/
void SDADC1_Initialize(void)
{
    // Load the Register values, while SD ADC is disabled.
    // SDGAIN 1; PWRLVL Normal; DITHER No dither; SDRST disabled; VOSCAL Normal operation; SDON enabled; SDREFP SVDD; SDSIDL disabled; SDREFN SVSS; 
    SD1CON1 = 0x8000 & 0x7FFF; // Enable SD ADC later
    // RNDRES Round result to 16 bits; SDWM Every interrupt; SDRDY enabled; CHOP enabled; SDINT Every sample; 
    SD1CON2 = 0xF111;
    // SDCH Single-ended Channel 1; SDDIV 16; SDCS FOSC/2; SDOSR 1024; 
    SD1CON3 = 0x8002;

    // Perform SD ADC Calibration.
	// Note: Calibration may update the register values.
    SDADC1_Calibrate();

    // After calibration, Re-Load the Register values, while SD ADC is disabled.
    SD1CON1 = 0x8000 & 0x7FFF; // Enable SD ADC later
    SD1CON2 = 0xF111;
    SD1CON3 = 0x8002;

    // Enable the SD ADC.
    SD1CON1bits.SDON = 1;  

    // Wait for ADC Settling.
    SDADC1_WaitForSettling();
}

void SDADC1_ChannelSelect(SDADC1_CHANNEL eChannel)
{
    // Select given channel for the measurement.
    SD1CON3bits.SDCH = eChannel;
    // Wait for ADC Settling.
    SDADC1_WaitForSettling();
}

bool SDADC1_IsConversionComplete(void)
{
    // Check the interrupt flag. If it is set, the result is available.
    if(1 == IFS6bits.SDA1IF){
        return true;
    }else{
        return false;
    }
}

int16_t SDADC1_ConversionRawResultGet(void)
{
    int16_t channelValue;
    // If the result is readily available, there will be no blocking.
    // Else, there will be blocking period till a new result is available.
    while (0 == IFS6bits.SDA1IF); //Wait until hardware says we have a result ready.
    channelValue = (int16_t)SD1RESH;
    // Clear interrupt flag
    IFS6bits.SDA1IF = 0;
    return channelValue;
}

int16_t SDADC1_ConversionResultGet(void)
{
   // double calibratedResult;
    int16_t calibratedResult;
    int16_t channelValue = SDADC1_ConversionRawResultGet();
    // Correct offset.
    channelValue -= sdadc1_offset;
    // Correct gain.
    calibratedResult = sdadc1_gain*channelValue;
    //calibratedResult = calibratedResult * 0.0000503 * 2; 
    return calibratedResult;
}

/**
  Section: Local Function Definition
*/
static void SDADC1_Calibrate(void) {
    int16_t maxValue;
    double expectedMaxValue = SDADC1_EXPECTED_MAX_VALUE;

    // ADC initialization for calibration.
    SD1CON1bits.PWRLVL = 0; // Low power, normal bandwidth
    SD1CON1bits.SDREFP = 0; // Positive Voltage Reference is SVDD
    SD1CON1bits.SDREFN = 0; // Negative Voltage Reference is SVSS
    SD1CON1bits.VOSCAL = 1; // Internal Offset Measurement Enable
    SD1CON1bits.DITHER = 1; // Low Dither
    SD1CON1bits.SDGAIN = 0; // Gain is 1:1
    SD1CON2bits.SDWM = 1; // SDxRESH/SDxRESL updated on every Interrupt
    SD1CON2bits.SDINT = 3; // Interrupt on every data output
    SD1CON2bits.RNDRES = SDADC1_RESULT_ROUNDING; // Result Rounding to 16-bit.
    SD1CON2bits.CHOP = SDADC1_CHOPPING_ENABLED; // Chopping enabled.
    SD1CON3bits.SDCH = 0; // Default Channel - Will be ignored for offset calculation.
    SD1CON3bits.SDOSR = 0; // Oversampling Ratio (OSR) is 1024 (best quality)
    // Enable ADC.
    SD1CON1bits.SDON = 1;
    // Wait for ADC Settling.
    SDADC1_WaitForSettling();

    // Save the initial VOSCAL offset value from the ADC.
    // This value will be used to correct the offset error for all
    // subsequent ADC measurements.
    sdadc1_offset = (int16_t) SD1RESH;
    // Configure ADC for normal operation.
    SD1CON1bits.VOSCAL = 0;
    // Measures the reference selected by SDREFP/SDREFN for calibration.
    SD1CON3bits.SDCH = SDADC1_CALIBRATION_CHANNEL;
    // Wait for ADC Settling.
    SDADC1_WaitForSettling();

    // Save the maximum value to calculate the gain.
    maxValue = (int16_t) SD1RESH;
    // Calculate gain.
    sdadc1_gain = expectedMaxValue / ((double) (maxValue - sdadc1_offset)); //GLOBAL
}

static void SDADC1_WaitForSettling(void) {
    uint16_t count;
    // Wait for a minimum of 6 interrupts to be generated.
    // Throw the first four away when using interrupt every period option, since the
    // low pass SINC filter needs to be flushed with new data.
    for (count = 0; count < SDADC1_WAIT_COUNT; count++) {
        //Clear interrupt flag.
        IFS6bits.SDA1IF = 0;
        //Wait for the result ready.
        while (0 == IFS6bits.SDA1IF);
    }
}
void __attribute__ (( interrupt, no_auto_psv )) _ISR _SDA1Interrupt( void )
{
    if(IFS6bits.SDA1IF)
    {
        IFS6bits.SDA1IF = 0;
    }
}

