#pragma config FEXTOSC = HS     // External Oscillator mode Selection bits (HS (crystal oscillator) above 8 MHz; PFM set to high power)
#pragma config RSTOSC = EXTOSC_4PLL// Power-up default value for COSC bits (EXTOSC with 4x PLL, with EXTOSC operating per FEXTOSC bits)
#pragma config WDTE = OFF        // WDT operating mode (WDT enabled regardless of sleep)

#include <xc.h>
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
  
    while (1) {
//        
        val = ADC_getval();
        val = val * 256;
        val = (val/refval);
        
        LEDarray_disp_bar(val); //output on the LED array
        
        
//		__delay_ms(400); // Delay so human eye can see change
        
    }
}
