#pragma config FEXTOSC = HS     // External Oscillator mode Selection bits (HS (crystal oscillator) above 8 MHz; PFM set to high power)
#pragma config RSTOSC = EXTOSC_4PLL// Power-up default value for COSC bits (EXTOSC with 4x PLL, with EXTOSC operating per FEXTOSC bits)
#pragma config WDTE = OFF        // WDT operating mode (WDT enabled regardless of sleep)

#include <xc.h>
#include <math.h>
#include "LEDarray.h"
#include "ADC.h"

#define _XTAL_FREQ 64000000 //note intrinsic _delay function is 62.5ns at 64,000,000Hz  

void main(void) 
{
	unsigned int count=0;
    unsigned int val = 0;
    LEDarray_init();
    ADC_init();
    
    // setup pin for input (connected to button)
    TRISFbits.TRISF2=1; //set TRIS value for pin (input)
    ANSELFbits.ANSELF2=0; //turn off analogue input on pin
    
    // get initial reference light level
    unsigned int refval = 0;
    refval = ADC_getval();
    unsigned int peakval = 0;
    
    while (1) {
        
        LATHbits.LATH3=0; 
        LATGbits.LATG0=0;
        LATGbits.LATG1=0;
        LATAbits.LATA2=0;
        LATAbits.LATA4=0;
        LATAbits.LATA5=0;
        LATFbits.LATF6=0;
        LATFbits.LATF0=0;
        LATBbits.LATB0=0;
        LATBbits.LATB1=0;
//       
        unsigned int powtwo = 1;
        
        int i;
        
        for(i=0; i<10; i++) {
        
        val = ADC_getval();
        val = val * 256;
        val = (val/refval);
        
        if (val>peakval) {
            peakval = val;
            while (peakval > powtwo) {
            powtwo = powtwo * 2;
            }
            peakval = powtwo/4;
        }
        
        LEDarray_disp_bar(val); //output on the LED array
        LEDarray_disp_bin(peakval);
        
        
		__delay_ms(50); // Delay to make 1s
        }
        
        peakval = peakval/2;
        
                
        
    }
}
