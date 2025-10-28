/*
 * FastTinyDriver.h
 * Copyright (c) 2025 Électro L.I.B Daniel C. electro_l.i.b@tinyjoypad.com
 *  https://github.com/phoenixbozo/TinyJoypad/tree/main/TinyJoypad
 *                    https://WWW.TINYJOYPAD.COM
 *          https://sites.google.com/view/arduino-collection
 * Developed with the assistance of Grok, an AI developed by xAI
 *
 * Description:
 * FastTinyDriver is an optimized graphics driver designed to work with 
 * ATtiny85 microcontrollers, particularly for the Tinyjoypad game console. 
 * This file contains the OLED driver code used in games developed for 
 * the ATtiny85. Although it is an integral part of each game code, 
 * FastTinyDriver is also designed to be used in other projects 
 * that require an OLED display based on the SSD1306 controller.
 *
 * This code is based on general knowledge of I2C programming and 
 * standard SSD1306 commands, as specified in the datasheet.
 *
 * **IMPORTANT**: This program is licensed under the GNU General Public License version 3 (GPLv3).
 * You can redistribute and/or modify it under the terms of the GPLv3, 
 * as published by the Free Software Foundation.
 *
 * This license grants you the right to use, modify, and share this software. 
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; 
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this program. 
 * If not, see <http://www.gnu.org/licenses/>.
 *
 * **IMPORTANT NOTE**: If this code is to be used for purposes other than the Tinyjoypad ATtiny85, 
 * it is imperative to remove the #define TINYJOYPAD_ASM_DRIVER to use the portable version 
 * of FastTinyDriver. Failing to do so may cause issues.
 *
 * for TINY JOYPAD rev2 (attiny85)
 * the code work at 16MHZ internal
 */

// -----------------------------------------
// BabyBoy adaptation: Miroslav Nemecek 2025
// -----------------------------------------

#ifndef FASTTINYDRIVER_H
#define FASTTINYDRIVER_H

#define TINYJOYPAD_LEFT KeyPressed(KEY_LEFT) //(analogRead(A0) >= 750) && (analogRead(A0) < 950)
#define TINYJOYPAD_RIGHT KeyPressed(KEY_RIGHT) //(analogRead(A0) > 500) && (analogRead(A0) < 750)
#define TINYJOYPAD_DOWN KeyPressed(KEY_DOWN) //(analogRead(A3) >= 750) && (analogRead(A3) < 950)
#define TINYJOYPAD_UP KeyPressed(KEY_UP) //(analogRead(A3) > 500) && (analogRead(A3) < 750)
#define BUTTON_DOWN (KeyPressed(KEY_A) || KeyPressed(KEY_B)) //(digitalRead(1) == 0)
#define BUTTON_UP (!KeyPressed(KEY_A) && !KeyPressed(KEY_B)) //(digitalRead(1) == 1)

// Fonction d’initialisation complète de l’écran OLED pour Tinyjoypad
INLINE void TinyOLED_init(void) {}

// select output page (1 page = 8 lines)
INLINE void ssd1306_selectPage(uint8_t page) { DispI2C_SelectPage(page); }

// write 1 byte to display
INLINE void i2c_write(uint8_t data) { DispI2C_Write(data); }

// Fonction d’arrêt de la communication I2C (exposée pour usage externe)
INLINE void i2c_stop(void) { DispI2C_Stop(); }

#endif /* FASTTINYDRIVER_H */
