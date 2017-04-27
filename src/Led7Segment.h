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

#ifndef __LED7SEGMENT__
#define __LED7SEGMENT__

#include <inttypes.h>

#define SEG_T 1
#define SEG_TR 2
#define SEG_BR 4
#define SEG_B 8
#define SEG_BL 16
#define SEG_TL 32
#define SEG_M 64
#define SEG_D 128

class Led7Segment {

public:
  //! Initialize a TM1637Display object, setting the clock and
  //! data pins; turn the display on and to the highest brightness.
  //!
  //! @param pinClk - The number of the digital pin connected to the clock pin of the module
  //! @param pinDIO - The number of the digital pin connected to the DIO pin of the module
  Led7Segment(uint8_t pinClk, uint8_t pinDIO);

  //! Turn the display off
  void turnOff();

  //! Turn the display on
  void turnOn();

  //! Set the brightness of the display and turned it on.
  //!
  //! @param brightness A number from 0 (lowes brightness) to 7 (highest brightness)
  void setBrightness(uint8_t brightness);

  //! Clear the display or a part of display
  //!
  //! @param pos The position of the first digit to clear (0 - leftmost, 3 - rightmost)
  //! @param length The number of digits to be cleared
  //! @param zeros If true, the digits are set to 0, otherwise blank
  void clearDisplay(uint8_t pos=0, uint8_t length=4, bool zeros=false);

  //! Set dots on the display
  //!
  //! @param dots Mask for dots; the rigthmost bit corresponds to the rightmost dot
  void setDots(uint8_t dots);

  //! Display a decimal number
  //!
  //! @param num The number to be shown
  //! @param pos The position most significant digit (0 - leftmost, 3 - rightmost)
  //! @param length The number of digits to set. The user must ensure that the width is sufficient
  //!        for the given number
  //! @param leading_zero If true, leading zeros are displayed. Otherwise leading digits are blank
  bool showNumber(int num, uint8_t pos=0, uint8_t length=4, bool leading_zero=false);

  void setSegments(uint8_t data[], uint8_t pos=0, uint8_t length=4);

protected:
   bool error(uint8_t pos, uint8_t length);

   inline void clipLength(uint8_t pos, uint8_t &length)
   { if (pos + length > 4) length = 4 - pos; }

   inline void clearDigits(uint8_t pos = 0, uint8_t length = 4, bool zeros=false)
   { memset(digits + pos, zeros ? 63 : 0, length); }

   void update(uint8_t pos=0, uint8_t length=0);
   void bitDelay();
   void start();
   void stop();
   bool writeByte(uint8_t b);

//private:
  public:
	uint8_t m_pinClk;
	uint8_t m_pinDIO;
	uint8_t m_brightness;
  uint8_t m_dots;
  uint8_t digits[4];
};

#endif // __LED7SEGMENT__
