Led7Segment
======

An Arduino library for 7-segment display modules based on the TM1637 chip.

The library is based on TM1637Display (https://github.com/avishorp/TM1637):
it retains the original low-level functions for communication with the TM1637
chip, but replaces or enhances the public methods.


Hardware Connection
-------------------
The display module has signal connections CLK and DIO (besides power
connections). These pins can be connected to any pair of digital pins on the
Arduino. There is no limitation on the number of instances used concurrently
(as long as each instance has a pin pair of its own).


Installation
------------
[Download the .zip file](https://github.com/janezd/LED7Segment/archive/master.zip)
and install it using *Sketch / Include Library / Add .ZIP Library* in Arduino IDE.
Alternatively, unzip the archive into directory sketches/libraries.


Usage
-----
The library provides a class named `Led7Segment` with the following methods.

<dl>
<dt>Led7Segment(pinClk, pinDio)</dt>
<dd>Initialize the display, enable it and set it to the highest brightness.</dd>

<dt>turnOn()</dt>
<dd>Turn the display on.</dd>

<dt>turnOff()</dt>
<dd>Turn the display off.</dd>

<dt>setBrightness(brightness)</dt>
<dd>Set the brightness (0 - 7). The change takes effect immediately.</dd>

<dt>clearDisplay(pos=0, length=4, zeros=false)<dt>
<dd>Clear the display or a part of a given <code>length</code> starting from
<code>pos</code> (0 is the leftmost digit). If <code>zeros</code> is set to
<code>true</code>, the display is filled with zeros instead of with blanks.</dd>

<dt>showNumber(number, pos=0, length=4, leading_zeros=false, base=10)</dt>
<dd>Show <code>num</code> starting at <code>pos</code> (0 being the left-most digit)
    and using <code>length</code> digits. The number is right-aligned; if
    <code>leading_zeros</code> is set to <code>true</code>, the number is
    left-padded with zeros. If pos + length >= 4, length is decreased
    accordingly.

If the number (including the minus sign, when needed) does not fit
into <code>length</code>, E's are shown instead of the number.</dd>

Base must be between 2 (binary) and 16 (hexadecimal).

<dt>setDots(mask)</dt>
<dd>Set dots at the places corresponding to the four right-most bits.
    For displays with a single colon at the middle, <code>setDots(4)</code> shows the
    colon and <code>setDots(0)</code> hides it.</dd>

<dt>setSegments(data[], pos, length)</dt>
<dd>Set <code>length</code> digits starting from <code>pos</code> with
    the given <code>data</code>, which contains one byte per digit, with
    one bit per segment. The library defines constants <code>SEG_T</code>,
    <code>SEG_TR</code>, <code>SEG_BR</code>, <code>SEG_B</code>,
    <code>SEG_BL</code>, <code>SEG_TL</code>, <code>SEG_M</code> and
    <code>SEG_D</code> with values 1, 2, 4, 8, ... 128 which correspond to bits
    representing the top, top-right, bottom-right, bottom, bottom-left,
    top-left, middle segment, and the dot, respectively.
    E.g. <code>donE</code> can be shown with <code>setSegment(done);</code>
    where <code>done</code> is

    uint8_t done[] = {
        SEG_TR | SEG_BR | SEG_B | SEG_BL | SEG_M,  // d
        SEG_BR | SEG_B | SEG_BL | SEG_M,           // o
        SEG_BR | SEG_BL | SEG_M,                   // n
        SEG_TL | SEG_BL | SEG_T | SEG_M | SEG_B    // E
    };
