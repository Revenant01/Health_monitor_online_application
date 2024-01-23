#include <pic.h>
#define _XTAL_FREQ 20000000

// Define the LCD connections
#define RS RD7
#define EN RB1
#define D4 RB2
#define D5 RB3
#define D6 RB4
#define D7 RB5

#define ADD 0 
#define SUB 1 
#define MUL 2

//Function to send a command to LCD
void lcd_cmd (unsigned char cmd)
{
 
    // PORTB = (cmd & 0xF0);
    D4 = (cmd >> 4) &1;
    D5 = (cmd >> 5) &1;
    D6 = (cmd >> 6) &1;
    D7 = (cmd >> 7) &1;
    EN = 1;
    RS = 0;
    __delay_ms(2);
    EN = 0;
    
    // PORTB = ((cmd<<4) & 0xF0);
    D4 = (cmd >> 0) &1;
    D5 = (cmd >> 1) &1;
    D6 = (cmd >> 2) &1;
    D7 = (cmd >> 3) &1;
    EN = 1;
    RS = 0;
    __delay_ms(2);
    EN = 0;
   
}

//Function to send a command to LCD
void lcd_data (unsigned char data)
{
      
    //PORTB = (data & 0xF0);
    D4 = (data >> 4) &1;
    D5 = (data >> 5) &1;
    D6 = (data >> 6) &1;
    D7 = (data >> 7) &1;
    EN = 1;
    RS = 1;
    __delay_ms(2);
    EN = 0;
    
    //PORTB = ((data<<4) & 0xF0);
    D4 = (data >> 0) &1;
    D5 = (data >> 1) &1;
    D6 = (data >> 2) &1;
    D7 = (data >> 3) &1;
    EN = 1;
    RS = 1;
    __delay_ms(2);
    EN = 0;
   
}


// Function to initialize the LCD
void lcd_init() { 
    
  lcd_cmd(0x33); // Initialize LCD in 4-bit mode
  lcd_cmd(0x32); // Set to 4-bit mode
  lcd_cmd(0x28); // 2 lines, 5x8 font
  lcd_cmd(0x0C); // Display on, cursor off, blink off
  lcd_cmd(0x06); // Increment cursor
  lcd_cmd(0x01); // Clear display

}


// Function to write a string to the LCD
void lcd_string(const char* str) {
    while (*str) {
        lcd_data(*str);
        str++;
    }
}


void lcd_number (int number)
{
    unsigned int temp = number;
    unsigned int divisor = 1;

    // Find the divisor for the most significant digit
    while (temp >= 10) {
        temp /= 10;
        divisor *= 10;
    }

    // Iterate through the digits and display one at a time
    while (divisor > 0) {
        unsigned char digit = (number / divisor) % 10;
        lcd_data(digit+48);
        divisor /= 10;
    }
}






