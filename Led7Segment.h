
//  Author: Janez Demsar, based on the work of avishorp@gmail.com
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

extern "C" {
    #include <stdlib.h>
    #include <string.h>
    #include <inttypes.h>
}

#include <Led7Segment.h>
#include <Arduino.h>

#define TM1637_I2C_COMM1    0x40
#define TM1637_I2C_COMM2    0xC0
#define TM1637_I2C_COMM3    0x80

//
//      A
//     ---
//  F |   | B
//     -G-
//  E |   | C
//     ---
//      D
const uint8_t digitToSegment[] = {
   // XGFEDCBA
    0b00111111,    // 0
    0b00000110,    // 1
    0b01011011,    // 2
    0b01001111,    // 3
    0b01100110,    // 4
    0b01101101,    // 5
    0b01111101,    // 6
    0b00000111,    // 7
    0b01111111,    // 8
    0b01101111,    // 9
    0b01110111,    // A
    0b01111100,    // b
    0b00111001,    // C
    0b01011110,    // d
    0b01111001,    // E
    0b01110001     // F
};


Led7Segment::Led7Segment(uint8_t pinClk, uint8_t pinDIO)
: m_pinClk(pinClk), m_pinDIO(pinDIO), m_brightness(0xf), m_dots(0)
{
    // Both pins are set as inputs, allowing the pull-up resistors to pull them up
    pinMode(m_pinClk, INPUT);
    pinMode(m_pinDIO,INPUT);
    digitalWrite(m_pinClk, LOW);
    digitalWrite(m_pinDIO, LOW);
    clearDisplay(0, 4);
}

void Led7Segment::clearDisplay(uint8_t pos, uint8_t length, bool zeros)
{
    clipLength(pos, length);
    clearDigits(pos, length, zeros);
    update();
}

void Led7Segment::turnOn()
{
    m_brightness |= 0x08;
    update();
}

void Led7Segment::turnOff()
{
    m_brightness &= 0x07;
    update();
}

void Led7Segment::setBrightness(uint8_t brightness)
{
    m_brightness = (m_brightness & 0x08) | brightness;
    update();
}

void Led7Segment::setDots(uint8_t dots) {
    m_dots = dots << 4;
    update();
}

void Led7Segment::showNumber(int num, uint8_t pos, uint8_t length, bool leading_zero)
{
    bool negative = num < 0;
    num = abs(num);
    clipLength(pos, length);
    if (!length) return;
    clearDigits(pos, length, leading_zero);
    pos += length;
    do {
        digits[--pos] = digitToSegment[num % 10];
        num /= 10;
    } while (--length && num);
    if (negative && length) {
        digits[--pos] = 64;
    }
    update();
}

void Led7Segment::setSegments(uint8_t data[], uint8_t pos=0, uint8_t length=4)
{
    clipLength(pos, length);
    memcpy(digits + pos, data, length);
}

/****** Protected stuff ******/

void Led7Segment::update()
{
    // Write COMM1
    start();
    writeByte(TM1637_I2C_COMM1);
    stop();

    // Write COMM2 + first digit address + data bytes
    start();
    writeByte(TM1637_I2C_COMM2);
    uint8_t tdots = m_dots;
    for (uint8_t k=0; k < 4; k++, tdots <<= 1) {
        writeByte(digits[k] | (tdots & 0x80));
    }
    stop();

    // Write COMM3 + brightness
    start();
    writeByte(TM1637_I2C_COMM3 + m_brightness);
    stop();
}

void Led7Segment::bitDelay()
{
    delayMicroseconds(50);
}

void Led7Segment::start()
{
    pinMode(m_pinDIO, OUTPUT);
    bitDelay();
}

void Led7Segment::stop()
{
    pinMode(m_pinDIO, OUTPUT);
    bitDelay();
    pinMode(m_pinClk, INPUT);
    bitDelay();
    pinMode(m_pinDIO, INPUT);
    bitDelay();
}

bool Led7Segment::writeByte(uint8_t b)
{
  uint8_t data = b;

  // 8 Data Bits
  for(uint8_t i = 0; i < 8; i++) {
    // CLK low
    pinMode(m_pinClk, OUTPUT);
    bitDelay();

    // Set data bit
    if (data & 0x01)
      pinMode(m_pinDIO, INPUT);
    else
      pinMode(m_pinDIO, OUTPUT);

    bitDelay();

    // CLK high
    pinMode(m_pinClk, INPUT);
    bitDelay();
    data = data >> 1;
  }

  // Wait for acknowledge
  // CLK to zero
  pinMode(m_pinClk, OUTPUT);
  pinMode(m_pinDIO, INPUT);
  bitDelay();

  // CLK to high
  pinMode(m_pinClk, INPUT);
  bitDelay();
  uint8_t ack = digitalRead(m_pinDIO);
  if (ack == 0)
    pinMode(m_pinDIO, OUTPUT);


  bitDelay();
  pinMode(m_pinClk, OUTPUT);
  bitDelay();

  return ack;
}
