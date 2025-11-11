CH32LibSDK - SDK library for low-end CH32 RISC-V microcontrollers
=================================================================
Pre-alpha version 0.32, under development.

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


- In the "_devices\<console>\diagram\" folders, you will find console schematic
  diagrams.

- In the "!<console>" folders, you will find compiled sample programs.

- The "<console>" folders contain the source codes for sample console
  applications.
