#include <Led7Segment.h>


Led7Segment display(13, 12); // CLK, DIO

uint8_t done[] = {
    SEG_TR | SEG_BR | SEG_B | SEG_BL | SEG_M,
    SEG_BR | SEG_B | SEG_BL | SEG_M,
    SEG_BR | SEG_BL | SEG_M,
    SEG_TL | SEG_BL | SEG_T | SEG_M | SEG_B
};

void setup() {
    // Display is initially turned on at the highest brightness
    display.showNumber(1234);
    delay(1000);

    // Turning it off and on again retains the display content
    display.turnOff();
    delay(1000);
    display.turnOn();
    delay(1000);

    // Change brightness from the lowest to the highest
    // The change takes effect immediatelly
    for(int i = 0; i < 8; i++) {
        display.setBrightness(i);
        delay(200);
    }

    // Uses the entire display (positions 0 - 3)
    for(int i = 10; i > -11; i--) {
        display.showNumber(i);
        delay(300);
    }

    // Same, with leading zero. Minus sign is at the left
    for(int i = 10; i > -11; i--) {
        display.showNumber(i, 0, 4, true);
        delay(300);
    }

    // Keep the last two digits, change the first two digits
    // Note that -10 would need three digits, so display shows EE
    for(int i = 10; i > -11; i--) {
        display.showNumber(i, 0, 2, true);
        delay(300);
    }

    // The number is too large, shows EEE
    display.showNumber(12345);
    delay(1000);

    // Shown
    display.showNumber(-123);
    delay(1000);

    // Not shown since it would need five digits
    display.showNumber(-1234);
    delay(1000);

    display.clearDisplay();
    display.showNumber(42, 1, 2);
    
    // Blink the dot(s) in the middle (e.g. like a clock)
    for(int i = 0; i < 5; i++) {
        display.setDots(4);
        delay(500);
        display.setDots(0);
        delay(500);
    }

    // Can't be shown in one digit, shows E; digits 1-3 are unchanged
    display.showNumber(42, 0, 1);
    delay(1000);

    // Changes digit 3, keeps the rest
    display.showNumber(3, 3, 2);
    delay(1000);

    // Attempt to show 13 with 4 digits at position 1: uses 3 digits instead
    display.showNumber(13, 1, 4);
    delay(1000);

    // Clear individual digits
    display.showNumber(1234);
    for(int i = 0; i < 4; i++) {
        delay(500);
        display.clearDisplay(i, 1);
    }


    // Scroll the 'donE' from the right
    for(int i = 3; i >= 0; i--) {
        display.setSegments(done, i);
        delay(300);
    }

    // ... and from the left
    display.clearDisplay();
    for(int i = 1; i <= 4; i++) {
        display.setSegments(done + 4 - i, 0, i);
        delay(300);
    }
}

void loop()
{
    display.setBrightness(0);
    delay(400);
    display.setBrightness(7);
    delay(400);
}