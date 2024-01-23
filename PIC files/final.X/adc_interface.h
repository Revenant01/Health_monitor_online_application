/* 
 * File:   adc_interfacce.h
 * Author: User
 *
 * Created on November 17, 2023, 8:06 PM
 */

#ifndef ADC_INTERFACCE_H
#define	ADC_INTERFACCE_H

#ifdef	__cplusplus
extern "C" {
#endif

void adc_init();
unsigned int adc_read(unsigned char channel);

#ifdef	__cplusplus
}
#endif

#endif	/* ADC_INTERFACCE_H */


