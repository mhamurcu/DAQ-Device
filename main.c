/**
  Generated main.c file from MPLAB Code Configurator

  @Company
    Microchip Technology Inc.

  @File Name
    main.c

  @Summary
    This is the generated main.c using PIC24 / dsPIC33 / PIC32MM MCUs.

  @Description
    This source file provides main entry point for system intialization and application code development.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.75.1
        Device            :  PIC24FJ128GC006
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.35
        MPLAB 	          :  MPLAB X v5.05
 */

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
#include "mcc_generated_files/system.h"
#include "mcc_generated_files/padc1.h"
#include "mcc_generated_files/sdadc1.h"
#include "mcc_generated_files/dma.h"
#include <libpic30.h>
#include <stdint.h>
#include "mcc_generated_files/usb/usb.h"
#include "mcc_generated_files/dac1.h"
#include "mcc_generated_files/tmr3.h"
#include "mcc_generated_files/dac2.h"
#include <math.h>
#define PI 3.14159265


#define BitVal(data,y) ( (data>>y) & 1) 

#define _XTAL_FREQ 16000000    




double ADCtotal(int16_t a[]);
double ADCtotal_2(int16_t a[]);
//void read_ADC(void);
void bubbleSort(int16_t x[]);
void DMAtoADC_calc(void);
void DMAtoADC_SDcalc(void);
void MCC_USB_CDC_Tasks(void);
int16_t RMS(int16_t rmsArray[], int16_t AN_Val_ch);
void CalculatePeriod(int16_t c[]);
int16_t OffsetFinder(int16_t volt_ch [], int16_t AN_Val_ch);

int16_t allch_result[10];
int16_t volt_ch1[SIZE - 1];
int16_t volt_ch2[SIZE - 1];
int16_t volt_ch3[SIZE - 1];
int16_t volt_ch4[SIZE - 1];
int16_t volt_ch5[SIZE - 1];
int16_t volt_ch6[SIZE - 1];
int16_t volt_ch7[SIZE - 1];
int16_t volt_ch8[SIZE - 1];
int16_t volt_ch9[SIZE - 1];
int16_t volt_ch10[SIZE - 1];
int16_t volt_SD[SIZE - 1];
int16_t AN_USB_Val[11];
//int p = 0;
int firstCrossing, secondCrossing;

//int16_t voltarray[SIZE - 1];
//int16_t voltarraySD[SIZE - 1];
double toplam, toplamson = 0;
double toplam_2, toplamson_2 = 0;

static uint16_t readBuffer[64]; // USB buffer
static uint16_t writeBuffer[64]; // USB buffer


/*uint16_t data[10];
uint8_t tableregindex = 0;
uint8_t slsize = 10;
uint8_t usbread_0 = 0;
uint8_t usbread_1 = 0;
uint8_t dg_out_1 = 0;
uint8_t dg_out_2 = 0;
uint8_t dg_out_3 = 0;
uint8_t dg_out_4 = 0;*/





int16_t AN_Val_ch1 = 0;
int16_t AN_Val_ch2 = 0;
int16_t AN_Val_ch3 = 0;
int16_t AN_Val_ch4 = 0;
int16_t AN_Val_ch5 = 0;
int16_t AN_Val_ch6 = 0;
int16_t AN_Val_ch7 = 0;
int16_t AN_Val_ch8 = 0;
int16_t AN_Val_ch9 = 0;
int16_t AN_Val_ch10 = 0;
int16_t AN_Val_SD = 0;

double AN_MVal_ch1 = 0;
double AN_MVal_ch2 = 0;
double AN_MVal_ch3 = 0;
double AN_MVal_ch4 = 0;
double AN_MVal_ch5 = 0;
double AN_MVal_ch6 = 0;
double AN_MVal_ch7 = 0;
double AN_MVal_ch8 = 0;
double AN_MVal_ch9 = 0;
double AN_MVal_ch10 = 0;
double AN_MVal_SD;

/*float fResult;
short PLADC = 0;
short SDADC = 0;*/
int16_t OffsetValue = 1940; //1318 guc kaynaksiz
//double DividerMultiplier = 6.666;
int k = 0, l = 0;
double rms = 0;
double rmsson = 0, rmsson1 = 0, rmsson2 = 0, rmsAvg = 0;
int ACDC_flag[2];
int16_t sum2 = 0;
int16_t OffsetValue2 = 0;
bool *ifCheckedAC;
bool flag1 = false;

/*
                         Main application
 */


int main(void) {
    SYSTEM_Initialize();


    ADC_Offset = 1; // Input Offset 
    while (1) {
        MCC_USB_CDC_Tasks();

        /* amp=amplitude/1000;
         freq*/
        // USB_led =1;
        //USB_led_2=1;
        //  __delay_ms(50);
        //  USB_led =0;



        //return 1;
    }
}

void MCC_USB_CDC_Tasks(void) {
    if (USBGetDeviceState() < CONFIGURED_STATE) {
        return;
    }

    if (USBIsDeviceSuspended() == true) {
        return;
    }

    if (USBUSARTIsTxTrfReady() == true) {

        uint8_t a = 0, b = 0, c = 0;
        uint8_t numBytesRead;

        numBytesRead = getsUSBUSART(readBuffer, sizeof (readBuffer));

        if (numBytesRead == 5) {
            ifCheckedAC = &flag1;


            if (readBuffer[4] == 1) { //Checking if the AC checkbox in the gui is checked or not
                *ifCheckedAC = true;
            } else {
                *ifCheckedAC = false;
            }


            for (a = 0; a < 8; a++) { // Writing the results into the buffer for each channel that is controlled by the gui
                if (BitVal(readBuffer[0], a) == 1) {
                    writeBuffer[b] = AN_USB_Val[a];
                    b++;
                }
            }
            for (c = 0; c < 3; c++) {

                if (BitVal(readBuffer[1], c) == 1) {
                    writeBuffer[b] = AN_USB_Val[a];
                    b++;
                    a++;
                }
            }

            DAC2_OutputSet(readBuffer[2]*4);
            DAC1_OutputSet(readBuffer[3]*4);
            Digital_O1 = BitVal(readBuffer[1], 4);
            Digital_O2 = BitVal(readBuffer[1], 5);
            Digital_O3 = BitVal(readBuffer[1], 6);
            Digital_O4 = BitVal(readBuffer[1], 7);

            if (b == 0) {
                writeBuffer[0] = 0;
                writeBuffer[1] = 0;
                putUSBUSART(writeBuffer, 1);
            } else {
                putUSBUSART(writeBuffer, b * 2);
                a = 0;
                b = 0;
                c = 0;
            }
        }
    }
    CDCTxService();
}

void DMAtoADC_calc(void) {
    // Calculating average values for each channel
    AN_Val_ch1 = (int) ADCtotal_2(volt_ch1);
    AN_Val_ch2 = (int) ADCtotal_2(volt_ch2);
    AN_Val_ch3 = (int) ADCtotal_2(volt_ch3);
    AN_Val_ch4 = (int) ADCtotal_2(volt_ch4);
    AN_Val_ch5 = (int) ADCtotal_2(volt_ch5);
    AN_Val_ch6 = (int) ADCtotal_2(volt_ch6);
    AN_Val_ch7 = (int) ADCtotal_2(volt_ch7);
    AN_Val_ch8 = (int) ADCtotal_2(volt_ch8);
    AN_Val_ch9 = (int) ADCtotal_2(volt_ch9);
    AN_Val_ch10 = (int) ADCtotal_2(volt_ch10);


    if (!*ifCheckedAC) {


        // Finding the offset value of the signal
        AN_USB_Val[0] = OffsetFinder(volt_ch1, AN_Val_ch1);
        AN_USB_Val[1] = OffsetFinder(volt_ch2, AN_Val_ch2);
        AN_USB_Val[2] = OffsetFinder(volt_ch3, AN_Val_ch3);
        AN_USB_Val[3] = OffsetFinder(volt_ch4, AN_Val_ch4);
        AN_USB_Val[4] = OffsetFinder(volt_ch5, AN_Val_ch5);
        AN_USB_Val[5] = OffsetFinder(volt_ch6, AN_Val_ch6);
        AN_USB_Val[6] = OffsetFinder(volt_ch7, AN_Val_ch7);
        AN_USB_Val[7] = OffsetFinder(volt_ch8, AN_Val_ch8);
        AN_USB_Val[8] = OffsetFinder(volt_ch9, AN_Val_ch9);
        AN_USB_Val[9] = OffsetFinder(volt_ch10, AN_Val_ch10);
    } else {

        AN_USB_Val[0] = RMS(volt_ch1, AN_Val_ch1);
        AN_USB_Val[1] = RMS(volt_ch2, AN_Val_ch2);
        AN_USB_Val[2] = RMS(volt_ch3, AN_Val_ch3);
        AN_USB_Val[3] = RMS(volt_ch4, AN_Val_ch4);
        AN_USB_Val[4] = RMS(volt_ch5, AN_Val_ch5);
        AN_USB_Val[5] = RMS(volt_ch6, AN_Val_ch6);
        AN_USB_Val[6] = RMS(volt_ch7, AN_Val_ch7);
        AN_USB_Val[7] = RMS(volt_ch8, AN_Val_ch8);
        AN_USB_Val[8] = RMS(volt_ch9, AN_Val_ch9);
        AN_USB_Val[9] = RMS(volt_ch10, AN_Val_ch10);
    }
}

int16_t RMS(int16_t rmsArray[], int16_t AN_Val_ch) {
    
    
 // Finding the period of the signal with comparing values and storing the first two crossings with the average value calculated before.
    
    
    for (k = 3; k < 127; k++) {
        if ((rmsArray[k] <= AN_Val_ch) && (rmsArray[k + 1] > AN_Val_ch)) {
            if (k) {

                firstCrossing = k;
                rms = 0;
                k++;
                break;
            }

        }
    }
    for (; k < 127; k++) {
        if ((rmsArray[k] <= AN_Val_ch) && (rmsArray[k + 1] > AN_Val_ch)) {
            if (k) {
                secondCrossing = k;
                break;
            }
        }

    }
    for (l = 1; l <= secondCrossing - firstCrossing; l++) {
        sum2 = sum2 + ((double) (rmsArray[firstCrossing + l]) / (double) (secondCrossing - firstCrossing));
    }


    OffsetValue2 = (int) sum2;

    // RMS Calculation

    for (l = 1; l <= secondCrossing - firstCrossing; l++) {
        rms = rms + (double) ((double) (rmsArray[firstCrossing + l] - OffsetValue2) / 10.0)* (double) ((double) (rmsArray[firstCrossing + l] - OffsetValue2) / (10.0));



    }

    rmsAvg = rms / (double) (secondCrossing - firstCrossing);
    rmsson = (int) ((sqrt(rmsAvg) * (double) 10.0) + OffsetValue + 10);


    sum2 = 0;
    rms = 0;
    return rmsson;




}

int16_t OffsetFinder(int16_t volt_ch [], int16_t AN_Val_ch) {


 // Finding the period of the signal with comparing values and storing the first two crossings with the average value calculated before.

    for (k = 3; k < 127; k++) {
        if ((volt_ch[k] <= AN_Val_ch) && (volt_ch[k + 1] > AN_Val_ch)) {
            if (k) {

                firstCrossing = k;
                rms = 0;

                k++;
                break;
            }

        }
    }
    for (; k < 127; k++) {
        if ((volt_ch[k] <= AN_Val_ch) && (volt_ch[k + 1] > AN_Val_ch)) {
            if (k) {
                secondCrossing = k;
                break;
            }
        }

    }
    for (l = 1; l <= secondCrossing - firstCrossing; l++) {
        sum2 = sum2 + (volt_ch[firstCrossing + l] / 10.0);
    }
    sum2 = (int) (((double) sum2 / (double) (secondCrossing - firstCrossing))*10.0);

    OffsetValue2 = sum2;
    sum2 = 0;
    return OffsetValue2;

}






void DMAtoADC_SDcalc(void) {


    bubbleSort(volt_SD);
    AN_Val_SD = ADCtotal(volt_SD);
    AN_USB_Val[10] = (int) AN_Val_SD;
    AN_MVal_SD = ((double) AN_Val_SD)* 0.0000503 * 2;

}

void bubbleSort(int16_t x[]) {
    int a, b;


    for (a = 1; a < SIZE; a++) {

        for (b = 0; b < SIZE - 2; b++) {

            if (x[b] > x[b + 1])
                swapf(b, b + 1, x);
        }
    }
}

void swapf(int x, int y, int16_t z[]) {
    int temp1;
    temp1 = z[x];
    z[x] = z[y];
    z[y] = temp1;

}

double ADCtotal(int16_t a[]) {
    int c;
    toplam = 0;
    for (c = 32; c < 96; c++) {
        toplam = toplam + a[c];
    }
    toplamson = toplam / 64;

    return toplamson;
}

double ADCtotal_2(int16_t a[]) {
    int d;
    toplam_2 = 0;
    for (d = 0; d < 128; d++) {
        toplam_2 = toplam_2 + a[d];
    }
    toplamson_2 = toplam_2 / 128;

    return toplamson_2;
}








/**
 End of File
 */

