
// ****************************************************************************
//
//                           AntCalc - main code
//
// ****************************************************************************

#include "../include.h"

// key level
u8 KeyLevel = KEYLEVEL_1ST;

// Error flag
Bool Error = False;

// programming in progress: 1..PROGNUM, 0=not programming
u8 Programming = 0;

// running in progress
u8 Running = 0; // counter of remaining bytes
u8* RunningPtr = NULL; // pointer to program

// ADC
u32 ADCAcc = 0; // ADC accumulator
int ADCNum = 0; // count of ADC value
u32 ADCStart; // ADC start time
int Supply; // supply voltage in [mV]

// texts of key level status
const char* KeyLevelTxt[KEYLEVEL_NUM] = {
	"1:digi",
	"2:oper",
	"3:func",
	"4:RCL ",
	"5:STO ",
	"6:run ",
	"7:prog",
};

// register name
const char* RegNameTxt[4] = { "X:", "Y:", "Z:", "T:" };

// set error
void SetError(void)
{
	Error = True;
}

// clear error
void ClearErr(void)
{
	if (Error)
	{
		Error = False;
		NumSet0(&RegX);
		EditBufClear();
	}
}

// display key level status (need to call DispUpdate)
void DispKeyLevel()
{
	DrawTextCondBg(KeyLevelTxt[KeyLevel], 0, 0);
}

// display angle unit (need to call DispUpdate)
void DispAngleUnit()
{
	DrawTextCondBg(AngleUnitDeg ? "DEG" : "RAD ", 59, 0);
}

// display battery (need to call DispUpdate)
void DispBat()
{
	int n = DecNum(DecNumBuf, Supply, '.');
	if (n == 5)
	{
		DecNumBuf[4] = 'V';
		DrawTextCondBg(DecNumBuf, WIDTH-5*6, 0);
	}
}

// measure battery, update display if needed
void BatUpdate()
{
	if (ADCNum < 400)
	{
		ADCAcc += ADC1_GetSingle(8);
		ADCNum++;
	}

	if ((u32)(Time() - ADCStart) > 1000000*HCLK_PER_US)
	{
		Supply = 1200 * 4096 * ADCNum / ADCAcc;
		ADCNum = 0;
		ADCAcc = 0;
		if (Programming == 0)
		{
			DispBat();
			DispUpdate();
		}
		ADCStart = Time();
	}
}

// display register 0..3 from calculator stack or from edit buffer (need to call DispUpdate)
void DispReg(int inx)
{
	const u8* src;
	int len;

	// use edit buffer
	if ((inx == 0) && FlagEdit) // edit mode is active
	{
		src = EditBuf;
		len = EditMantNum+EditExpNum;
	}

	// use stack register
	else
	{
		len = NumDecode(&CalcStk[inx]);
		src = PrintBuf;
	}

	// Y coordinate
	int y = HEIGHT - FONTH - inx*FONTH;

	// print register name
	int x = 0;
	int n = TEXTWIDTH - len;
	if (len <= TEXTWIDTH-2)
	{
		DrawTextBg(RegNameTxt[inx], x, y);
		x = 2*FONTW;
		n -= 2;
	}

	// print spaces
	for (; n > 0; n--)
	{
		DrawCharBg(' ', x, y);
		x += FONTW;
	}

	// print number
	for (; len > 0; len--)
	{
		DrawCharBg(*src++, x, y);
		x += FONTW;
	}
}

// display all registers (need to call DispUpdate)
void DispAllReg()
{
	DispReg(0);
	DispReg(1);
	DispReg(2);
	DispReg(3);
}

// write memory to flash
void WriteMem()
{
	Flash_Erase(SLOTADDR + FLASH_BASE, SLOTSIZE, 1000);
	Flash_Program(SLOTADDR + FLASH_BASE, (u32*)&Mem, SLOTSIZE, 1000);
}

int main(void)
{
	u8 ch, ch2, prg;

	// read memory from flash
	memcpy(&Mem, (const u8*)SLOTADDR, sizeof(Mem));
	if (Mem.magic != SLOTMAGIC)
	{
		memset(&Mem, 0, sizeof(Mem));
		Mem.magic = SLOTMAGIC;
	}

	// display init
	DispInit();

	// Initialize keyboard service
	KeyInit();

	// initialize ADC single conversion mode
	ADCStart = Time() - 2000000*HCLK_PER_US;
	ADC1_InitSingle();
	ADCAcc = ADC1_GetSingleMul(8, 400); // result value (12+10-2) 20 bits
	ADCNum = 400;

	// clear display
	DrawClear();

	// draw line on bottom of info row
	DrawHLine(0, THEIGHT-4, WIDTH, COL_WHITE);

	// display key level status
	DispKeyLevel();

	// display angle unit
	DispAngleUnit();

	// clear edit buffer
	EditBufClear();
	FlagEdit = True;

	// display all registers
	DispAllReg();

	// display battery
	BatUpdate();
	DispBat();

	// display update
	DispUpdate();

	// keyboard flush
	KeyFlush();

	while(True)
	{
		// programming indicator
		prg = Programming;
		if (prg != 0)
		{
			if ((((Time() >> 22) & 1) == 0) && (Mem.progsize[prg-1] < PROGSIZE))
			{
				DrawTextCondBg("     ", WIDTH-5*6, 0);
			}
			else
			{
				DrawTextCondBg("PROG", WIDTH-5*6, 0);
				DrawCharCondBg(prg - 1 + '0', WIDTH-6, 0);
			}
			DispUpdate();
		}

		// measure battery, update display if needed
		BatUpdate();

		// running in progress
		if (Running != 0)
		{
			Running--;
			ch = *RunningPtr++;
			KeyLevel = ch / KEY_NUM;
			ch -= KeyLevel*KEY_NUM;
		}
		else
			ch = KeyGet();

		// key
		if (ch != NOKEY)
		{
			// clear error and discard the key
			if (Error)
			{
				ClearErr();
				DispReg(0);
				DispUpdate();
				continue;
			}

			// full key code
			ch2 = ch + KeyLevel*KEY_NUM;

			// programming
			if ((prg != 0) && ((ch2 < KEY_PRG0) || (ch2 > KEY_PRG9)) && (ch != KEY_2ND))
			{
				prg--;
				if (Mem.progsize[prg] < PROGSIZE)
				{
					Mem.prog[prg*PROGSIZE + Mem.progsize[prg]] = ch2;
					Mem.progsize[prg]++;
				}
			}

			// key execute
			KeyExecList[ch2](ch2);

			// reset key level
			if (ch != KEY_2ND) ExecLevel(KEY_1ST);

			// display register X or edit buffer
			DispReg(0);

			// display update
			DispUpdate();
		}
	}
}
