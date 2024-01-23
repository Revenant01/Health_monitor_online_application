#include <xc.h>
#include <stdint.h>
#include "tmr0_interface.h"

const uint8_t tmr0_mask = 0xFF;

#define _XTAL_FREQ 200000000 //Crystal Frequency, used in delay
#define TMR0_INTERRUPT_TICKER_FACTOR    1


void TMR0_Initialize(void) {
  
    // Enable global and peripheral interrupts
    INTCONbits.GIE = 1;    // Global Interrupt Enable
    INTCONbits.PEIE = 1;   // Peripheral Interrupt Enable

    // Configure Timer0
    OPTION_REGbits.T0CS = 0;   // Use internal instruction cycle clock (FOSC/4)
    OPTION_REGbits.T0SE = 1;   // Increment on high-to-low transition on T0CKI pin
    OPTION_REGbits.PSA = 0;    // Assign prescaler to Timer0
    OPTION_REGbits.PS = 0x07;  // Prescaler divide ratio is 1:256

    // Calculate and set the initial value for Timer0
    TMR0 = (uint8_t)(tmr0_mask & (256-(((2 * _XTAL_FREQ) / (256 * 4)) / 1000))); // Delay for 2ms

    // Clear Timer0 interrupt flag before enabling the interrupt
    INTCONbits.TMR0IF = 0;

    // Enable external interrupt on RB0
    INTCONbits.INTE = 1;    // Enable external interrupt on RB0
    OPTION_REGbits.INTEDG = 1;  // Interrupt on rising edge of RB0
}


void TMR0_StartTimer(void) {
    INTCONbits.TMR0IE = 1;
}

void TMR0_StopTimer(void) {
    INTCONbits.TMR0IE = 0;
}

void TMR0_ISR(void) {
    static volatile uint16_t CountCallBack = 0;
    // disabling TMR0 interrupt.
    INTCONbits.TMR0IE = 0;
    // clear the TMR0 interrupt flag
    INTCONbits.TMR0IF = 0;

    // reload TMR0
    // Write to the Timer0 register
    TMR0 = (uint8_t)(tmr0_mask & (256-(((2 *_XTAL_FREQ)/(256*4))/1000)));     // delay for 2ms
    // TimerCountMax - (((delay(ms) * Focs(hz)) / (PreScale_Val * 4)) / 1000)
    
    
    if (++CountCallBack >= TMR0_INTERRUPT_TICKER_FACTOR)
    {
        // ticker function call
        timer_isr();

        // reset ticker counter
        CountCallBack = 0;
    }
    
    // Enabling TMR0 interrupt.
    INTCONbits.TMR0IE = 1;
}


