
#define INTERRUPT_GlobalInterruptEnable() (INTCONbits.GIE = 1)

#define INTERRUPT_GlobalInterruptDisable() (INTCONbits.GIE = 0)

#define INTERRUPT_PeripheralInterruptEnable() (INTCONbits.PEIE = 1)

#define INTERRUPT_PeripheralInterruptDisable() (INTCONbits.PEIE = 0)


void TMR0_Initialize(void); 

void TMR0_StartTimer(void); 

void TMR0_StopTimer(void);

void TMR0_ISR(void);

void timer_isr(void);

void __interrupt() INTERRUPT_InterruptManager (void);
