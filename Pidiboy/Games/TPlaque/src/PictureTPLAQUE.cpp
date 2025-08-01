//        >>>>>  T-I-N-Y  P-L-A-Q-U-E for ATTINY85  GPL v3 <<<<<
//                    Programmer: Daniel C 2020-2021
//               Contact EMAIL: electro_l.i.b@tinyjoypad.com
//                    https://WWW.TINYJOYPAD.COM
//          https://sites.google.com/view/arduino-collection

//  Tiny-Plaque is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.

//  You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

//for TINY JOYPAD rev2 (attiny85)
//the code work at 16MHZ internal
//Program the chip with an arduino uno in "Arduino as ISP" mode.

// -----------------------------------------
// PidiBoy adaptation: Miroslav Nemecek 2025
// -----------------------------------------

#include "../include.h"

const int8_t RnD_TPLAQUE[] PROGMEM = {-1,0,-1,1,0,1,-1,1,0,0,-1,1,0,1};

const uint8_t BACK1_TPLAQUE[] PROGMEM = {
	//104,2,
	0x80,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x80,0x80,0x80,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0xFE,0xF0,0xE0,0xC0,0x80,0xC0,0xE0,0xC0,0x80,
	0xC0,0xE0,0xE0,0xE0,0xE0,0xC0,0x80,0xC0,0xE0,0xC0,0x80,0xC0,0xE0,0xF0,0xF0,0xE0,0xC0,0x80,0xC0,0xE0,
	0xC0,0x80,0xC0,0xE0,0xF0,0xF0,0xE0,0xC0,0x80,0xC0,0xE0,0xC0,0x80,0xC0,0xE0,0xF0,0xF0,0xE0,0xC0,0x80,
	0xC0,0xE0,0xC0,0x80,0xC0,0xE0,0xF0,0xF0,0xE0,0xC0,0x80,0xC0,0xE0,0xC0,0x80,0xC0,0xE0,0xF0,0xF0,0xE0,
	0xC0,0x80,0xC0,0xE0,0xC0,0x80,0xC0,0xE0,0xF0,0xF0,0xE0,0xC0,0x80,0xC0,0xE0,0xC0,0x80,0xC0,0xE0,0xF0,
	0xFE,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
};

const uint8_t BACK2_TPLAQUE[] PROGMEM = {
	//104,2,
	0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0x40,0xC0,0xC0,0xC0,0x40,0xC0,0xC0,0xC0,0xC0,
	0xC0,0xC0,0x40,0xC0,0xC0,0xC0,0x40,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0x40,0xC0,0xC0,0xC0,0x40,0xC0,0xC0,
	0xC0,0xC0,0xC0,0xC0,0x40,0xC0,0xC0,0xC0,0x40,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0x40,0xC0,0xC0,0xC0,0x40,
	0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0x40,0xC0,0xC0,0xC0,0x40,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0x40,0xC0,0xC0,
	0xC0,0x40,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0x40,0xC0,0xC0,0xC0,0x40,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,
	0xC0,0xC0,0xC0,0xC0,0x7F,0x7F,0x7F,0x3F,0x3F,0x3F,0x1F,0x1F,0x03,0x01,0x00,0x00,0x00,0x01,0x00,0x00,
	0x00,0x01,0x01,0x01,0x01,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x01,0x03,0x03,0x01,0x00,0x00,0x00,0x01,
	0x00,0x00,0x00,0x01,0x03,0x03,0x01,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x01,0x03,0x03,0x01,0x00,0x00,
	0x00,0x01,0x00,0x00,0x00,0x01,0x03,0x03,0x01,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x01,0x03,0x03,0x01,
	0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x01,0x03,0x03,0x01,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x01,0x03,
	0x1F,0x1F,0x3F,0x3F,0x3F,0x7F,0x7F,0x7F
};

const uint8_t tube_TPLAQUE[] PROGMEM = {
	9,2,
	0x00,0xE8,0xDC,0xDF,0xDC,0xE8,0x00,0x00,0x00,
	0x00,0x05,0x0F,0x0F,0x0F,0x0D,0x0C,0x08,0x00,
	0x00,0x7A,0xBF,0xBF,0xBF,0x7B,0x03,0x01,0x00,
	0x00,0x01,0x03,0x0F,0x03,0x01,0x00,0x00,0x00,
	0x00,0xE8,0xDC,0xDF,0xDC,0xE8,0x00,0x00,0x00,
	0x00,0x02,0x07,0x07,0x07,0x06,0x06,0x04,0x00,
	0x00,0x74,0xBE,0xBE,0xBE,0x76,0x06,0x02,0x00,
	0x00,0x01,0x03,0x0F,0x03,0x01,0x00,0x00,0x00,
	0x00,0xD0,0xB8,0xBE,0xB8,0xD0,0x00,0x00,0x00,
	0x00,0x02,0x07,0x07,0x07,0x06,0x06,0x04,0x00,
	0x00,0xB4,0xDE,0xDE,0xDE,0xB6,0x06,0x02,0x00,
	0x00,0x00,0x01,0x07,0x01,0x00,0x00,0x00,0x00,
	0x00,0xA0,0x70,0x7C,0x70,0xA0,0x00,0x00,0x00,
	0x00,0x02,0x03,0x03,0x03,0x02,0x02,0x00,0x00,
	0x00,0x54,0xEC,0xEC,0xEC,0x54,0x04,0x00,0x00,
	0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};

const uint8_t teeth_up_TPLAQUE[] PROGMEM = {
	//11,1,
	0x78,0xFE,0xFF,0x6E,0x7C,0x5E,0x87,0xFE,0x78,0x00,0x00
};

const uint8_t teeth_DOWN_TPLAQUE[] PROGMEM = {
	//11,2,
	0x80,0xC0,0xC0,0x80,0x80,0x80,0x40,0xC0,0x80,0x00,0x00,
	0x07,0x1F,0x3F,0x1D,0x0F,0x1E,0x38,0x1F,0x07,0x00,0x00
};

const uint8_t BALISTIC_TPLAQUE[] PROGMEM = {1,1,0b00011000};

const uint8_t FOOD_TPLAQUE[] PROGMEM = {
	6,1,
	0x30,0x78,0x68,0x32,0x01,0x01,
	0x18,0x2C,0x34,0x2C,0x34,0x18,
	0x0A,0x3E,0xFF,0xED,0x36,0x0A,
	0x00,0xFC,0x02,0x02,0x04,0x00,
	0x1C,0x3A,0x32,0x32,0x3A,0x1C,
	0x54,0xC6,0xD6,0xD6,0xC6,0x54,
};

const uint8_t police_TPLAQUE[] PROGMEM = {
	4,1,
	0x1F,0x11,0x1F,0x00,0x00,0x1F,0x00,0x00,0x1D,0x15,0x17,0x00,0x11,0x15,0x1F,0x00,0x07,0x04,0x1F,0x00,
	0x17,0x15,0x1D,0x00,0x1F,0x15,0x1D,0x00,0x01,0x1D,0x03,0x00,0x1F,0x15,0x1F,0x00,0x17,0x15,0x1F,0x00
};

const uint8_t ExtraTeeth_TPLAQUE[] PROGMEM = {
	0x00,0x0F,0x1F,0x0E,0x1F,0x0F
};

const uint8_t START_TPLAQUE[] PROGMEM = {
	52,2,
	0xFE,0x01,0x01,0x91,0x29,0x49,0x91,0x01,0x09,0xF9,0x09,0x01,0xF1,0x29,0x29,0xF1,0x01,0xF9,0x29,0x29,
	0xD1,0x01,0x09,0xF9,0x09,0x01,0x01,0x01,0x01,0xF1,0x09,0x49,0xD1,0x01,0xF1,0x29,0x29,0xF1,0x01,0xF9,
	0x11,0x21,0x11,0xF9,0x01,0xF9,0x29,0x09,0x01,0x01,0x01,0xFE,0x07,0x08,0x08,0x08,0x09,0x09,0x08,0x08,
	0x08,0x09,0x08,0x08,0x09,0x08,0x08,0x09,0x08,0x09,0x08,0x08,0x09,0x08,0x08,0x09,0x08,0x08,0x08,0x08,
	0x08,0x08,0x09,0x09,0x09,0x08,0x09,0x08,0x08,0x09,0x08,0x09,0x08,0x08,0x08,0x09,0x08,0x09,0x09,0x09,
	0x08,0x08,0x08,0x07
};
