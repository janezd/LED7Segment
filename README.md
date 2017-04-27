Led7Segment
======

An Arduino library for 7-segment display modules based on the TM1637 chip.
The TM1637 chip also has keyboard input capability, but it's not implemented
in this library.

This library is based on TM1637Display (https://github.com/avishorp/TM1637):
it retains the original functions for communication with the TM1637 chip,
but replaces or modifies the public methods to simplify their use.


Hardware Connection
-------------------
The display modules has two signal connection (and two power connections)
which are CLK and DIO. These pins can be connected to any pair of digital
pins on the Arduino. There is no limitation on the number of instances used
concurrently (as long as each instance has a pin pair of its own).

Installation
------------
Download the .zip file and install it using *Sketch / Include Library /
Add .ZIP Library* in Arduino IDE. Alternatively, unzip the archive into
directory sketches/libraries.

Usage
-----
The library provides a class named `Led7Segment` with the following methods.

* `Led7Segment(pinClk, pinDio)`: initializes the display, enables it
    and sets it to the maximal brightness
* `turnOn()`: turn the display on
* `turnOff()`: turn the display off
* `setBrightness(brightness)`: set brightness (0 - 7). (Unlike in
    TM1637Display, the change takes effect immediately.)
* `clearDisplay(pos=0, length=4, zeros=false)`: clears display or a
    part of it starting from `pos` (0 is the leftmost digit) and of
    length `length`. If `zeros` is set to `true`, the display is filled
    with zeros instead of with blanks.
* `showNumber(number, pos=0, length=4, leading_zeros=false)`: show `num`
    right-aligned at `pos` (0 is the leftmost digit) with the given
    `length`.
    If `leading_zeros` is set to `true`, the space is padded with zeros
    instead of blanks.
    Zero-padding does not work for negative numbers.
    If the length is too short, the output is trimmed on the left.
* `setDots(mask)` sets dots at the places corresponding to the four
    right-most bits. For displays with a single colon at the middle,
    `setDots(4)` shows the colon and `setDots(0)` hides it.
* `setSegments(data[], pos, length)`: sets `length` digits starting from
    `pos` with the given `data`, which contains one byte per digit,
    with one bit per segment (`.GFEDCBA` in the [common enumeration](https://en.wikipedia.org/wiki/File:7_segment_display_labeled.svg)).
