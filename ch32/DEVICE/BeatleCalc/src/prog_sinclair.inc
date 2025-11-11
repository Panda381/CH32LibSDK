
// ****************************************************************************
//
//                          Sinclair program
//
// ****************************************************************************
// Original source Ken Shirriff
// https://static.righto.com/calculator/sinclair_scientific_simulator.html

const u16 ProgSinclair[320] = {
	1408,	// 0x000: 0x580 START    ZFA    ALL      init - clear flags
	1392,	// 0x001: 0x570          ZFB    ALL                        
	1792,	// 0x002: 0x700          AKA    ALL      clear A and C     
	1824,	// 0x003: 0x720          AKC    ALL                        
		//              For display, A's MANT starts in digit 5. For computation, MANT starts in digit 6
		//              C holds the previous value, with MANT starting in digit 6. Digit 5 counts inputted digits
	1860,	// 0x004: 0x744 MAINLOOP SLLA   MANT     Shift mantissa for display                      
	1808,	// 0x005: 0x710          AKB    ALL      clear B                                         
	1360,	// 0x006: 0x550 WAITSCAN SYNC            loop until no key pressed                       
	1376,	// 0x007: 0x560          SCAN                                                            
	518,	// 0x008: 0x206          BINE   WAITSCAN                                                 
	1319,	// 0x009: 0x527 WAITKEY  WAITNO WAITED   wait for key                                    
	1360,	// 0x00A: 0x550 WAITED2  SYNC            debounce: still pressed?                        
	1376,	// 0x00B: 0x560          SCAN                                                            
	9,	// 0x00C: 0x009          BIE    WAITKEY  loop if no key                                  
	1360,	// 0x00D: 0x550          SYNC                                                            
	1908,	// 0x00E: 0x774          SRLA   MANT     MANT is shifted right during calculation        
	1072,	// 0x00F: 0x430          BKO    LOWERKEY sequentially scan key columns                   
	1083,	// 0x010: 0x43B          BKO    PLUSKEY                                                  
	1075,	// 0x011: 0x433          BKO    MINUSKEY                                                 
	1121,	// 0x012: 0x461          BKO    DIVKEY                                                   
	1129,	// 0x013: 0x469          BKO    MULTKEY                                                  
	1073,	// 0x014: 0x431          BKO    UPPERKEY                                                 
	1069,	// 0x015: 0x42D          BKO    EKEY                                                     
	1051,	// 0x016: 0x41B          BKO    ZEROKEY                                                  
	1840,	// 0x017: 0x730          EXAB   ALL      save A in B, A=0                                
	1955,	// 0x018: 0x7A3          AKCN   DIGIT1   get digit by incrementing until column found    
	1840,	// 0x019: 0x730          EXAB   ALL      restore A, B holds count                        
	516,	// 0x01A: 0x204          BINE   MAINLOOP start over if nothing pressed                   
	1425,	// 0x01B: 0x591 ZEROKEY  TFB    EMODE    B holds key 0-9                                 
	552,	// 0x01C: 0x228          BINE   EDIGIT                                                   
		//              If OPDONE, a digit starts a new number in A, leaving the previous in C
	1430,	// 0x01D: 0x596          TFB    OPDONE   if OPDONE...                           
	33,	// 0x01E: 0x021          BIE    LABEL33                                         
	1792,	// 0x01F: 0x700          AKA    ALL      then clear A and OPDONE                
	1398,	// 0x020: 0x576          ZFB    OPDONE                                          
	1631,	// 0x021: 0x65F LABEL33  ACKA   DIGIT    C holds digit position                 
	1920,	// 0x022: 0x780 BSHIFT   SRLB   ALL      shift B right C times.                 
	1683,	// 0x023: 0x693          SAKA   DIGIT1   decrement A                            
	34,	// 0x024: 0x022          BIE    BSHIFT   (no borrow)                            
	2003,	// 0x025: 0x7D3          ACKC   DIGIT1   increment digit count in C             
	1540,	// 0x026: 0x604          AABA   MANT     Append new digit                       
	4,	// 0x027: 0x004          BIE    MAINLOOP done digit processing                  
	1399,	// 0x028: 0x577 EDIGIT   ZFB    NEWEXP   clear new exponent flag                
	1858,	// 0x029: 0x742          SLLA   EXP      shift exponent left                    
	1872,	// 0x02A: 0x750          SLLB   ALL      shift digit left                       
	1538,	// 0x02B: 0x602          AABA   EXP      append new digit to exponent           
	4,	// 0x02C: 0x004          BIE    MAINLOOP done                                   
	1329,	// 0x02D: 0x531 EKEY     SFB    EMODE    entering exponent mode                 
	1335,	// 0x02E: 0x537          SFB    NEWEXP                                          
	4,	// 0x02F: 0x004          BIE    MAINLOOP done                                   
	1349,	// 0x030: 0x545 LOWERKEY SFA    LOW      LOW and UP_LOW set for LOWER key       
	1347,	// 0x031: 0x543 UPPERKEY SFA    UP_LOW   UP_LOW set for UPPER key               
	4,	// 0x032: 0x004          BIE    MAINLOOP done                                   
	1443,	// 0x033: 0x5A3 MINUSKEY TFA    UP_LOW   alt-MINUS is COS                       
	676,	// 0x034: 0x2A4          BINE   COSKEY                                          
		//              Minus normally is just addition after negating A.
		//              Except - following E changes the exponent sign instead.
		//              Except a second minus following E - does a subtraction
	1431,	// 0x035: 0x597          TFB    NEWEXP   - follows E?                             
	57,	// 0x036: 0x039          BIE    DOSUBTR                                           
	1559,	// 0x037: 0x617          AAKA   EXP_S5   negate exponent for E - keystrokes       
	4,	// 0x038: 0x004          BIE    MAINLOOP if already neg, fall through subtract    
	1553,	// 0x039: 0x611 DOSUBTR  AAKA   MANT_S5  negate mantissa then fall through and add
	59,	// 0x03A: 0x03B          BIE    PLUSKEY  clear condition flag                     
	1443,	// 0x03B: 0x5A3 PLUSKEY  TFA    UP_LOW   alt-PLUS is SIN                          
	677,	// 0x03C: 0x2A5          BINE   SINKEY                                            
		//              Add A and C. First, C is copied to B. The numbers need to have equal
		//              exponents to be added so the difference in exponents is 
		//              computed using C and B is shifted left to align the mantissas.
		//              If the mantissas have different signs, they are subtracted instead of added,
		//              which may require A and B to be swapped.
	1839,	// 0x03D: 0x72F ADDSUB   AKC    DIGIT    Clear C DIGIT                                    
	1632,	// 0x03E: 0x660          ACKB   ALL      copy C to B                                      
	2018,	// 0x03F: 0x7E2          ABAC   EXP      add exponents into C                             
	65,	// 0x040: 0x041          BIE    CLRCC    Clear condition code                             
	2023,	// 0x041: 0x7E7 CLRCC    ABAC   EXP_S5   add exponent signs                               
	1719,	// 0x042: 0x6B7          SCKC   EXP_S5   subtract 5 from sign                             
	72,	// 0x043: 0x048          BIE    EXPSNES  signs were different                             
	1730,	// 0x044: 0x6C2          CAB    EXP      compare exponents                                
	71,	// 0x045: 0x047          BIE    EXPAGE   branch >=                                        
	1840,	// 0x046: 0x730          EXAB   ALL      switch arguments so A EXP > B EXP                
	1666,	// 0x047: 0x682 EXPAGE   SABC   EXP      same sign - subtract exponents into C            
	1751,	// 0x048: 0x6D7 EXPSNES  CAK    EXP_S5   Test A exponent sign                             
	587,	// 0x049: 0x24B          BINE   AEXPPOS  branch on borrow, A exp sign == 0                
	1840,	// 0x04A: 0x730          EXAB   ALL      switch arguments so A EXP > B EXP                
	1754,	// 0x04B: 0x6DA AEXPPOS  CAK    MANT1    make sure A is nonzero                           
	78,	// 0x04C: 0x04E          BIE    BSHIFT2                                                   
	1840,	// 0x04D: 0x730          EXAB   ALL                                                       
	1718,	// 0x04E: 0x6B6 BSHIFT2  SCKC   EXP1     shift B by difference in exponents (C) to line up
	594,	// 0x04F: 0x252          BINE   DONE2                                                     
	1924,	// 0x050: 0x784          SRLB   MANT                                                      
	78,	// 0x051: 0x04E          BIE    BSHIFT2  branch every time                                
	2017,	// 0x052: 0x7E1 DONE2    ABAC   MANT_S5  add mantissa signs and subtract 5                
	1713,	// 0x053: 0x6B1          SCKC   MANT_S5                                                   
	89,	// 0x054: 0x059          BIE    SUBMANT  signs different                                  
	1540,	// 0x055: 0x604 TRYADD   AABA   MANT     add mantissas, or restore A if did SUBMANT       
	130,	// 0x056: 0x082          BIE    NORMLIZE branch if no overflow, i.e. did add              
	1844,	// 0x057: 0x734          EXAB   MANT     failed subtract: swap A and B and try again.     
	1841,	// 0x058: 0x731          EXAB   MANT_S5                                                   
		//              Try subtracting mantissas: A-B. If B>A, add B back, swap, and try again
	1652,	// 0x059: 0x674 SUBMANT  SABA   MANT     subtract mantissa              
	597,	// 0x05A: 0x255          BINE   TRYADD   A was smaller than B: try again
	130,	// 0x05B: 0x082          BIE    NORMLIZE branch every time, done        
		//              Multiplication: add exponents with different signs
	1730,	// 0x05C: 0x6C2 SIGNSNE  CAB    EXP      compare EXP magnitudes  
	95,	// 0x05D: 0x05F          BIE    SUBEXPS  branch if |A| >= |B|    
	1849,	// 0x05E: 0x739          EXAB   EXPSGNS1 swap exponents and signs
		//              At this point, |A| >= |B|, so can subtract and A's sign won't change
	1650,	// 0x05F: 0x672 SUBEXPS  SABA   EXP      subtract EXPs    
	114,	// 0x060: 0x072          BIE    EXPSDONE branch every time
		//              Division entry point: compute C / A.
		//              First, normalize A mantissa since repeatedly subtracting A depends on
		//              having A normalized. Next, use multiply's add-exponent code to subtract
		//              A's exponent from C's.
		//              The DIVLOOP loop repeatedly subtracts B from C, counting into A.
		//              Successive loops shift by 10 to perform long division.
	1443,	// 0x061: 0x5A3 DIVKEY   TFA    UP_LOW   entry point for DIV                               
	675,	// 0x062: 0x2A3          BINE   TANKEY   alt-DIV is TAN                                    
	1355,	// 0x063: 0x54B          SFA    COS_TAN  reusing flag to indicate division                 
	1345,	// 0x064: 0x541 DODIV    SFA    RET1FLAG 'subroutine call' flag                            
	130,	// 0x065: 0x082          BIE    NORMLIZE 'Subroutine call' to normalize A                  
	1409,	// 0x066: 0x581 RET1     ZFA    RET1FLAG 'Return' here after NORMLIZE                      
	1559,	// 0x067: 0x617          AAKA   EXP_S5   toggle A's EXP sign since dividing not multiplying
	105,	// 0x068: 0x069          BIE    MULTKEY  clear cc                                          
		//              Multiply by adding exponents and multiplying mantissas
		//              If COS_TAN set, divide by adding exponents, then jump to DIVMANT
		//              i.e. the code to add exponents is reused for division
	1443,	// 0x069: 0x5A3 MULTKEY  TFA    UP_LOW   alt-MULT is LOG          
	750,	// 0x06A: 0x2EE          BINE   LOGKEY                            
	1839,	// 0x06B: 0x72F          AKC    DIGIT    clear entered digit count
	1632,	// 0x06C: 0x660          ACKB   ALL      copy C to B              
	1844,	// 0x06D: 0x734          EXAB   MANT                              
		//              Add exponents; tricky if signs are different
	2023,	// 0x06E: 0x7E7          ABAC   EXP_S5                                  
	1719,	// 0x06F: 0x6B7          SCKC   EXP_S5                                  
	92,	// 0x070: 0x05C          BIE    SIGNSNE  if signs different, use SIGNSNE
	1538,	// 0x071: 0x602          AABA   EXP      simply add exponents           
	1537,	// 0x072: 0x601 EXPSDONE AABA   MANT_S5  xor signs                      
	116,	// 0x073: 0x074          BIE    CLRCC2   clear before test              
	1451,	// 0x074: 0x5AB CLRCC2   TFA    COS_TAN  set if dividing                
		//              Compute A = B * C mantissas; EXP already computed
	1796,	// 0x075: 0x704 MULTMANT AKA    MANT     clear mantissa                             
	791,	// 0x076: 0x317          BINE   DIVMANT  branch if dividing                         
	1908,	// 0x077: 0x774 MLTLOOP1 SRLA   MANT     multiply B * C                             
	1781,	// 0x078: 0x6F5 MLTLOOP2 CCK    MANTLOW1 Add B to A, repeat low digit of C times    
	637,	// 0x079: 0x27D          BINE   MULTSHFT                                            
	1722,	// 0x07A: 0x6BA          SCKC   MANT1                                               
	1540,	// 0x07B: 0x604          AABA   MANT                                                
	120,	// 0x07C: 0x078          BIE    MLTLOOP2                                            
	1940,	// 0x07D: 0x794 MULTSHFT SRLC   MANT     shift C right                              
	1786,	// 0x07E: 0x6FA          CCK    MANT1                                               
	119,	// 0x07F: 0x077          BIE    MLTLOOP1 loop if not done                           
	1445,	// 0x080: 0x5A5          TFA    LOW                                                 
	820,	// 0x081: 0x334          BINE   ALOGRET  Return to ALOGRET if LOW flag set (ANTILOG)
		//              Normalizes mantissa by removing leading zeros.
		//              This is called to finish up after an operation
		//              Also subroutine call; RET1FLAG will cause return to RET1
	1754,	// 0x082: 0x6DA NORMLIZE CAK    MANT1    Test if mantissa is < 1
	512,	// 0x083: 0x200          BINE   START    if mantissa is 0, reset
		//              Repeatedly shift MANT left until a value in the 5 digit.
		//              Decrement EXP each step to compensate
	1747,	// 0x084: 0x6D3 MANTSHL  CAK    DIGIT1   Loop to left-align mantissa
	145,	// 0x085: 0x091          BIE    MANTOK   Branch if mantissa aligned 
	1860,	// 0x086: 0x744          SLLA   MANT     Shift mantissa left        
		//              Decrementing the exponent is a bit tricky because sign is separate
		//              Cases are: positive exponent, exponent becoming -1, and negative exponent
	1751,	// 0x087: 0x6D7          CAK    EXP_S5   Check exponent sign                          
	142,	// 0x088: 0x08E          BIE    EXPNEG   Branch if negative                           
	1686,	// 0x089: 0x696          SAKA   EXP1     Decrement exponent                           
	141,	// 0x08A: 0x08D          BIE    EXPPOS3  Branch if no borrow                          
	1799,	// 0x08B: 0x707          AKA    EXP_S5   EXP went negative: Set exponent sign         
	1798,	// 0x08C: 0x706          AKA    EXP1     Set exponent to 1                            
	1686,	// 0x08D: 0x696 EXPPOS3  SAKA   EXP1     Decrement exponent to cancel next instruction
	1558,	// 0x08E: 0x616 EXPNEG   AAKA   EXP1     For negative exponent, inc EXP to decrement  
	132,	// 0x08F: 0x084          BIE    MANTSHL  two branches to clear condition flag         
	132,	// 0x090: 0x084          BIE    MANTSHL                                               
		//              At this point, mantissa is left-aligned into digit 5
		//              Now shift one position right and increment exponent, taking sign into account
	1908,	// 0x091: 0x774 MANTOK   SRLA   MANT                                   
	1751,	// 0x092: 0x6D7          CAK    EXP_S5   Test exponent sign            
	662,	// 0x093: 0x296          BINE   EXPPOS                                 
	1686,	// 0x094: 0x696          SAKA   EXP1     Decrement exponent            
	1686,	// 0x095: 0x696          SAKA   EXP1     Decrement exponent            
	1558,	// 0x096: 0x616 EXPPOS   AAKA   EXP1     Increment exponent            
	152,	// 0x097: 0x098          BIE    CLRCC1   clear condition               
	1441,	// 0x098: 0x5A1 CLRCC1   TFA    RET1FLAG Subroutine return             
	614,	// 0x099: 0x266          BINE   RET1     return to RET1 if RET1FLAG set
		//              returned if RET1FLAG set, otherwise clean up...
		//              clear B, set OPDONE, clear A flags, fix EXP sign, copy A result to C
	1392,	// 0x09A: 0x570          ZFB    ALL      Clear B          
	1334,	// 0x09B: 0x536          SFB    OPDONE   Set op done flag?
	1408,	// 0x09C: 0x580          ZFA    ALL      Clear A flags    
		//              Fix EXP of -00 if necessary
	1750,	// 0x09D: 0x6D6          CAK    EXP1     Is exponent zero (< 1)         
	161,	// 0x09E: 0x0A1          BIE    EXPPOS2                                 
	1559,	// 0x09F: 0x617 CLEARSGN AAKA   EXP_S5   Flip sign                      
	159,	// 0x0A0: 0x09F          BIE    CLEARSGN Branch if sign was clear before
	1568,	// 0x0A1: 0x620 EXPPOS2  AAKC   ALL      Copy A to C                    
	4,	// 0x0A2: 0x004          BIE    MAINLOOP BET                            
		//              Entry points for TAN, COS, and SIN
	1351,	// 0x0A3: 0x547 TANKEY   SFA    TAN                                
	1355,	// 0x0A4: 0x54B COSKEY   SFA    COS_TAN                            
	1686,	// 0x0A5: 0x696 SINKEY   SAKA   EXP1     shift mantissa by exponent
	681,	// 0x0A6: 0x2A9          BINE   DONESHFT                           
	1908,	// 0x0A7: 0x774          SRLA   MANT                               
	165,	// 0x0A8: 0x0A5          BIE    SINKEY                             
	1801,	// 0x0A9: 0x709 DONESHFT AKA    EXPSGNS1 clear signs               
	1689,	// 0x0AA: 0x699          SAKA   EXPSGNS1 EXP = 0                   
	1824,	// 0x0AB: 0x720          AKC    ALL      clear C                   
	1445,	// 0x0AC: 0x5A5          TFA    LOW      check for ARC-            
	180,	// 0x0AD: 0x0B4          BIE    NORMOP   branch if no              
	1447,	// 0x0AE: 0x5A7          TFA    TAN      check ARCTAN?             
	179,	// 0x0AF: 0x0B3          BIE    ASINCOS  branch if no              
	1568,	// 0x0B0: 0x620          AAKC   ALL      ARCTAN: copy A to C       
	1819,	// 0x0B1: 0x71B          AKB    MASKA1   set digit in B            
	185,	// 0x0B2: 0x0B9          BIE    TRGLOOP2 branch every time         
	1565,	// 0x0B3: 0x61D ASINCOS  AAKA   MANTD1                             
	1820,	// 0x0B4: 0x71C NORMOP   AKB    MANTD5   B = .0005 (current SIN)   
	1924,	// 0x0B5: 0x784          SRLB   MANT                               
	2011,	// 0x0B6: 0x7DB          ACKC   MASKA1   C += 1 (current COS)      
		//              Loop test for SIN/COS/TAN
	1693,	// 0x0B7: 0x69D TRIGLOOP SAKA   MANTD1   rotate A times, by .001 rad
	738,	// 0x0B8: 0x2E2          BINE   TRIGDONE branch on borrow - done    
		//              The main trig loop. B holds sin, C holds cos.
		//              The loop is performed A times, rotating by .001 rad each time.
	1888,	// 0x0B9: 0x760 TRGLOOP2 SLLC   ALL      shift C to prepare for add
	1888,	// 0x0BA: 0x760          SLLC   ALL                                
	1888,	// 0x0BB: 0x760          SLLC   ALL                                
	2012,	// 0x0BC: 0x7DC          ACKC   MANTD5   C=C-B/1000 (rounded)      
	1696,	// 0x0BD: 0x6A0          SCBC   ALL                                
	1936,	// 0x0BE: 0x790          SRLC   ALL      restore C                 
	1936,	// 0x0BF: 0x790          SRLC   ALL                                
	1936,	// 0x0C0: 0x790          SRLC   ALL                                
	1872,	// 0x0C1: 0x750          SLLB   ALL      shift B to prepare for add
	1872,	// 0x0C2: 0x750          SLLB   ALL                                
	1872,	// 0x0C3: 0x750          SLLB   ALL                                
	2012,	// 0x0C4: 0x7DC          ACKC   MANTD5   B=B+C/1000 (rounded)      
	1584,	// 0x0C5: 0x630          ABCB   ALL                                
	1724,	// 0x0C6: 0x6BC          SCKC   MANTD5   restore C                 
	1920,	// 0x0C7: 0x780          SRLB   ALL                                
	1920,	// 0x0C8: 0x780          SRLB   ALL                                
	1920,	// 0x0C9: 0x780          SRLB   ALL                                
	1445,	// 0x0CA: 0x5A5          TFA    LOW      ARC-op?                   
	183,	// 0x0CB: 0x0B7          BIE    TRIGLOOP no: branch                
		//              Increment ARC-trig count, check termination
	1561,	// 0x0CC: 0x619          AAKA   EXPSGNS1 Count iterations in top digits of A
	1447,	// 0x0CD: 0x5A7          TFA    TAN                                         
	210,	// 0x0CE: 0x0D2          BIE    ASINCOS1 branch if SIN/COS                  
		//              Test ARCTAN termination
	1779,	// 0x0CF: 0x6F3          CCK    DIGIT1   ARCTAN, compare C to K
	697,	// 0x0D0: 0x2B9          BINE   TRGLOOP2 loop if not done      
	220,	// 0x0D1: 0x0DC          BIE    ARCDONE  BET                   
	1451,	// 0x0D2: 0x5AB ASINCOS1 TFA    COS_TAN  SIN/COS               
	727,	// 0x0D3: 0x2D7          BINE   ACOSCHK  branch if COS         
		//              Test ARCSIN termination
	1732,	// 0x0D4: 0x6C4          CAB    MANT     must be SIN      
	185,	// 0x0D5: 0x0B9          BIE    TRGLOOP2                  
	220,	// 0x0D6: 0x0DC          BIE    ARCDONE  Branch every time
		//              Test ARCCOS termination
	1754,	// 0x0D7: 0x6DA ACOSCHK  CAK    MANT1    COS                                                
	1844,	// 0x0D8: 0x734          EXAB   MANT     compare C-A the hard way                           
	1764,	// 0x0D9: 0x6E4          CCB    MANT                                                        
	1844,	// 0x0DA: 0x734          EXAB   MANT                                                        
	185,	// 0x0DB: 0x0B9          BIE    TRGLOOP2 C==A                                               
	1904,	// 0x0DC: 0x770 ARCDONE  SRLA   ALL      shift iteration count into mantissa, divide by 1000
	1904,	// 0x0DD: 0x770          SRLA   ALL                                                         
	1904,	// 0x0DE: 0x770          SRLA   ALL                                                         
	1904,	// 0x0DF: 0x770          SRLA   ALL                                                         
	1904,	// 0x0E0: 0x770          SRLA   ALL                                                         
	130,	// 0x0E1: 0x082          BIE    NORMLIZE branch every time                                  
		//              SIN/COS/TAN loop done
	1447,	// 0x0E2: 0x5A7 TRIGDONE TFA    TAN                            
	233,	// 0x0E3: 0x0E9          BIE    SINCOS                         
	1616,	// 0x0E4: 0x650          ACKA   ALL      doing TAN: A=C (denom)
	1600,	// 0x0E5: 0x640          ABOC   ALL      C=B (numer)           
	1808,	// 0x0E6: 0x710          AKB    ALL      B=0                   
	1411,	// 0x0E7: 0x583          ZFA    UP_LOW                         
	100,	// 0x0E8: 0x064          BIE    DODIV    branch every time     
	1451,	// 0x0E9: 0x5AB SINCOS   TFA    COS_TAN                        
	236,	// 0x0EA: 0x0EC          BIE    SIN      branch for SIN        
	1632,	// 0x0EB: 0x660          ACKB   ALL      COS: return C via B   
	1840,	// 0x0EC: 0x730 SIN      EXAB   ALL      SIN: return B         
	130,	// 0x0ED: 0x082          BIE    NORMLIZE BET (no overflow)     
	1445,	// 0x0EE: 0x5A5 LOGKEY   TFA    LOW      low-MULT is antilog   
	251,	// 0x0EF: 0x0FB          BIE    LOG                            
		//              Antilog entry point.
		//              The concept is to split the integer and fractional part of A. The integer
		//              part becomes the EXP of the result. The antilog of the fractional part is 
		//              computed using the equation 10^f = 10*.99^(229.15*(1-f))
		//              First, split int and frac parts of A. Next LOGLOOP computes constant 229.15.
		//              Control continues at ANTILOG which calls MULTMANT to multiply 1-frac by 229.15
	1750,	// 0x0F0: 0x6D6 DOALOG   CAK    EXP1     Test exponent
		//              Split int and frac parts of A: int in digits 1-4, frac in 7-10
		//              Shortcut: If EXP > 0, assume EXP is 1. Anything bigger would probably overflow
		//              This is totally wrong for cases like antilog(0.001E3)
	760,	// 0x0F1: 0x2F8          BINE   EXPZERO  branch if exponent is 0                         
	1751,	// 0x0F2: 0x6D7          CAK    EXP_S5   Test exponent sign                              
	759,	// 0x0F3: 0x2F7          BINE   EXPPOS4                                                  
	1908,	// 0x0F4: 0x774          SRLA   MANT     Negative exponent: shift mantissa right to align
	1686,	// 0x0F5: 0x696          SAKA   EXP1                                                     
	240,	// 0x0F6: 0x0F0          BIE    DOALOG   Loop every time                                 
	1860,	// 0x0F7: 0x744 EXPPOS4  SLLA   MANT     Positive EXP, assume it is 1                    
	1794,	// 0x0F8: 0x702 EXPZERO  AKA    EXP      Clear exponent                                  
	1864,	// 0x0F9: 0x748          SLLA   TOPSTUFF Shift integer part into digits 1-4 for later    
	1864,	// 0x0FA: 0x748          SLLA   TOPSTUFF                                                 
		//              Compute log of A.
		//              First compute -1/log(.99) = 229.15. Then compute -log(MANT A)/log(.99).
		//              Divide the results to get log(MANT A). Finally, add EXP A to get the result.
		//              Then compute -log(A)/go through power loop a second time
	1824,	// 0x0FB: 0x720 LOG      AKC    ALL      This entry point computes -1/log(.99) = 229.15
	2003,	// 0x0FC: 0x7D3          ACKC   DIGIT1   C = 10.00000                                  
		//              LOGLOOP is used twice; once to compute the constant 229.15 and then again
		//              on the actual argument.
		//              Compute -log(C MANT) / log(.99).
		//              Do this by repeatedly incrementing count until (C MANT)*.99^count is < 1
		//              That yields count = -log(C) / log(.99) approximately
		//              count is stored in C EXP, and the current C*.99 in C MANT
	1636,	// 0x0FD: 0x664 LOGLOOP  ACKB   MANT     Compute log B*.99^C until < .1
	1924,	// 0x0FE: 0x784          SRLB   MANT                                   
	1924,	// 0x0FF: 0x784          SRLB   MANT                                   
	1700,	// 0x100: 0x6A4          SCBC   MANT     C -= C / 100                  
	1431,	// 0x101: 0x597          TFB    NEWEXP   indicates ALOG here           
	823,	// 0x102: 0x337          BINE   ALOGLOOP                               
	2009,	// 0x103: 0x7D9          ACKC   EXPSGNS1 Count number of iterations    
	1787,	// 0x104: 0x6FB          CCK    MASKA1   C vs 100000                   
	253,	// 0x105: 0x0FD          BIE    LOGLOOP  Loop if >=                    
		//              Get a couple decimal points of accuracy by adding the remainder*100
		//              Explanation using Taylor series:
		//              .99^(epsilon*100) = 1-epsilon = 1/(1+epsilon) approximately
		//              So if C*.99^N = 1+epsilon, then C*.99^(N+epsilon*100) = (1+epsilon)/(1+epsilon) = 1
		//              Thus N + epsilon * 100 is the better approximation
	1993,	// 0x106: 0x7C9          SCBB   EXPSGNS1 undo last iteration: count in B EXP       
	2036,	// 0x107: 0x7F4          ABCC   MANT     undo last MANT subtract                   
	1723,	// 0x108: 0x6BB          SCKC   MASKA1                                             
	1920,	// 0x109: 0x780          SRLB   ALL      Shift count into B mantissa               
	1920,	// 0x10A: 0x780          SRLB   ALL                                                
	1920,	// 0x10B: 0x780          SRLB   ALL                                                
	1920,	// 0x10C: 0x780          SRLB   ALL                                                
	1588,	// 0x10D: 0x634          ABCB   MANT     add epsilon*100                           
	1844,	// 0x10E: 0x734          EXAB   MANT     result in A MANT                          
	1445,	// 0x10F: 0x5A5          TFA    LOW                                                
	814,	// 0x110: 0x32E          BINE   ANTILOG  return to ANTILOG if LOW set              
	1600,	// 0x111: 0x640          ABOC   ALL      Copy B (arg) to C                         
	1479,	// 0x112: 0x5C7          FFA    TAN      go through loop twice, tracked by TAN flag
	1447,	// 0x113: 0x5A7          TFA    TAN                                                
	765,	// 0x114: 0x2FD          BINE   LOGLOOP  back to the loop with the argument        
		//              Second power loop done for LOG. A EXP is original EXP.
		//              A MANT = -log(original A MANT) / log(.99)
		//              B MANT = 229.15 = -1 / log(.99)
		//              Copy A MANT to C MANT, then compute C MANT / B MANT
		//              This yields A MANT = log(original A MANT)
	1572,	// 0x115: 0x624          AAKC   MANT     
		//              For LOG fall-through: 229.15 in B, -log(arg)/log(.99) in A and C
		//              At ALOGDIV entry: 1+epsilon in B, .99^N in C
	1796,	// 0x116: 0x704 ALOGDIV  AKA    MANT     clear A mant, arg exp still in A
		//              Compute A MANT = C MANT / B MANT by long division
	1806,	// 0x117: 0x70E DIVMANT  AKA    DIGIT4   start digit count at 4, iterate until 10
		//              The DIVLOOP loop repeatedly subtracts B from C, counting into A
	1764,	// 0x118: 0x6E4 DIVLOOP  CCB    MANT     Compare C and B to see if subtraction done
	797,	// 0x119: 0x31D          BINE   SHIFTDIV branch if C < B                           
	1700,	// 0x11A: 0x6A4          SCBC   MANT     C -= B                                    
	1562,	// 0x11B: 0x61A          AAKA   MANT1    increment low digit of A                  
	280,	// 0x11C: 0x118          BIE    DIVLOOP  BET                                       
	1571,	// 0x11D: 0x623 SHIFTDIV AAKC   DIGIT1   increment digit count into C              
	803,	// 0x11E: 0x323          BINE   DIVDONE  overflow                                  
	1860,	// 0x11F: 0x744          SLLA   MANT     shift A mantissa left                     
	1631,	// 0x120: 0x65F          ACKA   DIGIT    copy digit count back to A                
	1892,	// 0x121: 0x764          SLLC   MANT     and shift C mantissa left                 
	280,	// 0x122: 0x118          BIE    DIVLOOP  branch every time                         
	1807,	// 0x123: 0x70F DIVDONE  AKA    DIGIT    NOP to clear flag                         
	1443,	// 0x124: 0x5A3          TFA    UP_LOW   pick the return target                    
	808,	// 0x125: 0x328          BINE   ADDLOG   continue for LOG                          
	130,	// 0x126: 0x082          BIE    NORMLIZE done for DIV                              
	10,	// 0x127: 0x00A WAITED   BIE    WAITED2  inconvenient WAITNO target                
		//              For LOG, add (original) A exponent to result via ADDSUB
	1572,	// 0x128: 0x624 ADDLOG   AAKC   MANT     A mantissa -> C                                      
	1796,	// 0x129: 0x704          AKA    MANT     clear A mantissa                                     
	1904,	// 0x12A: 0x770          SRLA   ALL      shift exponent into top of mantissa (log of exponent)
	1904,	// 0x12B: 0x770          SRLA   ALL                                                           
	1794,	// 0x12C: 0x702          AKA    EXP      clear exponent                                       
		//              At this point, original EXP is in A digits 5 and 6, log of original MANT is in C
		//              Add them together to get final log
	61,	// 0x12D: 0x03D          BIE    ADDSUB   BET (clear from AAKC)
		//              A holds the original int part in digits 1-4, 229.15 in digits 6-10
		//              B holds the original fractional part in digits 6-10
	1572,	// 0x12E: 0x624 ANTILOG  AAKC   MANT     copy 229.15 to C                    
	1796,	// 0x12F: 0x704          AKA    MANT     clear A MANT                        
	1803,	// 0x130: 0x70B          AKA    MASKA1                                       
	1652,	// 0x131: 0x674          SABA   MANT                                         
	1844,	// 0x132: 0x734          EXAB   MANT     B holds 1 - original fractional part
	117,	// 0x133: 0x075          BIE    MULTMANT Sub call to multiply by 229.15      
	1908,	// 0x134: 0x774 ALOGRET  SRLA   MANT                                         
	1335,	// 0x135: 0x537          SFB    NEWEXP   indicates ALOG                      
	251,	// 0x136: 0x0FB          BIE    LOG      Branch every time                   
		//              conditional for LOGLOOP when doing ANTILOG
		//              loop number of times in A MANT
	1693,	// 0x137: 0x69D ALOGLOOP SAKA   MANTD1   decrement A and if non-negative...
	253,	// 0x138: 0x0FD          BIE    LOGLOOP  go back to LOGLOOP                
		//              Get a couple more digits of accuracy. The idea is that
		//              .99^epsilon = 1-epsilon/100 = 1/(1+epsilon/100)) approximately
		//              so divide by 1+remainder/100 to account for the fractional part of
		//              the exponent in .99^N, since the loop only does the integer part.
	1565,	// 0x139: 0x61D          AAKA   MANTD1   restore A digits to 0                     
	1860,	// 0x13A: 0x744          SLLA   MANT     use the ignored digits for extra accuracy?
	1563,	// 0x13B: 0x61B          AAKA   MASKA1   A = 1 + remainder/100                     
	2036,	// 0x13C: 0x7F4          ABCC   MANT     restore value of C from extra iteration   
	1844,	// 0x13D: 0x734          EXAB   MANT     B has correction factor, C has 10*.99^N   
	1411,	// 0x13E: 0x583          ZFA    UP_LOW                                             
	790,	// 0x13F: 0x316          BINE   ALOGDIV  BET divide and finish up ALOG             
		//              A Flags:
		//              0 ALL - all flags, for clearing
		//              1 (S10) RET1FLAG - indicates return to DIV
		//              3 (S6) UP_LOW - indicates either UP or LOW functions
		//              5 (S0) LOW - indicates a LOW function
		//              7 (S9) TAN - indicates TAN selected
		//              11 (S5) COS_TAN - indicates COS or TAN selected
		//              B Flags:
		//              0 ALL - all flags, for clearing
		//              1 (S10) EMODE - indicates E has been pressed
		//              6 (S8S7) OPDONE - indicates operation completed, waiting for number
		//              7 (S9) NEWEXP: E pressed, entering a new exponent; also for ALOG
		//
		//              Masks:
		//               S value
		//              a9876543210
		//              00000000000 mask 0 ALL - all digits
		//              5           mask 1 MANT_S5 - mantissa sign; 5 is negative
		//                00        mask 2 EXP - exponent for value
		//                  1       mask 3 DIGIT1
		//                  0000000 mask 4 MANT - mantissa
		//                        1 mask 5 MANTLOW1 - low digit of mantissa
		//                01        mask 6 EXP1 - mantissa constant 1
		//               5          mask 7 EXP_S5 - exponent sign; 5 is negative
		//              000000      mask 8 TOPSTUFF
		//              0001        mask 9 EXPSGNS1 - exponent and signs, also a counter
		//                  0000001 mask a MANT1 - mantissa constant 1
		//                   1      mask b MASKA1 - counter or digit in mantissa
		//                  00005   mask c MANTD5
		//                  00001   mask d MANTD1
		//                  4       mask e DIGIT4
		//                  0       mask f DIGIT
};
