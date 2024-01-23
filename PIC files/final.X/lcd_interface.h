/* 
 * File:   lcd.h
 * Author: User
 *
 * Created on November 8, 2023, 7:40 PM
 */

#ifndef LCD_INTERFACE_H
#define	LCD_INTERFACE_H

#ifdef	__cplusplus
extern "C" {
#endif


void lcd_cmd (unsigned char cmd);
void lcd_data (unsigned char data);
void lcd_init();
void lcd_string(const char* str);
void lcd_number (int number);
    
#ifdef	__cplusplus
}
#endif

#endif	/* LCD_H */

