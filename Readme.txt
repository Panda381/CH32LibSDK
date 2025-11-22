CH32LibSDK - SDK library for low-end CH32 RISC-V microcontrollers
=================================================================
Pre-alpha version 0.37, under development.

Copyright (c) 2025 Miroslav Nemecek

Panda38@seznam.cz
hardyplotter2@gmail.com
https://github.com/Panda381/CH32LibSDK
https://www.breatharian.eu/hw/ch32libsdk/index_en.html

How to compile on Windows, using command line:

- Use FAR Manager to edit source files and run BAT scripts.
- Download MounRiver Studio v1.92 http://mounriver.com/download
- Install MounRiver Studio. 
- Extract "toolchain\RISC-V Embedded GCC12" compiler to separate folder.
- Edit _c1.bat file and enter path to "bin" folder of the compiler:
   set GCC_CH32_PATH=C:\GCC_CH32\bin
- Extract "toolchain\OpenOCD\bin" tool or use openocd from _tools\openocd.
- Sometimes you may need to use WCH-LinkUtility from the ExTool\SQWTool folder.
  It may sometimes be necessary to erase the flash memory using power-off,
  because OpenOcd cannot do this.
- Compile sample using c.bat.
- Flash compiled sample using e.bat with WCH-LinkE programmer (available here,
  for example: https://pajenicko.cz/usb-programator-a-debug-adapter-wch-link ).
  For the SD card version of the console, simply upload the program to the
  SD card and load it into the processor using the boot loader.
- Clear compilation using d.bat.


AntCalc
-------
AntCalc is a wrist-worn programmable calculator with scientific functions. It
features an inexpensive CH32V002A4M6 processor, a blue-yellow 0.96" I2C OLED
display with an SSD1306 controller and a resolution of 128x64 pixels B&W
(available here, for example:
https://www.hadex.cz/m508c-displej-oled-096-128x64-znaku-iici2c-4piny-modrozluty/).
It also has 12 buttons and is powered by a CR2032 battery. The calculator works
with reverse Polish notation (RPN), which means that numbers are first entered
into the calculator's stack using the Enter button, and then the desired
operation is performed by pressing the operator. The calculator's stack has a
size of 10 registers. The lowest 4 registers are shown on the display under the
names X, Y, Z, and T. The calculator calculates in BCD code with an accuracy of
21 valid digits, along with an exponent in the range of +-99. The display shows
a maximum of 14 digits when displayed without an exponent or 11 digits with an
exponent. Functions are available for calculating direct and inverse
trigonometric functions, power function, decimal and natural logarithmic and
exponential functions. The calculator has 10 memory registers, the contents of
which are stored in flash memory even when the calculator is turned off. The
calculator can be programmed using macros containing a record of keystrokes.
Up to 10 macros, each up to 38 keys long, can be loaded into the calculator's
memory. The calculator measures 30x55 mm. A jumper is used as a switch on the
connector, which is also used to program the processor.

AntCalc calculator functions

The calculator is operated using 12 buttons. 10 buttons are digits, 1 button
is a decimal point, and 1 button is 2nd for switching between modes. In total,
you can switch between 7 states by repeatedly pressing the 2nd button. If an
error occurs during operations (division by zero or square root of a negative
number), the text "overflow" is displayed on the X register row. Pressing any
key will end the error messages and reset the X register.

0..9 ... enter a digit.

. ... Enter a decimal point. If the calculator is in exponent editing mode,
   you can use the decimal point button to return to mantissa editing.

2nd ... Switch between additional calculator functions. The selected mode is
   displayed on the top line of the display on the left.

+, -, *, :, Y^x (2nd 0..4) ... arithmetic operations between registers X and Y

y<>x (2nd 5) ... swap registers X and Y

Vx (2nd 6) ... square root

Enter (2nd 7) ... move number X to register Y

CE (2nd 8) ... Delete the last character during editing. The EE key switches to
   exponent editing, the dot key switches to mantissa editing. The CE key
   activates number editing mode if editing is not in progress.

EE (2nd 9) ... Enter exponent. Use the EE key to start editing the number shown
   on the display. Use the decimal point key to switch to mantissa editing.

+/- (2nd .) ... Change the sign of the mantissa or exponent of the number on
   the display.

sin (2x2nd 0) ... sine

asin (2x2nd 1) ... arc sine

log (2x2nd 2) ... decimal logarithm

ln (2x2nd 3) ... natural logarithm

cos (2x2nd 4) ... cosine

acos (2x2nd 5) ... arccosine

exp10 (2x2nd 6) ... decimal exponent

exp (2x2nd 7) ... natural exponent

tan (2x2nd 8) ... tangent

atan (2x2nd 9) ... arctangent

1/x (2x2nd .) ... reciprocal value

RCL0..RCL9 (3x2nd 0..9) ... recall memory contents 0 to 9

PI (3x2nd .) ... Pi number

STO0..STO9 (4x2nd 0..9) ... Saving a number to memory 0 to 9. The content is
   stored in flash memory even when the device is turned off.

DEG (4x2nd .) ... Switching the angular measure of goniometric functions
   between degrees (DEG) and radians (RAD). The selected setting is displayed
   in the middle of the top line of the display and is stored in flash memory.

RUN0..RUN9 (5x2nd 0..9) ... Play macro number 0 to 9.

INT (5x2nd .) ... Cut off the decimal part of the number (rounding to whole
   numbers towards zero).

PRG0..PRG9 (6x2nd 0..9) ... Start recording a macro into program number 0 to 9.
   The codes of the pressed keys are stored in memory. Up to 38 button codes
   can be stored in one macro. Presses of the 2nd button are not stored in the
   program - the resulting function code is stored as 1 code. During macro
   recording, the text PROG0..PROG9 flashes in the upper right corner of the
   display, indicating that recording is in progress. If the number of buttons
   is exceeded, the indicator remains lit but stops flashing to indicate that
   buttons are no longer being stored. Macro recording can be stopped by
   pressing any of the PRG0 to PRG9 functions (it is not necessary to use the
   same macro number).

C (6x2nd .) ... Clears the calculator's registers. The contents of the memory
   and programs are retained. Turning the calculator off and on has the same
   effect.

Notes on construction:

The calculator uses a very inexpensive Chinese processor CH32V002A4M6. It is
housed in an SOP16 package with large pin spacing, making the calculator's
design suitable even for novice designers. The calculator has two eyelets on
the bottom for attaching a strap. To simplify the design, a jumper plugged into
the connector, which is also used to program the calculator's processor, was
used as a switch. When switched on, the jumper is plugged into the two pins on
the right, and when switched off, it is plugged into the two pins on the left.
A two-color, blue-yellow OLED display with an SSD1306 controller and a
resolution of 128x64 was used. The display is actually monochrome, with the top
16 lines displayed in yellow and the next 48 lines in blue. Alternatively, a
monochrome display can also be used. I leave the design of the top cover with
button labels to other designers – in the prototype, I only used a paper label
with cut-out holes for the buttons.

>>> Source codes and all necessary documentation of the AntCalc calculator can
be found in the CH32LibSDK library in the ch32\DEVICE\ folder.
https://github.com/Panda381/CH32LibSDK/tree/main/ch32/DEVICE <<<


BeatleBoyPad (BeatleBoy, BeatlePad)
-----------------------------------
BeatleBoyPad is dual console with interchangeable ROM cartridges. It consists
of two consoles. The first console, BeatleBoy, contains 128x64 pixel black and
white OLED I2C display with SSD1306 controller, built-in speaker and 6 buttons
(4 directional arrows and A and B buttons). The console is powered by CR2032
battery. The second console, BeatlePad, has black and white output to VGA
monitor and connector for external speaker. Cartridge with program contains
cheap Chinese processor CH32V002J4M6, CH32V003J4M6 or CH32V006F8P6. Note: for
processor V006 different cartridge wiring than for processors V002 and V003 is
used.

The cartridges are common to both consoles. The processor in the cartridge
distinguishes between the two consoles based on the voltage and switches to
the appropriate mode accordingly. Due to the console's auto-detection, it is
therefore necessary to maintain the power supply used - the BeatleBoy console
is powered by a 3V battery, while the BeatlePad console is powered by a 5V
external source. In addition to detecting the supply voltage, the processor
in the BeatlePad console also detects the connection of a VGA cable. The
program in the console will only start after connecting a VGA monitor. This
is so that the cartridge can be reprogrammed in the programmer, as the VGA
console also uses programming pin.

There are 25 games available for the console. All prepared games can be
programmed into all types of cartridges - with V002, V003, or V006 processors.
The V002 processor variant has more RAM available than the V003 processor, and
the output to the VGA monitor is via SPI controller, which allows the use of
higher video mode resolutions (this is not used in the prepared games). The
V006 processor has more RAM than the V002 processor. However, unless required
by the software, it is recommended to use the CH32V003J4M6 processor. Although
this is an older type of processor, its advantage is higher oscillator
stability and therefore less noise in the VGA image.

When constructing the device, it is necessary to use resistors with 1%
accuracy, otherwise button presses may be detected incorrectly. The
brightness of the OLED display is kept low to minimize battery consumption.
The current voltage of the CR2032 battery is displayed when most programs
start. The measurement is performed using the internal reference of the
processor, and therefore the displayed value may vary by up to 10% and
should therefore be taken as a guide only. Pay attention to the pin layout
of the display - there are usually two versions, with the pin order
VCC-GND-SCL-SDA or GND-VDD-SCL-SDA. Both variants are available on the
printed circuit board (alternatively, the display can be connected
interchangeably via a pin header). The OLED display is used here in an
inverted position compared to other consoles - the image rotation is defined
in the display initialization sequence.

An internal HSI RC oscillator is used for VGA image output. Its frequency is
not stabilized by a crystal, so slight signal timing deviations and image
noise must be expected. The V003 processor has slightly lower image noise than
the V002 and V006 processors. Some VGA monitors may not display the image due
to the low quality of the image signal timing.

Programs can be loaded into the cartridge using the WCH-LinkE programmer
(available, for example, here:
https://pajenicko.cz/usb-programator-a-debug-adapter-wch-link). Pin number 4
on the cartridge is left as an option for reprogramming processors requiring
2-wire programming (SWDIO+SWCLK, e.g., CH32X035). Currently, this option is
not used, and it is possible to use this pin as a blind pin to facilitate
cartridge insertion orientation (i.e., cut off pin number 4 on the cartridge
and plug the corresponding pin on the console, e.g., with heat shrink tubing).


BeatleCalc with emulation of Sinclair Scientific and Datamath calculators
-------------------------------------------------------------------------
BeatleCalc is a minimalist scientific calculator, supplemented with emulators
of calculators Sinclair Scientific (1974, TMC0805 processor) and Texas
Instruments TI-2500 Datamath (1972, TMS0803 processor). The calculator uses BCD
code internally, so it does not suffer from the inaccuracies of binary
representation of decimal numbers. It calculates internally with an accuracy
of 13 digits. The exponent ranges from -99 to +99. It includes calculations
of direct and inverse trigonometric functions, in radians and degrees, natural
and decimal logarithmic and exponential functions, powers and roots. It prefers
operation priority, and parentheses can also be used. Numbers can be stored in
4 memory registers, which retain their value even when the power is turned off.

Switching the calculator mode between emulation or BeatleCalc calculator:

- Press and hold the number 1 to 3: 1 selects the default BeatleCalc
  calculator, 2 selects Sinclair Scientific emulation, 3 selects Datamath
  emulation.
- Press the C button briefly. This will reset the calculator.
- Release the number 1 to 3 key. While you hold the key, the selected mode text
  will appear on the display: "CALCUL" is the default BeatleCalc calculator,
  "SINCLAIr" is Sinclair Scientific emulation, and "DATAMATH" is Datamath
  emulation.

Controls for emulated calculators can be found in the relevant calculator
manuals. Please note that the Sinclair calculator uses RPN reverse logic
- you must first enter the number and then the desired operation (typically '+'
is used to insert a number into the stack). Emulators use only some of the
calculator buttons - the layout of the buttons used can be seen in the pictures
of the calculator labels.

BeatleCalc calculator functions:

STO1..STO4 ... Stores the number on the display in memory registers 1 to 4.
   The number is stored in the flash memory of the second CPU2 processor and
   remains available even after the power is turned off.

RCL1..RCL4 ... Displaying a number from memory registers 1 to 4.

CE ... Clearing the last digit or turning off the error indicator. If an
   unedited number is displayed, the calculator switches to edit mode.

2nd, 3rd ... Selection of alternative functions. An indicator appears at the
   first position on the display (2nd=upper line, 3rd=lower line).

= ... Calculation of the expression. Repeated pressing repeats the last
   operation with the last operand.

EE ... Exponent input mode. If an unedited number is displayed, the calculator
   enters exponent edit mode. Press the decimal point key to enter mantissa
   edit mode.

LOG, EXP10 ... Logarithmic and exponential functions with a decimal base.

LN, EXP ... Logarithmic and exponential functions with a natural base.

TAN, ATAN, SIN, ASIN, COS, ACOS ... Trigonometric functions calculated in
   radians.

TAND, ATAND, SIND, ASIND, COSD, ACOSD ... Trigonometric functions calculated
   in degrees.

Notes on construction:

Two CH32V002A4M6 processors were used in the calculator. The reason for this
choice (apart from the low price) is that they are easy to solder, which is
also suitable for beginners. The CPU1 processor is the main processing unit.
The CPU2 processor controls the display multiplexer and is used to store the
configuration and memory registers. The photos show a prototype of the
calculator – I focused primarily on the calculator software, not the design,
so I recommend choosing your own calculator design. A printed circuit board can
be used as the top cover of the calculator. For the prototype, I printed the
label on paper, covered it with transparent adhesive tape on both sides, and
cut out the holes for the buttons with a skin punch. I recommend covering the
display with red Plexiglas, otherwise it may be difficult to read in bright
light. The capacitors should be soldered horizontally so that they do not
interfere with the top cover. I used a 1-digit LED display as the digit in the
first position. You do not have to use it, because only the sign of the number
and the indicators for the 2nd and 3rd buttons (segments A, D, and G) are
displayed in this position. You can replace the digit display with a flat red
LED connected between signals D1 and SG. The 2nd and 3rd indicators are not
necessary. I did not solve the power supply issue in the prototype. It is also
possible to use, for example, a 3.7V battery with a charging circuit. A CR2032
battery may not be powerful enough, as the display may have a high power
consumption.

The calculator firmware consists of two parts. In the ch32\DEVICE\BeatleCalc
folder, you will find the main executive firmware, which you will upload to the
CPU1 processor (e.g., using the WCH-LinkE programmer:
https://pajenicko.cz/usb-programator-a-debug-adapter-wch-link).
The ch32\DEVICE\BeatleCalc_CPU2 folder contains the firmware for the second
processor, CPU2. Until the firmware is loaded into both processors and
communication between them is working, the display will remain dark. If you
need to find a malfunction, use the ch32\DEMO\LED program, in which you will
enter the appropriate pins and use the control LED to check whether the signals
are OK.

Note: Calculator emulation was verified using the emulator
https://static.righto.com/calculator/sinclair_scientific_simulator.html by
Ken Shirriff. No physical calculators were available to verify functionality,
so it is possible that the calculators' functions may not correspond exactly
to the original.

>>> Source codes and all necessary documentation can be found in the CH32LibSDK
  library in the ch32\DEVICE\ folder. <<<


BabyBoy
-------
BabyBoy is the simplest game mini-console with 6 buttons, an inexpensive
CH32V002A4M6 processor (price 10 cents), a built-in speaker, and 128x64 pixel
black-and-white OLED I2C display with an SSD1306 controller. The console is
powered by a CR2032 battery, or it can be powered by an external 3.3V source
via the programming connector. Thanks to simplifications and the easy soldering
of the processor in the SOP16 package with a pin pitch of 1.27mm, the console
is primarily intended for beginners as a kit for their first introduction to
electronics.

Pay attention to the pin layout on the display – there are usually two
versions, with the pin order VCC-GND-SCL-SDA or GND-VDD-SCL-SDA. I used two pin
headers on the circuit board for both display versions so that I could change
the displays and insert them into the correct position.

BabyBoy does not include an SD card. Programs must be uploaded to the processor
using the WCH-LinkE programmer (available here, for example:
https://pajenicko.cz/usb-programator-a-debug-adapter-wch-link).


BabyPad
-------
BabyPad is a mini game console with 7 buttons, CH32V002A4M6 processor,
25 MHz crystal (optional), audio output, and VGA mono B&W output to a
monitor. The crystal and associated capacitors are not required - if
the software detects that the crystal is not available, it will use the
internal HSI oscillator, tuned to a frequency close to 25 MHz. In this
case, the image will be slightly noisy, but still usable - it depends
on the monitor used how well it handles image stabilization. BabyPad
uses a processor in an SOP16 package with a pin pitch of 1.27 mm, which
makes soldering easy even for beginners. Together with its simple design
(and the option of not installing a crystal), it is primarily intended
for beginners as a kit for their first introduction to electronics.

BabyPad does not include an SD card. Programs must be uploaded to the
processor using the WCH-LinkE programmer (available here, for example:
https://pajenicko.cz/usb-programator-a-debug-adapter-wch-link).

In the _devices\babypad\diagram\ folder, you will find diagram of the
BabyPad console. In the !Babypad folder, you will find a ready-made
sample programs for the BabyPad. The Babypad folder contains source
codes of sample applications for BabyPad.


BabyPC - WCH80
--------------
The BabyPC - WCH80 is an inexpensive mini-computer with two CH32V002
processors, created based on the ZX80 computer. It is not an emulator;
the computer does not emulate the ZX80 computer's ROM, nor does it emulate Z80
machine instructions. It was created as a completely independent computer with
the BASIC80 programming language and VGA monitor output, only replicating the
ZX80's functionality as closely as possible. It uses a CH32V002A4M6 processor,
which, thanks to its large 1.27 mm pin pitch, is suitable for easy soldering
even for novice designers. Together with other THT components, the WCH80 is
particularly suitable as a kit for novice designers. The built-in BASIC80
programming language is used to familiarize users with computer programming and
to try out how programmers programmed in the 1980s.

The computer does not contain a storage medium for saving programs. Your own
programs can be saved directly to the processor's flash memory. There are 14
memory slots available, i.e. 14 places to store your own programs, numbered 0
to 13. Slot 0 is located in the main CPU1 processor. When stored in slot 0,
data variables are also stored along with the program (more precisely, only the
first half of the memory with variables). Slot 0 is automatically loaded into
the program memory when the computer is turned on. Memory slots 1 to 13 are
located in the second processor, CPU2. All slots allow the entire memory with
the program to be stored, except for the last slot 13, which is only half the
size.

After initial programming, the processors contain 28 sample programs and games
written in BASIC80. Once the processors have been programmed, the programmer is
no longer needed, but it can be useful if you want to back up the contents of
the processors to a PC or if you want to change program versions. Using slot 0,
programs can also be transferred between the processors' memory backups by
copying between the CPU1 and CPU2 processors.

In addition to the BASIC80 firmware, games and programs written in C can also
be uploaded to the computer using a programmer. There are 25 sample games
available. The games can be found in the CH32LibSDK library. However, it is
important to remember that reprogramming the CPU1 processor will also overwrite
the contents of slot 0. The contents of slots 1 to 13 in CPU2 will not change
when games are loaded. For games in C code, the following keys are usually used
for control: 8, F=right, 7, E=up, 5, S=left, 6, D=down, A, space=action, B,
NEW LINE=alternative action, X, P=info, Y, 0=back.

More details and supporting documents can be found on a separate page:
https://www.breatharian.eu/hw/wch80/index_en.html or on GitHub:
https://github.com/Panda381/WCH80.


Pidiboy
-------
PidiBoy is a mini game console with 7 buttons, an inexpensive CH32V006F8P6
processor (costing 20 cents), a microSD card, a built-in speaker, audio
output, and a 128x64 pixel black-and-white OLED I2C display with an SSD1306
controller. https://pajenicko.cz/graficky-oled-displej-096-128x64-i2c-bily
The console is equipped with an ME2108A33PG step-up voltage converter
with a 3.3V output and can therefore be operated from 1 or 2 AA or AAA
batteries in the voltage range of 1.1V to 3.3V, or the console can be
powered by an external 3.3V source via the programming connector. Programs
can be run from an SD card using a boot loader, which loads the program into
the processor's flash memory. Boot loader controls: up/down arrows - move the
cursor by 1 item, left/right arrows - move the cursor by 1 page, A - start
program or change folder, B - display voltage or move to parent folder, Y -
run program located in flash memory. Pay attention to the pin layout on the
display – there are usually two versions, with the pin order VCC-GND-SCL-SDA
or GND-VDD-SCL-SDA. I used two pin headers on the circuit board for both
display versions so that I could change the displays and insert them into the
correct position.

Programs compiled for PidiBoy contain a boot loader. Writing to flash memory
using a programmer writes both the program and the boot loader. Pressing the Y
button (or resetting with an SD card inserted) launches the boot loader,
allowing you to select the program to be run from the SD card. The boot loader
ensures that the program is loaded from the SD card into the flash memory.
Another program can be loaded by pressing Y or by resetting with an SD card
inserted. If no SD card is inserted after resetting, the boot loader will not
start, but the program in the flash memory will start immediately. The program
in the flash memory can also be started from the boot loader by pressing the Y
button.

BIN and ELF files are provided with a checksum during compilation using the
LoaderCrc program. Checksum is used by the boot loader to check the application
in flash memory. If you want to load the application into flash memory using
WCH-LinkUtility, you must use a BIN file and not a HEX file, because the
generated HEX file does not have a checksum.

In the _devices\pidiboy\diagram\ folder, you will find diagram of the PidiBoy
console. In the !Pidiboy folder, you will find a ready-made SD card image.
The Pidiboy folder contains source codes of sample applications for PidiBoy.


Pidipad
-------
Pidipad is mini game console with 8 buttons, CH32V006E8R6 processor,
25 MHz crystal (optional), microSD card, audio output, and VGA output
to monitor. The crystal and associated capacitors do not need to be
used - if the software detects that the crystal is not present, it will
use the internal HSI oscillator, tuned to a frequency close to 25 MHz.
In this case, the image will be slightly noisy, but still usable - it
depends on the monitor used how well it handles image stabilization.

Programs compiled for PidiPad contain a boot loader. Writing to flash
memory using a programmer writes both the program and the boot loader.
Pressing the Y button (or resetting with an SD card inserted) launches
the boot loader, allowing you to select the program to be run from the
SD card. The boot loader ensures that the program is loaded from the SD
card into the flash memory. Another program can be loaded by pressing Y
or by resetting with an SD card inserted. If no SD card is inserted after
resetting, the boot loader will not start, but the program in the flash
memory will start immediately. The program in the flash memory can also
be started from the boot loader by pressing the Y button.

BIN and ELF files are provided with a checksum during compilation using
the LoaderCrc program. This is used by the boot loader to check the
application in flash memory. If you want to load the application into
flash memory using WCH-LinkUtility, you must use a BIN file and not a HEX
file, because the generated HEX file does not have a checksum.

In the _devices\pidipad\diagram\ folder, you will find diagram of the
PidiPad console. In the !Pidipad folder, you will find a ready-made SD
card image. The Pidipad folder contains source codes of sample
applications for PidiPad.


TweetyBoy
---------
TweetyBoy is a mini game console with 8 buttons, a low-cost CH32X035G8R6
processor (price: 50 cents), a microSD card, a built-in speaker, audio output,
and 160x80 pixel LCD SPI color display with an ST7735S controller
https://pajenicko.cz/komponenty/displeje/barevny-displej-ips-0.96-80x160-st7735s-spi.
The console is equipped with an ME2108A33PG step-up voltage converter with
a 3.3V output and can therefore be operated from 1 or 2 AA or AAA batteries in
the voltage range of 1.1V to 3.3V, or the console can be powered by an external
3.3V source via the programming connector. Programs can be run from an SD card
using a boot loader, which loads the program into the processor's flash memory.
Boot loader controls: up/down arrows - move the cursor by 1 item, left/right
arrows - move the cursor by 1 page, A - start program or change folder, B -
display voltage, adjust display brightness, or move to parent folder, Y - start
the program located in the flash memory.

The brightness of the LCD display can be adjusted from the boot loader by
pressing the B button. The display brightness can be adjusted in 9 steps, from
1 to 9. Complete dimming of the display (level 0) is not possible to prevent
the console from becoming uncontrollable. When powered by battery, it is
recommended to keep the display brightness as low as possible to minimize
battery consumption. The display has a power consumption of 0.5mA to 17mA from
a 3.3V source, at brightness levels 1 to 9. Each 1-step decrease in display
brightness represents a reduction in display power consumption by almost half.
The default brightness value of 6 means a display consumption of 3mA. The
processor consumption is about 6mA. However, this is the consumption from a
3.3V source. The battery consumption is about 3 times higher due to the step-up
converter voltage transformation.

Programs compiled for TweetyBoy contain a boot loader. When writing a program
to flash memory using a programmer, both the program and the boot loader are
written. Pressing the Y button (or resetting with an SD card inserted)
launches the boot loader, which allows you to select the program to be run
from the SD card. The boot loader ensures that the program is loaded from the
SD card into flash memory. Another program can be loaded by pressing the Y
button or by resetting with the SD card inserted. If no SD card is inserted
during the reset, the boot loader will not start, but the program in flash
memory will start immediately. The program in flash memory can also be started
from the boot loader by pressing the Y button.

BIN and ELF files are provided with a checksum during compilation using
the LoaderCrc program. This is used by the boot loader to check the
application in flash memory. If you want to load the application into
flash memory using WCH-LinkUtility, you must use a BIN file and not a HEX
file, because the generated HEX file does not have a checksum.

In the _devices\tweetyboy\diagram\ folder, you will find diagram of the
TweetyBoy console. In the !Tweetyboy folder, you will find a ready-made SD
card image. The Tweetyboy folder contains source codes of sample
applications for TweetyBoy.


XTree
-----
XTree is a Christmas tree-shaped pendant with a CH32V002J4M6 processor, 12
flashing LEDs, and a speaker that plays "Jingle Bells." XTree is powered by a
CR2032 battery. A label with a picture of a Christmas tree and, optionally, a
star is glued to the front. Only the LEDs are on the front; all other
components are soldered to the back of the circuit board. The components used
should be easy to solder, even for novice designers. On the bottom edge is a
connector for programming the processor, which also serves as a switch -
inserting the jumper on the right side of the connector turns XTree on. The
jumper also represents the trunk of the tree. When turned off, the jumper can
be inserted on the left side of the connector. High-brightness LEDs should be
used, otherwise they may have low brightness. Matte LEDs would be more
suitable, but they have lower brightness. Alternatively, reduce the resistor
values. On the other hand, low LED brightness ensures lower battery consumption
- the consumption is around 8mA. The sound from the speaker is not very loud,
but it should be enough so that the music is not too distracting. In the
prototype, I used wires instead of the top layer of the printed circuit board
- I recommend using a double-sided printed circuit board, or even one with a
printed image.

>>> The source codes and all necessary XTree documentation can be found in the
CH32LibSDK library in the ch32\TOYS\XTree folder.
https://github.com/Panda381/CH32LibSDK/tree/main/ch32/TOYS/XTree <<<


MiniDice
--------
MiniDice is an electronic dice with 7 LEDs, a CH32V002J4M6 processor, and a
CR2032 battery. The dice is activated by pressing it against the table - there
is a microswitch on the bottom. A 4-pin pin header with a jumper serves as a
power switch, and is also used to program the processor. However, it is not
necessary to use the power switch. The dice automatically turns off 10 seconds
after the last use and enters power-saving mode, when it consumes only 10uA
from the battery. If you do not need to program the processor, you can remove
the programming connector and connect the BAT and VCC pins. In power-saving
mode, the battery should last 1 to 2 years. Alternatively, remove the battery
if you are not going to use it for a long time.

Only 7 LEDs are located on the top of the circuit board; all other components
are soldered to the bottom of the circuit board. In the prototype, I used wires
instead of one layer of printed circuit board. You will certainly use a
double-sided printed circuit board. I used TS6604B-7.0 with a 3.5mm tactile
length as the activation microswitch. Two layers of foam rubber are glued to
the sides from below for cushioning, so that the dice stands upright on the
table and can be easily pressed. I printed the top label on an inkjet printer,
glued it on, and covered it with transparent adhesive tape. You will probably
use printing on the printed circuit board. When soldering the battery holder,
be careful not to short-circuit the middle LED - if necessary, bend the battery
holder slightly in that spot. If the battery is too difficult to insert, bend
the pressure springs of the battery holder.

>>> The source codes and all necessary MiniDice documentation can be found in
the CH32LibSDK library in the ch32\TOYS\MiniDice folder.
https://github.com/Panda381/CH32LibSDK/tree/main/ch32/TOYS/MiniDice <<<


Magic Beater
------------
Magic Beater is a simple sound synthesizer-sequencer controlled by photosensor,
with processor CH32V002J4M6. It allows you to play rhythms and melodies that
repeat in a loop. The entire loop is 4 bars long - corresponding to 4 flashes
of the indicator LED. Magic Beater is controlled by 2 buttons. Button A is used
to record the melody. The pitch is determined by the light falling on the
photodiode. The pitch can be controlled by modulating the light. If the tone
range is not suitable (too high or too low), use a different R2 value,
depending on the type of photodiode used. Button B is used to record the
rhythm. Pressing buttons A and B simultaneously resets the memory.

Magic Beater is based on the RaveBOX v1.0 project, created by Vladimir Bartos
https://github.com/Mat0ny/RaveBOX.

>>> The source codes and all necessary Magic Beater documentation can be found
in the CH32LibSDK library in the ch32\TOYS\MagicBeater folder.
https://github.com/Panda381/CH32LibSDK/tree/main/ch32/TOYS/MagicBeater <<<


Pianissimo
----------
Pianissimo is a small electronic piano with a range of 2 octaves, a
CH32V002A4M6 processor, and CR2032 battery power. In addition to basic tones,
it also includes semitones. Using the MODE button, you can record a song up to
75 seconds long. During recording, the MODE button must be held down at all
times. Recording starts when the first tone is pressed while holding down the
MODE button. Pressing the MODE button again (without pressing any tone keys)
will play back the recorded song. Playback can be interrupted by pressing any
key, including the MODE button.

The tones are generated with the correct mutual accuracy of the tones. The time
base is generated by an internal HSI oscillator, which is why the absolute
tuning may deviate by up to 5%. If you connect a 24 MHz crystal to pins 12 and
13, together with 22pF capacitors, you will achieve accurate absolute tuning of
the tones. It is not necessary to change the firmware, but after connecting the
crystal, it is necessary to reset the processor by disconnecting the power
supply. 

The piano is powered by a CR2032 battery. It can also be powered by an external
voltage in the range of 3 to 5V. The programming connector is also used as a
power switch - the device is turned on by connecting a jumper between the BAT
and VCC pins. However, it is not necessary to use the power switch. If you do
not need to program the processor, you can desolder the connector and simply
connect the BAT and VCC pins. If the piano is not used for more than 5 seconds,
the processor goes into power-saving mode, consuming only 10 uA from the
battery. In power-saving mode, the battery will last for about 1 year. If you
need to reprogram the processor, it may not be possible while the processor is
asleep - you must wake up the processor by pressing any key or disconnecting the
power supply, and then start programming the processor within 5 seconds.

>>> The source codes and all necessary Pianissimo documentation can be found in
the CH32LibSDK library in the ch32\TOYS\Pianissimo folder.
https://github.com/Panda381/CH32LibSDK/tree/main/ch32/TOYS/Pianissimo <<<


- In the "_devices\<console>\diagram\" folders, you will find console schematic
  diagrams.

- In the "!<console>" folders, you will find compiled sample programs.

- The "<console>" folders contain the source codes for sample console
  applications.
