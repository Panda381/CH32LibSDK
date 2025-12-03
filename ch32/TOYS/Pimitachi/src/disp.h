
// ****************************************************************************
//
//                                 Display
//
// ****************************************************************************
// OLED I2C 0.96" SSD1306 display, resolution 128x64 pixels, controller SSD1306, power 3 to 5V.
// https://pajenicko.cz/graficky-oled-displej-096-128x64-i2c-bily

#ifndef _DISP_H
#define _DISP_H

#ifdef __cplusplus
extern "C" {
#endif

// start I2C communication (on start, SDA and SCL must be high)
void DispI2C_Start(void);

// stop I2C communication
void DispI2C_Stop(void);

// write a byte over I2C
void DispI2C_Write(u8 data);

// Display select SSD1306 page 0..7, start transfer data
void DispI2C_SelectPage(int page);

// send command to the display
void DispCmd(u8 cmd);

// display ON
void DispOn(void);

// display OFF
void DispOff(void);

// Display update - send frame buffer to the display
void DispUpdate();

// Display initialize (port clock must be enabled)
void DispInit(void);

#ifdef __cplusplus
}
#endif

#endif // _DISP_H
