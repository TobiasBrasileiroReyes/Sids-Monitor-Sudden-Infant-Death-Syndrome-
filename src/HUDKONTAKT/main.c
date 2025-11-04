#include "gd32vf103.h"
#include "drivers.h"
#include "lcd.h"

int main(void){
    int ms = 0, idle = 0, key;
    int lookUpTbl[16] = {1,4,7,14,2,5,8,0,3,6,9,15,10,11,12,13};  // Lookup table for key values
    int dac = 0, speed = -100;
    int adcr, tmpr;

    t5omsi(); // Initialize timer5 1kHz
    colinit(); // Initialize column toolbox
    l88init(); // Initialize 8*8 led toolbox
    keyinit(); // Initialize keyboard toolbox
    Lcd_SetType(LCD_NORMAL); // or use LCD_INVERTED!
    Lcd_Init();
    LCD_Clear(GRAY);

    while (1) {
        idle++; // Manage Async events
        LCD_WR_Queue(); // Manage LCD com queue!

        if (t5expq()) { // Manage periodic tasks
            l88row(colset()); // ...8*8LED and Keyboard
            ms++; // ...One second heart beat
          
            key = keyscan(); // Scan for key press once
            if (key >= 0) {
                if (lookUpTbl[key] == 1) {
                    LCD_ShowStr(10, 30, "1", WHITE, BLACK); // Show "1" if key '1' is pressed
                } else {
                    LCD_ShowStr(10, 30, "0", WHITE, BLACK); // Show "0" if any other key is pressed
                }
            } 
        }
    }
}
