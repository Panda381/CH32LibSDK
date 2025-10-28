
// ****************************************************************************
//
//                                Program
//
// ****************************************************************************

#include "../include.h"

#if !USE_PROG_ASM		// 1=use ASM in Prog module

// LIST command (no error)
// ZX80: L0256
void CmdList()
{
	// current edited program line
	int line = LastResult;
	if ((line <= 0) || ((u32)line >= 0xffff)) line = 1;
	CurLine = line;
	TopLine = line;
	ProgLine = 0; // stop running (no error report)
}

// GOSUB command (can raise errors)
// ZX80: L0943
void CmdGosub()
{
	// save current line + 1 in the stack
	int n = StckNum;
	if (n >= STCKNUM)
	{
		MemError();	// stack overflow
		return;
	}
	u16* p = &Stck[n];
	n++;
	StckNum = n;
	*p = ProgLine + 1;

	// jump to new line
	CmdGoto();
}

// RETURN command (can raise errors)
// ZX80: L0965
void CmdReturn()
{
	// get return address
	int n = StckNum - 1;
	if (n < 0)
	{
		ReturnError(); // RETURN without GOSUB
		return;
	}
	StckNum = n;
	u16* p = &Stck[n];

	// jump to the address
	LastResult = *p;
	CmdGoto();
}

// GOTO program line (no error)
// ZX80: L0934
void CmdGoto()
{
	ProgLine = LastResult;
	SET_GOTO;	// goto program line
}

// CONTINUE program (no error)
// ZX80: L0930
void CmdContinue()
{
	LastResult = OldLine;
	CmdGoto();
}

// RUN program (no error)
// ZX80: L093D
void CmdRun()
{
	// initialize stacks
	CalcNum = 0;
	StckNum = 0;

	// reset data pointer
	DataPtr = NULL;

	// clear variables
//	CmdClear();
	VarsNum = 1;
	Vars[0] = VAR_END;

	// default run from line 1
	if (LastResult == 0) LastResult = 1;

	// clear timer
	LastTime = Time();

	// goto line
	CmdGoto();
}

// IF command (no error)
// - Called during syntax checking from CLASS5.
// ZX80: L08B9
void CmdIf()
{
	// condition FALSE, skip rest of line
	if (LastResult == 0)
	{
		// if not checking syntax
		if (IS_SYNTOFF)
		{
			// if run-time, skip rest of the line
			CmdRem();
			return;
		}
	}
	// condition is TRUE (or check syntax), continue execution
}

// REM command (no error)
// - Called during syntax checking from CLASS5.
// ZX80: L0849 (incorrectly L084A)
void CmdRem()
{
	u8 ch = GetChar();
	while (ch != NEWLINE) { ch = NextChar(); }
}

// DATA command
void CmdData()
{
	u8 ch;

	// if checking syntax
	if (IS_SYNTON)
	{
		while (True)
		{
			// get character, skip spaces
			ch = GetChar();

			// end of row
			if (ch == NEWLINE) break;

			// separator ','
			if (ch == TOKEN_COMMA)
			{
				// skip comma
				NextChar();
			}

			// expression
			else
			{
				ScanCalc();
				if (!IS_NUMRES)
				{
					SyntaxError();
					return;
				}

				// break on error
				if (IS_ERROR) return;
			}
		}
	}

	// runtime - ignore rest of line
	else
	{
		// if run-time, skip rest of the line
		CmdRem();
	}
}

// move to next program line (returns next program line) (no error)
//  lineL lineH text NEWLINE ... program line, 0 = end of program
u8* NextLine(u8* p)
{
	// end of program
	if (CHECKLINE0(p)) return p;

	// skip line number
	p += 2;

	// search end of program line
	u8 a;
	do { a = *p++; } while (a != NEWLINE);
	return p;
}

// find currect edited program line (no error)
u8* FindCurLine()
{
	return FindLine(CurLine, NULL);
}

// find program line by line number (returns required line or higher or end of program) (no error)
//   prevline ... returns previous line (if prevline != NULL), or NULL if this is first line
// ZX80: L060A
u8* FindLine(int line, u8** prevline)
{
	int line2;
	u8 a;
	if (prevline != NULL) *prevline = NULL;

	// prepare pointer to start of program
	u8* p = Prog;

	// search program line
	for (;;)
	{
		// get line number
		line2 = GETLINE(p);

		// line has been found, or end of program reached
		if ((line2 == 0) || (line2 >= line)) break;

		// save previous line
		if (prevline != NULL) *prevline = p;

		// move to next program line
		p += 2;
		do { a = *p++; } while (a != NEWLINE);
	}

	return p;
}

// WAIT command
void CmdWait()
{
	int i;
	int ms = LastResult;
	while (ms > 0)
	{
		// delay, max. 100ms at once
		i = 100;
		if (ms < i) i = ms;
		ms -= i;
		WaitMs(i);

		// break program (space key is pressed)
		if (KeyPressed(KEY_SPACE))
		{
			CmdStop(); // stop program
			KeyFlush();
			break;
		}
	}
}

// POKE command
// - Called during syntax checking from CLASS5.
// ZX80: L09D1
void CmdPoke()
{
	// push previous result - destination address
	val addr = LastResult;

	// evaluate expression after comma, get value (can raise error)
	ScanCalc();
	if (!IS_NUMRES)
	{
		SyntaxError();
		return;
	}

	// break on error
	if (IS_ERROR) return;

	// check end of command - quit if only checking syntax
	if (!CheckEnd()) return;

	// get value to be set
	val n = LastResult;

	// Frame counter (addr = -1)
	if (addr == -1)
	{
		DispFrame = n;
	}

	// Random seed (addr = -2)
	else if (addr == -2)
	{
		RandSeed = n;
	}

	// Time in 0.02 us (addr = -3)
	else if (addr == -3)
	{
		LastTime = Time() + n;
	}

	// print position X (addr = -4)
	else if (addr == -4)
	{
		if (n < 0) n = 0;
		if (n > WIDTH) n = WIDTH;
		PrintX = (u8)n;
	}

	// print position Y (addr = -5)
	else if (addr == -5)
	{
		if (n < 0) n = 0;
		if (n > HEIGHT-1) n = HEIGHT-1;
		PrintY = (u8)n;
	}

	// buffers
	else if (addr >= 0)
	{
		// set character to the screen (addr = 0..0x2FF)
		if (addr < FRAMESIZE) FrameBuf[addr] = (u8)n;
	}
}

// MEMORY command
void CmdMemory()
{
	// program size
	PrintNum(ProgNum);		// print program used
	PrintCh(CH_PLUS);		// print '+'
	PrintNum(PROGNUM - ProgNum);	// print program free
	PrintCh(CH_COMMA);		// print ','

	// variable size
	PrintNum(VarsNum);		// print variable used
	PrintCh(CH_PLUS);		// print '+'
	PrintNum(VARSNUM - VarsNum);	// print variable free

	// display NEWLINE
	PrintCR();
}

// BEEP command
void CmdBeep()
{
	// save previous result - required frequency in 0.01 Hz (0 = silent)
	int f = LastResult;

	// evaluate expression after comma, get value (can raise error)
	ScanCalc();
	if (!IS_NUMRES)
	{
		SyntaxError();
		return;
	}

	// break on error
	if (IS_ERROR) return;

	// check end of command - quit if only checking syntax
	if (!CheckEnd()) return;

	// minimal frequency 16 Hz, maximal frequency 16 kHz
	if (f > 0) // 0 = silent
	{
		if ((f >= 1600) && (f <= 1600000))
		{
			// get divider
			u32 div = (100*1000000 + f/2)/f - 1;

			// play tone
			PlayTone(div);
		}
	}

	// wait
	CmdWait();

	// stop sound
	StopSound();
}

// FOR command (can raise errors)
// - Called during syntax checking from CLASS5.
// ZX80: L08C4
void CmdFor()
{
	// get INIT value
	val ini = LastResult;

	// load LIMIT
	ScanCalc();			// evaluate expression (can raise error)
	if (!IS_NUMRES) SyntaxError();	// not numeric result
	if (IS_ERROR) return;

	// check end of command - quit if only checking syntax
	if (!CheckEnd()) return;

	// get LIMIT value
	val lim = LastResult;

	// store init value into variable (or create variable)
	LastResult = ini;
	CmdLet();
	if (IS_ERROR) return;

	// find variable (returned pointer is valid)
	// returns pointer to data of variable, or NULL if not found
	u8* var;
	u8* p = GetVar(VarDest, &var);

	// check if variable is already initialized (change simple variable to loop variable)
// 00aaaaaa name valL (val2 val3) valH ... integer variable 'name'
// 01aaaaaa name valL (val2 val3) valH maxL (max2 max3) maxH lineL lineH ... FOR control, val=value, max=limit TO, line=line with FOR, variable 'name'
	u8 ch = *var; // get variable type and length
	int namelen = ch & VAR_MASK; // length of name of the variable
	*var = namelen | (VARTYPE_FOR << VAR_SHIFT); // set FOR type of the variable

#if VALSIZE == 32
	p += 4; // move to end of variable
#define FORSIZE	6	// required size of new data to insert
#else
	p += 2;
#define FORSIZE	4
#endif

	// check FOR type of the variable
	if ((ch >> VAR_SHIFT) == VARTYPE_NUM) // simple integer variable?
	{
		// check free space
		int num = VarsNum;	// current size of variables
		if (num > VARSNUM - FORSIZE)
		{
			MemError();
			return;
		}

		// shift data
		VarsNum = num + FORSIZE; // set new size of variables

// use "volatile" so that the compiler uses a program loop instead of memmove, as this is more memory efficient.

		volatile u8* s = &Vars[num];	// old end of variables + 1
		int i = s - p;		// size of data to move
		for (; i > 0; i--)
		{
			s--;
			s[FORSIZE] = s[0]; // move data
		}
	}

	// store limit
	*p++ = (u8)lim;
	*p++ = (u8)(lim >> 8);
#if VALSIZE == 32
	*p++ = (u8)(lim >> 16);
	*p++ = (u8)(lim >> 24);
#endif

	// store following program line
	int line = ProgLine + 1;
	p[0] = (u8)line;
	p[1] = (u8)(line >> 8);
}

// NEXT command (can raise errors)
// ZX80: L08F9
void CmdNext()
{
	// get address of variable name
	u8* var = VarDest;

	// find variable
	// returns pointer to data of integer variable, or start of text variable, or NULL if not found
	u8* v;
	u8* p = GetVar(var, &v);
	if ((p == NULL) || IS_ERROR)
	{
		VarNotFound(); // variable not found
		return;
	}

	// check correct variable type
// 01aaaaaa name valL (val2 val3) valH maxL (max2 max3) maxH lineL lineH ... FOR control, val=value, max=limit TO, line=line with FOR, variable 'name'
	if ((*v >> VAR_SHIFT) != VARTYPE_FOR)
	{
		NextError(); // NEXT without FOR
		return;
	}

	// increment variable value
	val num = LastResult + 1;

	// save new variable value
	p[0] = (u8)num;
	p[1] = (u8)(num >> 8);
#if VALSIZE == 32
	p[2] = (u8)(num >> 16);
	p[3] = (u8)(num >> 24);
#endif

	// load limit of the loop
#if VALSIZE == 32
	val max = p[4] | (p[5] << 8) | (p[6] << 16) | (p[7] << 24);
#else
	val max = p[2] | (p[3] << 8);
#endif

	// check if limit has been reached
	if (num <= max)
	{
		// get destination line
#if VALSIZE == 32
		int line = p[8] | (p[9] << 8);
#else
		int line = p[4] | (p[5] << 8);
#endif

		// go to line
		LastResult = line;
		CmdGoto();
	}
}

// Auto list (no error)
// ZX80: L0293
void AutoList()
{
	// save and clear ErrPtr (not to indicate an error in the list)
	u8* err = ErrPtr;
	ErrPtr = NULL;

AutoListRestart:
	// prepare top screen
	PrintX = 0;
	PrintY = 0;
	PrintYMax = HEIGHT-LowScreenH-1;

	// check top line underflow
	int top = TopLine;	// top line
	if (top == 0) top = 1;
	int cur = CurLine;	// current line
	if (cur == 0) cur = 1;	// minimal line
	if (cur < top)
	{
		top = cur; // maximal top line
		TopLine = top;
	}
	int line = top;		// current line
	Bool curok = False;	// flag - cursor found OK

	// find first line
	u8* p = FindLine(line, NULL);

	// until end of screen
	while ((PrintY < PrintYMax) || (PrintX != WIDTH))
	{
		// get line number
		line = GETLINE(p);

		// this is cursor
		if ((line > cur) && !curok)
		{
			cur = line;
			CurLine = cur;
		}

		// end of program, print empty row
		if (line == 0)
		{
			// print empty row
			PrintCR();
		}
		else
		{
			// this is current line
			if (line == cur) curok = True;

			// print program line
			if (!PrintBasNum(p))
			{
				// display overflow - last line was not printed whole, increase top line
				if (line == cur) goto AutoListNextLine;
				break;
			}
		}

		// find next line
		p = NextLine(p);
	}

	// cursor was not printed
	if (!curok) // && (ProgNum > 2))
	{
		// get line number
		line = GETLINE(p);
		if (line >= cur) // next line is line with cursor
		{
AutoListNextLine:
			// shift to next top line
			p = FindLine(top, NULL); // find first line
			p = NextLine(p); // find next line
			line = GETLINE(p); // get line number
			if ((line != 0) && (line <= cur))
			{
				TopLine = line;
				goto AutoListRestart; // restart
			}
		}

		// move to new top line
		u8* prev;
		p = FindLine(cur, &prev);
		cur = GETLINE(p);
		if ((cur == 0) && (prev != NULL)) cur = GETLINE(prev);
		if (cur > 0)
		{
			CurLine = cur;
			goto AutoListRestart; // restart
		}
	}

	// restore ErrPtr
	ErrPtr = err;
}

// Process command or check syntax in edit line (can raise errors)
// ZX80: L07BE
void MainGo(u8* p)
{
	u8 ch, ch2;
	int cmd;

	// set text pointer to start of edit/program line - 1
	CharPtr = p - 1;

	// clear error pointer
	ErrPtr = NULL;
	ErrNr = ERR_OK;

	// pre-set L mode
	SET_LMODE;	// L mode

	// if inputting, only fetch value
	if (IS_INPUT)
	{
		// do not update cursor mode
		SET_NOUPDATE;

		// shift cursor and update cursor mode
		CharAdd();

		// fetch value (can raise error)
		FetchVal();
		return;
	}

// ---- else editing

	// update cursor mode
	SET_KUPDATE;

	// skip spaces and update cursor mode
	NextChar();

	// parse line number
	u32 line = ParseUNum();
	if (line >= 0xffff)
	{
		SyntaxError(); // invalid line number
		return;
	}

// ZX80: L07E8
LineScan:
	// load next character - command code
	cmd = (u8)GetChar();

	// do not update cursor mode
	SET_NOUPDATE;

	// clear result
	LastResult = 0;

	// quit if row is empty
	if (cmd == NEWLINE) return;

	// only tokens are allowed at this place
	cmd -= TOKEN_MIN;
	if (cmd < 0)
	{
		SyntaxError();
		return;
	}

	// skip token character
	NextChar();

	// scanning syntax table
	const u8* s = SyntTab[cmd]; // get pointer to syntax table

	// parse syntax
	for (;;)
	{
		// break on error
		if (IS_ERROR) return;

		// get next character (skip spaces)
		ch2 = GetChar();

		// get next syntax descriptor
		ch = *s++;

		// parse token separator
		if (ch > CLASS_MAX)
		{
			// if token 'THEN', set update cursor mode
			if (ch2 == TOKEN_THEN) SET_KUPDATE;

			// check token
			if (ch2 != ch)
			{
				SyntaxError();
				return;
			}

			// skip separator
			NextChar();
		}

		// check class
		else
		{
			switch (ch)
			{
			// ZX80: L0850
			case CLASS3:	// a numeric expression may follow, otherwise zero will be used ... CLASS3 terminates sequence
			// Used in: CmdList, CmdSave, CmdRandomise, CmdRun, CmdLoad

				// if not end of line, load value
				if (ch2 != NEWLINE)
				{
					// evaluate expression (can raise error)
					ScanCalc();

					// check numeric expression
					if (!IS_NUMRES)
					{
						SyntaxError();
						return;
					}
				}

		// continue to CLASS0

			// ZX80: L0855
			case CLASS0:	// no further operands ... CLASS0 terminates sequence
			// Used in: CmdReturn, CmdCls, CmdDim, CmdGoto, CmdInput, CmdNext, CmdMemory,
			//          CmdNew, CmdStop, CmdContinue, CmdGosub, CmdClear, CmdBeep

				// check end of command - quit if only checking syntax
				if (!CheckEnd()) return;

				// run command
				TokenFncList[cmd]();
				return;

			// ZX80: L086A
			case CLASS1:	// destination variable name is required
			// Used in: CmdInput, CmdLet

				// check alpha character
				if (!IsAlpha(ch2))
				{
					SyntaxError();	
					return;
				}

				// if checking syntax, go to look vars
				if (IS_SYNTON)
				{
					// scan variable (not functions)
					LookVars(False);
				}

				// runtime - temporary switch ON syntax checking, to only get variable name
				else
				{
					// save variable name
					VarDest = CharPtr;

					// scan variable or function
					SET_SYNTON;	// temporary enable syntax checking
					LookVars(False); // scan variable (not functions)
					SET_SYNTOFF;	// disable syntax checking
				}
				break;

			// ZX80: L0885
			case CLASS2:	// an expression (of type integer or string) must follow ... CLASS2 terminates sequence
			// Used in: CmdLet

				// fetch value (can raise error)
				FetchVal();
				return;

			// ZX80: L089E
			case CLASS4:	// integer variable must follow
			// Used in: CmdDim, CmdFor, CmdNext

				// store pointer to variable name
				VarDest = CharPtr;

				// parse variable name
				ch = ParseVarName(VarDest);

				// check variable type 'name' or 'name()' (error includes invalid name VAR_END)
				if (((ch >> VAR_SHIFT) != VARTYPE_NUM) &&
					((ch >> VAR_SHIFT) != VARTYPE_ARRAY))
				{
					SyntaxError();
					return;
				}

				// skip name of the variable
				ch &= VAR_MASK; // length of the name
				for (; ch > 0; ch--) CharAdd();
				break;

			// ZX80: L0856
			case CLASS5:	// variable syntax checked entirely by routine ... CLASS5 terminates sequence
			// Used in: CmdFor, CmdPoke, CmdPrint, CmdIf, CmdRem, CmdBeep, CmdData

				// jump to the command
				TokenFncList[cmd]();

				// break on error
				if (IS_ERROR) return;

				// on IF command - continue scanning (on FALSE, rest of line is already skipped)
				if (cmd == TOKEN_IF - TOKEN_MIN) goto LineScan;
				return;

			// ZX80: L08A8
			case CLASS6:	// a numeric expression must follow
			// Used in: CmdDim, CmdFor, CmdGoto, CmdPoke, CmdIf, CmdGosub, CmdBeep, CmdWait

				// evaluate expression (can raise error)
				ScanCalc();

				// check numeric expression
				if (!IS_NUMRES) 
				{
					SyntaxError();
					return;
				}
				break;
			}
		}
	}
}

#endif // USE_PROG_ASM
