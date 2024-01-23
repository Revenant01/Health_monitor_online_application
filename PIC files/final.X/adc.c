#include <pic.h>
#include <pic16f877a.h>

#define _XTAL_FREQ 20000000
void adc_init()
{

  ADCON0 = 0b01000001; //ADC ON and Fosc/16 is selected , 
  ADCON1 = 0b11000000; // use RIGHT justified methodology , 

}


unsigned int adc_read(unsigned char channel)

{

  ADCON0 &= 0x11000101; //Clearing the Channel Selection Bits
  ADCON0 |= channel<<3; //Setting the required Bits

  __delay_ms(2); //Acquisition time to charge hold capacitor

  GO_nDONE = 1; //Initializes A/D Conversion
  while(GO_nDONE); //Wait for A/D Conversion to complete

  return ((ADRESH<<8)+ADRESL); //Returns Result

}


