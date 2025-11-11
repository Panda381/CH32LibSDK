
// ****************************************************************************
//
//                          Datamath program
//
// ****************************************************************************
// Original source Ken Shirriff
// https://static.righto.com/calculator/TI_calculator_simulator.html

const u16 ProgDatamath[320] = {
	1423,	// 0x000: 0x58F .CLEAR   ZFA    ALL      Power on, clear flags
	1407,	// 0x001: 0x57F          ZFB    ALL
	1807,	// 0x002: 0x70F          AKA    ALL      Clear A and C
	1839,	// 0x003: 0x72F          AKC    ALL
	5,	// 0x004: 0x005          BET    RJ       Reset condition latch
	1755,	// 0x005: 0x6DB .RJ      CAK    MANT1    Right justify A, maybe add minu...
	531,	// 0x006: 0x213          BILT   ZERO     Mantissa is zero?
	1446,	// 0x007: 0x5A6 .S       TFA    SIGN
	12,	// 0x008: 0x00C          BIZ    RJ1      A is positive
	1992,	// 0x009: 0x7C8          SAKAH  OV1      Minus sign is hex 14
	1992,	// 0x00A: 0x7C8          SAKAH  OV1
	12,	// 0x00B: 0x00C          BET    RJ1      Reset condition latch
	1746,	// 0x00C: 0x6D2 .RJ1     CAK    LSD1     Right justify the display
	21,	// 0x00D: 0x015          BIGE   DPTPOS
	1757,	// 0x00E: 0x6DD          CAK    EXP1
	533,	// 0x00F: 0x215          BILT   DPTPOS
	1916,	// 0x010: 0x77C          SRLA   MANT     Shift A mantissa right
	1693,	// 0x011: 0x69D          SAKA   EXP1     Decrement A exponent
	12,	// 0x012: 0x00C          BET    RJ1
	1807,	// 0x013: 0x70F .ZERO    AKA    ALL      A is zero, clear entire register
	1414,	// 0x014: 0x586          ZFA    SIGN     Clear A sign flag
	1855,	// 0x015: 0x73F .DPTPOS  EXAB   ALL      Compute decimal point position...
	1803,	// 0x016: 0x70B          AKA    MANT1
	1563,	// 0x017: 0x61B          AAKA   MANT1
	1852,	// 0x018: 0x73C          EXAB   MANT     B mantissa is 2
	1598,	// 0x019: 0x63E          ABOA   EXP      Restore A exponent
	1693,	// 0x01A: 0x69D .DP1     SAKA   EXP1     Shift B (2) left by A exponent...
	542,	// 0x01B: 0x21E          BILT   DP2
	1884,	// 0x01C: 0x75C          SLLB   MANT
	26,	// 0x01D: 0x01A          BET    DP1
	1598,	// 0x01E: 0x63E .DP2     ABOA   EXP
	1432,	// 0x01F: 0x598          TFB    F10
	553,	// 0x020: 0x229          BIO    ID1
	1360,	// 0x021: 0x550 .LOCK    SYNC            Debounce: wait for no key for a few cycles...
	1376,	// 0x022: 0x560          SCAN
	545,	// 0x023: 0x221          BID    LOCK
	1360,	// 0x024: 0x550          SYNC
	1376,	// 0x025: 0x560          SCAN
	545,	// 0x026: 0x221          BID    LOCK
	1646,	// 0x027: 0x66E          ACKB   EXP
	1838,	// 0x028: 0x72E .IDLE    AKC    EXP      Idle loop entry
	1400,	// 0x029: 0x578 .ID1     ZFB    F10
	1319,	// 0x02A: 0x527 .ID2     WAITNO ID3      Wait for key press or timeout
	1360,	// 0x02B: 0x550 .ID4     SYNC
	1376,	// 0x02C: 0x560          SCAN
	616,	// 0x02D: 0x268          BID    KEY      Key down
	2013,	// 0x02E: 0x7DD .FD1     ACKC   EXP1
	1777,	// 0x02F: 0x6F1          CCK    TIM4     Check number of timeouts
	564,	// 0x030: 0x234          BILT   FD3
	1838,	// 0x031: 0x72E          AKC    EXP
	1360,	// 0x032: 0x550          SYNC
	1297,	// 0x033: 0x511          WAITDK ID5      Turn off display, wait for DK
	1429,	// 0x034: 0x595 .FD3     TFB    F5       Test overflow
	42,	// 0x035: 0x02A          BIZ    ID2
	1336,	// 0x036: 0x538          SFB    F10
	1836,	// 0x037: 0x72C          AKC    MANT
	1723,	// 0x038: 0x6BB          SCKC   MANT1
	58,	// 0x039: 0x03A          BET    FD5      Reset condition latch
	1644,	// 0x03A: 0x66C .FD5     ACKB   MANT
	2013,	// 0x03B: 0x7DD          ACKC   EXP1
	1320,	// 0x03C: 0x528          WAITNO FD4
	1329,	// 0x03D: 0x531 .MINKEY  SFB    OP2      MINUS = flags II, III
	1443,	// 0x03E: 0x5A3          TFA    F3       If CD is clear...
	77,	// 0x03F: 0x04D          BIZ    PLSKEY   perform subtract operation
	1444,	// 0x040: 0x5A4          TFA    F4       Or EQ is clear...
	589,	// 0x041: 0x24D          BIO    PLSKEY   perform subtract operation
	1440,	// 0x042: 0x5A0          TFA    OP1      Or not after multi/div...
	77,	// 0x043: 0x04D          BIZ    PLSKEY   perform subtract operation
	1393,	// 0x044: 0x571          ZFB    OP2      Minus key as sign after mult or divide
	1350,	// 0x045: 0x546          SFA    SIGN     Set sign to minus
	1807,	// 0x046: 0x70F          AKA    ALL      Clear A
	1351,	// 0x047: 0x547          SFA    F9       Set ST flag (sign temp) for unary minus
	1552,	// 0x048: 0x610          AAKA   DPT7     Set A exponent to 7
	1411,	// 0x049: 0x583          ZFA    F3       Clear CD
	7,	// 0x04A: 0x007          BET    S        Update display
	1329,	// 0x04B: 0x531 .DIVKEY  SFB    OP2      DIV = flags II, III
	1328,	// 0x04C: 0x530 .MLTKEY  SFB    OP1      MULT = flags I, III
	1330,	// 0x04D: 0x532 .PLSKEY  SFB    OP3      PLUS = flag III
	1443,	// 0x04E: 0x5A3          TFA    F3       Clear display flag
	594,	// 0x04F: 0x252          BIO    KS1
	1444,	// 0x050: 0x5A4          TFA    F4       Equal flag
	86,	// 0x051: 0x056          BIZ    KS2
	1412,	// 0x052: 0x584 .KS1     ZFA    F4
	1349,	// 0x053: 0x545          SFA    F5
	86,	// 0x054: 0x056          BET    KS2
	1348,	// 0x055: 0x544 .EQLKEY  SFA    F4       F4 (EQ) flag set for equals
	1755,	// 0x056: 0x6DB .KS2     CAK    MANT1
	670,	// 0x057: 0x29E          BILT   KS6      A mantissa == 0?
	1752,	// 0x058: 0x6D8 .KS3     CAK    OV1      Left justify A...
	299,	// 0x059: 0x12B          BIGE   KS4      Digit has reached left?
	1868,	// 0x05A: 0x74C          SLLA   MANT     Shift mantissa left
	1565,	// 0x05B: 0x61D          AAKA   EXP1     Increment exponent
	88,	// 0x05C: 0x058          BET    KS3
	1352,	// 0x05D: 0x548 .DPTKEY  SFA    F10      Decimal point key...
	1415,	// 0x05E: 0x587          ZFA    F9       Set DPT flag, clear ST flag
	1443,	// 0x05F: 0x5A3          TFA    F3
	21,	// 0x060: 0x015          BIZ    DPTPOS
	1411,	// 0x061: 0x583          ZFA    F3
	19,	// 0x062: 0x013          BET    ZERO
	1443,	// 0x063: 0x5A3 .CEKEY   TFA    F3
	533,	// 0x064: 0x215          BIO    DPTPOS
	1347,	// 0x065: 0x543          SFA    F3
	1416,	// 0x066: 0x588          ZFA    F10
	19,	// 0x067: 0x013          BET    ZERO
	1614,	// 0x068: 0x64E .KEY     ABOC   EXP      Process key down...
	1429,	// 0x069: 0x595          TFB    F5       Test overflow
	545,	// 0x06A: 0x221          BIO    LOCK     overflow never gets cleared?
	1360,	// 0x06B: 0x550          SYNC            Wait to debounce key
	1360,	// 0x06C: 0x550          SYNC
	1376,	// 0x06D: 0x560          SCAN
	40,	// 0x06E: 0x028          BIU    IDLE
	1823,	// 0x06F: 0x71F          AKB    ALL
	1360,	// 0x070: 0x550          SYNC
	1024,	// 0x071: 0x400          BKO    CLEAR    Clear key pressed?
	1109,	// 0x072: 0x455          BKO    EQLKEY   Equal key pressed?
	1101,	// 0x073: 0x44D          BKO    PLSKEY   Plus key pressed?
	1085,	// 0x074: 0x43D          BKO    MINKEY   Minus key pressed?
	1100,	// 0x075: 0x44C          BKO    MLTKEY   Mult key pressed?
	1099,	// 0x076: 0x44B          BKO    DIVKEY   Divide key pressed?
	1123,	// 0x077: 0x463          BKO    CEKEY    CE key pressed?
	1117,	// 0x078: 0x45D          BKO    DPTKEY   Decimal point key pressed?
	1150,	// 0x079: 0x47E          BKO    ZERKEY   Zero key pressed?
	1855,	// 0x07A: 0x73F          EXAB   ALL      Process digit key...
	1954,	// 0x07B: 0x7A2          AKCN   LSD1     Count key position into A
	1855,	// 0x07C: 0x73F          EXAB   ALL
	533,	// 0x07D: 0x215          BIC    DPTPOS   No key pressed
	1443,	// 0x07E: 0x5A3 .ZERKEY  TFA    F3       Clear display flag
	131,	// 0x07F: 0x083          BIZ    NUM1
	1414,	// 0x080: 0x586 .CD      ZFA    SIGN
	1807,	// 0x081: 0x70F .CD1     AKA    ALL
	1411,	// 0x082: 0x583          ZFA    F3
	1446,	// 0x083: 0x5A6 .NUM1    TFA    SIGN     Number: Digit is in B...
	148,	// 0x084: 0x094          BIZ    NUM3     Branch if A SIGN clear
	1976,	// 0x085: 0x7B8          AAKAH  OV1      Test for 15 in OV1?
	1976,	// 0x086: 0x7B8          AAKAH  OV1
	1992,	// 0x087: 0x7C8          SAKAH  OV1
	1992,	// 0x088: 0x7C8          SAKAH  OV1
	533,	// 0x089: 0x215          BIC    DPTPOS   Borrow set if OV1 == 15?
	1447,	// 0x08A: 0x5A7 .NUM2    TFA    F9       Test ST (sign temp) flag
	152,	// 0x08B: 0x098          BIZ    NUM4
	1448,	// 0x08C: 0x5A8          TFA    F10
	658,	// 0x08D: 0x292          BIO    NUM7
	1855,	// 0x08E: 0x73F          EXAB   ALL
	1755,	// 0x08F: 0x6DB          CAK    MANT1
	1855,	// 0x090: 0x73F          EXAB   ALL
	533,	// 0x091: 0x215          BILT   DPTPOS
	1415,	// 0x092: 0x587 .NUM7    ZFA    F9       Clear ST flag
	156,	// 0x093: 0x09C          BET    NUM6
	1754,	// 0x094: 0x6DA .NUM3    CAK    MSD1
	21,	// 0x095: 0x015          BIGE   DPTPOS
	1744,	// 0x096: 0x6D0          CAK    DPT7
	21,	// 0x097: 0x015          BIGE   DPTPOS
	1448,	// 0x098: 0x5A8 .NUM4    TFA    F10
	155,	// 0x099: 0x09B          BIZ    NUM5
	1565,	// 0x09A: 0x61D          AAKA   EXP1
	1868,	// 0x09B: 0x74C .NUM5    SLLA   MANT
	1586,	// 0x09C: 0x632 .NUM6    ABOA   LSD1
	21,	// 0x09D: 0x015          BET    DPTPOS
	1806,	// 0x09E: 0x70E .KS6     AKA    EXP
	1414,	// 0x09F: 0x586          ZFA    SIGN
	1552,	// 0x0A0: 0x610          AAKA   DPT7
	1418,	// 0x0A1: 0x58A .KS7     ZFA    FD       Zeros temp(num) and dpt flag
	1445,	// 0x0A2: 0x5A5          TFA    F5       Post flag
	765,	// 0x0A3: 0x2FD          BIO    POST
	1442,	// 0x0A4: 0x5A2          TFA    OP3
	253,	// 0x0A5: 0x0FD          BIZ    POST
	1647,	// 0x0A6: 0x66F          ACKB   ALL
	1427,	// 0x0A7: 0x593          TFB    F3       Constant flag
	173,	// 0x0A8: 0x0AD          BIZ    KS8
	1395,	// 0x0A9: 0x573          ZFB    F3
	1855,	// 0x0AA: 0x73F          EXAB   ALL
	1615,	// 0x0AB: 0x64F          ABOC   ALL
	1526,	// 0x0AC: 0x5F6          EXF    SIGN
	1440,	// 0x0AD: 0x5A0 .KS8     TFA    OP1
	719,	// 0x0AE: 0x2CF          BIO    MLTDIV
	1430,	// 0x0AF: 0x596 .ADDSUB  TFB    SIGN     Add / subtract...
	178,	// 0x0B0: 0x0B2          BIZ    AS1      Copy B sign to TEMP...
	1349,	// 0x0B1: 0x545          SFA    F5
	1441,	// 0x0B2: 0x5A1 .AS1     TFA    OP2      Flip B sign for subtract...
	181,	// 0x0B3: 0x0B5          BIZ    AS2
	1462,	// 0x0B4: 0x5B6          FFB    SIGN
	1742,	// 0x0B5: 0x6CE .AS2     CAB    EXP      Make sure A exponent >= B exponent...
	185,	// 0x0B6: 0x0B9          BIGE   AS3
	1855,	// 0x0B7: 0x73F          EXAB   ALL      Exchange if A exponent smaller
	1526,	// 0x0B8: 0x5F6          EXF    SIGN     And exchange the signs
	1693,	// 0x0B9: 0x69D .AS3     SAKA   EXP1     Shift A right until exponents equal...
	1742,	// 0x0BA: 0x6CE          CAB    EXP      Infinite loop if B EXP == 0?
	702,	// 0x0BB: 0x2BE          BILT   AS4
	1916,	// 0x0BC: 0x77C          SRLA   MANT
	185,	// 0x0BD: 0x0B9          BET    AS3
	1565,	// 0x0BE: 0x61D .AS4     AAKA   EXP1     Exponents now equal
	192,	// 0x0BF: 0x0C0          BET    AS5      Reset condition
	1740,	// 0x0C0: 0x6CC .AS5     CAB    MANT     Make sure A >= B...
	196,	// 0x0C1: 0x0C4          BIGE   AS6
	1855,	// 0x0C2: 0x73F          EXAB   ALL      If not, exchange exponents
	1526,	// 0x0C3: 0x5F6          EXF    SIGN     and exchange signs
	1494,	// 0x0C4: 0x5D6 .AS6     CF     SIGN
	200,	// 0x0C5: 0x0C8          BIE    AS7      If signs equal, add...
	1660,	// 0x0C6: 0x67C          SABA   MANT     Otherwise subtract
	201,	// 0x0C7: 0x0C9          BET    AS8
	1548,	// 0x0C8: 0x60C .AS7     AABA   MANT     Add mantissas
	1398,	// 0x0C9: 0x576 .AS8     ZFB    SIGN     Restore B sign from TEMP flag...
	1445,	// 0x0CA: 0x5A5          TFA    F5
	253,	// 0x0CB: 0x0FD          BIZ    POST
	1334,	// 0x0CC: 0x536          SFB    SIGN
	1413,	// 0x0CD: 0x585          ZFA    F5       And clear TEMP
	253,	// 0x0CE: 0x0FD          BET    POST     Done add/sub
	1494,	// 0x0CF: 0x5D6 .MLTDIV  CF     SIGN     Mult / div operation...
	1414,	// 0x0D0: 0x586          ZFA    SIGN     Positive result if signs the same
	211,	// 0x0D1: 0x0D3          BIE    MD1
	1350,	// 0x0D2: 0x546          SFA    SIGN     A, B signs different: negative result
	1441,	// 0x0D3: 0x5A1 .MD1     TFA    OP2
	740,	// 0x0D4: 0x2E4          BIC    DIV
	1583,	// 0x0D5: 0x62F          AAKC   ALL      Copy A to C
	1804,	// 0x0D6: 0x70C          AKA    MANT     Clear A mantissa
	1550,	// 0x0D7: 0x60E          AABA   EXP      Add A and B exponents
	1714,	// 0x0D8: 0x6B2 .M1      SCKC   LSD1     Repeat least-significant-digit of C times...
	732,	// 0x0D9: 0x2DC          BILT   M2
	1548,	// 0x0DA: 0x60C          AABA   MANT     Add B to A
	216,	// 0x0DB: 0x0D8          BET    M1
	1948,	// 0x0DC: 0x79C .M2      SRLC   MANT     Shift C right
	1787,	// 0x0DD: 0x6FB          CCK    MANT1    Is C zero?
	764,	// 0x0DE: 0x2FC          BILT   MD2      Multiply done
	1916,	// 0x0DF: 0x77C          SRLA   MANT     Shift A right
	1693,	// 0x0E0: 0x69D          SAKA   EXP1     And decrease exponent
	216,	// 0x0E1: 0x0D8          BIGE   M1       Repeat the addition loop for the next C digit
	1333,	// 0x0E2: 0x535          SFB    F5       Set overflow to indicate exponent negative
	216,	// 0x0E3: 0x0D8          BET    M1       But keep going
	1787,	// 0x0E4: 0x6FB .DIV     CCK    MANT1    Divide code: A / B...
	762,	// 0x0E5: 0x2FA          BILT   ERR      Divide by zero
	1583,	// 0x0E6: 0x62F          AAKC   ALL      C / B, result goes in A...
	1804,	// 0x0E7: 0x70C .D1      AKA    MANT     Clear A mantissa
	1787,	// 0x0E8: 0x6FB          CCK    MANT1
	764,	// 0x0E9: 0x2FC          BILT   MD2      Answer zero
	1662,	// 0x0EA: 0x67E          SABA   EXP
	237,	// 0x0EB: 0x0ED          BIGE   D2
	1333,	// 0x0EC: 0x535          SFB    F5
	1772,	// 0x0ED: 0x6EC .D2      CCB    MANT     Repeatedly subtract B from C...
	754,	// 0x0EE: 0x2F2          BILT   D3       Can't subtract any more
	1708,	// 0x0EF: 0x6AC          SCBC   MANT     Subtract B from C
	1554,	// 0x0F0: 0x612          AAKA   LSD1     And increment quotient in A
	237,	// 0x0F1: 0x0ED          BET    D2
	1754,	// 0x0F2: 0x6DA .D3      CAK    MSD1     Value in A's most significant digit?
	252,	// 0x0F3: 0x0FC          BIGE   MD2      Divide done
	1900,	// 0x0F4: 0x76C          SLLC   MANT     Shift C left
	1868,	// 0x0F5: 0x74C          SLLA   MANT     Shift A left
	1565,	// 0x0F6: 0x61D          AAKA   EXP1     Increment exponent
	237,	// 0x0F7: 0x0ED          BINC   D2       If negative exponent becomes zero...
	1397,	// 0x0F8: 0x575          ZFB    F5       Clear the overflow
	237,	// 0x0F9: 0x0ED          BET    D2       And keep going
	1333,	// 0x0FA: 0x535 .ERR     SFB    F5       Divide by zero - Set overflow
	19,	// 0x0FB: 0x013          BET    ZERO
	1615,	// 0x0FC: 0x64F .MD2     ABOC   ALL      Done: move B to C
	1822,	// 0x0FD: 0x71E .POST    AKB    EXP      Post-operation normalization...
	1808,	// 0x0FE: 0x710          AKB    DPT7     Set B exponent to 7
	1752,	// 0x0FF: 0x6D8          CAK    OV1      Is A overflow (top digit) set?
	776,	// 0x100: 0x308          BILT   P1       Branch if zero
	1916,	// 0x101: 0x77C          SRLA   MANT
	1693,	// 0x102: 0x69D          SAKA   EXP1
	264,	// 0x103: 0x108          BIGE   P1
	1333,	// 0x104: 0x535          SFB    F5
	1550,	// 0x105: 0x60E .OVF     AABA   EXP
	1565,	// 0x106: 0x61D          AAKA   EXP1
	825,	// 0x107: 0x339          BIC    OVF1
	1429,	// 0x108: 0x595 .P1      TFB    F5       Test BF overflow
	773,	// 0x109: 0x305          BIO    OVF
	1755,	// 0x10A: 0x6DB          CAK    MANT1    Is A mantissa zero?
	786,	// 0x10B: 0x312          BILT   P3       Branch if zero?
	1754,	// 0x10C: 0x6DA .P2      CAK    MSD1     Left-justify A...
	276,	// 0x10D: 0x114          BIGE   P4
	1868,	// 0x10E: 0x74C          SLLA   MANT
	1565,	// 0x10F: 0x61D          AAKA   EXP1     Incrementing exponent each shift
	268,	// 0x110: 0x10C          BET    P2
	43,	// 0x111: 0x02B .ID5     BET    ID4      Random branch destination from WAITDK
	1598,	// 0x112: 0x63E .P3      ABOA   EXP      A is zero
	1414,	// 0x113: 0x586          ZFA    SIGN     And clear the sign
	1426,	// 0x114: 0x592 .P4      TFB    OP3      In middle of operation?
	285,	// 0x115: 0x11D          BIZ    P7       Branch if operation completed
	1331,	// 0x116: 0x533          SFB    F3       Set BF CONST
	1583,	// 0x117: 0x62F .P5      AAKC   ALL      Copy A to C
	1494,	// 0x118: 0x5D6          CF     SIGN     Flip B SIGN if A and B SIGN different...
	283,	// 0x119: 0x11B          BIE    P6
	1462,	// 0x11A: 0x5B6          FFB    SIGN
	1529,	// 0x11B: 0x5F9 .P6      EXF    OPFGS    Move BF op flags to AF
	1401,	// 0x11C: 0x579          ZFB    OPFGS    and clear B op flags
	1347,	// 0x11D: 0x543 .P7      SFA    F3       Set AF CD
	1413,	// 0x11E: 0x585          ZFA    F5       Clear AF POST/TEMP
	1742,	// 0x11F: 0x6CE          CAB    EXP      Shift A right until exponent <= 7...
	517,	// 0x120: 0x205          BILT   RJ       Branch if done
	1662,	// 0x121: 0x67E          SABA   EXP      Subtract 7 from A exponent
	1757,	// 0x122: 0x6DD .P8      CAK    EXP1     Shift A right until exponent 0...
	809,	// 0x123: 0x329          BILT   P9       Add 7 back to exponent when done...
	1693,	// 0x124: 0x69D          SAKA   EXP1     otherwise
	1916,	// 0x125: 0x77C          SRLA   MANT
	290,	// 0x126: 0x122          BET    P8       keep looping
	43,	// 0x127: 0x02B .ID3     BET    ID4
	21,	// 0x128: 0x015 .FD4     BET    DPTPOS   Random WAITNO jump destination
	1552,	// 0x129: 0x610 .P9      AAKA   DPT7     Add 7 to A exponent
	5,	// 0x12A: 0x005          BET    RJ       Branch
	1446,	// 0x12B: 0x5A6 .KS4     TFA    SIGN     A negative?
	310,	// 0x12C: 0x136          BIZ    KS9
	1800,	// 0x12D: 0x708          AKA    OV1      1 -> OV1
	1688,	// 0x12E: 0x698          SAKA   OV1      0 -> OV1 ?
	1755,	// 0x12F: 0x6DB          CAK    MANT1
	670,	// 0x130: 0x29E          BILT   KS6
	1754,	// 0x131: 0x6DA .KS5     CAK    MSD1
	161,	// 0x132: 0x0A1          BIGE   KS7
	1868,	// 0x133: 0x74C          SLLA   MANT
	1565,	// 0x134: 0x61D          AAKA   EXP1
	305,	// 0x135: 0x131          BET    KS5
	1916,	// 0x136: 0x77C .KS9     SRLA   MANT
	1693,	// 0x137: 0x69D          SAKA   EXP1
	161,	// 0x138: 0x0A1          BET    KS7
	1446,	// 0x139: 0x5A6 .OVF1    TFA    SIGN
	21,	// 0x13A: 0x015          BIZ    DPTPOS
	1992,	// 0x13B: 0x7C8          SAKAH  OV1
	1992,	// 0x13C: 0x7C8          SAKAH  OV1
	533,	// 0x13D: 0x215          BILT   DPTPOS   Will this ever be true?
	0,	// 0x13E: 0x000
	0,	// 0x13F: 0x000
};
