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
//    TRISFbits.TRISF2=1; //set TRIS value for pin (input)
//    ANSELFbits.ANSELF2=0; //turn off analogue input on pin
    
    // get initial reference light level
    unsigned int refval = 0;
    refval = ADC_getval() - 50;
    unsigned int peakval = 0;
    
    while (1) {
        
        
        int i;
        for(i=0; i<100; i++) {
            
            val = ADC_getval() - 50;
        
            if (val > 255) {
                val = 0;
            }

            val = val << 8;
            val = (val/refval);

            if (val>peakval) {
                peakval = val;
            }
            
            
            LEDarray_disp_PPM(val,peakval);

            __delay_ms(10); // Delay to make 1s
        }
        
        peakval = peakval - 255/8;
        
        if (peakval > 255) {
        peakval = 0;
        }
       
        
                
        
    }
}
