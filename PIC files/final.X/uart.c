#include <pic.h>


#define _XTAL_FREQ 20000000 
// Define the UART baud rate for your HC-05 module.
#define UART_BAUD_RATE 9600

void uart_init() {
    TRISC6 = 0; // TX as input
    TRISC7 = 1; // RX as output
    TXSTAbits.BRGH = 0;    // High-Speed mode
    RCSTAbits.CREN = 1;    // Enable continuous reception
    TXSTAbits.SYNC = 0;    // Asynchronous mode
    TXSTAbits.TXEN = 1;    // Enable transmission
    RCSTAbits.SPEN = 1;    // Enable serial port (TX and RX pins)
    SPBRG = 31;           // for 9600 baud rate in freq 20MHz
}

void uart_write(int data) {

    while (!PIR1bits.TXIF)
        continue;
    PIR1bits.TXIF = 0;
    TXREG = data;
}

char uart_read ()
{
    if (PIR1bits.RCIF)
    {
        PIR1bits.RCIF = 0 ;
        return RCREG;
    }
}

void uart_writestring(const unsigned char* data) {
    while (*data) {
        uart_write(*data);
        __delay_us(200);
        data++;
    }
}

