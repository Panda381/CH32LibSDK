/*
    minimidi file created by midiconverter.py v2 
        
    Times are in 10 ms (.010s)
    Assumes same instrument is on all tracks
    
    byt bit desc
    1   8   ticks
            0xff song end (max delay 253)
            0xfe extended delay (16 bit delay) two more bytecount then note info
            
    2   1.7 voicehigh.1 note.7
        6.2 velocity.6 voicelow.2, velocity 0 is note off
*/

const unsigned char song[]={

	0,((( 0 &4)<<5)|( 62 &0x7f)), ((0 &3)|((64 &0x7e)<<1)),	//# 1, ticks 0, elapsed 0, voice: 0 note: 62 velocity 64 event ('note', 0, 1, 62, 64)
	0,((( 1 &4)<<5)|( 59 &0x7f)), ((1 &3)|((56 &0x7e)<<1)),	//# 2, ticks 0, elapsed 0, voice: 1 note: 59 velocity 56 event ('note', 0, 1, 59, 56)
	0,((( 1 &4)<<5)|( 43 &0x7f)), ((1 &3)|((55 &0x7e)<<1)),	//# 3, ticks 0, elapsed 0, voice: 1 note: 43 velocity 55 event ('note', 0, 1, 43, 55)
	28,((( 0 &4)<<5)|( 62 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 4, ticks 128, elapsed 28, voice: 0 note: 62 velocity 0 event ('note', 128, 1, 62, 0)
	0,((( 0 &4)<<5)|( 71 &0x7f)), ((0 &3)|((75 &0x7e)<<1)),	//# 5, ticks 128, elapsed 0, voice: 0 note: 71 velocity 75 event ('note', 128, 1, 71, 75)
	0,((( 1 &4)<<5)|( 43 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 6, ticks 128, elapsed 0, voice: 1 note: 43 velocity 0 event ('note', 128, 1, 43, 0)
	0,((( 1 &4)<<5)|( 50 &0x7f)), ((1 &3)|((63 &0x7e)<<1)),	//# 7, ticks 128, elapsed 0, voice: 1 note: 50 velocity 63 event ('note', 128, 1, 50, 63)
	28,((( 0 &4)<<5)|( 71 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 8, ticks 256, elapsed 28, voice: 0 note: 71 velocity 0 event ('note', 256, 1, 71, 0)
	0,((( 0 &4)<<5)|( 69 &0x7f)), ((0 &3)|((70 &0x7e)<<1)),	//# 9, ticks 256, elapsed 0, voice: 0 note: 69 velocity 70 event ('note', 256, 1, 69, 70)
	0,((( 1 &4)<<5)|( 50 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 10, ticks 256, elapsed 0, voice: 1 note: 50 velocity 0 event ('note', 256, 1, 50, 0)
	0,((( 1 &4)<<5)|( 55 &0x7f)), ((1 &3)|((62 &0x7e)<<1)),	//# 11, ticks 256, elapsed 0, voice: 1 note: 55 velocity 62 event ('note', 256, 1, 55, 62)
	28,((( 0 &4)<<5)|( 69 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 12, ticks 384, elapsed 28, voice: 0 note: 69 velocity 0 event ('note', 384, 1, 69, 0)
	0,((( 0 &4)<<5)|( 67 &0x7f)), ((0 &3)|((68 &0x7e)<<1)),	//# 13, ticks 384, elapsed 0, voice: 0 note: 67 velocity 68 event ('note', 384, 1, 67, 68)
	0,((( 1 &4)<<5)|( 55 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 14, ticks 384, elapsed 0, voice: 1 note: 55 velocity 0 event ('note', 384, 1, 55, 0)
	0,((( 1 &4)<<5)|( 50 &0x7f)), ((1 &3)|((59 &0x7e)<<1)),	//# 15, ticks 384, elapsed 0, voice: 1 note: 50 velocity 59 event ('note', 384, 1, 50, 59)
	// Note off skipped, note 59 not found in channels, probably interrupted
	28,((( 0 &4)<<5)|( 67 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 17, ticks 512, elapsed 28, voice: 0 note: 67 velocity 0 event ('note', 512, 1, 67, 0)
	0,((( 0 &4)<<5)|( 62 &0x7f)), ((0 &3)|((66 &0x7e)<<1)),	//# 18, ticks 512, elapsed 0, voice: 0 note: 62 velocity 66 event ('note', 512, 1, 62, 66)
	0,((( 1 &4)<<5)|( 59 &0x7f)), ((1 &3)|((58 &0x7e)<<1)),	//# 19, ticks 512, elapsed 0, voice: 1 note: 59 velocity 58 event ('note', 512, 1, 59, 58)
	// Note off skipped, note 50 not found in channels, probably interrupted
	0,((( 1 &4)<<5)|( 43 &0x7f)), ((1 &3)|((58 &0x7e)<<1)),	//# 21, ticks 512, elapsed 0, voice: 1 note: 43 velocity 58 event ('note', 512, 1, 43, 58)
	28,((( 1 &4)<<5)|( 43 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 22, ticks 640, elapsed 28, voice: 1 note: 43 velocity 0 event ('note', 640, 1, 43, 0)
	0,((( 1 &4)<<5)|( 50 &0x7f)), ((1 &3)|((63 &0x7e)<<1)),	//# 23, ticks 640, elapsed 0, voice: 1 note: 50 velocity 63 event ('note', 640, 1, 50, 63)
	28,((( 1 &4)<<5)|( 50 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 24, ticks 768, elapsed 28, voice: 1 note: 50 velocity 0 event ('note', 768, 1, 50, 0)
	0,((( 1 &4)<<5)|( 55 &0x7f)), ((1 &3)|((63 &0x7e)<<1)),	//# 25, ticks 768, elapsed 0, voice: 1 note: 55 velocity 63 event ('note', 768, 1, 55, 63)
	28,((( 0 &4)<<5)|( 62 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 26, ticks 896, elapsed 28, voice: 0 note: 62 velocity 0 event ('note', 896, 1, 62, 0)
	0,((( 0 &4)<<5)|( 62 &0x7f)), ((0 &3)|((70 &0x7e)<<1)),	//# 27, ticks 896, elapsed 0, voice: 0 note: 62 velocity 70 event ('note', 896, 1, 62, 70)
	0,((( 1 &4)<<5)|( 55 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 28, ticks 896, elapsed 0, voice: 1 note: 55 velocity 0 event ('note', 896, 1, 55, 0)
	0,((( 1 &4)<<5)|( 50 &0x7f)), ((1 &3)|((59 &0x7e)<<1)),	//# 29, ticks 896, elapsed 0, voice: 1 note: 50 velocity 59 event ('note', 896, 1, 50, 59)
	14,((( 0 &4)<<5)|( 62 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 30, ticks 960, elapsed 14, voice: 0 note: 62 velocity 0 event ('note', 960, 1, 62, 0)
	0,((( 0 &4)<<5)|( 62 &0x7f)), ((0 &3)|((73 &0x7e)<<1)),	//# 31, ticks 960, elapsed 0, voice: 0 note: 62 velocity 73 event ('note', 960, 1, 62, 73)
	// Note off skipped, note 59 not found in channels, probably interrupted
	14,((( 0 &4)<<5)|( 62 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 33, ticks 1024, elapsed 14, voice: 0 note: 62 velocity 0 event ('note', 1024, 1, 62, 0)
	0,((( 0 &4)<<5)|( 62 &0x7f)), ((0 &3)|((70 &0x7e)<<1)),	//# 34, ticks 1024, elapsed 0, voice: 0 note: 62 velocity 70 event ('note', 1024, 1, 62, 70)
	0,((( 1 &4)<<5)|( 59 &0x7f)), ((1 &3)|((60 &0x7e)<<1)),	//# 35, ticks 1024, elapsed 0, voice: 1 note: 59 velocity 60 event ('note', 1024, 1, 59, 60)
	// Note off skipped, note 50 not found in channels, probably interrupted
	0,((( 1 &4)<<5)|( 43 &0x7f)), ((1 &3)|((56 &0x7e)<<1)),	//# 37, ticks 1024, elapsed 0, voice: 1 note: 43 velocity 56 event ('note', 1024, 1, 43, 56)
	28,((( 0 &4)<<5)|( 62 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 38, ticks 1152, elapsed 28, voice: 0 note: 62 velocity 0 event ('note', 1152, 1, 62, 0)
	0,((( 0 &4)<<5)|( 71 &0x7f)), ((0 &3)|((79 &0x7e)<<1)),	//# 39, ticks 1152, elapsed 0, voice: 0 note: 71 velocity 79 event ('note', 1152, 1, 71, 79)
	0,((( 1 &4)<<5)|( 43 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 40, ticks 1152, elapsed 0, voice: 1 note: 43 velocity 0 event ('note', 1152, 1, 43, 0)
	0,((( 1 &4)<<5)|( 50 &0x7f)), ((1 &3)|((63 &0x7e)<<1)),	//# 41, ticks 1152, elapsed 0, voice: 1 note: 50 velocity 63 event ('note', 1152, 1, 50, 63)
	28,((( 0 &4)<<5)|( 71 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 42, ticks 1280, elapsed 28, voice: 0 note: 71 velocity 0 event ('note', 1280, 1, 71, 0)
	0,((( 0 &4)<<5)|( 69 &0x7f)), ((0 &3)|((70 &0x7e)<<1)),	//# 43, ticks 1280, elapsed 0, voice: 0 note: 69 velocity 70 event ('note', 1280, 1, 69, 70)
	0,((( 1 &4)<<5)|( 50 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 44, ticks 1280, elapsed 0, voice: 1 note: 50 velocity 0 event ('note', 1280, 1, 50, 0)
	0,((( 1 &4)<<5)|( 55 &0x7f)), ((1 &3)|((64 &0x7e)<<1)),	//# 45, ticks 1280, elapsed 0, voice: 1 note: 55 velocity 64 event ('note', 1280, 1, 55, 64)
	28,((( 0 &4)<<5)|( 69 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 46, ticks 1408, elapsed 28, voice: 0 note: 69 velocity 0 event ('note', 1408, 1, 69, 0)
	0,((( 0 &4)<<5)|( 67 &0x7f)), ((0 &3)|((69 &0x7e)<<1)),	//# 47, ticks 1408, elapsed 0, voice: 0 note: 67 velocity 69 event ('note', 1408, 1, 67, 69)
	0,((( 1 &4)<<5)|( 55 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 48, ticks 1408, elapsed 0, voice: 1 note: 55 velocity 0 event ('note', 1408, 1, 55, 0)
	0,((( 1 &4)<<5)|( 50 &0x7f)), ((1 &3)|((58 &0x7e)<<1)),	//# 49, ticks 1408, elapsed 0, voice: 1 note: 50 velocity 58 event ('note', 1408, 1, 50, 58)
	// Note off skipped, note 59 not found in channels, probably interrupted
	28,((( 0 &4)<<5)|( 67 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 51, ticks 1536, elapsed 28, voice: 0 note: 67 velocity 0 event ('note', 1536, 1, 67, 0)
	0,((( 0 &4)<<5)|( 64 &0x7f)), ((0 &3)|((68 &0x7e)<<1)),	//# 52, ticks 1536, elapsed 0, voice: 0 note: 64 velocity 68 event ('note', 1536, 1, 64, 68)
	0,((( 1 &4)<<5)|( 60 &0x7f)), ((1 &3)|((63 &0x7e)<<1)),	//# 53, ticks 1536, elapsed 0, voice: 1 note: 60 velocity 63 event ('note', 1536, 1, 60, 63)
	// Note off skipped, note 50 not found in channels, probably interrupted
	0,((( 1 &4)<<5)|( 48 &0x7f)), ((1 &3)|((61 &0x7e)<<1)),	//# 55, ticks 1536, elapsed 0, voice: 1 note: 48 velocity 61 event ('note', 1536, 1, 48, 61)
	28,((( 1 &4)<<5)|( 48 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 56, ticks 1664, elapsed 28, voice: 1 note: 48 velocity 0 event ('note', 1664, 1, 48, 0)
	0,((( 1 &4)<<5)|( 52 &0x7f)), ((1 &3)|((60 &0x7e)<<1)),	//# 57, ticks 1664, elapsed 0, voice: 1 note: 52 velocity 60 event ('note', 1664, 1, 52, 60)
	28,((( 1 &4)<<5)|( 52 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 58, ticks 1792, elapsed 28, voice: 1 note: 52 velocity 0 event ('note', 1792, 1, 52, 0)
	0,((( 1 &4)<<5)|( 55 &0x7f)), ((1 &3)|((62 &0x7e)<<1)),	//# 59, ticks 1792, elapsed 0, voice: 1 note: 55 velocity 62 event ('note', 1792, 1, 55, 62)
	28,((( 1 &4)<<5)|( 55 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 60, ticks 1920, elapsed 28, voice: 1 note: 55 velocity 0 event ('note', 1920, 1, 55, 0)
	0,((( 1 &4)<<5)|( 52 &0x7f)), ((1 &3)|((63 &0x7e)<<1)),	//# 61, ticks 1920, elapsed 0, voice: 1 note: 52 velocity 63 event ('note', 1920, 1, 52, 63)
	28,((( 0 &4)<<5)|( 64 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 62, ticks 2048, elapsed 28, voice: 0 note: 64 velocity 0 event ('note', 2048, 1, 64, 0)
	// Note off skipped, note 60 not found in channels, probably interrupted
	0,((( 0 &4)<<5)|( 64 &0x7f)), ((0 &3)|((71 &0x7e)<<1)),	//# 64, ticks 2048, elapsed 0, voice: 0 note: 64 velocity 71 event ('note', 2048, 1, 64, 71)
	0,((( 1 &4)<<5)|( 60 &0x7f)), ((1 &3)|((58 &0x7e)<<1)),	//# 65, ticks 2048, elapsed 0, voice: 1 note: 60 velocity 58 event ('note', 2048, 1, 60, 58)
	// Note off skipped, note 52 not found in channels, probably interrupted
	0,((( 1 &4)<<5)|( 45 &0x7f)), ((1 &3)|((59 &0x7e)<<1)),	//# 67, ticks 2048, elapsed 0, voice: 1 note: 45 velocity 59 event ('note', 2048, 1, 45, 59)
	28,((( 0 &4)<<5)|( 64 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 68, ticks 2176, elapsed 28, voice: 0 note: 64 velocity 0 event ('note', 2176, 1, 64, 0)
	0,((( 0 &4)<<5)|( 72 &0x7f)), ((0 &3)|((78 &0x7e)<<1)),	//# 69, ticks 2176, elapsed 0, voice: 0 note: 72 velocity 78 event ('note', 2176, 1, 72, 78)
	0,((( 1 &4)<<5)|( 45 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 70, ticks 2176, elapsed 0, voice: 1 note: 45 velocity 0 event ('note', 2176, 1, 45, 0)
	0,((( 1 &4)<<5)|( 52 &0x7f)), ((1 &3)|((61 &0x7e)<<1)),	//# 71, ticks 2176, elapsed 0, voice: 1 note: 52 velocity 61 event ('note', 2176, 1, 52, 61)
	28,((( 0 &4)<<5)|( 72 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 72, ticks 2304, elapsed 28, voice: 0 note: 72 velocity 0 event ('note', 2304, 1, 72, 0)
	0,((( 0 &4)<<5)|( 71 &0x7f)), ((0 &3)|((70 &0x7e)<<1)),	//# 73, ticks 2304, elapsed 0, voice: 0 note: 71 velocity 70 event ('note', 2304, 1, 71, 70)
	0,((( 1 &4)<<5)|( 52 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 74, ticks 2304, elapsed 0, voice: 1 note: 52 velocity 0 event ('note', 2304, 1, 52, 0)
	0,((( 1 &4)<<5)|( 57 &0x7f)), ((1 &3)|((63 &0x7e)<<1)),	//# 75, ticks 2304, elapsed 0, voice: 1 note: 57 velocity 63 event ('note', 2304, 1, 57, 63)
	28,((( 0 &4)<<5)|( 71 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 76, ticks 2432, elapsed 28, voice: 0 note: 71 velocity 0 event ('note', 2432, 1, 71, 0)
	0,((( 0 &4)<<5)|( 69 &0x7f)), ((0 &3)|((68 &0x7e)<<1)),	//# 77, ticks 2432, elapsed 0, voice: 0 note: 69 velocity 68 event ('note', 2432, 1, 69, 68)
	0,((( 1 &4)<<5)|( 57 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 78, ticks 2432, elapsed 0, voice: 1 note: 57 velocity 0 event ('note', 2432, 1, 57, 0)
	0,((( 1 &4)<<5)|( 52 &0x7f)), ((1 &3)|((57 &0x7e)<<1)),	//# 79, ticks 2432, elapsed 0, voice: 1 note: 52 velocity 57 event ('note', 2432, 1, 52, 57)
	// Note off skipped, note 60 not found in channels, probably interrupted
	28,((( 0 &4)<<5)|( 69 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 81, ticks 2560, elapsed 28, voice: 0 note: 69 velocity 0 event ('note', 2560, 1, 69, 0)
	0,((( 0 &4)<<5)|( 66 &0x7f)), ((0 &3)|((67 &0x7e)<<1)),	//# 82, ticks 2560, elapsed 0, voice: 0 note: 66 velocity 67 event ('note', 2560, 1, 66, 67)
	0,((( 1 &4)<<5)|( 62 &0x7f)), ((1 &3)|((62 &0x7e)<<1)),	//# 83, ticks 2560, elapsed 0, voice: 1 note: 62 velocity 62 event ('note', 2560, 1, 62, 62)
	// Note off skipped, note 52 not found in channels, probably interrupted
	0,((( 1 &4)<<5)|( 50 &0x7f)), ((1 &3)|((60 &0x7e)<<1)),	//# 85, ticks 2560, elapsed 0, voice: 1 note: 50 velocity 60 event ('note', 2560, 1, 50, 60)
	28,((( 1 &4)<<5)|( 50 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 86, ticks 2688, elapsed 28, voice: 1 note: 50 velocity 0 event ('note', 2688, 1, 50, 0)
	0,((( 1 &4)<<5)|( 54 &0x7f)), ((1 &3)|((62 &0x7e)<<1)),	//# 87, ticks 2688, elapsed 0, voice: 1 note: 54 velocity 62 event ('note', 2688, 1, 54, 62)
	28,((( 1 &4)<<5)|( 54 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 88, ticks 2816, elapsed 28, voice: 1 note: 54 velocity 0 event ('note', 2816, 1, 54, 0)
	0,((( 1 &4)<<5)|( 57 &0x7f)), ((1 &3)|((60 &0x7e)<<1)),	//# 89, ticks 2816, elapsed 0, voice: 1 note: 57 velocity 60 event ('note', 2816, 1, 57, 60)
	28,((( 1 &4)<<5)|( 57 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 90, ticks 2944, elapsed 28, voice: 1 note: 57 velocity 0 event ('note', 2944, 1, 57, 0)
	0,((( 1 &4)<<5)|( 54 &0x7f)), ((1 &3)|((60 &0x7e)<<1)),	//# 91, ticks 2944, elapsed 0, voice: 1 note: 54 velocity 60 event ('note', 2944, 1, 54, 60)
	28,((( 0 &4)<<5)|( 66 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 92, ticks 3072, elapsed 28, voice: 0 note: 66 velocity 0 event ('note', 3072, 1, 66, 0)
	// Note off skipped, note 62 not found in channels, probably interrupted
	0,((( 0 &4)<<5)|( 74 &0x7f)), ((0 &3)|((77 &0x7e)<<1)),	//# 94, ticks 3072, elapsed 0, voice: 0 note: 74 velocity 77 event ('note', 3072, 1, 74, 77)
	0,((( 1 &4)<<5)|( 66 &0x7f)), ((1 &3)|((64 &0x7e)<<1)),	//# 95, ticks 3072, elapsed 0, voice: 1 note: 66 velocity 64 event ('note', 3072, 1, 66, 64)
	// Note off skipped, note 54 not found in channels, probably interrupted
	0,((( 1 &4)<<5)|( 50 &0x7f)), ((1 &3)|((61 &0x7e)<<1)),	//# 97, ticks 3072, elapsed 0, voice: 1 note: 50 velocity 61 event ('note', 3072, 1, 50, 61)
	28,((( 0 &4)<<5)|( 74 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 98, ticks 3200, elapsed 28, voice: 0 note: 74 velocity 0 event ('note', 3200, 1, 74, 0)
	0,((( 0 &4)<<5)|( 74 &0x7f)), ((0 &3)|((73 &0x7e)<<1)),	//# 99, ticks 3200, elapsed 0, voice: 0 note: 74 velocity 73 event ('note', 3200, 1, 74, 73)
	0,((( 1 &4)<<5)|( 50 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 100, ticks 3200, elapsed 0, voice: 1 note: 50 velocity 0 event ('note', 3200, 1, 50, 0)
	0,((( 1 &4)<<5)|( 54 &0x7f)), ((1 &3)|((61 &0x7e)<<1)),	//# 101, ticks 3200, elapsed 0, voice: 1 note: 54 velocity 61 event ('note', 3200, 1, 54, 61)
	// Note off skipped, note 66 not found in channels, probably interrupted
	28,((( 0 &4)<<5)|( 74 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 103, ticks 3328, elapsed 28, voice: 0 note: 74 velocity 0 event ('note', 3328, 1, 74, 0)
	0,((( 0 &4)<<5)|( 72 &0x7f)), ((0 &3)|((68 &0x7e)<<1)),	//# 104, ticks 3328, elapsed 0, voice: 0 note: 72 velocity 68 event ('note', 3328, 1, 72, 68)
	0,((( 1 &4)<<5)|( 66 &0x7f)), ((1 &3)|((60 &0x7e)<<1)),	//# 105, ticks 3328, elapsed 0, voice: 1 note: 66 velocity 60 event ('note', 3328, 1, 66, 60)
	// Note off skipped, note 54 not found in channels, probably interrupted
	0,((( 1 &4)<<5)|( 57 &0x7f)), ((1 &3)|((60 &0x7e)<<1)),	//# 107, ticks 3328, elapsed 0, voice: 1 note: 57 velocity 60 event ('note', 3328, 1, 57, 60)
	28,((( 0 &4)<<5)|( 72 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 108, ticks 3456, elapsed 28, voice: 0 note: 72 velocity 0 event ('note', 3456, 1, 72, 0)
	0,((( 0 &4)<<5)|( 69 &0x7f)), ((0 &3)|((68 &0x7e)<<1)),	//# 109, ticks 3456, elapsed 0, voice: 0 note: 69 velocity 68 event ('note', 3456, 1, 69, 68)
	0,((( 1 &4)<<5)|( 57 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 110, ticks 3456, elapsed 0, voice: 1 note: 57 velocity 0 event ('note', 3456, 1, 57, 0)
	0,((( 1 &4)<<5)|( 50 &0x7f)), ((1 &3)|((60 &0x7e)<<1)),	//# 111, ticks 3456, elapsed 0, voice: 1 note: 50 velocity 60 event ('note', 3456, 1, 50, 60)
	// Note off skipped, note 66 not found in channels, probably interrupted
	28,((( 0 &4)<<5)|( 69 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 113, ticks 3584, elapsed 28, voice: 0 note: 69 velocity 0 event ('note', 3584, 1, 69, 0)
	0,((( 0 &4)<<5)|( 71 &0x7f)), ((0 &3)|((72 &0x7e)<<1)),	//# 114, ticks 3584, elapsed 0, voice: 0 note: 71 velocity 72 event ('note', 3584, 1, 71, 72)
	0,((( 1 &4)<<5)|( 67 &0x7f)), ((1 &3)|((64 &0x7e)<<1)),	//# 115, ticks 3584, elapsed 0, voice: 1 note: 67 velocity 64 event ('note', 3584, 1, 67, 64)
	// Note off skipped, note 50 not found in channels, probably interrupted
	0,((( 1 &4)<<5)|( 43 &0x7f)), ((1 &3)|((59 &0x7e)<<1)),	//# 117, ticks 3584, elapsed 0, voice: 1 note: 43 velocity 59 event ('note', 3584, 1, 43, 59)
	28,((( 1 &4)<<5)|( 43 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 118, ticks 3712, elapsed 28, voice: 1 note: 43 velocity 0 event ('note', 3712, 1, 43, 0)
	0,((( 1 &4)<<5)|( 50 &0x7f)), ((1 &3)|((65 &0x7e)<<1)),	//# 119, ticks 3712, elapsed 0, voice: 1 note: 50 velocity 65 event ('note', 3712, 1, 50, 65)
	28,((( 1 &4)<<5)|( 50 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 120, ticks 3840, elapsed 28, voice: 1 note: 50 velocity 0 event ('note', 3840, 1, 50, 0)
	0,((( 1 &4)<<5)|( 55 &0x7f)), ((1 &3)|((63 &0x7e)<<1)),	//# 121, ticks 3840, elapsed 0, voice: 1 note: 55 velocity 63 event ('note', 3840, 1, 55, 63)
	28,((( 1 &4)<<5)|( 55 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 122, ticks 3968, elapsed 28, voice: 1 note: 55 velocity 0 event ('note', 3968, 1, 55, 0)
	0,((( 1 &4)<<5)|( 50 &0x7f)), ((1 &3)|((59 &0x7e)<<1)),	//# 123, ticks 3968, elapsed 0, voice: 1 note: 50 velocity 59 event ('note', 3968, 1, 50, 59)
	28,((( 0 &4)<<5)|( 71 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 124, ticks 4096, elapsed 28, voice: 0 note: 71 velocity 0 event ('note', 4096, 1, 71, 0)
	// Note off skipped, note 67 not found in channels, probably interrupted
	0,((( 0 &4)<<5)|( 62 &0x7f)), ((0 &3)|((64 &0x7e)<<1)),	//# 126, ticks 4096, elapsed 0, voice: 0 note: 62 velocity 64 event ('note', 4096, 1, 62, 64)
	0,((( 1 &4)<<5)|( 59 &0x7f)), ((1 &3)|((59 &0x7e)<<1)),	//# 127, ticks 4096, elapsed 0, voice: 1 note: 59 velocity 59 event ('note', 4096, 1, 59, 59)
	// Note off skipped, note 50 not found in channels, probably interrupted
	0,((( 1 &4)<<5)|( 43 &0x7f)), ((1 &3)|((57 &0x7e)<<1)),	//# 129, ticks 4096, elapsed 0, voice: 1 note: 43 velocity 57 event ('note', 4096, 1, 43, 57)
	28,((( 0 &4)<<5)|( 62 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 130, ticks 4224, elapsed 28, voice: 0 note: 62 velocity 0 event ('note', 4224, 1, 62, 0)
	0,((( 0 &4)<<5)|( 71 &0x7f)), ((0 &3)|((78 &0x7e)<<1)),	//# 131, ticks 4224, elapsed 0, voice: 0 note: 71 velocity 78 event ('note', 4224, 1, 71, 78)
	0,((( 1 &4)<<5)|( 43 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 132, ticks 4224, elapsed 0, voice: 1 note: 43 velocity 0 event ('note', 4224, 1, 43, 0)
	0,((( 1 &4)<<5)|( 50 &0x7f)), ((1 &3)|((62 &0x7e)<<1)),	//# 133, ticks 4224, elapsed 0, voice: 1 note: 50 velocity 62 event ('note', 4224, 1, 50, 62)
	28,((( 0 &4)<<5)|( 71 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 134, ticks 4352, elapsed 28, voice: 0 note: 71 velocity 0 event ('note', 4352, 1, 71, 0)
	0,((( 0 &4)<<5)|( 69 &0x7f)), ((0 &3)|((68 &0x7e)<<1)),	//# 135, ticks 4352, elapsed 0, voice: 0 note: 69 velocity 68 event ('note', 4352, 1, 69, 68)
	0,((( 1 &4)<<5)|( 50 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 136, ticks 4352, elapsed 0, voice: 1 note: 50 velocity 0 event ('note', 4352, 1, 50, 0)
	0,((( 1 &4)<<5)|( 55 &0x7f)), ((1 &3)|((63 &0x7e)<<1)),	//# 137, ticks 4352, elapsed 0, voice: 1 note: 55 velocity 63 event ('note', 4352, 1, 55, 63)
	28,((( 0 &4)<<5)|( 69 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 138, ticks 4480, elapsed 28, voice: 0 note: 69 velocity 0 event ('note', 4480, 1, 69, 0)
	0,((( 0 &4)<<5)|( 67 &0x7f)), ((0 &3)|((70 &0x7e)<<1)),	//# 139, ticks 4480, elapsed 0, voice: 0 note: 67 velocity 70 event ('note', 4480, 1, 67, 70)
	0,((( 1 &4)<<5)|( 55 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 140, ticks 4480, elapsed 0, voice: 1 note: 55 velocity 0 event ('note', 4480, 1, 55, 0)
	0,((( 1 &4)<<5)|( 50 &0x7f)), ((1 &3)|((59 &0x7e)<<1)),	//# 141, ticks 4480, elapsed 0, voice: 1 note: 50 velocity 59 event ('note', 4480, 1, 50, 59)
	// Note off skipped, note 59 not found in channels, probably interrupted
	28,((( 0 &4)<<5)|( 67 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 143, ticks 4608, elapsed 28, voice: 0 note: 67 velocity 0 event ('note', 4608, 1, 67, 0)
	0,((( 0 &4)<<5)|( 62 &0x7f)), ((0 &3)|((67 &0x7e)<<1)),	//# 144, ticks 4608, elapsed 0, voice: 0 note: 62 velocity 67 event ('note', 4608, 1, 62, 67)
	0,((( 1 &4)<<5)|( 59 &0x7f)), ((1 &3)|((61 &0x7e)<<1)),	//# 145, ticks 4608, elapsed 0, voice: 1 note: 59 velocity 61 event ('note', 4608, 1, 59, 61)
	// Note off skipped, note 50 not found in channels, probably interrupted
	0,((( 1 &4)<<5)|( 43 &0x7f)), ((1 &3)|((61 &0x7e)<<1)),	//# 147, ticks 4608, elapsed 0, voice: 1 note: 43 velocity 61 event ('note', 4608, 1, 43, 61)
	28,((( 1 &4)<<5)|( 43 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 148, ticks 4736, elapsed 28, voice: 1 note: 43 velocity 0 event ('note', 4736, 1, 43, 0)
	0,((( 1 &4)<<5)|( 50 &0x7f)), ((1 &3)|((63 &0x7e)<<1)),	//# 149, ticks 4736, elapsed 0, voice: 1 note: 50 velocity 63 event ('note', 4736, 1, 50, 63)
	28,((( 1 &4)<<5)|( 50 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 150, ticks 4864, elapsed 28, voice: 1 note: 50 velocity 0 event ('note', 4864, 1, 50, 0)
	0,((( 1 &4)<<5)|( 55 &0x7f)), ((1 &3)|((60 &0x7e)<<1)),	//# 151, ticks 4864, elapsed 0, voice: 1 note: 55 velocity 60 event ('note', 4864, 1, 55, 60)
	28,((( 0 &4)<<5)|( 62 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 152, ticks 4992, elapsed 28, voice: 0 note: 62 velocity 0 event ('note', 4992, 1, 62, 0)
	0,((( 0 &4)<<5)|( 62 &0x7f)), ((0 &3)|((72 &0x7e)<<1)),	//# 153, ticks 4992, elapsed 0, voice: 0 note: 62 velocity 72 event ('note', 4992, 1, 62, 72)
	0,((( 1 &4)<<5)|( 55 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 154, ticks 4992, elapsed 0, voice: 1 note: 55 velocity 0 event ('note', 4992, 1, 55, 0)
	0,((( 1 &4)<<5)|( 50 &0x7f)), ((1 &3)|((60 &0x7e)<<1)),	//# 155, ticks 4992, elapsed 0, voice: 1 note: 50 velocity 60 event ('note', 4992, 1, 50, 60)
	14,((( 0 &4)<<5)|( 62 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 156, ticks 5056, elapsed 14, voice: 0 note: 62 velocity 0 event ('note', 5056, 1, 62, 0)
	0,((( 0 &4)<<5)|( 62 &0x7f)), ((0 &3)|((73 &0x7e)<<1)),	//# 157, ticks 5056, elapsed 0, voice: 0 note: 62 velocity 73 event ('note', 5056, 1, 62, 73)
	// Note off skipped, note 59 not found in channels, probably interrupted
	14,((( 0 &4)<<5)|( 62 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 159, ticks 5120, elapsed 14, voice: 0 note: 62 velocity 0 event ('note', 5120, 1, 62, 0)
	0,((( 0 &4)<<5)|( 62 &0x7f)), ((0 &3)|((70 &0x7e)<<1)),	//# 160, ticks 5120, elapsed 0, voice: 0 note: 62 velocity 70 event ('note', 5120, 1, 62, 70)
	0,((( 1 &4)<<5)|( 59 &0x7f)), ((1 &3)|((61 &0x7e)<<1)),	//# 161, ticks 5120, elapsed 0, voice: 1 note: 59 velocity 61 event ('note', 5120, 1, 59, 61)
	// Note off skipped, note 50 not found in channels, probably interrupted
	0,((( 1 &4)<<5)|( 43 &0x7f)), ((1 &3)|((58 &0x7e)<<1)),	//# 163, ticks 5120, elapsed 0, voice: 1 note: 43 velocity 58 event ('note', 5120, 1, 43, 58)
	28,((( 0 &4)<<5)|( 62 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 164, ticks 5248, elapsed 28, voice: 0 note: 62 velocity 0 event ('note', 5248, 1, 62, 0)
	0,((( 0 &4)<<5)|( 71 &0x7f)), ((0 &3)|((79 &0x7e)<<1)),	//# 165, ticks 5248, elapsed 0, voice: 0 note: 71 velocity 79 event ('note', 5248, 1, 71, 79)
	0,((( 1 &4)<<5)|( 43 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 166, ticks 5248, elapsed 0, voice: 1 note: 43 velocity 0 event ('note', 5248, 1, 43, 0)
	0,((( 1 &4)<<5)|( 50 &0x7f)), ((1 &3)|((63 &0x7e)<<1)),	//# 167, ticks 5248, elapsed 0, voice: 1 note: 50 velocity 63 event ('note', 5248, 1, 50, 63)
	28,((( 0 &4)<<5)|( 71 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 168, ticks 5376, elapsed 28, voice: 0 note: 71 velocity 0 event ('note', 5376, 1, 71, 0)
	0,((( 0 &4)<<5)|( 69 &0x7f)), ((0 &3)|((70 &0x7e)<<1)),	//# 169, ticks 5376, elapsed 0, voice: 0 note: 69 velocity 70 event ('note', 5376, 1, 69, 70)
	0,((( 1 &4)<<5)|( 50 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 170, ticks 5376, elapsed 0, voice: 1 note: 50 velocity 0 event ('note', 5376, 1, 50, 0)
	0,((( 1 &4)<<5)|( 55 &0x7f)), ((1 &3)|((61 &0x7e)<<1)),	//# 171, ticks 5376, elapsed 0, voice: 1 note: 55 velocity 61 event ('note', 5376, 1, 55, 61)
	28,((( 0 &4)<<5)|( 69 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 172, ticks 5504, elapsed 28, voice: 0 note: 69 velocity 0 event ('note', 5504, 1, 69, 0)
	0,((( 0 &4)<<5)|( 67 &0x7f)), ((0 &3)|((68 &0x7e)<<1)),	//# 173, ticks 5504, elapsed 0, voice: 0 note: 67 velocity 68 event ('note', 5504, 1, 67, 68)
	0,((( 1 &4)<<5)|( 55 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 174, ticks 5504, elapsed 0, voice: 1 note: 55 velocity 0 event ('note', 5504, 1, 55, 0)
	0,((( 1 &4)<<5)|( 50 &0x7f)), ((1 &3)|((59 &0x7e)<<1)),	//# 175, ticks 5504, elapsed 0, voice: 1 note: 50 velocity 59 event ('note', 5504, 1, 50, 59)
	// Note off skipped, note 59 not found in channels, probably interrupted
	28,((( 0 &4)<<5)|( 67 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 177, ticks 5632, elapsed 28, voice: 0 note: 67 velocity 0 event ('note', 5632, 1, 67, 0)
	0,((( 0 &4)<<5)|( 64 &0x7f)), ((0 &3)|((69 &0x7e)<<1)),	//# 178, ticks 5632, elapsed 0, voice: 0 note: 64 velocity 69 event ('note', 5632, 1, 64, 69)
	0,((( 1 &4)<<5)|( 60 &0x7f)), ((1 &3)|((63 &0x7e)<<1)),	//# 179, ticks 5632, elapsed 0, voice: 1 note: 60 velocity 63 event ('note', 5632, 1, 60, 63)
	// Note off skipped, note 50 not found in channels, probably interrupted
	0,((( 1 &4)<<5)|( 48 &0x7f)), ((1 &3)|((60 &0x7e)<<1)),	//# 181, ticks 5632, elapsed 0, voice: 1 note: 48 velocity 60 event ('note', 5632, 1, 48, 60)
	28,((( 1 &4)<<5)|( 48 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 182, ticks 5760, elapsed 28, voice: 1 note: 48 velocity 0 event ('note', 5760, 1, 48, 0)
	0,((( 1 &4)<<5)|( 52 &0x7f)), ((1 &3)|((63 &0x7e)<<1)),	//# 183, ticks 5760, elapsed 0, voice: 1 note: 52 velocity 63 event ('note', 5760, 1, 52, 63)
	28,((( 1 &4)<<5)|( 52 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 184, ticks 5888, elapsed 28, voice: 1 note: 52 velocity 0 event ('note', 5888, 1, 52, 0)
	0,((( 1 &4)<<5)|( 55 &0x7f)), ((1 &3)|((62 &0x7e)<<1)),	//# 185, ticks 5888, elapsed 0, voice: 1 note: 55 velocity 62 event ('note', 5888, 1, 55, 62)
	28,((( 1 &4)<<5)|( 55 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 186, ticks 6016, elapsed 28, voice: 1 note: 55 velocity 0 event ('note', 6016, 1, 55, 0)
	0,((( 1 &4)<<5)|( 52 &0x7f)), ((1 &3)|((58 &0x7e)<<1)),	//# 187, ticks 6016, elapsed 0, voice: 1 note: 52 velocity 58 event ('note', 6016, 1, 52, 58)
	28,((( 0 &4)<<5)|( 64 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 188, ticks 6144, elapsed 28, voice: 0 note: 64 velocity 0 event ('note', 6144, 1, 64, 0)
	// Note off skipped, note 60 not found in channels, probably interrupted
	0,((( 0 &4)<<5)|( 64 &0x7f)), ((0 &3)|((72 &0x7e)<<1)),	//# 190, ticks 6144, elapsed 0, voice: 0 note: 64 velocity 72 event ('note', 6144, 1, 64, 72)
	0,((( 1 &4)<<5)|( 60 &0x7f)), ((1 &3)|((62 &0x7e)<<1)),	//# 191, ticks 6144, elapsed 0, voice: 1 note: 60 velocity 62 event ('note', 6144, 1, 60, 62)
	// Note off skipped, note 52 not found in channels, probably interrupted
	0,((( 1 &4)<<5)|( 45 &0x7f)), ((1 &3)|((60 &0x7e)<<1)),	//# 193, ticks 6144, elapsed 0, voice: 1 note: 45 velocity 60 event ('note', 6144, 1, 45, 60)
	28,((( 0 &4)<<5)|( 64 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 194, ticks 6272, elapsed 28, voice: 0 note: 64 velocity 0 event ('note', 6272, 1, 64, 0)
	0,((( 0 &4)<<5)|( 72 &0x7f)), ((0 &3)|((77 &0x7e)<<1)),	//# 195, ticks 6272, elapsed 0, voice: 0 note: 72 velocity 77 event ('note', 6272, 1, 72, 77)
	0,((( 1 &4)<<5)|( 45 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 196, ticks 6272, elapsed 0, voice: 1 note: 45 velocity 0 event ('note', 6272, 1, 45, 0)
	0,((( 1 &4)<<5)|( 52 &0x7f)), ((1 &3)|((62 &0x7e)<<1)),	//# 197, ticks 6272, elapsed 0, voice: 1 note: 52 velocity 62 event ('note', 6272, 1, 52, 62)
	28,((( 0 &4)<<5)|( 72 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 198, ticks 6400, elapsed 28, voice: 0 note: 72 velocity 0 event ('note', 6400, 1, 72, 0)
	0,((( 0 &4)<<5)|( 71 &0x7f)), ((0 &3)|((71 &0x7e)<<1)),	//# 199, ticks 6400, elapsed 0, voice: 0 note: 71 velocity 71 event ('note', 6400, 1, 71, 71)
	0,((( 1 &4)<<5)|( 52 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 200, ticks 6400, elapsed 0, voice: 1 note: 52 velocity 0 event ('note', 6400, 1, 52, 0)
	0,((( 1 &4)<<5)|( 57 &0x7f)), ((1 &3)|((63 &0x7e)<<1)),	//# 201, ticks 6400, elapsed 0, voice: 1 note: 57 velocity 63 event ('note', 6400, 1, 57, 63)
	28,((( 0 &4)<<5)|( 71 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 202, ticks 6528, elapsed 28, voice: 0 note: 71 velocity 0 event ('note', 6528, 1, 71, 0)
	0,((( 0 &4)<<5)|( 69 &0x7f)), ((0 &3)|((71 &0x7e)<<1)),	//# 203, ticks 6528, elapsed 0, voice: 0 note: 69 velocity 71 event ('note', 6528, 1, 69, 71)
	0,((( 1 &4)<<5)|( 57 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 204, ticks 6528, elapsed 0, voice: 1 note: 57 velocity 0 event ('note', 6528, 1, 57, 0)
	0,((( 1 &4)<<5)|( 52 &0x7f)), ((1 &3)|((59 &0x7e)<<1)),	//# 205, ticks 6528, elapsed 0, voice: 1 note: 52 velocity 59 event ('note', 6528, 1, 52, 59)
	// Note off skipped, note 60 not found in channels, probably interrupted
	28,((( 0 &4)<<5)|( 69 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 207, ticks 6656, elapsed 28, voice: 0 note: 69 velocity 0 event ('note', 6656, 1, 69, 0)
	0,((( 0 &4)<<5)|( 74 &0x7f)), ((0 &3)|((75 &0x7e)<<1)),	//# 208, ticks 6656, elapsed 0, voice: 0 note: 74 velocity 75 event ('note', 6656, 1, 74, 75)
	0,((( 1 &4)<<5)|( 67 &0x7f)), ((1 &3)|((67 &0x7e)<<1)),	//# 209, ticks 6656, elapsed 0, voice: 1 note: 67 velocity 67 event ('note', 6656, 1, 67, 67)
	// Note off skipped, note 52 not found in channels, probably interrupted
	0,((( 1 &4)<<5)|( 47 &0x7f)), ((1 &3)|((60 &0x7e)<<1)),	//# 211, ticks 6656, elapsed 0, voice: 1 note: 47 velocity 60 event ('note', 6656, 1, 47, 60)
	28,((( 0 &4)<<5)|( 74 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 212, ticks 6784, elapsed 28, voice: 0 note: 74 velocity 0 event ('note', 6784, 1, 74, 0)
	0,((( 0 &4)<<5)|( 74 &0x7f)), ((0 &3)|((73 &0x7e)<<1)),	//# 213, ticks 6784, elapsed 0, voice: 0 note: 74 velocity 73 event ('note', 6784, 1, 74, 73)
	0,((( 1 &4)<<5)|( 47 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 214, ticks 6784, elapsed 0, voice: 1 note: 47 velocity 0 event ('note', 6784, 1, 47, 0)
	0,((( 1 &4)<<5)|( 50 &0x7f)), ((1 &3)|((62 &0x7e)<<1)),	//# 215, ticks 6784, elapsed 0, voice: 1 note: 50 velocity 62 event ('note', 6784, 1, 50, 62)
	// Note off skipped, note 67 not found in channels, probably interrupted
	28,((( 0 &4)<<5)|( 74 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 217, ticks 6912, elapsed 28, voice: 0 note: 74 velocity 0 event ('note', 6912, 1, 74, 0)
	0,((( 0 &4)<<5)|( 74 &0x7f)), ((0 &3)|((72 &0x7e)<<1)),	//# 218, ticks 6912, elapsed 0, voice: 0 note: 74 velocity 72 event ('note', 6912, 1, 74, 72)
	0,((( 1 &4)<<5)|( 67 &0x7f)), ((1 &3)|((62 &0x7e)<<1)),	//# 219, ticks 6912, elapsed 0, voice: 1 note: 67 velocity 62 event ('note', 6912, 1, 67, 62)
	// Note off skipped, note 50 not found in channels, probably interrupted
	0,((( 1 &4)<<5)|( 55 &0x7f)), ((1 &3)|((61 &0x7e)<<1)),	//# 221, ticks 6912, elapsed 0, voice: 1 note: 55 velocity 61 event ('note', 6912, 1, 55, 61)
	28,((( 0 &4)<<5)|( 74 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 222, ticks 7040, elapsed 28, voice: 0 note: 74 velocity 0 event ('note', 7040, 1, 74, 0)
	0,((( 0 &4)<<5)|( 74 &0x7f)), ((0 &3)|((70 &0x7e)<<1)),	//# 223, ticks 7040, elapsed 0, voice: 0 note: 74 velocity 70 event ('note', 7040, 1, 74, 70)
	0,((( 1 &4)<<5)|( 55 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 224, ticks 7040, elapsed 0, voice: 1 note: 55 velocity 0 event ('note', 7040, 1, 55, 0)
	0,((( 1 &4)<<5)|( 50 &0x7f)), ((1 &3)|((60 &0x7e)<<1)),	//# 225, ticks 7040, elapsed 0, voice: 1 note: 50 velocity 60 event ('note', 7040, 1, 50, 60)
	// Note off skipped, note 67 not found in channels, probably interrupted
	28,((( 0 &4)<<5)|( 74 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 227, ticks 7168, elapsed 28, voice: 0 note: 74 velocity 0 event ('note', 7168, 1, 74, 0)
	0,((( 0 &4)<<5)|( 76 &0x7f)), ((0 &3)|((73 &0x7e)<<1)),	//# 228, ticks 7168, elapsed 0, voice: 0 note: 76 velocity 73 event ('note', 7168, 1, 76, 73)
	0,((( 1 &4)<<5)|( 66 &0x7f)), ((1 &3)|((61 &0x7e)<<1)),	//# 229, ticks 7168, elapsed 0, voice: 1 note: 66 velocity 61 event ('note', 7168, 1, 66, 61)
	// Note off skipped, note 50 not found in channels, probably interrupted
	0,((( 1 &4)<<5)|( 45 &0x7f)), ((1 &3)|((57 &0x7e)<<1)),	//# 231, ticks 7168, elapsed 0, voice: 1 note: 45 velocity 57 event ('note', 7168, 1, 45, 57)
	28,((( 0 &4)<<5)|( 76 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 232, ticks 7296, elapsed 28, voice: 0 note: 76 velocity 0 event ('note', 7296, 1, 76, 0)
	0,((( 0 &4)<<5)|( 74 &0x7f)), ((0 &3)|((69 &0x7e)<<1)),	//# 233, ticks 7296, elapsed 0, voice: 0 note: 74 velocity 69 event ('note', 7296, 1, 74, 69)
	0,((( 1 &4)<<5)|( 45 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 234, ticks 7296, elapsed 0, voice: 1 note: 45 velocity 0 event ('note', 7296, 1, 45, 0)
	0,((( 1 &4)<<5)|( 50 &0x7f)), ((1 &3)|((62 &0x7e)<<1)),	//# 235, ticks 7296, elapsed 0, voice: 1 note: 50 velocity 62 event ('note', 7296, 1, 50, 62)
	// Note off skipped, note 66 not found in channels, probably interrupted
	28,((( 0 &4)<<5)|( 74 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 237, ticks 7424, elapsed 28, voice: 0 note: 74 velocity 0 event ('note', 7424, 1, 74, 0)
	0,((( 0 &4)<<5)|( 72 &0x7f)), ((0 &3)|((69 &0x7e)<<1)),	//# 238, ticks 7424, elapsed 0, voice: 0 note: 72 velocity 69 event ('note', 7424, 1, 72, 69)
	0,((( 1 &4)<<5)|( 66 &0x7f)), ((1 &3)|((63 &0x7e)<<1)),	//# 239, ticks 7424, elapsed 0, voice: 1 note: 66 velocity 63 event ('note', 7424, 1, 66, 63)
	// Note off skipped, note 50 not found in channels, probably interrupted
	0,((( 1 &4)<<5)|( 54 &0x7f)), ((1 &3)|((62 &0x7e)<<1)),	//# 241, ticks 7424, elapsed 0, voice: 1 note: 54 velocity 62 event ('note', 7424, 1, 54, 62)
	28,((( 0 &4)<<5)|( 72 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 242, ticks 7552, elapsed 28, voice: 0 note: 72 velocity 0 event ('note', 7552, 1, 72, 0)
	0,((( 0 &4)<<5)|( 69 &0x7f)), ((0 &3)|((69 &0x7e)<<1)),	//# 243, ticks 7552, elapsed 0, voice: 0 note: 69 velocity 69 event ('note', 7552, 1, 69, 69)
	0,((( 1 &4)<<5)|( 54 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 244, ticks 7552, elapsed 0, voice: 1 note: 54 velocity 0 event ('note', 7552, 1, 54, 0)
	0,((( 1 &4)<<5)|( 50 &0x7f)), ((1 &3)|((59 &0x7e)<<1)),	//# 245, ticks 7552, elapsed 0, voice: 1 note: 50 velocity 59 event ('note', 7552, 1, 50, 59)
	// Note off skipped, note 66 not found in channels, probably interrupted
	28,((( 0 &4)<<5)|( 69 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 247, ticks 7680, elapsed 28, voice: 0 note: 69 velocity 0 event ('note', 7680, 1, 69, 0)
	0,((( 0 &4)<<5)|( 67 &0x7f)), ((0 &3)|((70 &0x7e)<<1)),	//# 248, ticks 7680, elapsed 0, voice: 0 note: 67 velocity 70 event ('note', 7680, 1, 67, 70)
	0,((( 1 &4)<<5)|( 62 &0x7f)), ((1 &3)|((58 &0x7e)<<1)),	//# 249, ticks 7680, elapsed 0, voice: 1 note: 62 velocity 58 event ('note', 7680, 1, 62, 58)
	// Note off skipped, note 50 not found in channels, probably interrupted
	0,((( 1 &4)<<5)|( 43 &0x7f)), ((1 &3)|((59 &0x7e)<<1)),	//# 251, ticks 7680, elapsed 0, voice: 1 note: 43 velocity 59 event ('note', 7680, 1, 43, 59)
	28,((( 1 &4)<<5)|( 43 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 252, ticks 7808, elapsed 28, voice: 1 note: 43 velocity 0 event ('note', 7808, 1, 43, 0)
	0,((( 1 &4)<<5)|( 50 &0x7f)), ((1 &3)|((62 &0x7e)<<1)),	//# 253, ticks 7808, elapsed 0, voice: 1 note: 50 velocity 62 event ('note', 7808, 1, 50, 62)
	28,((( 0 &4)<<5)|( 67 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 254, ticks 7936, elapsed 28, voice: 0 note: 67 velocity 0 event ('note', 7936, 1, 67, 0)
	// Note off skipped, note 62 not found in channels, probably interrupted
	0,((( 0 &4)<<5)|( 74 &0x7f)), ((0 &3)|((77 &0x7e)<<1)),	//# 256, ticks 7936, elapsed 0, voice: 0 note: 74 velocity 77 event ('note', 7936, 1, 74, 77)
	0,((( 1 &4)<<5)|( 67 &0x7f)), ((1 &3)|((65 &0x7e)<<1)),	//# 257, ticks 7936, elapsed 0, voice: 1 note: 67 velocity 65 event ('note', 7936, 1, 67, 65)
	// Note off skipped, note 50 not found in channels, probably interrupted
	0,((( 1 &4)<<5)|( 55 &0x7f)), ((1 &3)|((63 &0x7e)<<1)),	//# 259, ticks 7936, elapsed 0, voice: 1 note: 55 velocity 63 event ('note', 7936, 1, 55, 63)
	57,((( 0 &4)<<5)|( 74 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 260, ticks 8192, elapsed 57, voice: 0 note: 74 velocity 0 event ('note', 8192, 1, 74, 0)
	// Note off skipped, note 67 not found in channels, probably interrupted
	0,((( 0 &4)<<5)|( 67 &0x7f)), ((0 &3)|((69 &0x7e)<<1)),	//# 262, ticks 8192, elapsed 0, voice: 0 note: 67 velocity 69 event ('note', 8192, 1, 67, 69)
	0,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((69 &0x7e)<<1)),	//# 263, ticks 8192, elapsed 0, voice: 1 note: 71 velocity 69 event ('note', 8192, 1, 71, 69)
	// Note off skipped, note 55 not found in channels, probably interrupted
	0,((( 0 &4)<<5)|( 43 &0x7f)), ((0 &3)|((55 &0x7e)<<1)),	//# 265, ticks 8192, elapsed 0, voice: 0 note: 43 velocity 55 event ('note', 8192, 1, 43, 55)
	// Note off skipped, note 67 not found in channels, probably interrupted
	28,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 267, ticks 8320, elapsed 28, voice: 1 note: 71 velocity 0 event ('note', 8320, 1, 71, 0)
	0,((( 1 &4)<<5)|( 67 &0x7f)), ((1 &3)|((74 &0x7e)<<1)),	//# 268, ticks 8320, elapsed 0, voice: 1 note: 67 velocity 74 event ('note', 8320, 1, 67, 74)
	0,((( 0 &4)<<5)|( 71 &0x7f)), ((0 &3)|((74 &0x7e)<<1)),	//# 269, ticks 8320, elapsed 0, voice: 0 note: 71 velocity 74 event ('note', 8320, 1, 71, 74)
	28,((( 1 &4)<<5)|( 67 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 270, ticks 8448, elapsed 28, voice: 1 note: 67 velocity 0 event ('note', 8448, 1, 67, 0)
	0,((( 0 &4)<<5)|( 71 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 271, ticks 8448, elapsed 0, voice: 0 note: 71 velocity 0 event ('note', 8448, 1, 71, 0)
	0,((( 0 &4)<<5)|( 67 &0x7f)), ((0 &3)|((70 &0x7e)<<1)),	//# 272, ticks 8448, elapsed 0, voice: 0 note: 67 velocity 70 event ('note', 8448, 1, 67, 70)
	0,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((70 &0x7e)<<1)),	//# 273, ticks 8448, elapsed 0, voice: 1 note: 71 velocity 70 event ('note', 8448, 1, 71, 70)
	// Note off skipped, note 43 not found in channels, probably interrupted
	28,((( 0 &4)<<5)|( 50 &0x7f)), ((0 &3)|((64 &0x7e)<<1)),	//# 275, ticks 8576, elapsed 28, voice: 0 note: 50 velocity 64 event ('note', 8576, 1, 50, 64)
	// Note off skipped, note 67 not found in channels, probably interrupted
	28,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 277, ticks 8704, elapsed 28, voice: 1 note: 71 velocity 0 event ('note', 8704, 1, 71, 0)
	0,((( 1 &4)<<5)|( 67 &0x7f)), ((1 &3)|((72 &0x7e)<<1)),	//# 278, ticks 8704, elapsed 0, voice: 1 note: 67 velocity 72 event ('note', 8704, 1, 67, 72)
	0,((( 0 &4)<<5)|( 71 &0x7f)), ((0 &3)|((72 &0x7e)<<1)),	//# 279, ticks 8704, elapsed 0, voice: 0 note: 71 velocity 72 event ('note', 8704, 1, 71, 72)
	// Note off skipped, note 50 not found in channels, probably interrupted
	0,((( 0 &4)<<5)|( 55 &0x7f)), ((0 &3)|((64 &0x7e)<<1)),	//# 281, ticks 8704, elapsed 0, voice: 0 note: 55 velocity 64 event ('note', 8704, 1, 55, 64)
	28,((( 1 &4)<<5)|( 67 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 282, ticks 8832, elapsed 28, voice: 1 note: 67 velocity 0 event ('note', 8832, 1, 67, 0)
	// Note off skipped, note 71 not found in channels, probably interrupted
	0,((( 1 &4)<<5)|( 67 &0x7f)), ((1 &3)|((70 &0x7e)<<1)),	//# 284, ticks 8832, elapsed 0, voice: 1 note: 67 velocity 70 event ('note', 8832, 1, 67, 70)
	0,((( 0 &4)<<5)|( 71 &0x7f)), ((0 &3)|((70 &0x7e)<<1)),	//# 285, ticks 8832, elapsed 0, voice: 0 note: 71 velocity 70 event ('note', 8832, 1, 71, 70)
	28,((( 1 &4)<<5)|( 67 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 286, ticks 8960, elapsed 28, voice: 1 note: 67 velocity 0 event ('note', 8960, 1, 67, 0)
	0,((( 0 &4)<<5)|( 71 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 287, ticks 8960, elapsed 0, voice: 0 note: 71 velocity 0 event ('note', 8960, 1, 71, 0)
	0,((( 0 &4)<<5)|( 67 &0x7f)), ((0 &3)|((72 &0x7e)<<1)),	//# 288, ticks 8960, elapsed 0, voice: 0 note: 67 velocity 72 event ('note', 8960, 1, 67, 72)
	0,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((72 &0x7e)<<1)),	//# 289, ticks 8960, elapsed 0, voice: 1 note: 71 velocity 72 event ('note', 8960, 1, 71, 72)
	// Note off skipped, note 55 not found in channels, probably interrupted
	28,((( 0 &4)<<5)|( 50 &0x7f)), ((0 &3)|((58 &0x7e)<<1)),	//# 291, ticks 9088, elapsed 28, voice: 0 note: 50 velocity 58 event ('note', 9088, 1, 50, 58)
	// Note off skipped, note 67 not found in channels, probably interrupted
	28,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 293, ticks 9216, elapsed 28, voice: 1 note: 71 velocity 0 event ('note', 9216, 1, 71, 0)
	0,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((70 &0x7e)<<1)),	//# 294, ticks 9216, elapsed 0, voice: 1 note: 71 velocity 70 event ('note', 9216, 1, 71, 70)
	0,((( 0 &4)<<5)|( 67 &0x7f)), ((0 &3)|((62 &0x7e)<<1)),	//# 295, ticks 9216, elapsed 0, voice: 0 note: 67 velocity 62 event ('note', 9216, 1, 67, 62)
	// Note off skipped, note 50 not found in channels, probably interrupted
	0,((( 0 &4)<<5)|( 43 &0x7f)), ((0 &3)|((57 &0x7e)<<1)),	//# 297, ticks 9216, elapsed 0, voice: 0 note: 43 velocity 57 event ('note', 9216, 1, 43, 57)
	28,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 298, ticks 9344, elapsed 28, voice: 1 note: 71 velocity 0 event ('note', 9344, 1, 71, 0)
	0,((( 1 &4)<<5)|( 74 &0x7f)), ((1 &3)|((73 &0x7e)<<1)),	//# 299, ticks 9344, elapsed 0, voice: 1 note: 74 velocity 73 event ('note', 9344, 1, 74, 73)
	0,((( 0 &4)<<5)|( 43 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 300, ticks 9344, elapsed 0, voice: 0 note: 43 velocity 0 event ('note', 9344, 1, 43, 0)
	0,((( 0 &4)<<5)|( 50 &0x7f)), ((0 &3)|((64 &0x7e)<<1)),	//# 301, ticks 9344, elapsed 0, voice: 0 note: 50 velocity 64 event ('note', 9344, 1, 50, 64)
	// Note off skipped, note 67 not found in channels, probably interrupted
	28,((( 1 &4)<<5)|( 74 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 303, ticks 9472, elapsed 28, voice: 1 note: 74 velocity 0 event ('note', 9472, 1, 74, 0)
	0,((( 1 &4)<<5)|( 67 &0x7f)), ((1 &3)|((64 &0x7e)<<1)),	//# 304, ticks 9472, elapsed 0, voice: 1 note: 67 velocity 64 event ('note', 9472, 1, 67, 64)
	0,((( 0 &4)<<5)|( 64 &0x7f)), ((0 &3)|((59 &0x7e)<<1)),	//# 305, ticks 9472, elapsed 0, voice: 0 note: 64 velocity 59 event ('note', 9472, 1, 64, 59)
	// Note off skipped, note 50 not found in channels, probably interrupted
	0,((( 0 &4)<<5)|( 48 &0x7f)), ((0 &3)|((62 &0x7e)<<1)),	//# 307, ticks 9472, elapsed 0, voice: 0 note: 48 velocity 62 event ('note', 9472, 1, 48, 62)
	0,((( 0 &4)<<5)|( 52 &0x7f)), ((0 &3)|((62 &0x7e)<<1)),	//# 308, ticks 9472, elapsed 0, voice: 0 note: 52 velocity 62 event ('note', 9472, 1, 52, 62)
	42,((( 1 &4)<<5)|( 67 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 309, ticks 9664, elapsed 42, voice: 1 note: 67 velocity 0 event ('note', 9664, 1, 67, 0)
	0,((( 1 &4)<<5)|( 69 &0x7f)), ((1 &3)|((73 &0x7e)<<1)),	//# 310, ticks 9664, elapsed 0, voice: 1 note: 69 velocity 73 event ('note', 9664, 1, 69, 73)
	// Note off skipped, note 64 not found in channels, probably interrupted
	14,((( 1 &4)<<5)|( 69 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 312, ticks 9728, elapsed 14, voice: 1 note: 69 velocity 0 event ('note', 9728, 1, 69, 0)
	0,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((75 &0x7e)<<1)),	//# 313, ticks 9728, elapsed 0, voice: 1 note: 71 velocity 75 event ('note', 9728, 1, 71, 75)
	0,((( 0 &4)<<5)|( 62 &0x7f)), ((0 &3)|((60 &0x7e)<<1)),	//# 314, ticks 9728, elapsed 0, voice: 0 note: 62 velocity 60 event ('note', 9728, 1, 62, 60)
	// Note off skipped, note 48 not found in channels, probably interrupted
	// Note off skipped, note 52 not found in channels, probably interrupted
	0,((( 0 &4)<<5)|( 43 &0x7f)), ((0 &3)|((56 &0x7e)<<1)),	//# 317, ticks 9728, elapsed 0, voice: 0 note: 43 velocity 56 event ('note', 9728, 1, 43, 56)
	28,((( 0 &4)<<5)|( 43 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 318, ticks 9856, elapsed 28, voice: 0 note: 43 velocity 0 event ('note', 9856, 1, 43, 0)
	0,((( 0 &4)<<5)|( 50 &0x7f)), ((0 &3)|((64 &0x7e)<<1)),	//# 319, ticks 9856, elapsed 0, voice: 0 note: 50 velocity 64 event ('note', 9856, 1, 50, 64)
	28,((( 0 &4)<<5)|( 50 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 320, ticks 9984, elapsed 28, voice: 0 note: 50 velocity 0 event ('note', 9984, 1, 50, 0)
	0,((( 0 &4)<<5)|( 55 &0x7f)), ((0 &3)|((62 &0x7e)<<1)),	//# 321, ticks 9984, elapsed 0, voice: 0 note: 55 velocity 62 event ('note', 9984, 1, 55, 62)
	57,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 322, ticks 10240, elapsed 57, voice: 1 note: 71 velocity 0 event ('note', 10240, 1, 71, 0)
	// Note off skipped, note 62 not found in channels, probably interrupted
	0,((( 1 &4)<<5)|( 72 &0x7f)), ((1 &3)|((73 &0x7e)<<1)),	//# 324, ticks 10240, elapsed 0, voice: 1 note: 72 velocity 73 event ('note', 10240, 1, 72, 73)
	0,((( 0 &4)<<5)|( 64 &0x7f)), ((0 &3)|((64 &0x7e)<<1)),	//# 325, ticks 10240, elapsed 0, voice: 0 note: 64 velocity 64 event ('note', 10240, 1, 64, 64)
	// Note off skipped, note 55 not found in channels, probably interrupted
	0,((( 0 &4)<<5)|( 48 &0x7f)), ((0 &3)|((60 &0x7e)<<1)),	//# 327, ticks 10240, elapsed 0, voice: 0 note: 48 velocity 60 event ('note', 10240, 1, 48, 60)
	28,((( 1 &4)<<5)|( 72 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 328, ticks 10368, elapsed 28, voice: 1 note: 72 velocity 0 event ('note', 10368, 1, 72, 0)
	// Note off skipped, note 64 not found in channels, probably interrupted
	0,((( 1 &4)<<5)|( 72 &0x7f)), ((1 &3)|((72 &0x7e)<<1)),	//# 330, ticks 10368, elapsed 0, voice: 1 note: 72 velocity 72 event ('note', 10368, 1, 72, 72)
	0,((( 0 &4)<<5)|( 64 &0x7f)), ((0 &3)|((61 &0x7e)<<1)),	//# 331, ticks 10368, elapsed 0, voice: 0 note: 64 velocity 61 event ('note', 10368, 1, 64, 61)
	// Note off skipped, note 48 not found in channels, probably interrupted
	0,((( 0 &4)<<5)|( 52 &0x7f)), ((0 &3)|((64 &0x7e)<<1)),	//# 333, ticks 10368, elapsed 0, voice: 0 note: 52 velocity 64 event ('note', 10368, 1, 52, 64)
	28,((( 1 &4)<<5)|( 72 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 334, ticks 10496, elapsed 28, voice: 1 note: 72 velocity 0 event ('note', 10496, 1, 72, 0)
	// Note off skipped, note 64 not found in channels, probably interrupted
	0,((( 1 &4)<<5)|( 72 &0x7f)), ((1 &3)|((72 &0x7e)<<1)),	//# 336, ticks 10496, elapsed 0, voice: 1 note: 72 velocity 72 event ('note', 10496, 1, 72, 72)
	0,((( 0 &4)<<5)|( 64 &0x7f)), ((0 &3)|((62 &0x7e)<<1)),	//# 337, ticks 10496, elapsed 0, voice: 0 note: 64 velocity 62 event ('note', 10496, 1, 64, 62)
	// Note off skipped, note 52 not found in channels, probably interrupted
	0,((( 0 &4)<<5)|( 55 &0x7f)), ((0 &3)|((61 &0x7e)<<1)),	//# 339, ticks 10496, elapsed 0, voice: 0 note: 55 velocity 61 event ('note', 10496, 1, 55, 61)
	28,((( 0 &4)<<5)|( 55 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 340, ticks 10624, elapsed 28, voice: 0 note: 55 velocity 0 event ('note', 10624, 1, 55, 0)
	0,((( 0 &4)<<5)|( 52 &0x7f)), ((0 &3)|((60 &0x7e)<<1)),	//# 341, ticks 10624, elapsed 0, voice: 0 note: 52 velocity 60 event ('note', 10624, 1, 52, 60)
	14,((( 1 &4)<<5)|( 72 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 342, ticks 10688, elapsed 14, voice: 1 note: 72 velocity 0 event ('note', 10688, 1, 72, 0)
	0,((( 1 &4)<<5)|( 72 &0x7f)), ((1 &3)|((71 &0x7e)<<1)),	//# 343, ticks 10688, elapsed 0, voice: 1 note: 72 velocity 71 event ('note', 10688, 1, 72, 71)
	// Note off skipped, note 64 not found in channels, probably interrupted
	14,((( 1 &4)<<5)|( 72 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 345, ticks 10752, elapsed 14, voice: 1 note: 72 velocity 0 event ('note', 10752, 1, 72, 0)
	0,((( 1 &4)<<5)|( 72 &0x7f)), ((1 &3)|((73 &0x7e)<<1)),	//# 346, ticks 10752, elapsed 0, voice: 1 note: 72 velocity 73 event ('note', 10752, 1, 72, 73)
	0,((( 0 &4)<<5)|( 62 &0x7f)), ((0 &3)|((58 &0x7e)<<1)),	//# 347, ticks 10752, elapsed 0, voice: 0 note: 62 velocity 58 event ('note', 10752, 1, 62, 58)
	// Note off skipped, note 52 not found in channels, probably interrupted
	0,((( 0 &4)<<5)|( 47 &0x7f)), ((0 &3)|((58 &0x7e)<<1)),	//# 349, ticks 10752, elapsed 0, voice: 0 note: 47 velocity 58 event ('note', 10752, 1, 47, 58)
	28,((( 1 &4)<<5)|( 72 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 350, ticks 10880, elapsed 28, voice: 1 note: 72 velocity 0 event ('note', 10880, 1, 72, 0)
	0,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((70 &0x7e)<<1)),	//# 351, ticks 10880, elapsed 0, voice: 1 note: 71 velocity 70 event ('note', 10880, 1, 71, 70)
	0,((( 0 &4)<<5)|( 47 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 352, ticks 10880, elapsed 0, voice: 0 note: 47 velocity 0 event ('note', 10880, 1, 47, 0)
	0,((( 0 &4)<<5)|( 50 &0x7f)), ((0 &3)|((61 &0x7e)<<1)),	//# 353, ticks 10880, elapsed 0, voice: 0 note: 50 velocity 61 event ('note', 10880, 1, 50, 61)
	// Note off skipped, note 62 not found in channels, probably interrupted
	28,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 355, ticks 11008, elapsed 28, voice: 1 note: 71 velocity 0 event ('note', 11008, 1, 71, 0)
	0,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((72 &0x7e)<<1)),	//# 356, ticks 11008, elapsed 0, voice: 1 note: 71 velocity 72 event ('note', 11008, 1, 71, 72)
	0,((( 0 &4)<<5)|( 62 &0x7f)), ((0 &3)|((61 &0x7e)<<1)),	//# 357, ticks 11008, elapsed 0, voice: 0 note: 62 velocity 61 event ('note', 11008, 1, 62, 61)
	// Note off skipped, note 50 not found in channels, probably interrupted
	0,((( 0 &4)<<5)|( 55 &0x7f)), ((0 &3)|((60 &0x7e)<<1)),	//# 359, ticks 11008, elapsed 0, voice: 0 note: 55 velocity 60 event ('note', 11008, 1, 55, 60)
	28,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 360, ticks 11136, elapsed 28, voice: 1 note: 71 velocity 0 event ('note', 11136, 1, 71, 0)
	0,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((70 &0x7e)<<1)),	//# 361, ticks 11136, elapsed 0, voice: 1 note: 71 velocity 70 event ('note', 11136, 1, 71, 70)
	0,((( 0 &4)<<5)|( 55 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 362, ticks 11136, elapsed 0, voice: 0 note: 55 velocity 0 event ('note', 11136, 1, 55, 0)
	0,((( 0 &4)<<5)|( 50 &0x7f)), ((0 &3)|((58 &0x7e)<<1)),	//# 363, ticks 11136, elapsed 0, voice: 0 note: 50 velocity 58 event ('note', 11136, 1, 50, 58)
	14,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 364, ticks 11200, elapsed 14, voice: 1 note: 71 velocity 0 event ('note', 11200, 1, 71, 0)
	0,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((71 &0x7e)<<1)),	//# 365, ticks 11200, elapsed 0, voice: 1 note: 71 velocity 71 event ('note', 11200, 1, 71, 71)
	// Note off skipped, note 62 not found in channels, probably interrupted
	14,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 367, ticks 11264, elapsed 14, voice: 1 note: 71 velocity 0 event ('note', 11264, 1, 71, 0)
	0,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((70 &0x7e)<<1)),	//# 368, ticks 11264, elapsed 0, voice: 1 note: 71 velocity 70 event ('note', 11264, 1, 71, 70)
	0,((( 0 &4)<<5)|( 61 &0x7f)), ((0 &3)|((59 &0x7e)<<1)),	//# 369, ticks 11264, elapsed 0, voice: 0 note: 61 velocity 59 event ('note', 11264, 1, 61, 59)
	// Note off skipped, note 50 not found in channels, probably interrupted
	0,((( 0 &4)<<5)|( 45 &0x7f)), ((0 &3)|((59 &0x7e)<<1)),	//# 371, ticks 11264, elapsed 0, voice: 0 note: 45 velocity 59 event ('note', 11264, 1, 45, 59)
	28,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 372, ticks 11392, elapsed 28, voice: 1 note: 71 velocity 0 event ('note', 11392, 1, 71, 0)
	0,((( 1 &4)<<5)|( 69 &0x7f)), ((1 &3)|((67 &0x7e)<<1)),	//# 373, ticks 11392, elapsed 0, voice: 1 note: 69 velocity 67 event ('note', 11392, 1, 69, 67)
	0,((( 0 &4)<<5)|( 45 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 374, ticks 11392, elapsed 0, voice: 0 note: 45 velocity 0 event ('note', 11392, 1, 45, 0)
	0,((( 0 &4)<<5)|( 52 &0x7f)), ((0 &3)|((61 &0x7e)<<1)),	//# 375, ticks 11392, elapsed 0, voice: 0 note: 52 velocity 61 event ('note', 11392, 1, 52, 61)
	// Note off skipped, note 61 not found in channels, probably interrupted
	28,((( 1 &4)<<5)|( 69 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 377, ticks 11520, elapsed 28, voice: 1 note: 69 velocity 0 event ('note', 11520, 1, 69, 0)
	0,((( 1 &4)<<5)|( 69 &0x7f)), ((1 &3)|((71 &0x7e)<<1)),	//# 378, ticks 11520, elapsed 0, voice: 1 note: 69 velocity 71 event ('note', 11520, 1, 69, 71)
	0,((( 0 &4)<<5)|( 61 &0x7f)), ((0 &3)|((61 &0x7e)<<1)),	//# 379, ticks 11520, elapsed 0, voice: 0 note: 61 velocity 61 event ('note', 11520, 1, 61, 61)
	// Note off skipped, note 52 not found in channels, probably interrupted
	0,((( 0 &4)<<5)|( 57 &0x7f)), ((0 &3)|((62 &0x7e)<<1)),	//# 381, ticks 11520, elapsed 0, voice: 0 note: 57 velocity 62 event ('note', 11520, 1, 57, 62)
	28,((( 1 &4)<<5)|( 69 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 382, ticks 11648, elapsed 28, voice: 1 note: 69 velocity 0 event ('note', 11648, 1, 69, 0)
	0,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((73 &0x7e)<<1)),	//# 383, ticks 11648, elapsed 0, voice: 1 note: 71 velocity 73 event ('note', 11648, 1, 71, 73)
	0,((( 0 &4)<<5)|( 57 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 384, ticks 11648, elapsed 0, voice: 0 note: 57 velocity 0 event ('note', 11648, 1, 57, 0)
	0,((( 0 &4)<<5)|( 52 &0x7f)), ((0 &3)|((60 &0x7e)<<1)),	//# 385, ticks 11648, elapsed 0, voice: 0 note: 52 velocity 60 event ('note', 11648, 1, 52, 60)
	// Note off skipped, note 61 not found in channels, probably interrupted
	28,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 387, ticks 11776, elapsed 28, voice: 1 note: 71 velocity 0 event ('note', 11776, 1, 71, 0)
	0,((( 1 &4)<<5)|( 69 &0x7f)), ((1 &3)|((71 &0x7e)<<1)),	//# 388, ticks 11776, elapsed 0, voice: 1 note: 69 velocity 71 event ('note', 11776, 1, 69, 71)
	0,((( 0 &4)<<5)|( 62 &0x7f)), ((0 &3)|((63 &0x7e)<<1)),	//# 389, ticks 11776, elapsed 0, voice: 0 note: 62 velocity 63 event ('note', 11776, 1, 62, 63)
	// Note off skipped, note 52 not found in channels, probably interrupted
	0,((( 0 &4)<<5)|( 50 &0x7f)), ((0 &3)|((61 &0x7e)<<1)),	//# 391, ticks 11776, elapsed 0, voice: 0 note: 50 velocity 61 event ('note', 11776, 1, 50, 61)
	28,((( 0 &4)<<5)|( 50 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 392, ticks 11904, elapsed 28, voice: 0 note: 50 velocity 0 event ('note', 11904, 1, 50, 0)
	0,((( 0 &4)<<5)|( 54 &0x7f)), ((0 &3)|((62 &0x7e)<<1)),	//# 393, ticks 11904, elapsed 0, voice: 0 note: 54 velocity 62 event ('note', 11904, 1, 54, 62)
	28,((( 1 &4)<<5)|( 69 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 394, ticks 12032, elapsed 28, voice: 1 note: 69 velocity 0 event ('note', 12032, 1, 69, 0)
	// Note off skipped, note 62 not found in channels, probably interrupted
	0,((( 1 &4)<<5)|( 74 &0x7f)), ((1 &3)|((74 &0x7e)<<1)),	//# 396, ticks 12032, elapsed 0, voice: 1 note: 74 velocity 74 event ('note', 12032, 1, 74, 74)
	0,((( 0 &4)<<5)|( 66 &0x7f)), ((0 &3)|((64 &0x7e)<<1)),	//# 397, ticks 12032, elapsed 0, voice: 0 note: 66 velocity 64 event ('note', 12032, 1, 66, 64)
	// Note off skipped, note 54 not found in channels, probably interrupted
	0,((( 0 &4)<<5)|( 57 &0x7f)), ((0 &3)|((64 &0x7e)<<1)),	//# 399, ticks 12032, elapsed 0, voice: 0 note: 57 velocity 64 event ('note', 12032, 1, 57, 64)
	28,((( 0 &4)<<5)|( 57 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 400, ticks 12160, elapsed 28, voice: 0 note: 57 velocity 0 event ('note', 12160, 1, 57, 0)
	0,((( 0 &4)<<5)|( 54 &0x7f)), ((0 &3)|((58 &0x7e)<<1)),	//# 401, ticks 12160, elapsed 0, voice: 0 note: 54 velocity 58 event ('note', 12160, 1, 54, 58)
	28,((( 1 &4)<<5)|( 74 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 402, ticks 12288, elapsed 28, voice: 1 note: 74 velocity 0 event ('note', 12288, 1, 74, 0)
	// Note off skipped, note 66 not found in channels, probably interrupted
	0,((( 1 &4)<<5)|( 67 &0x7f)), ((1 &3)|((68 &0x7e)<<1)),	//# 404, ticks 12288, elapsed 0, voice: 1 note: 67 velocity 68 event ('note', 12288, 1, 67, 68)
	0,((( 0 &4)<<5)|( 71 &0x7f)), ((0 &3)|((68 &0x7e)<<1)),	//# 405, ticks 12288, elapsed 0, voice: 0 note: 71 velocity 68 event ('note', 12288, 1, 71, 68)
	// Note off skipped, note 54 not found in channels, probably interrupted
	0,((( 0 &4)<<5)|( 43 &0x7f)), ((0 &3)|((57 &0x7e)<<1)),	//# 407, ticks 12288, elapsed 0, voice: 0 note: 43 velocity 57 event ('note', 12288, 1, 43, 57)
	28,((( 1 &4)<<5)|( 67 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 408, ticks 12416, elapsed 28, voice: 1 note: 67 velocity 0 event ('note', 12416, 1, 67, 0)
	// Note off skipped, note 71 not found in channels, probably interrupted
	0,((( 1 &4)<<5)|( 67 &0x7f)), ((1 &3)|((71 &0x7e)<<1)),	//# 410, ticks 12416, elapsed 0, voice: 1 note: 67 velocity 71 event ('note', 12416, 1, 67, 71)
	0,((( 0 &4)<<5)|( 71 &0x7f)), ((0 &3)|((71 &0x7e)<<1)),	//# 411, ticks 12416, elapsed 0, voice: 0 note: 71 velocity 71 event ('note', 12416, 1, 71, 71)
	28,((( 1 &4)<<5)|( 67 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 412, ticks 12544, elapsed 28, voice: 1 note: 67 velocity 0 event ('note', 12544, 1, 67, 0)
	0,((( 0 &4)<<5)|( 71 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 413, ticks 12544, elapsed 0, voice: 0 note: 71 velocity 0 event ('note', 12544, 1, 71, 0)
	0,((( 0 &4)<<5)|( 67 &0x7f)), ((0 &3)|((71 &0x7e)<<1)),	//# 414, ticks 12544, elapsed 0, voice: 0 note: 67 velocity 71 event ('note', 12544, 1, 67, 71)
	0,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((71 &0x7e)<<1)),	//# 415, ticks 12544, elapsed 0, voice: 1 note: 71 velocity 71 event ('note', 12544, 1, 71, 71)
	// Note off skipped, note 43 not found in channels, probably interrupted
	28,((( 0 &4)<<5)|( 50 &0x7f)), ((0 &3)|((63 &0x7e)<<1)),	//# 417, ticks 12672, elapsed 28, voice: 0 note: 50 velocity 63 event ('note', 12672, 1, 50, 63)
	// Note off skipped, note 67 not found in channels, probably interrupted
	28,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 419, ticks 12800, elapsed 28, voice: 1 note: 71 velocity 0 event ('note', 12800, 1, 71, 0)
	0,((( 1 &4)<<5)|( 67 &0x7f)), ((1 &3)|((71 &0x7e)<<1)),	//# 420, ticks 12800, elapsed 0, voice: 1 note: 67 velocity 71 event ('note', 12800, 1, 67, 71)
	0,((( 0 &4)<<5)|( 71 &0x7f)), ((0 &3)|((71 &0x7e)<<1)),	//# 421, ticks 12800, elapsed 0, voice: 0 note: 71 velocity 71 event ('note', 12800, 1, 71, 71)
	// Note off skipped, note 50 not found in channels, probably interrupted
	0,((( 0 &4)<<5)|( 55 &0x7f)), ((0 &3)|((62 &0x7e)<<1)),	//# 423, ticks 12800, elapsed 0, voice: 0 note: 55 velocity 62 event ('note', 12800, 1, 55, 62)
	28,((( 1 &4)<<5)|( 67 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 424, ticks 12928, elapsed 28, voice: 1 note: 67 velocity 0 event ('note', 12928, 1, 67, 0)
	// Note off skipped, note 71 not found in channels, probably interrupted
	0,((( 1 &4)<<5)|( 67 &0x7f)), ((1 &3)|((71 &0x7e)<<1)),	//# 426, ticks 12928, elapsed 0, voice: 1 note: 67 velocity 71 event ('note', 12928, 1, 67, 71)
	0,((( 0 &4)<<5)|( 71 &0x7f)), ((0 &3)|((71 &0x7e)<<1)),	//# 427, ticks 12928, elapsed 0, voice: 0 note: 71 velocity 71 event ('note', 12928, 1, 71, 71)
	28,((( 1 &4)<<5)|( 67 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 428, ticks 13056, elapsed 28, voice: 1 note: 67 velocity 0 event ('note', 13056, 1, 67, 0)
	0,((( 0 &4)<<5)|( 71 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 429, ticks 13056, elapsed 0, voice: 0 note: 71 velocity 0 event ('note', 13056, 1, 71, 0)
	0,((( 0 &4)<<5)|( 67 &0x7f)), ((0 &3)|((71 &0x7e)<<1)),	//# 430, ticks 13056, elapsed 0, voice: 0 note: 67 velocity 71 event ('note', 13056, 1, 67, 71)
	0,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((71 &0x7e)<<1)),	//# 431, ticks 13056, elapsed 0, voice: 1 note: 71 velocity 71 event ('note', 13056, 1, 71, 71)
	// Note off skipped, note 55 not found in channels, probably interrupted
	28,((( 0 &4)<<5)|( 50 &0x7f)), ((0 &3)|((58 &0x7e)<<1)),	//# 433, ticks 13184, elapsed 28, voice: 0 note: 50 velocity 58 event ('note', 13184, 1, 50, 58)
	// Note off skipped, note 67 not found in channels, probably interrupted
	28,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 435, ticks 13312, elapsed 28, voice: 1 note: 71 velocity 0 event ('note', 13312, 1, 71, 0)
	0,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((71 &0x7e)<<1)),	//# 436, ticks 13312, elapsed 0, voice: 1 note: 71 velocity 71 event ('note', 13312, 1, 71, 71)
	0,((( 0 &4)<<5)|( 67 &0x7f)), ((0 &3)|((61 &0x7e)<<1)),	//# 437, ticks 13312, elapsed 0, voice: 0 note: 67 velocity 61 event ('note', 13312, 1, 67, 61)
	// Note off skipped, note 50 not found in channels, probably interrupted
	0,((( 0 &4)<<5)|( 43 &0x7f)), ((0 &3)|((60 &0x7e)<<1)),	//# 439, ticks 13312, elapsed 0, voice: 0 note: 43 velocity 60 event ('note', 13312, 1, 43, 60)
	28,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 440, ticks 13440, elapsed 28, voice: 1 note: 71 velocity 0 event ('note', 13440, 1, 71, 0)
	0,((( 1 &4)<<5)|( 74 &0x7f)), ((1 &3)|((73 &0x7e)<<1)),	//# 441, ticks 13440, elapsed 0, voice: 1 note: 74 velocity 73 event ('note', 13440, 1, 74, 73)
	0,((( 0 &4)<<5)|( 43 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 442, ticks 13440, elapsed 0, voice: 0 note: 43 velocity 0 event ('note', 13440, 1, 43, 0)
	0,((( 0 &4)<<5)|( 50 &0x7f)), ((0 &3)|((62 &0x7e)<<1)),	//# 443, ticks 13440, elapsed 0, voice: 0 note: 50 velocity 62 event ('note', 13440, 1, 50, 62)
	// Note off skipped, note 67 not found in channels, probably interrupted
	28,((( 1 &4)<<5)|( 74 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 445, ticks 13568, elapsed 28, voice: 1 note: 74 velocity 0 event ('note', 13568, 1, 74, 0)
	0,((( 1 &4)<<5)|( 67 &0x7f)), ((1 &3)|((62 &0x7e)<<1)),	//# 446, ticks 13568, elapsed 0, voice: 1 note: 67 velocity 62 event ('note', 13568, 1, 67, 62)
	0,((( 0 &4)<<5)|( 64 &0x7f)), ((0 &3)|((58 &0x7e)<<1)),	//# 447, ticks 13568, elapsed 0, voice: 0 note: 64 velocity 58 event ('note', 13568, 1, 64, 58)
	// Note off skipped, note 50 not found in channels, probably interrupted
	0,((( 0 &4)<<5)|( 48 &0x7f)), ((0 &3)|((61 &0x7e)<<1)),	//# 449, ticks 13568, elapsed 0, voice: 0 note: 48 velocity 61 event ('note', 13568, 1, 48, 61)
	0,((( 0 &4)<<5)|( 52 &0x7f)), ((0 &3)|((61 &0x7e)<<1)),	//# 450, ticks 13568, elapsed 0, voice: 0 note: 52 velocity 61 event ('note', 13568, 1, 52, 61)
	42,((( 1 &4)<<5)|( 67 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 451, ticks 13760, elapsed 42, voice: 1 note: 67 velocity 0 event ('note', 13760, 1, 67, 0)
	0,((( 1 &4)<<5)|( 69 &0x7f)), ((1 &3)|((74 &0x7e)<<1)),	//# 452, ticks 13760, elapsed 0, voice: 1 note: 69 velocity 74 event ('note', 13760, 1, 69, 74)
	// Note off skipped, note 64 not found in channels, probably interrupted
	14,((( 1 &4)<<5)|( 69 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 454, ticks 13824, elapsed 14, voice: 1 note: 69 velocity 0 event ('note', 13824, 1, 69, 0)
	0,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((73 &0x7e)<<1)),	//# 455, ticks 13824, elapsed 0, voice: 1 note: 71 velocity 73 event ('note', 13824, 1, 71, 73)
	0,((( 0 &4)<<5)|( 62 &0x7f)), ((0 &3)|((58 &0x7e)<<1)),	//# 456, ticks 13824, elapsed 0, voice: 0 note: 62 velocity 58 event ('note', 13824, 1, 62, 58)
	// Note off skipped, note 48 not found in channels, probably interrupted
	// Note off skipped, note 52 not found in channels, probably interrupted
	0,((( 0 &4)<<5)|( 43 &0x7f)), ((0 &3)|((56 &0x7e)<<1)),	//# 459, ticks 13824, elapsed 0, voice: 0 note: 43 velocity 56 event ('note', 13824, 1, 43, 56)
	28,((( 0 &4)<<5)|( 43 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 460, ticks 13952, elapsed 28, voice: 0 note: 43 velocity 0 event ('note', 13952, 1, 43, 0)
	0,((( 0 &4)<<5)|( 50 &0x7f)), ((0 &3)|((66 &0x7e)<<1)),	//# 461, ticks 13952, elapsed 0, voice: 0 note: 50 velocity 66 event ('note', 13952, 1, 50, 66)
	28,((( 0 &4)<<5)|( 50 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 462, ticks 14080, elapsed 28, voice: 0 note: 50 velocity 0 event ('note', 14080, 1, 50, 0)
	0,((( 0 &4)<<5)|( 55 &0x7f)), ((0 &3)|((65 &0x7e)<<1)),	//# 463, ticks 14080, elapsed 0, voice: 0 note: 55 velocity 65 event ('note', 14080, 1, 55, 65)
	57,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 464, ticks 14336, elapsed 57, voice: 1 note: 71 velocity 0 event ('note', 14336, 1, 71, 0)
	// Note off skipped, note 62 not found in channels, probably interrupted
	0,((( 1 &4)<<5)|( 72 &0x7f)), ((1 &3)|((73 &0x7e)<<1)),	//# 466, ticks 14336, elapsed 0, voice: 1 note: 72 velocity 73 event ('note', 14336, 1, 72, 73)
	0,((( 0 &4)<<5)|( 64 &0x7f)), ((0 &3)|((64 &0x7e)<<1)),	//# 467, ticks 14336, elapsed 0, voice: 0 note: 64 velocity 64 event ('note', 14336, 1, 64, 64)
	// Note off skipped, note 55 not found in channels, probably interrupted
	0,((( 0 &4)<<5)|( 48 &0x7f)), ((0 &3)|((57 &0x7e)<<1)),	//# 469, ticks 14336, elapsed 0, voice: 0 note: 48 velocity 57 event ('note', 14336, 1, 48, 57)
	28,((( 1 &4)<<5)|( 72 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 470, ticks 14464, elapsed 28, voice: 1 note: 72 velocity 0 event ('note', 14464, 1, 72, 0)
	// Note off skipped, note 64 not found in channels, probably interrupted
	0,((( 1 &4)<<5)|( 72 &0x7f)), ((1 &3)|((69 &0x7e)<<1)),	//# 472, ticks 14464, elapsed 0, voice: 1 note: 72 velocity 69 event ('note', 14464, 1, 72, 69)
	0,((( 0 &4)<<5)|( 64 &0x7f)), ((0 &3)|((62 &0x7e)<<1)),	//# 473, ticks 14464, elapsed 0, voice: 0 note: 64 velocity 62 event ('note', 14464, 1, 64, 62)
	// Note off skipped, note 48 not found in channels, probably interrupted
	0,((( 0 &4)<<5)|( 52 &0x7f)), ((0 &3)|((64 &0x7e)<<1)),	//# 475, ticks 14464, elapsed 0, voice: 0 note: 52 velocity 64 event ('note', 14464, 1, 52, 64)
	28,((( 1 &4)<<5)|( 72 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 476, ticks 14592, elapsed 28, voice: 1 note: 72 velocity 0 event ('note', 14592, 1, 72, 0)
	// Note off skipped, note 64 not found in channels, probably interrupted
	0,((( 1 &4)<<5)|( 72 &0x7f)), ((1 &3)|((73 &0x7e)<<1)),	//# 478, ticks 14592, elapsed 0, voice: 1 note: 72 velocity 73 event ('note', 14592, 1, 72, 73)
	0,((( 0 &4)<<5)|( 64 &0x7f)), ((0 &3)|((62 &0x7e)<<1)),	//# 479, ticks 14592, elapsed 0, voice: 0 note: 64 velocity 62 event ('note', 14592, 1, 64, 62)
	// Note off skipped, note 52 not found in channels, probably interrupted
	0,((( 0 &4)<<5)|( 55 &0x7f)), ((0 &3)|((62 &0x7e)<<1)),	//# 481, ticks 14592, elapsed 0, voice: 0 note: 55 velocity 62 event ('note', 14592, 1, 55, 62)
	28,((( 0 &4)<<5)|( 55 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 482, ticks 14720, elapsed 28, voice: 0 note: 55 velocity 0 event ('note', 14720, 1, 55, 0)
	0,((( 0 &4)<<5)|( 52 &0x7f)), ((0 &3)|((60 &0x7e)<<1)),	//# 483, ticks 14720, elapsed 0, voice: 0 note: 52 velocity 60 event ('note', 14720, 1, 52, 60)
	14,((( 1 &4)<<5)|( 72 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 484, ticks 14784, elapsed 14, voice: 1 note: 72 velocity 0 event ('note', 14784, 1, 72, 0)
	0,((( 1 &4)<<5)|( 72 &0x7f)), ((1 &3)|((72 &0x7e)<<1)),	//# 485, ticks 14784, elapsed 0, voice: 1 note: 72 velocity 72 event ('note', 14784, 1, 72, 72)
	// Note off skipped, note 64 not found in channels, probably interrupted
	14,((( 1 &4)<<5)|( 72 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 487, ticks 14848, elapsed 14, voice: 1 note: 72 velocity 0 event ('note', 14848, 1, 72, 0)
	0,((( 1 &4)<<5)|( 72 &0x7f)), ((1 &3)|((72 &0x7e)<<1)),	//# 488, ticks 14848, elapsed 0, voice: 1 note: 72 velocity 72 event ('note', 14848, 1, 72, 72)
	0,((( 0 &4)<<5)|( 62 &0x7f)), ((0 &3)|((59 &0x7e)<<1)),	//# 489, ticks 14848, elapsed 0, voice: 0 note: 62 velocity 59 event ('note', 14848, 1, 62, 59)
	// Note off skipped, note 52 not found in channels, probably interrupted
	0,((( 0 &4)<<5)|( 47 &0x7f)), ((0 &3)|((60 &0x7e)<<1)),	//# 491, ticks 14848, elapsed 0, voice: 0 note: 47 velocity 60 event ('note', 14848, 1, 47, 60)
	28,((( 1 &4)<<5)|( 72 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 492, ticks 14976, elapsed 28, voice: 1 note: 72 velocity 0 event ('note', 14976, 1, 72, 0)
	0,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((69 &0x7e)<<1)),	//# 493, ticks 14976, elapsed 0, voice: 1 note: 71 velocity 69 event ('note', 14976, 1, 71, 69)
	0,((( 0 &4)<<5)|( 47 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 494, ticks 14976, elapsed 0, voice: 0 note: 47 velocity 0 event ('note', 14976, 1, 47, 0)
	0,((( 0 &4)<<5)|( 50 &0x7f)), ((0 &3)|((62 &0x7e)<<1)),	//# 495, ticks 14976, elapsed 0, voice: 0 note: 50 velocity 62 event ('note', 14976, 1, 50, 62)
	// Note off skipped, note 62 not found in channels, probably interrupted
	28,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 497, ticks 15104, elapsed 28, voice: 1 note: 71 velocity 0 event ('note', 15104, 1, 71, 0)
	0,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((71 &0x7e)<<1)),	//# 498, ticks 15104, elapsed 0, voice: 1 note: 71 velocity 71 event ('note', 15104, 1, 71, 71)
	0,((( 0 &4)<<5)|( 62 &0x7f)), ((0 &3)|((61 &0x7e)<<1)),	//# 499, ticks 15104, elapsed 0, voice: 0 note: 62 velocity 61 event ('note', 15104, 1, 62, 61)
	// Note off skipped, note 50 not found in channels, probably interrupted
	0,((( 0 &4)<<5)|( 55 &0x7f)), ((0 &3)|((64 &0x7e)<<1)),	//# 501, ticks 15104, elapsed 0, voice: 0 note: 55 velocity 64 event ('note', 15104, 1, 55, 64)
	28,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 502, ticks 15232, elapsed 28, voice: 1 note: 71 velocity 0 event ('note', 15232, 1, 71, 0)
	0,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((73 &0x7e)<<1)),	//# 503, ticks 15232, elapsed 0, voice: 1 note: 71 velocity 73 event ('note', 15232, 1, 71, 73)
	0,((( 0 &4)<<5)|( 55 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 504, ticks 15232, elapsed 0, voice: 0 note: 55 velocity 0 event ('note', 15232, 1, 55, 0)
	0,((( 0 &4)<<5)|( 50 &0x7f)), ((0 &3)|((58 &0x7e)<<1)),	//# 505, ticks 15232, elapsed 0, voice: 0 note: 50 velocity 58 event ('note', 15232, 1, 50, 58)
	14,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 506, ticks 15296, elapsed 14, voice: 1 note: 71 velocity 0 event ('note', 15296, 1, 71, 0)
	0,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((72 &0x7e)<<1)),	//# 507, ticks 15296, elapsed 0, voice: 1 note: 71 velocity 72 event ('note', 15296, 1, 71, 72)
	// Note off skipped, note 62 not found in channels, probably interrupted
	14,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 509, ticks 15360, elapsed 14, voice: 1 note: 71 velocity 0 event ('note', 15360, 1, 71, 0)
	0,((( 1 &4)<<5)|( 74 &0x7f)), ((1 &3)|((74 &0x7e)<<1)),	//# 510, ticks 15360, elapsed 0, voice: 1 note: 74 velocity 74 event ('note', 15360, 1, 74, 74)
	0,((( 0 &4)<<5)|( 66 &0x7f)), ((0 &3)|((66 &0x7e)<<1)),	//# 511, ticks 15360, elapsed 0, voice: 0 note: 66 velocity 66 event ('note', 15360, 1, 66, 66)
	// Note off skipped, note 50 not found in channels, probably interrupted
	0,((( 0 &4)<<5)|( 45 &0x7f)), ((0 &3)|((58 &0x7e)<<1)),	//# 513, ticks 15360, elapsed 0, voice: 0 note: 45 velocity 58 event ('note', 15360, 1, 45, 58)
	28,((( 1 &4)<<5)|( 74 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 514, ticks 15488, elapsed 28, voice: 1 note: 74 velocity 0 event ('note', 15488, 1, 74, 0)
	0,((( 1 &4)<<5)|( 74 &0x7f)), ((1 &3)|((72 &0x7e)<<1)),	//# 515, ticks 15488, elapsed 0, voice: 1 note: 74 velocity 72 event ('note', 15488, 1, 74, 72)
	0,((( 0 &4)<<5)|( 45 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 516, ticks 15488, elapsed 0, voice: 0 note: 45 velocity 0 event ('note', 15488, 1, 45, 0)
	0,((( 0 &4)<<5)|( 50 &0x7f)), ((0 &3)|((61 &0x7e)<<1)),	//# 517, ticks 15488, elapsed 0, voice: 0 note: 50 velocity 61 event ('note', 15488, 1, 50, 61)
	// Note off skipped, note 66 not found in channels, probably interrupted
	28,((( 1 &4)<<5)|( 74 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 519, ticks 15616, elapsed 28, voice: 1 note: 74 velocity 0 event ('note', 15616, 1, 74, 0)
	0,((( 1 &4)<<5)|( 72 &0x7f)), ((1 &3)|((67 &0x7e)<<1)),	//# 520, ticks 15616, elapsed 0, voice: 1 note: 72 velocity 67 event ('note', 15616, 1, 72, 67)
	0,((( 0 &4)<<5)|( 62 &0x7f)), ((0 &3)|((56 &0x7e)<<1)),	//# 521, ticks 15616, elapsed 0, voice: 0 note: 62 velocity 56 event ('note', 15616, 1, 62, 56)
	// Note off skipped, note 50 not found in channels, probably interrupted
	0,((( 0 &4)<<5)|( 54 &0x7f)), ((0 &3)|((61 &0x7e)<<1)),	//# 523, ticks 15616, elapsed 0, voice: 0 note: 54 velocity 61 event ('note', 15616, 1, 54, 61)
	28,((( 1 &4)<<5)|( 72 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 524, ticks 15744, elapsed 28, voice: 1 note: 72 velocity 0 event ('note', 15744, 1, 72, 0)
	0,((( 1 &4)<<5)|( 69 &0x7f)), ((1 &3)|((69 &0x7e)<<1)),	//# 525, ticks 15744, elapsed 0, voice: 1 note: 69 velocity 69 event ('note', 15744, 1, 69, 69)
	0,((( 0 &4)<<5)|( 54 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 526, ticks 15744, elapsed 0, voice: 0 note: 54 velocity 0 event ('note', 15744, 1, 54, 0)
	0,((( 0 &4)<<5)|( 50 &0x7f)), ((0 &3)|((62 &0x7e)<<1)),	//# 527, ticks 15744, elapsed 0, voice: 0 note: 50 velocity 62 event ('note', 15744, 1, 50, 62)
	// Note off skipped, note 62 not found in channels, probably interrupted
	28,((( 1 &4)<<5)|( 69 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 529, ticks 15872, elapsed 28, voice: 1 note: 69 velocity 0 event ('note', 15872, 1, 69, 0)
	0,((( 1 &4)<<5)|( 67 &0x7f)), ((1 &3)|((69 &0x7e)<<1)),	//# 530, ticks 15872, elapsed 0, voice: 1 note: 67 velocity 69 event ('note', 15872, 1, 67, 69)
	0,((( 0 &4)<<5)|( 59 &0x7f)), ((0 &3)|((60 &0x7e)<<1)),	//# 531, ticks 15872, elapsed 0, voice: 0 note: 59 velocity 60 event ('note', 15872, 1, 59, 60)
	// Note off skipped, note 50 not found in channels, probably interrupted
	0,((( 0 &4)<<5)|( 43 &0x7f)), ((0 &3)|((58 &0x7e)<<1)),	//# 533, ticks 15872, elapsed 0, voice: 0 note: 43 velocity 58 event ('note', 15872, 1, 43, 58)
	28,((( 0 &4)<<5)|( 43 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 534, ticks 16000, elapsed 28, voice: 0 note: 43 velocity 0 event ('note', 16000, 1, 43, 0)
	0,((( 0 &4)<<5)|( 50 &0x7f)), ((0 &3)|((61 &0x7e)<<1)),	//# 535, ticks 16000, elapsed 0, voice: 0 note: 50 velocity 61 event ('note', 16000, 1, 50, 61)
	28,((( 0 &4)<<5)|( 50 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 536, ticks 16128, elapsed 28, voice: 0 note: 50 velocity 0 event ('note', 16128, 1, 50, 0)
	0,((( 0 &4)<<5)|( 55 &0x7f)), ((0 &3)|((63 &0x7e)<<1)),	//# 537, ticks 16128, elapsed 0, voice: 0 note: 55 velocity 63 event ('note', 16128, 1, 55, 63)
	57,((( 1 &4)<<5)|( 67 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 540, ticks 16384, elapsed 57, voice: 1 note: 67 velocity 0 event ('note', 16384, 1, 67, 0)
	// Note off skipped, note 59 not found in channels, probably interrupted
	0,((( 1 &4)<<5)|( 62 &0x7f)), ((1 &3)|((65 &0x7e)<<1)),	//# 542, ticks 16384, elapsed 0, voice: 1 note: 62 velocity 65 event ('note', 16384, 1, 62, 65)
	0,((( 0 &4)<<5)|( 59 &0x7f)), ((0 &3)|((59 &0x7e)<<1)),	//# 543, ticks 16384, elapsed 0, voice: 0 note: 59 velocity 59 event ('note', 16384, 1, 59, 59)
	// Note off skipped, note 55 not found in channels, probably interrupted
	0,((( 0 &4)<<5)|( 43 &0x7f)), ((0 &3)|((55 &0x7e)<<1)),	//# 545, ticks 16384, elapsed 0, voice: 0 note: 43 velocity 55 event ('note', 16384, 1, 43, 55)
	28,((( 1 &4)<<5)|( 62 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 546, ticks 16512, elapsed 28, voice: 1 note: 62 velocity 0 event ('note', 16512, 1, 62, 0)
	0,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((78 &0x7e)<<1)),	//# 547, ticks 16512, elapsed 0, voice: 1 note: 71 velocity 78 event ('note', 16512, 1, 71, 78)
	0,((( 0 &4)<<5)|( 43 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 548, ticks 16512, elapsed 0, voice: 0 note: 43 velocity 0 event ('note', 16512, 1, 43, 0)
	0,((( 0 &4)<<5)|( 50 &0x7f)), ((0 &3)|((63 &0x7e)<<1)),	//# 549, ticks 16512, elapsed 0, voice: 0 note: 50 velocity 63 event ('note', 16512, 1, 50, 63)
	28,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 550, ticks 16640, elapsed 28, voice: 1 note: 71 velocity 0 event ('note', 16640, 1, 71, 0)
	0,((( 1 &4)<<5)|( 69 &0x7f)), ((1 &3)|((70 &0x7e)<<1)),	//# 551, ticks 16640, elapsed 0, voice: 1 note: 69 velocity 70 event ('note', 16640, 1, 69, 70)
	0,((( 0 &4)<<5)|( 50 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 552, ticks 16640, elapsed 0, voice: 0 note: 50 velocity 0 event ('note', 16640, 1, 50, 0)
	0,((( 0 &4)<<5)|( 55 &0x7f)), ((0 &3)|((64 &0x7e)<<1)),	//# 553, ticks 16640, elapsed 0, voice: 0 note: 55 velocity 64 event ('note', 16640, 1, 55, 64)
	28,((( 1 &4)<<5)|( 69 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 554, ticks 16768, elapsed 28, voice: 1 note: 69 velocity 0 event ('note', 16768, 1, 69, 0)
	0,((( 1 &4)<<5)|( 67 &0x7f)), ((1 &3)|((70 &0x7e)<<1)),	//# 555, ticks 16768, elapsed 0, voice: 1 note: 67 velocity 70 event ('note', 16768, 1, 67, 70)
	0,((( 0 &4)<<5)|( 55 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 556, ticks 16768, elapsed 0, voice: 0 note: 55 velocity 0 event ('note', 16768, 1, 55, 0)
	0,((( 0 &4)<<5)|( 50 &0x7f)), ((0 &3)|((57 &0x7e)<<1)),	//# 557, ticks 16768, elapsed 0, voice: 0 note: 50 velocity 57 event ('note', 16768, 1, 50, 57)
	// Note off skipped, note 59 not found in channels, probably interrupted
	28,((( 1 &4)<<5)|( 67 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 559, ticks 16896, elapsed 28, voice: 1 note: 67 velocity 0 event ('note', 16896, 1, 67, 0)
	0,((( 1 &4)<<5)|( 62 &0x7f)), ((1 &3)|((65 &0x7e)<<1)),	//# 560, ticks 16896, elapsed 0, voice: 1 note: 62 velocity 65 event ('note', 16896, 1, 62, 65)
	0,((( 0 &4)<<5)|( 59 &0x7f)), ((0 &3)|((61 &0x7e)<<1)),	//# 561, ticks 16896, elapsed 0, voice: 0 note: 59 velocity 61 event ('note', 16896, 1, 59, 61)
	// Note off skipped, note 50 not found in channels, probably interrupted
	0,((( 0 &4)<<5)|( 43 &0x7f)), ((0 &3)|((59 &0x7e)<<1)),	//# 563, ticks 16896, elapsed 0, voice: 0 note: 43 velocity 59 event ('note', 16896, 1, 43, 59)
	28,((( 0 &4)<<5)|( 43 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 564, ticks 17024, elapsed 28, voice: 0 note: 43 velocity 0 event ('note', 17024, 1, 43, 0)
	0,((( 0 &4)<<5)|( 50 &0x7f)), ((0 &3)|((63 &0x7e)<<1)),	//# 565, ticks 17024, elapsed 0, voice: 0 note: 50 velocity 63 event ('note', 17024, 1, 50, 63)
	28,((( 0 &4)<<5)|( 50 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 566, ticks 17152, elapsed 28, voice: 0 note: 50 velocity 0 event ('note', 17152, 1, 50, 0)
	0,((( 0 &4)<<5)|( 55 &0x7f)), ((0 &3)|((65 &0x7e)<<1)),	//# 567, ticks 17152, elapsed 0, voice: 0 note: 55 velocity 65 event ('note', 17152, 1, 55, 65)
	28,((( 1 &4)<<5)|( 62 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 568, ticks 17280, elapsed 28, voice: 1 note: 62 velocity 0 event ('note', 17280, 1, 62, 0)
	0,((( 1 &4)<<5)|( 62 &0x7f)), ((1 &3)|((70 &0x7e)<<1)),	//# 569, ticks 17280, elapsed 0, voice: 1 note: 62 velocity 70 event ('note', 17280, 1, 62, 70)
	0,((( 0 &4)<<5)|( 55 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 570, ticks 17280, elapsed 0, voice: 0 note: 55 velocity 0 event ('note', 17280, 1, 55, 0)
	0,((( 0 &4)<<5)|( 50 &0x7f)), ((0 &3)|((59 &0x7e)<<1)),	//# 571, ticks 17280, elapsed 0, voice: 0 note: 50 velocity 59 event ('note', 17280, 1, 50, 59)
	14,((( 1 &4)<<5)|( 62 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 572, ticks 17344, elapsed 14, voice: 1 note: 62 velocity 0 event ('note', 17344, 1, 62, 0)
	0,((( 1 &4)<<5)|( 62 &0x7f)), ((1 &3)|((70 &0x7e)<<1)),	//# 573, ticks 17344, elapsed 0, voice: 1 note: 62 velocity 70 event ('note', 17344, 1, 62, 70)
	// Note off skipped, note 59 not found in channels, probably interrupted
	14,((( 1 &4)<<5)|( 62 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 575, ticks 17408, elapsed 14, voice: 1 note: 62 velocity 0 event ('note', 17408, 1, 62, 0)
	0,((( 1 &4)<<5)|( 62 &0x7f)), ((1 &3)|((71 &0x7e)<<1)),	//# 576, ticks 17408, elapsed 0, voice: 1 note: 62 velocity 71 event ('note', 17408, 1, 62, 71)
	0,((( 0 &4)<<5)|( 59 &0x7f)), ((0 &3)|((62 &0x7e)<<1)),	//# 577, ticks 17408, elapsed 0, voice: 0 note: 59 velocity 62 event ('note', 17408, 1, 59, 62)
	// Note off skipped, note 50 not found in channels, probably interrupted
	0,((( 0 &4)<<5)|( 43 &0x7f)), ((0 &3)|((59 &0x7e)<<1)),	//# 579, ticks 17408, elapsed 0, voice: 0 note: 43 velocity 59 event ('note', 17408, 1, 43, 59)
	28,((( 1 &4)<<5)|( 62 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 580, ticks 17536, elapsed 28, voice: 1 note: 62 velocity 0 event ('note', 17536, 1, 62, 0)
	0,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((80 &0x7e)<<1)),	//# 581, ticks 17536, elapsed 0, voice: 1 note: 71 velocity 80 event ('note', 17536, 1, 71, 80)
	0,((( 0 &4)<<5)|( 43 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 582, ticks 17536, elapsed 0, voice: 0 note: 43 velocity 0 event ('note', 17536, 1, 43, 0)
	0,((( 0 &4)<<5)|( 50 &0x7f)), ((0 &3)|((62 &0x7e)<<1)),	//# 583, ticks 17536, elapsed 0, voice: 0 note: 50 velocity 62 event ('note', 17536, 1, 50, 62)
	28,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 584, ticks 17664, elapsed 28, voice: 1 note: 71 velocity 0 event ('note', 17664, 1, 71, 0)
	0,((( 1 &4)<<5)|( 69 &0x7f)), ((1 &3)|((70 &0x7e)<<1)),	//# 585, ticks 17664, elapsed 0, voice: 1 note: 69 velocity 70 event ('note', 17664, 1, 69, 70)
	0,((( 0 &4)<<5)|( 50 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 586, ticks 17664, elapsed 0, voice: 0 note: 50 velocity 0 event ('note', 17664, 1, 50, 0)
	0,((( 0 &4)<<5)|( 55 &0x7f)), ((0 &3)|((63 &0x7e)<<1)),	//# 587, ticks 17664, elapsed 0, voice: 0 note: 55 velocity 63 event ('note', 17664, 1, 55, 63)
	28,((( 1 &4)<<5)|( 69 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 588, ticks 17792, elapsed 28, voice: 1 note: 69 velocity 0 event ('note', 17792, 1, 69, 0)
	0,((( 1 &4)<<5)|( 67 &0x7f)), ((1 &3)|((68 &0x7e)<<1)),	//# 589, ticks 17792, elapsed 0, voice: 1 note: 67 velocity 68 event ('note', 17792, 1, 67, 68)
	0,((( 0 &4)<<5)|( 55 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 590, ticks 17792, elapsed 0, voice: 0 note: 55 velocity 0 event ('note', 17792, 1, 55, 0)
	0,((( 0 &4)<<5)|( 50 &0x7f)), ((0 &3)|((60 &0x7e)<<1)),	//# 591, ticks 17792, elapsed 0, voice: 0 note: 50 velocity 60 event ('note', 17792, 1, 50, 60)
	// Note off skipped, note 59 not found in channels, probably interrupted
	28,((( 1 &4)<<5)|( 67 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 593, ticks 17920, elapsed 28, voice: 1 note: 67 velocity 0 event ('note', 17920, 1, 67, 0)
	0,((( 1 &4)<<5)|( 64 &0x7f)), ((1 &3)|((69 &0x7e)<<1)),	//# 594, ticks 17920, elapsed 0, voice: 1 note: 64 velocity 69 event ('note', 17920, 1, 64, 69)
	0,((( 0 &4)<<5)|( 60 &0x7f)), ((0 &3)|((64 &0x7e)<<1)),	//# 595, ticks 17920, elapsed 0, voice: 0 note: 60 velocity 64 event ('note', 17920, 1, 60, 64)
	// Note off skipped, note 50 not found in channels, probably interrupted
	0,((( 0 &4)<<5)|( 48 &0x7f)), ((0 &3)|((60 &0x7e)<<1)),	//# 597, ticks 17920, elapsed 0, voice: 0 note: 48 velocity 60 event ('note', 17920, 1, 48, 60)
	28,((( 0 &4)<<5)|( 48 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 598, ticks 18048, elapsed 28, voice: 0 note: 48 velocity 0 event ('note', 18048, 1, 48, 0)
	0,((( 0 &4)<<5)|( 52 &0x7f)), ((0 &3)|((64 &0x7e)<<1)),	//# 599, ticks 18048, elapsed 0, voice: 0 note: 52 velocity 64 event ('note', 18048, 1, 52, 64)
	28,((( 0 &4)<<5)|( 52 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 600, ticks 18176, elapsed 28, voice: 0 note: 52 velocity 0 event ('note', 18176, 1, 52, 0)
	0,((( 0 &4)<<5)|( 55 &0x7f)), ((0 &3)|((61 &0x7e)<<1)),	//# 601, ticks 18176, elapsed 0, voice: 0 note: 55 velocity 61 event ('note', 18176, 1, 55, 61)
	28,((( 0 &4)<<5)|( 55 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 602, ticks 18304, elapsed 28, voice: 0 note: 55 velocity 0 event ('note', 18304, 1, 55, 0)
	0,((( 0 &4)<<5)|( 52 &0x7f)), ((0 &3)|((59 &0x7e)<<1)),	//# 603, ticks 18304, elapsed 0, voice: 0 note: 52 velocity 59 event ('note', 18304, 1, 52, 59)
	28,((( 1 &4)<<5)|( 64 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 604, ticks 18432, elapsed 28, voice: 1 note: 64 velocity 0 event ('note', 18432, 1, 64, 0)
	// Note off skipped, note 60 not found in channels, probably interrupted
	0,((( 1 &4)<<5)|( 64 &0x7f)), ((1 &3)|((69 &0x7e)<<1)),	//# 606, ticks 18432, elapsed 0, voice: 1 note: 64 velocity 69 event ('note', 18432, 1, 64, 69)
	0,((( 0 &4)<<5)|( 60 &0x7f)), ((0 &3)|((62 &0x7e)<<1)),	//# 607, ticks 18432, elapsed 0, voice: 0 note: 60 velocity 62 event ('note', 18432, 1, 60, 62)
	// Note off skipped, note 52 not found in channels, probably interrupted
	0,((( 0 &4)<<5)|( 45 &0x7f)), ((0 &3)|((59 &0x7e)<<1)),	//# 609, ticks 18432, elapsed 0, voice: 0 note: 45 velocity 59 event ('note', 18432, 1, 45, 59)
	28,((( 1 &4)<<5)|( 64 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 610, ticks 18560, elapsed 28, voice: 1 note: 64 velocity 0 event ('note', 18560, 1, 64, 0)
	0,((( 1 &4)<<5)|( 72 &0x7f)), ((1 &3)|((78 &0x7e)<<1)),	//# 611, ticks 18560, elapsed 0, voice: 1 note: 72 velocity 78 event ('note', 18560, 1, 72, 78)
	0,((( 0 &4)<<5)|( 45 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 612, ticks 18560, elapsed 0, voice: 0 note: 45 velocity 0 event ('note', 18560, 1, 45, 0)
	0,((( 0 &4)<<5)|( 52 &0x7f)), ((0 &3)|((64 &0x7e)<<1)),	//# 613, ticks 18560, elapsed 0, voice: 0 note: 52 velocity 64 event ('note', 18560, 1, 52, 64)
	28,((( 1 &4)<<5)|( 72 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 614, ticks 18688, elapsed 28, voice: 1 note: 72 velocity 0 event ('note', 18688, 1, 72, 0)
	0,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((71 &0x7e)<<1)),	//# 615, ticks 18688, elapsed 0, voice: 1 note: 71 velocity 71 event ('note', 18688, 1, 71, 71)
	0,((( 0 &4)<<5)|( 52 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 616, ticks 18688, elapsed 0, voice: 0 note: 52 velocity 0 event ('note', 18688, 1, 52, 0)
	0,((( 0 &4)<<5)|( 57 &0x7f)), ((0 &3)|((62 &0x7e)<<1)),	//# 617, ticks 18688, elapsed 0, voice: 0 note: 57 velocity 62 event ('note', 18688, 1, 57, 62)
	28,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 618, ticks 18816, elapsed 28, voice: 1 note: 71 velocity 0 event ('note', 18816, 1, 71, 0)
	0,((( 1 &4)<<5)|( 69 &0x7f)), ((1 &3)|((66 &0x7e)<<1)),	//# 619, ticks 18816, elapsed 0, voice: 1 note: 69 velocity 66 event ('note', 18816, 1, 69, 66)
	0,((( 0 &4)<<5)|( 57 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 620, ticks 18816, elapsed 0, voice: 0 note: 57 velocity 0 event ('note', 18816, 1, 57, 0)
	0,((( 0 &4)<<5)|( 52 &0x7f)), ((0 &3)|((59 &0x7e)<<1)),	//# 621, ticks 18816, elapsed 0, voice: 0 note: 52 velocity 59 event ('note', 18816, 1, 52, 59)
	// Note off skipped, note 60 not found in channels, probably interrupted
	28,((( 1 &4)<<5)|( 69 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 623, ticks 18944, elapsed 28, voice: 1 note: 69 velocity 0 event ('note', 18944, 1, 69, 0)
	0,((( 1 &4)<<5)|( 66 &0x7f)), ((1 &3)|((68 &0x7e)<<1)),	//# 624, ticks 18944, elapsed 0, voice: 1 note: 66 velocity 68 event ('note', 18944, 1, 66, 68)
	0,((( 0 &4)<<5)|( 62 &0x7f)), ((0 &3)|((62 &0x7e)<<1)),	//# 625, ticks 18944, elapsed 0, voice: 0 note: 62 velocity 62 event ('note', 18944, 1, 62, 62)
	// Note off skipped, note 52 not found in channels, probably interrupted
	0,((( 0 &4)<<5)|( 50 &0x7f)), ((0 &3)|((59 &0x7e)<<1)),	//# 627, ticks 18944, elapsed 0, voice: 0 note: 50 velocity 59 event ('note', 18944, 1, 50, 59)
	28,((( 0 &4)<<5)|( 50 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 628, ticks 19072, elapsed 28, voice: 0 note: 50 velocity 0 event ('note', 19072, 1, 50, 0)
	0,((( 0 &4)<<5)|( 54 &0x7f)), ((0 &3)|((65 &0x7e)<<1)),	//# 629, ticks 19072, elapsed 0, voice: 0 note: 54 velocity 65 event ('note', 19072, 1, 54, 65)
	28,((( 0 &4)<<5)|( 54 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 630, ticks 19200, elapsed 28, voice: 0 note: 54 velocity 0 event ('note', 19200, 1, 54, 0)
	0,((( 0 &4)<<5)|( 57 &0x7f)), ((0 &3)|((61 &0x7e)<<1)),	//# 631, ticks 19200, elapsed 0, voice: 0 note: 57 velocity 61 event ('note', 19200, 1, 57, 61)
	28,((( 0 &4)<<5)|( 57 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 632, ticks 19328, elapsed 28, voice: 0 note: 57 velocity 0 event ('note', 19328, 1, 57, 0)
	0,((( 0 &4)<<5)|( 54 &0x7f)), ((0 &3)|((65 &0x7e)<<1)),	//# 633, ticks 19328, elapsed 0, voice: 0 note: 54 velocity 65 event ('note', 19328, 1, 54, 65)
	28,((( 1 &4)<<5)|( 66 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 634, ticks 19456, elapsed 28, voice: 1 note: 66 velocity 0 event ('note', 19456, 1, 66, 0)
	// Note off skipped, note 62 not found in channels, probably interrupted
	0,((( 1 &4)<<5)|( 74 &0x7f)), ((1 &3)|((78 &0x7e)<<1)),	//# 636, ticks 19456, elapsed 0, voice: 1 note: 74 velocity 78 event ('note', 19456, 1, 74, 78)
	0,((( 0 &4)<<5)|( 66 &0x7f)), ((0 &3)|((64 &0x7e)<<1)),	//# 637, ticks 19456, elapsed 0, voice: 0 note: 66 velocity 64 event ('note', 19456, 1, 66, 64)
	// Note off skipped, note 54 not found in channels, probably interrupted
	0,((( 0 &4)<<5)|( 50 &0x7f)), ((0 &3)|((61 &0x7e)<<1)),	//# 639, ticks 19456, elapsed 0, voice: 0 note: 50 velocity 61 event ('note', 19456, 1, 50, 61)
	28,((( 1 &4)<<5)|( 74 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 640, ticks 19584, elapsed 28, voice: 1 note: 74 velocity 0 event ('note', 19584, 1, 74, 0)
	0,((( 1 &4)<<5)|( 74 &0x7f)), ((1 &3)|((71 &0x7e)<<1)),	//# 641, ticks 19584, elapsed 0, voice: 1 note: 74 velocity 71 event ('note', 19584, 1, 74, 71)
	0,((( 0 &4)<<5)|( 50 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 642, ticks 19584, elapsed 0, voice: 0 note: 50 velocity 0 event ('note', 19584, 1, 50, 0)
	0,((( 0 &4)<<5)|( 54 &0x7f)), ((0 &3)|((62 &0x7e)<<1)),	//# 643, ticks 19584, elapsed 0, voice: 0 note: 54 velocity 62 event ('note', 19584, 1, 54, 62)
	// Note off skipped, note 66 not found in channels, probably interrupted
	28,((( 1 &4)<<5)|( 74 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 645, ticks 19712, elapsed 28, voice: 1 note: 74 velocity 0 event ('note', 19712, 1, 74, 0)
	0,((( 1 &4)<<5)|( 72 &0x7f)), ((1 &3)|((72 &0x7e)<<1)),	//# 646, ticks 19712, elapsed 0, voice: 1 note: 72 velocity 72 event ('note', 19712, 1, 72, 72)
	0,((( 0 &4)<<5)|( 66 &0x7f)), ((0 &3)|((60 &0x7e)<<1)),	//# 647, ticks 19712, elapsed 0, voice: 0 note: 66 velocity 60 event ('note', 19712, 1, 66, 60)
	// Note off skipped, note 54 not found in channels, probably interrupted
	0,((( 0 &4)<<5)|( 57 &0x7f)), ((0 &3)|((61 &0x7e)<<1)),	//# 649, ticks 19712, elapsed 0, voice: 0 note: 57 velocity 61 event ('note', 19712, 1, 57, 61)
	28,((( 1 &4)<<5)|( 72 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 650, ticks 19840, elapsed 28, voice: 1 note: 72 velocity 0 event ('note', 19840, 1, 72, 0)
	0,((( 1 &4)<<5)|( 69 &0x7f)), ((1 &3)|((67 &0x7e)<<1)),	//# 651, ticks 19840, elapsed 0, voice: 1 note: 69 velocity 67 event ('note', 19840, 1, 69, 67)
	0,((( 0 &4)<<5)|( 57 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 652, ticks 19840, elapsed 0, voice: 0 note: 57 velocity 0 event ('note', 19840, 1, 57, 0)
	0,((( 0 &4)<<5)|( 50 &0x7f)), ((0 &3)|((59 &0x7e)<<1)),	//# 653, ticks 19840, elapsed 0, voice: 0 note: 50 velocity 59 event ('note', 19840, 1, 50, 59)
	// Note off skipped, note 66 not found in channels, probably interrupted
	28,((( 1 &4)<<5)|( 69 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 655, ticks 19968, elapsed 28, voice: 1 note: 69 velocity 0 event ('note', 19968, 1, 69, 0)
	0,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((74 &0x7e)<<1)),	//# 656, ticks 19968, elapsed 0, voice: 1 note: 71 velocity 74 event ('note', 19968, 1, 71, 74)
	0,((( 0 &4)<<5)|( 67 &0x7f)), ((0 &3)|((62 &0x7e)<<1)),	//# 657, ticks 19968, elapsed 0, voice: 0 note: 67 velocity 62 event ('note', 19968, 1, 67, 62)
	// Note off skipped, note 50 not found in channels, probably interrupted
	0,((( 0 &4)<<5)|( 43 &0x7f)), ((0 &3)|((62 &0x7e)<<1)),	//# 659, ticks 19968, elapsed 0, voice: 0 note: 43 velocity 62 event ('note', 19968, 1, 43, 62)
	28,((( 0 &4)<<5)|( 43 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 660, ticks 20096, elapsed 28, voice: 0 note: 43 velocity 0 event ('note', 20096, 1, 43, 0)
	0,((( 0 &4)<<5)|( 50 &0x7f)), ((0 &3)|((63 &0x7e)<<1)),	//# 661, ticks 20096, elapsed 0, voice: 0 note: 50 velocity 63 event ('note', 20096, 1, 50, 63)
	28,((( 0 &4)<<5)|( 50 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 662, ticks 20224, elapsed 28, voice: 0 note: 50 velocity 0 event ('note', 20224, 1, 50, 0)
	0,((( 0 &4)<<5)|( 55 &0x7f)), ((0 &3)|((64 &0x7e)<<1)),	//# 663, ticks 20224, elapsed 0, voice: 0 note: 55 velocity 64 event ('note', 20224, 1, 55, 64)
	28,((( 0 &4)<<5)|( 55 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 664, ticks 20352, elapsed 28, voice: 0 note: 55 velocity 0 event ('note', 20352, 1, 55, 0)
	0,((( 0 &4)<<5)|( 50 &0x7f)), ((0 &3)|((61 &0x7e)<<1)),	//# 665, ticks 20352, elapsed 0, voice: 0 note: 50 velocity 61 event ('note', 20352, 1, 50, 61)
	28,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 666, ticks 20480, elapsed 28, voice: 1 note: 71 velocity 0 event ('note', 20480, 1, 71, 0)
	// Note off skipped, note 67 not found in channels, probably interrupted
	0,((( 1 &4)<<5)|( 62 &0x7f)), ((1 &3)|((61 &0x7e)<<1)),	//# 668, ticks 20480, elapsed 0, voice: 1 note: 62 velocity 61 event ('note', 20480, 1, 62, 61)
	0,((( 0 &4)<<5)|( 59 &0x7f)), ((0 &3)|((59 &0x7e)<<1)),	//# 669, ticks 20480, elapsed 0, voice: 0 note: 59 velocity 59 event ('note', 20480, 1, 59, 59)
	// Note off skipped, note 50 not found in channels, probably interrupted
	0,((( 0 &4)<<5)|( 43 &0x7f)), ((0 &3)|((57 &0x7e)<<1)),	//# 671, ticks 20480, elapsed 0, voice: 0 note: 43 velocity 57 event ('note', 20480, 1, 43, 57)
	28,((( 1 &4)<<5)|( 62 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 672, ticks 20608, elapsed 28, voice: 1 note: 62 velocity 0 event ('note', 20608, 1, 62, 0)
	0,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((80 &0x7e)<<1)),	//# 673, ticks 20608, elapsed 0, voice: 1 note: 71 velocity 80 event ('note', 20608, 1, 71, 80)
	0,((( 0 &4)<<5)|( 43 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 674, ticks 20608, elapsed 0, voice: 0 note: 43 velocity 0 event ('note', 20608, 1, 43, 0)
	0,((( 0 &4)<<5)|( 50 &0x7f)), ((0 &3)|((63 &0x7e)<<1)),	//# 675, ticks 20608, elapsed 0, voice: 0 note: 50 velocity 63 event ('note', 20608, 1, 50, 63)
	28,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 676, ticks 20736, elapsed 28, voice: 1 note: 71 velocity 0 event ('note', 20736, 1, 71, 0)
	0,((( 1 &4)<<5)|( 69 &0x7f)), ((1 &3)|((69 &0x7e)<<1)),	//# 677, ticks 20736, elapsed 0, voice: 1 note: 69 velocity 69 event ('note', 20736, 1, 69, 69)
	0,((( 0 &4)<<5)|( 50 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 678, ticks 20736, elapsed 0, voice: 0 note: 50 velocity 0 event ('note', 20736, 1, 50, 0)
	0,((( 0 &4)<<5)|( 55 &0x7f)), ((0 &3)|((63 &0x7e)<<1)),	//# 679, ticks 20736, elapsed 0, voice: 0 note: 55 velocity 63 event ('note', 20736, 1, 55, 63)
	28,((( 1 &4)<<5)|( 69 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 680, ticks 20864, elapsed 28, voice: 1 note: 69 velocity 0 event ('note', 20864, 1, 69, 0)
	0,((( 1 &4)<<5)|( 67 &0x7f)), ((1 &3)|((69 &0x7e)<<1)),	//# 681, ticks 20864, elapsed 0, voice: 1 note: 67 velocity 69 event ('note', 20864, 1, 67, 69)
	0,((( 0 &4)<<5)|( 55 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 682, ticks 20864, elapsed 0, voice: 0 note: 55 velocity 0 event ('note', 20864, 1, 55, 0)
	0,((( 0 &4)<<5)|( 50 &0x7f)), ((0 &3)|((59 &0x7e)<<1)),	//# 683, ticks 20864, elapsed 0, voice: 0 note: 50 velocity 59 event ('note', 20864, 1, 50, 59)
	// Note off skipped, note 59 not found in channels, probably interrupted
	28,((( 1 &4)<<5)|( 67 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 685, ticks 20992, elapsed 28, voice: 1 note: 67 velocity 0 event ('note', 20992, 1, 67, 0)
	0,((( 1 &4)<<5)|( 62 &0x7f)), ((1 &3)|((66 &0x7e)<<1)),	//# 686, ticks 20992, elapsed 0, voice: 1 note: 62 velocity 66 event ('note', 20992, 1, 62, 66)
	0,((( 0 &4)<<5)|( 59 &0x7f)), ((0 &3)|((61 &0x7e)<<1)),	//# 687, ticks 20992, elapsed 0, voice: 0 note: 59 velocity 61 event ('note', 20992, 1, 59, 61)
	// Note off skipped, note 50 not found in channels, probably interrupted
	0,((( 0 &4)<<5)|( 43 &0x7f)), ((0 &3)|((61 &0x7e)<<1)),	//# 689, ticks 20992, elapsed 0, voice: 0 note: 43 velocity 61 event ('note', 20992, 1, 43, 61)
	28,((( 0 &4)<<5)|( 43 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 690, ticks 21120, elapsed 28, voice: 0 note: 43 velocity 0 event ('note', 21120, 1, 43, 0)
	0,((( 0 &4)<<5)|( 50 &0x7f)), ((0 &3)|((61 &0x7e)<<1)),	//# 691, ticks 21120, elapsed 0, voice: 0 note: 50 velocity 61 event ('note', 21120, 1, 50, 61)
	28,((( 0 &4)<<5)|( 50 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 692, ticks 21248, elapsed 28, voice: 0 note: 50 velocity 0 event ('note', 21248, 1, 50, 0)
	0,((( 0 &4)<<5)|( 55 &0x7f)), ((0 &3)|((63 &0x7e)<<1)),	//# 693, ticks 21248, elapsed 0, voice: 0 note: 55 velocity 63 event ('note', 21248, 1, 55, 63)
	28,((( 1 &4)<<5)|( 62 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 694, ticks 21376, elapsed 28, voice: 1 note: 62 velocity 0 event ('note', 21376, 1, 62, 0)
	0,((( 1 &4)<<5)|( 62 &0x7f)), ((1 &3)|((72 &0x7e)<<1)),	//# 695, ticks 21376, elapsed 0, voice: 1 note: 62 velocity 72 event ('note', 21376, 1, 62, 72)
	0,((( 0 &4)<<5)|( 55 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 696, ticks 21376, elapsed 0, voice: 0 note: 55 velocity 0 event ('note', 21376, 1, 55, 0)
	0,((( 0 &4)<<5)|( 50 &0x7f)), ((0 &3)|((59 &0x7e)<<1)),	//# 697, ticks 21376, elapsed 0, voice: 0 note: 50 velocity 59 event ('note', 21376, 1, 50, 59)
	14,((( 1 &4)<<5)|( 62 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 698, ticks 21440, elapsed 14, voice: 1 note: 62 velocity 0 event ('note', 21440, 1, 62, 0)
	0,((( 1 &4)<<5)|( 62 &0x7f)), ((1 &3)|((72 &0x7e)<<1)),	//# 699, ticks 21440, elapsed 0, voice: 1 note: 62 velocity 72 event ('note', 21440, 1, 62, 72)
	// Note off skipped, note 59 not found in channels, probably interrupted
	14,((( 1 &4)<<5)|( 62 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 701, ticks 21504, elapsed 14, voice: 1 note: 62 velocity 0 event ('note', 21504, 1, 62, 0)
	0,((( 1 &4)<<5)|( 62 &0x7f)), ((1 &3)|((73 &0x7e)<<1)),	//# 702, ticks 21504, elapsed 0, voice: 1 note: 62 velocity 73 event ('note', 21504, 1, 62, 73)
	0,((( 0 &4)<<5)|( 59 &0x7f)), ((0 &3)|((58 &0x7e)<<1)),	//# 703, ticks 21504, elapsed 0, voice: 0 note: 59 velocity 58 event ('note', 21504, 1, 59, 58)
	// Note off skipped, note 50 not found in channels, probably interrupted
	0,((( 0 &4)<<5)|( 43 &0x7f)), ((0 &3)|((59 &0x7e)<<1)),	//# 705, ticks 21504, elapsed 0, voice: 0 note: 43 velocity 59 event ('note', 21504, 1, 43, 59)
	28,((( 1 &4)<<5)|( 62 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 706, ticks 21632, elapsed 28, voice: 1 note: 62 velocity 0 event ('note', 21632, 1, 62, 0)
	0,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((77 &0x7e)<<1)),	//# 707, ticks 21632, elapsed 0, voice: 1 note: 71 velocity 77 event ('note', 21632, 1, 71, 77)
	0,((( 0 &4)<<5)|( 43 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 708, ticks 21632, elapsed 0, voice: 0 note: 43 velocity 0 event ('note', 21632, 1, 43, 0)
	0,((( 0 &4)<<5)|( 50 &0x7f)), ((0 &3)|((66 &0x7e)<<1)),	//# 709, ticks 21632, elapsed 0, voice: 0 note: 50 velocity 66 event ('note', 21632, 1, 50, 66)
	28,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 710, ticks 21760, elapsed 28, voice: 1 note: 71 velocity 0 event ('note', 21760, 1, 71, 0)
	0,((( 1 &4)<<5)|( 69 &0x7f)), ((1 &3)|((69 &0x7e)<<1)),	//# 711, ticks 21760, elapsed 0, voice: 1 note: 69 velocity 69 event ('note', 21760, 1, 69, 69)
	0,((( 0 &4)<<5)|( 50 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 712, ticks 21760, elapsed 0, voice: 0 note: 50 velocity 0 event ('note', 21760, 1, 50, 0)
	0,((( 0 &4)<<5)|( 55 &0x7f)), ((0 &3)|((64 &0x7e)<<1)),	//# 713, ticks 21760, elapsed 0, voice: 0 note: 55 velocity 64 event ('note', 21760, 1, 55, 64)
	28,((( 1 &4)<<5)|( 69 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 714, ticks 21888, elapsed 28, voice: 1 note: 69 velocity 0 event ('note', 21888, 1, 69, 0)
	0,((( 1 &4)<<5)|( 67 &0x7f)), ((1 &3)|((69 &0x7e)<<1)),	//# 715, ticks 21888, elapsed 0, voice: 1 note: 67 velocity 69 event ('note', 21888, 1, 67, 69)
	0,((( 0 &4)<<5)|( 55 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 716, ticks 21888, elapsed 0, voice: 0 note: 55 velocity 0 event ('note', 21888, 1, 55, 0)
	0,((( 0 &4)<<5)|( 50 &0x7f)), ((0 &3)|((57 &0x7e)<<1)),	//# 717, ticks 21888, elapsed 0, voice: 0 note: 50 velocity 57 event ('note', 21888, 1, 50, 57)
	// Note off skipped, note 59 not found in channels, probably interrupted
	28,((( 1 &4)<<5)|( 67 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 719, ticks 22016, elapsed 28, voice: 1 note: 67 velocity 0 event ('note', 22016, 1, 67, 0)
	0,((( 1 &4)<<5)|( 64 &0x7f)), ((1 &3)|((68 &0x7e)<<1)),	//# 720, ticks 22016, elapsed 0, voice: 1 note: 64 velocity 68 event ('note', 22016, 1, 64, 68)
	0,((( 0 &4)<<5)|( 60 &0x7f)), ((0 &3)|((62 &0x7e)<<1)),	//# 721, ticks 22016, elapsed 0, voice: 0 note: 60 velocity 62 event ('note', 22016, 1, 60, 62)
	// Note off skipped, note 50 not found in channels, probably interrupted
	0,((( 0 &4)<<5)|( 48 &0x7f)), ((0 &3)|((62 &0x7e)<<1)),	//# 723, ticks 22016, elapsed 0, voice: 0 note: 48 velocity 62 event ('note', 22016, 1, 48, 62)
	28,((( 0 &4)<<5)|( 48 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 724, ticks 22144, elapsed 28, voice: 0 note: 48 velocity 0 event ('note', 22144, 1, 48, 0)
	0,((( 0 &4)<<5)|( 52 &0x7f)), ((0 &3)|((61 &0x7e)<<1)),	//# 725, ticks 22144, elapsed 0, voice: 0 note: 52 velocity 61 event ('note', 22144, 1, 52, 61)
	28,((( 0 &4)<<5)|( 52 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 726, ticks 22272, elapsed 28, voice: 0 note: 52 velocity 0 event ('note', 22272, 1, 52, 0)
	0,((( 0 &4)<<5)|( 55 &0x7f)), ((0 &3)|((63 &0x7e)<<1)),	//# 727, ticks 22272, elapsed 0, voice: 0 note: 55 velocity 63 event ('note', 22272, 1, 55, 63)
	28,((( 0 &4)<<5)|( 55 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 728, ticks 22400, elapsed 28, voice: 0 note: 55 velocity 0 event ('note', 22400, 1, 55, 0)
	0,((( 0 &4)<<5)|( 52 &0x7f)), ((0 &3)|((58 &0x7e)<<1)),	//# 729, ticks 22400, elapsed 0, voice: 0 note: 52 velocity 58 event ('note', 22400, 1, 52, 58)
	28,((( 1 &4)<<5)|( 64 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 730, ticks 22528, elapsed 28, voice: 1 note: 64 velocity 0 event ('note', 22528, 1, 64, 0)
	// Note off skipped, note 60 not found in channels, probably interrupted
	0,((( 1 &4)<<5)|( 64 &0x7f)), ((1 &3)|((73 &0x7e)<<1)),	//# 732, ticks 22528, elapsed 0, voice: 1 note: 64 velocity 73 event ('note', 22528, 1, 64, 73)
	0,((( 0 &4)<<5)|( 60 &0x7f)), ((0 &3)|((63 &0x7e)<<1)),	//# 733, ticks 22528, elapsed 0, voice: 0 note: 60 velocity 63 event ('note', 22528, 1, 60, 63)
	// Note off skipped, note 52 not found in channels, probably interrupted
	0,((( 0 &4)<<5)|( 45 &0x7f)), ((0 &3)|((59 &0x7e)<<1)),	//# 735, ticks 22528, elapsed 0, voice: 0 note: 45 velocity 59 event ('note', 22528, 1, 45, 59)
	28,((( 1 &4)<<5)|( 64 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 736, ticks 22656, elapsed 28, voice: 1 note: 64 velocity 0 event ('note', 22656, 1, 64, 0)
	0,((( 1 &4)<<5)|( 72 &0x7f)), ((1 &3)|((77 &0x7e)<<1)),	//# 737, ticks 22656, elapsed 0, voice: 1 note: 72 velocity 77 event ('note', 22656, 1, 72, 77)
	0,((( 0 &4)<<5)|( 45 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 738, ticks 22656, elapsed 0, voice: 0 note: 45 velocity 0 event ('note', 22656, 1, 45, 0)
	0,((( 0 &4)<<5)|( 52 &0x7f)), ((0 &3)|((62 &0x7e)<<1)),	//# 739, ticks 22656, elapsed 0, voice: 0 note: 52 velocity 62 event ('note', 22656, 1, 52, 62)
	28,((( 1 &4)<<5)|( 72 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 740, ticks 22784, elapsed 28, voice: 1 note: 72 velocity 0 event ('note', 22784, 1, 72, 0)
	0,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((73 &0x7e)<<1)),	//# 741, ticks 22784, elapsed 0, voice: 1 note: 71 velocity 73 event ('note', 22784, 1, 71, 73)
	0,((( 0 &4)<<5)|( 52 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 742, ticks 22784, elapsed 0, voice: 0 note: 52 velocity 0 event ('note', 22784, 1, 52, 0)
	0,((( 0 &4)<<5)|( 57 &0x7f)), ((0 &3)|((61 &0x7e)<<1)),	//# 743, ticks 22784, elapsed 0, voice: 0 note: 57 velocity 61 event ('note', 22784, 1, 57, 61)
	28,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 744, ticks 22912, elapsed 28, voice: 1 note: 71 velocity 0 event ('note', 22912, 1, 71, 0)
	0,((( 1 &4)<<5)|( 69 &0x7f)), ((1 &3)|((68 &0x7e)<<1)),	//# 745, ticks 22912, elapsed 0, voice: 1 note: 69 velocity 68 event ('note', 22912, 1, 69, 68)
	0,((( 0 &4)<<5)|( 57 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 746, ticks 22912, elapsed 0, voice: 0 note: 57 velocity 0 event ('note', 22912, 1, 57, 0)
	0,((( 0 &4)<<5)|( 52 &0x7f)), ((0 &3)|((56 &0x7e)<<1)),	//# 747, ticks 22912, elapsed 0, voice: 0 note: 52 velocity 56 event ('note', 22912, 1, 52, 56)
	// Note off skipped, note 60 not found in channels, probably interrupted
	28,((( 1 &4)<<5)|( 69 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 749, ticks 23040, elapsed 28, voice: 1 note: 69 velocity 0 event ('note', 23040, 1, 69, 0)
	0,((( 1 &4)<<5)|( 74 &0x7f)), ((1 &3)|((77 &0x7e)<<1)),	//# 750, ticks 23040, elapsed 0, voice: 1 note: 74 velocity 77 event ('note', 23040, 1, 74, 77)
	0,((( 0 &4)<<5)|( 67 &0x7f)), ((0 &3)|((65 &0x7e)<<1)),	//# 751, ticks 23040, elapsed 0, voice: 0 note: 67 velocity 65 event ('note', 23040, 1, 67, 65)
	// Note off skipped, note 52 not found in channels, probably interrupted
	0,((( 0 &4)<<5)|( 47 &0x7f)), ((0 &3)|((58 &0x7e)<<1)),	//# 753, ticks 23040, elapsed 0, voice: 0 note: 47 velocity 58 event ('note', 23040, 1, 47, 58)
	28,((( 1 &4)<<5)|( 74 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 754, ticks 23168, elapsed 28, voice: 1 note: 74 velocity 0 event ('note', 23168, 1, 74, 0)
	0,((( 1 &4)<<5)|( 74 &0x7f)), ((1 &3)|((74 &0x7e)<<1)),	//# 755, ticks 23168, elapsed 0, voice: 1 note: 74 velocity 74 event ('note', 23168, 1, 74, 74)
	0,((( 0 &4)<<5)|( 47 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 756, ticks 23168, elapsed 0, voice: 0 note: 47 velocity 0 event ('note', 23168, 1, 47, 0)
	0,((( 0 &4)<<5)|( 50 &0x7f)), ((0 &3)|((61 &0x7e)<<1)),	//# 757, ticks 23168, elapsed 0, voice: 0 note: 50 velocity 61 event ('note', 23168, 1, 50, 61)
	// Note off skipped, note 67 not found in channels, probably interrupted
	28,((( 1 &4)<<5)|( 74 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 759, ticks 23296, elapsed 28, voice: 1 note: 74 velocity 0 event ('note', 23296, 1, 74, 0)
	0,((( 1 &4)<<5)|( 74 &0x7f)), ((1 &3)|((74 &0x7e)<<1)),	//# 760, ticks 23296, elapsed 0, voice: 1 note: 74 velocity 74 event ('note', 23296, 1, 74, 74)
	0,((( 0 &4)<<5)|( 67 &0x7f)), ((0 &3)|((62 &0x7e)<<1)),	//# 761, ticks 23296, elapsed 0, voice: 0 note: 67 velocity 62 event ('note', 23296, 1, 67, 62)
	// Note off skipped, note 50 not found in channels, probably interrupted
	0,((( 0 &4)<<5)|( 55 &0x7f)), ((0 &3)|((63 &0x7e)<<1)),	//# 763, ticks 23296, elapsed 0, voice: 0 note: 55 velocity 63 event ('note', 23296, 1, 55, 63)
	28,((( 1 &4)<<5)|( 74 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 764, ticks 23424, elapsed 28, voice: 1 note: 74 velocity 0 event ('note', 23424, 1, 74, 0)
	0,((( 1 &4)<<5)|( 74 &0x7f)), ((1 &3)|((71 &0x7e)<<1)),	//# 765, ticks 23424, elapsed 0, voice: 1 note: 74 velocity 71 event ('note', 23424, 1, 74, 71)
	0,((( 0 &4)<<5)|( 55 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 766, ticks 23424, elapsed 0, voice: 0 note: 55 velocity 0 event ('note', 23424, 1, 55, 0)
	0,((( 0 &4)<<5)|( 50 &0x7f)), ((0 &3)|((61 &0x7e)<<1)),	//# 767, ticks 23424, elapsed 0, voice: 0 note: 50 velocity 61 event ('note', 23424, 1, 50, 61)
	// Note off skipped, note 67 not found in channels, probably interrupted
	28,((( 1 &4)<<5)|( 74 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 769, ticks 23552, elapsed 28, voice: 1 note: 74 velocity 0 event ('note', 23552, 1, 74, 0)
	0,((( 1 &4)<<5)|( 76 &0x7f)), ((1 &3)|((74 &0x7e)<<1)),	//# 770, ticks 23552, elapsed 0, voice: 1 note: 76 velocity 74 event ('note', 23552, 1, 76, 74)
	0,((( 0 &4)<<5)|( 66 &0x7f)), ((0 &3)|((57 &0x7e)<<1)),	//# 771, ticks 23552, elapsed 0, voice: 0 note: 66 velocity 57 event ('note', 23552, 1, 66, 57)
	// Note off skipped, note 50 not found in channels, probably interrupted
	0,((( 0 &4)<<5)|( 45 &0x7f)), ((0 &3)|((59 &0x7e)<<1)),	//# 773, ticks 23552, elapsed 0, voice: 0 note: 45 velocity 59 event ('note', 23552, 1, 45, 59)
	28,((( 1 &4)<<5)|( 76 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 774, ticks 23680, elapsed 28, voice: 1 note: 76 velocity 0 event ('note', 23680, 1, 76, 0)
	0,((( 1 &4)<<5)|( 74 &0x7f)), ((1 &3)|((70 &0x7e)<<1)),	//# 775, ticks 23680, elapsed 0, voice: 1 note: 74 velocity 70 event ('note', 23680, 1, 74, 70)
	0,((( 0 &4)<<5)|( 45 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 776, ticks 23680, elapsed 0, voice: 0 note: 45 velocity 0 event ('note', 23680, 1, 45, 0)
	0,((( 0 &4)<<5)|( 50 &0x7f)), ((0 &3)|((62 &0x7e)<<1)),	//# 777, ticks 23680, elapsed 0, voice: 0 note: 50 velocity 62 event ('note', 23680, 1, 50, 62)
	// Note off skipped, note 66 not found in channels, probably interrupted
	28,((( 1 &4)<<5)|( 74 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 779, ticks 23808, elapsed 28, voice: 1 note: 74 velocity 0 event ('note', 23808, 1, 74, 0)
	0,((( 1 &4)<<5)|( 72 &0x7f)), ((1 &3)|((69 &0x7e)<<1)),	//# 780, ticks 23808, elapsed 0, voice: 1 note: 72 velocity 69 event ('note', 23808, 1, 72, 69)
	0,((( 0 &4)<<5)|( 66 &0x7f)), ((0 &3)|((60 &0x7e)<<1)),	//# 781, ticks 23808, elapsed 0, voice: 0 note: 66 velocity 60 event ('note', 23808, 1, 66, 60)
	// Note off skipped, note 50 not found in channels, probably interrupted
	0,((( 0 &4)<<5)|( 54 &0x7f)), ((0 &3)|((64 &0x7e)<<1)),	//# 783, ticks 23808, elapsed 0, voice: 0 note: 54 velocity 64 event ('note', 23808, 1, 54, 64)
	28,((( 1 &4)<<5)|( 72 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 784, ticks 23936, elapsed 28, voice: 1 note: 72 velocity 0 event ('note', 23936, 1, 72, 0)
	0,((( 1 &4)<<5)|( 69 &0x7f)), ((1 &3)|((69 &0x7e)<<1)),	//# 785, ticks 23936, elapsed 0, voice: 1 note: 69 velocity 69 event ('note', 23936, 1, 69, 69)
	0,((( 0 &4)<<5)|( 54 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 786, ticks 23936, elapsed 0, voice: 0 note: 54 velocity 0 event ('note', 23936, 1, 54, 0)
	0,((( 0 &4)<<5)|( 50 &0x7f)), ((0 &3)|((58 &0x7e)<<1)),	//# 787, ticks 23936, elapsed 0, voice: 0 note: 50 velocity 58 event ('note', 23936, 1, 50, 58)
	// Note off skipped, note 66 not found in channels, probably interrupted
	28,((( 1 &4)<<5)|( 69 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 789, ticks 24064, elapsed 28, voice: 1 note: 69 velocity 0 event ('note', 24064, 1, 69, 0)
	0,((( 1 &4)<<5)|( 67 &0x7f)), ((1 &3)|((69 &0x7e)<<1)),	//# 790, ticks 24064, elapsed 0, voice: 1 note: 67 velocity 69 event ('note', 24064, 1, 67, 69)
	0,((( 0 &4)<<5)|( 62 &0x7f)), ((0 &3)|((56 &0x7e)<<1)),	//# 791, ticks 24064, elapsed 0, voice: 0 note: 62 velocity 56 event ('note', 24064, 1, 62, 56)
	// Note off skipped, note 50 not found in channels, probably interrupted
	0,((( 0 &4)<<5)|( 43 &0x7f)), ((0 &3)|((59 &0x7e)<<1)),	//# 793, ticks 24064, elapsed 0, voice: 0 note: 43 velocity 59 event ('note', 24064, 1, 43, 59)
	28,((( 0 &4)<<5)|( 43 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 794, ticks 24192, elapsed 28, voice: 0 note: 43 velocity 0 event ('note', 24192, 1, 43, 0)
	0,((( 0 &4)<<5)|( 50 &0x7f)), ((0 &3)|((64 &0x7e)<<1)),	//# 795, ticks 24192, elapsed 0, voice: 0 note: 50 velocity 64 event ('note', 24192, 1, 50, 64)
	28,((( 1 &4)<<5)|( 67 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 796, ticks 24320, elapsed 28, voice: 1 note: 67 velocity 0 event ('note', 24320, 1, 67, 0)
	// Note off skipped, note 62 not found in channels, probably interrupted
	0,((( 1 &4)<<5)|( 74 &0x7f)), ((1 &3)|((76 &0x7e)<<1)),	//# 798, ticks 24320, elapsed 0, voice: 1 note: 74 velocity 76 event ('note', 24320, 1, 74, 76)
	0,((( 0 &4)<<5)|( 67 &0x7f)), ((0 &3)|((64 &0x7e)<<1)),	//# 799, ticks 24320, elapsed 0, voice: 0 note: 67 velocity 64 event ('note', 24320, 1, 67, 64)
	// Note off skipped, note 50 not found in channels, probably interrupted
	0,((( 0 &4)<<5)|( 55 &0x7f)), ((0 &3)|((65 &0x7e)<<1)),	//# 801, ticks 24320, elapsed 0, voice: 0 note: 55 velocity 65 event ('note', 24320, 1, 55, 65)
	57,((( 1 &4)<<5)|( 74 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 802, ticks 24576, elapsed 57, voice: 1 note: 74 velocity 0 event ('note', 24576, 1, 74, 0)
	// Note off skipped, note 67 not found in channels, probably interrupted
	0,((( 1 &4)<<5)|( 67 &0x7f)), ((1 &3)|((69 &0x7e)<<1)),	//# 804, ticks 24576, elapsed 0, voice: 1 note: 67 velocity 69 event ('note', 24576, 1, 67, 69)
	0,((( 0 &4)<<5)|( 71 &0x7f)), ((0 &3)|((69 &0x7e)<<1)),	//# 805, ticks 24576, elapsed 0, voice: 0 note: 71 velocity 69 event ('note', 24576, 1, 71, 69)
	// Note off skipped, note 55 not found in channels, probably interrupted
	0,((( 0 &4)<<5)|( 43 &0x7f)), ((0 &3)|((60 &0x7e)<<1)),	//# 807, ticks 24576, elapsed 0, voice: 0 note: 43 velocity 60 event ('note', 24576, 1, 43, 60)
	28,((( 1 &4)<<5)|( 67 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 808, ticks 24704, elapsed 28, voice: 1 note: 67 velocity 0 event ('note', 24704, 1, 67, 0)
	// Note off skipped, note 71 not found in channels, probably interrupted
	0,((( 1 &4)<<5)|( 67 &0x7f)), ((1 &3)|((72 &0x7e)<<1)),	//# 810, ticks 24704, elapsed 0, voice: 1 note: 67 velocity 72 event ('note', 24704, 1, 67, 72)
	0,((( 0 &4)<<5)|( 71 &0x7f)), ((0 &3)|((72 &0x7e)<<1)),	//# 811, ticks 24704, elapsed 0, voice: 0 note: 71 velocity 72 event ('note', 24704, 1, 71, 72)
	28,((( 1 &4)<<5)|( 67 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 812, ticks 24832, elapsed 28, voice: 1 note: 67 velocity 0 event ('note', 24832, 1, 67, 0)
	0,((( 0 &4)<<5)|( 71 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 813, ticks 24832, elapsed 0, voice: 0 note: 71 velocity 0 event ('note', 24832, 1, 71, 0)
	0,((( 0 &4)<<5)|( 67 &0x7f)), ((0 &3)|((70 &0x7e)<<1)),	//# 814, ticks 24832, elapsed 0, voice: 0 note: 67 velocity 70 event ('note', 24832, 1, 67, 70)
	0,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((70 &0x7e)<<1)),	//# 815, ticks 24832, elapsed 0, voice: 1 note: 71 velocity 70 event ('note', 24832, 1, 71, 70)
	// Note off skipped, note 43 not found in channels, probably interrupted
	28,((( 0 &4)<<5)|( 50 &0x7f)), ((0 &3)|((65 &0x7e)<<1)),	//# 817, ticks 24960, elapsed 28, voice: 0 note: 50 velocity 65 event ('note', 24960, 1, 50, 65)
	// Note off skipped, note 67 not found in channels, probably interrupted
	28,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 819, ticks 25088, elapsed 28, voice: 1 note: 71 velocity 0 event ('note', 25088, 1, 71, 0)
	0,((( 1 &4)<<5)|( 67 &0x7f)), ((1 &3)|((70 &0x7e)<<1)),	//# 820, ticks 25088, elapsed 0, voice: 1 note: 67 velocity 70 event ('note', 25088, 1, 67, 70)
	0,((( 0 &4)<<5)|( 71 &0x7f)), ((0 &3)|((70 &0x7e)<<1)),	//# 821, ticks 25088, elapsed 0, voice: 0 note: 71 velocity 70 event ('note', 25088, 1, 71, 70)
	// Note off skipped, note 50 not found in channels, probably interrupted
	0,((( 0 &4)<<5)|( 55 &0x7f)), ((0 &3)|((63 &0x7e)<<1)),	//# 823, ticks 25088, elapsed 0, voice: 0 note: 55 velocity 63 event ('note', 25088, 1, 55, 63)
	28,((( 1 &4)<<5)|( 67 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 824, ticks 25216, elapsed 28, voice: 1 note: 67 velocity 0 event ('note', 25216, 1, 67, 0)
	// Note off skipped, note 71 not found in channels, probably interrupted
	0,((( 1 &4)<<5)|( 67 &0x7f)), ((1 &3)|((71 &0x7e)<<1)),	//# 826, ticks 25216, elapsed 0, voice: 1 note: 67 velocity 71 event ('note', 25216, 1, 67, 71)
	0,((( 0 &4)<<5)|( 71 &0x7f)), ((0 &3)|((71 &0x7e)<<1)),	//# 827, ticks 25216, elapsed 0, voice: 0 note: 71 velocity 71 event ('note', 25216, 1, 71, 71)
	28,((( 1 &4)<<5)|( 67 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 828, ticks 25344, elapsed 28, voice: 1 note: 67 velocity 0 event ('note', 25344, 1, 67, 0)
	0,((( 0 &4)<<5)|( 71 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 829, ticks 25344, elapsed 0, voice: 0 note: 71 velocity 0 event ('note', 25344, 1, 71, 0)
	0,((( 0 &4)<<5)|( 67 &0x7f)), ((0 &3)|((72 &0x7e)<<1)),	//# 830, ticks 25344, elapsed 0, voice: 0 note: 67 velocity 72 event ('note', 25344, 1, 67, 72)
	0,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((72 &0x7e)<<1)),	//# 831, ticks 25344, elapsed 0, voice: 1 note: 71 velocity 72 event ('note', 25344, 1, 71, 72)
	// Note off skipped, note 55 not found in channels, probably interrupted
	28,((( 0 &4)<<5)|( 50 &0x7f)), ((0 &3)|((60 &0x7e)<<1)),	//# 833, ticks 25472, elapsed 28, voice: 0 note: 50 velocity 60 event ('note', 25472, 1, 50, 60)
	// Note off skipped, note 67 not found in channels, probably interrupted
	28,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 835, ticks 25600, elapsed 28, voice: 1 note: 71 velocity 0 event ('note', 25600, 1, 71, 0)
	0,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((71 &0x7e)<<1)),	//# 836, ticks 25600, elapsed 0, voice: 1 note: 71 velocity 71 event ('note', 25600, 1, 71, 71)
	0,((( 0 &4)<<5)|( 67 &0x7f)), ((0 &3)|((63 &0x7e)<<1)),	//# 837, ticks 25600, elapsed 0, voice: 0 note: 67 velocity 63 event ('note', 25600, 1, 67, 63)
	// Note off skipped, note 50 not found in channels, probably interrupted
	0,((( 0 &4)<<5)|( 43 &0x7f)), ((0 &3)|((55 &0x7e)<<1)),	//# 839, ticks 25600, elapsed 0, voice: 0 note: 43 velocity 55 event ('note', 25600, 1, 43, 55)
	28,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 840, ticks 25728, elapsed 28, voice: 1 note: 71 velocity 0 event ('note', 25728, 1, 71, 0)
	0,((( 1 &4)<<5)|( 74 &0x7f)), ((1 &3)|((73 &0x7e)<<1)),	//# 841, ticks 25728, elapsed 0, voice: 1 note: 74 velocity 73 event ('note', 25728, 1, 74, 73)
	0,((( 0 &4)<<5)|( 43 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 842, ticks 25728, elapsed 0, voice: 0 note: 43 velocity 0 event ('note', 25728, 1, 43, 0)
	0,((( 0 &4)<<5)|( 50 &0x7f)), ((0 &3)|((63 &0x7e)<<1)),	//# 843, ticks 25728, elapsed 0, voice: 0 note: 50 velocity 63 event ('note', 25728, 1, 50, 63)
	// Note off skipped, note 67 not found in channels, probably interrupted
	28,((( 1 &4)<<5)|( 74 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 845, ticks 25856, elapsed 28, voice: 1 note: 74 velocity 0 event ('note', 25856, 1, 74, 0)
	0,((( 1 &4)<<5)|( 67 &0x7f)), ((1 &3)|((65 &0x7e)<<1)),	//# 846, ticks 25856, elapsed 0, voice: 1 note: 67 velocity 65 event ('note', 25856, 1, 67, 65)
	0,((( 0 &4)<<5)|( 64 &0x7f)), ((0 &3)|((59 &0x7e)<<1)),	//# 847, ticks 25856, elapsed 0, voice: 0 note: 64 velocity 59 event ('note', 25856, 1, 64, 59)
	// Note off skipped, note 50 not found in channels, probably interrupted
	0,((( 0 &4)<<5)|( 48 &0x7f)), ((0 &3)|((64 &0x7e)<<1)),	//# 849, ticks 25856, elapsed 0, voice: 0 note: 48 velocity 64 event ('note', 25856, 1, 48, 64)
	0,((( 0 &4)<<5)|( 52 &0x7f)), ((0 &3)|((64 &0x7e)<<1)),	//# 850, ticks 25856, elapsed 0, voice: 0 note: 52 velocity 64 event ('note', 25856, 1, 52, 64)
	42,((( 1 &4)<<5)|( 67 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 851, ticks 26048, elapsed 42, voice: 1 note: 67 velocity 0 event ('note', 26048, 1, 67, 0)
	0,((( 1 &4)<<5)|( 69 &0x7f)), ((1 &3)|((72 &0x7e)<<1)),	//# 852, ticks 26048, elapsed 0, voice: 1 note: 69 velocity 72 event ('note', 26048, 1, 69, 72)
	// Note off skipped, note 64 not found in channels, probably interrupted
	14,((( 1 &4)<<5)|( 69 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 854, ticks 26112, elapsed 14, voice: 1 note: 69 velocity 0 event ('note', 26112, 1, 69, 0)
	0,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((74 &0x7e)<<1)),	//# 855, ticks 26112, elapsed 0, voice: 1 note: 71 velocity 74 event ('note', 26112, 1, 71, 74)
	0,((( 0 &4)<<5)|( 62 &0x7f)), ((0 &3)|((58 &0x7e)<<1)),	//# 856, ticks 26112, elapsed 0, voice: 0 note: 62 velocity 58 event ('note', 26112, 1, 62, 58)
	// Note off skipped, note 48 not found in channels, probably interrupted
	// Note off skipped, note 52 not found in channels, probably interrupted
	0,((( 0 &4)<<5)|( 43 &0x7f)), ((0 &3)|((59 &0x7e)<<1)),	//# 859, ticks 26112, elapsed 0, voice: 0 note: 43 velocity 59 event ('note', 26112, 1, 43, 59)
	28,((( 0 &4)<<5)|( 43 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 860, ticks 26240, elapsed 28, voice: 0 note: 43 velocity 0 event ('note', 26240, 1, 43, 0)
	0,((( 0 &4)<<5)|( 50 &0x7f)), ((0 &3)|((63 &0x7e)<<1)),	//# 861, ticks 26240, elapsed 0, voice: 0 note: 50 velocity 63 event ('note', 26240, 1, 50, 63)
	28,((( 0 &4)<<5)|( 50 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 862, ticks 26368, elapsed 28, voice: 0 note: 50 velocity 0 event ('note', 26368, 1, 50, 0)
	0,((( 0 &4)<<5)|( 55 &0x7f)), ((0 &3)|((62 &0x7e)<<1)),	//# 863, ticks 26368, elapsed 0, voice: 0 note: 55 velocity 62 event ('note', 26368, 1, 55, 62)
	57,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 864, ticks 26624, elapsed 57, voice: 1 note: 71 velocity 0 event ('note', 26624, 1, 71, 0)
	// Note off skipped, note 62 not found in channels, probably interrupted
	0,((( 1 &4)<<5)|( 72 &0x7f)), ((1 &3)|((72 &0x7e)<<1)),	//# 866, ticks 26624, elapsed 0, voice: 1 note: 72 velocity 72 event ('note', 26624, 1, 72, 72)
	0,((( 0 &4)<<5)|( 64 &0x7f)), ((0 &3)|((64 &0x7e)<<1)),	//# 867, ticks 26624, elapsed 0, voice: 0 note: 64 velocity 64 event ('note', 26624, 1, 64, 64)
	// Note off skipped, note 55 not found in channels, probably interrupted
	0,((( 0 &4)<<5)|( 48 &0x7f)), ((0 &3)|((59 &0x7e)<<1)),	//# 869, ticks 26624, elapsed 0, voice: 0 note: 48 velocity 59 event ('note', 26624, 1, 48, 59)
	28,((( 1 &4)<<5)|( 72 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 870, ticks 26752, elapsed 28, voice: 1 note: 72 velocity 0 event ('note', 26752, 1, 72, 0)
	// Note off skipped, note 64 not found in channels, probably interrupted
	0,((( 1 &4)<<5)|( 72 &0x7f)), ((1 &3)|((72 &0x7e)<<1)),	//# 872, ticks 26752, elapsed 0, voice: 1 note: 72 velocity 72 event ('note', 26752, 1, 72, 72)
	0,((( 0 &4)<<5)|( 64 &0x7f)), ((0 &3)|((60 &0x7e)<<1)),	//# 873, ticks 26752, elapsed 0, voice: 0 note: 64 velocity 60 event ('note', 26752, 1, 64, 60)
	// Note off skipped, note 48 not found in channels, probably interrupted
	0,((( 0 &4)<<5)|( 52 &0x7f)), ((0 &3)|((62 &0x7e)<<1)),	//# 875, ticks 26752, elapsed 0, voice: 0 note: 52 velocity 62 event ('note', 26752, 1, 52, 62)
	28,((( 1 &4)<<5)|( 72 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 876, ticks 26880, elapsed 28, voice: 1 note: 72 velocity 0 event ('note', 26880, 1, 72, 0)
	// Note off skipped, note 64 not found in channels, probably interrupted
	0,((( 1 &4)<<5)|( 72 &0x7f)), ((1 &3)|((73 &0x7e)<<1)),	//# 878, ticks 26880, elapsed 0, voice: 1 note: 72 velocity 73 event ('note', 26880, 1, 72, 73)
	0,((( 0 &4)<<5)|( 64 &0x7f)), ((0 &3)|((61 &0x7e)<<1)),	//# 879, ticks 26880, elapsed 0, voice: 0 note: 64 velocity 61 event ('note', 26880, 1, 64, 61)
	// Note off skipped, note 52 not found in channels, probably interrupted
	0,((( 0 &4)<<5)|( 55 &0x7f)), ((0 &3)|((64 &0x7e)<<1)),	//# 881, ticks 26880, elapsed 0, voice: 0 note: 55 velocity 64 event ('note', 26880, 1, 55, 64)
	28,((( 0 &4)<<5)|( 55 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 882, ticks 27008, elapsed 28, voice: 0 note: 55 velocity 0 event ('note', 27008, 1, 55, 0)
	0,((( 0 &4)<<5)|( 52 &0x7f)), ((0 &3)|((60 &0x7e)<<1)),	//# 883, ticks 27008, elapsed 0, voice: 0 note: 52 velocity 60 event ('note', 27008, 1, 52, 60)
	14,((( 1 &4)<<5)|( 72 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 884, ticks 27072, elapsed 14, voice: 1 note: 72 velocity 0 event ('note', 27072, 1, 72, 0)
	0,((( 1 &4)<<5)|( 72 &0x7f)), ((1 &3)|((71 &0x7e)<<1)),	//# 885, ticks 27072, elapsed 0, voice: 1 note: 72 velocity 71 event ('note', 27072, 1, 72, 71)
	// Note off skipped, note 64 not found in channels, probably interrupted
	14,((( 1 &4)<<5)|( 72 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 887, ticks 27136, elapsed 14, voice: 1 note: 72 velocity 0 event ('note', 27136, 1, 72, 0)
	0,((( 1 &4)<<5)|( 72 &0x7f)), ((1 &3)|((71 &0x7e)<<1)),	//# 888, ticks 27136, elapsed 0, voice: 1 note: 72 velocity 71 event ('note', 27136, 1, 72, 71)
	0,((( 0 &4)<<5)|( 62 &0x7f)), ((0 &3)|((58 &0x7e)<<1)),	//# 889, ticks 27136, elapsed 0, voice: 0 note: 62 velocity 58 event ('note', 27136, 1, 62, 58)
	// Note off skipped, note 52 not found in channels, probably interrupted
	0,((( 0 &4)<<5)|( 47 &0x7f)), ((0 &3)|((59 &0x7e)<<1)),	//# 891, ticks 27136, elapsed 0, voice: 0 note: 47 velocity 59 event ('note', 27136, 1, 47, 59)
	28,((( 1 &4)<<5)|( 72 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 892, ticks 27264, elapsed 28, voice: 1 note: 72 velocity 0 event ('note', 27264, 1, 72, 0)
	0,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((71 &0x7e)<<1)),	//# 893, ticks 27264, elapsed 0, voice: 1 note: 71 velocity 71 event ('note', 27264, 1, 71, 71)
	0,((( 0 &4)<<5)|( 47 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 894, ticks 27264, elapsed 0, voice: 0 note: 47 velocity 0 event ('note', 27264, 1, 47, 0)
	0,((( 0 &4)<<5)|( 50 &0x7f)), ((0 &3)|((62 &0x7e)<<1)),	//# 895, ticks 27264, elapsed 0, voice: 0 note: 50 velocity 62 event ('note', 27264, 1, 50, 62)
	// Note off skipped, note 62 not found in channels, probably interrupted
	28,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 897, ticks 27392, elapsed 28, voice: 1 note: 71 velocity 0 event ('note', 27392, 1, 71, 0)
	0,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((75 &0x7e)<<1)),	//# 898, ticks 27392, elapsed 0, voice: 1 note: 71 velocity 75 event ('note', 27392, 1, 71, 75)
	0,((( 0 &4)<<5)|( 62 &0x7f)), ((0 &3)|((60 &0x7e)<<1)),	//# 899, ticks 27392, elapsed 0, voice: 0 note: 62 velocity 60 event ('note', 27392, 1, 62, 60)
	// Note off skipped, note 50 not found in channels, probably interrupted
	0,((( 0 &4)<<5)|( 55 &0x7f)), ((0 &3)|((66 &0x7e)<<1)),	//# 901, ticks 27392, elapsed 0, voice: 0 note: 55 velocity 66 event ('note', 27392, 1, 55, 66)
	28,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 902, ticks 27520, elapsed 28, voice: 1 note: 71 velocity 0 event ('note', 27520, 1, 71, 0)
	0,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((72 &0x7e)<<1)),	//# 903, ticks 27520, elapsed 0, voice: 1 note: 71 velocity 72 event ('note', 27520, 1, 71, 72)
	0,((( 0 &4)<<5)|( 55 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 904, ticks 27520, elapsed 0, voice: 0 note: 55 velocity 0 event ('note', 27520, 1, 55, 0)
	0,((( 0 &4)<<5)|( 50 &0x7f)), ((0 &3)|((58 &0x7e)<<1)),	//# 905, ticks 27520, elapsed 0, voice: 0 note: 50 velocity 58 event ('note', 27520, 1, 50, 58)
	14,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 906, ticks 27584, elapsed 14, voice: 1 note: 71 velocity 0 event ('note', 27584, 1, 71, 0)
	0,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((71 &0x7e)<<1)),	//# 907, ticks 27584, elapsed 0, voice: 1 note: 71 velocity 71 event ('note', 27584, 1, 71, 71)
	// Note off skipped, note 62 not found in channels, probably interrupted
	14,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 909, ticks 27648, elapsed 14, voice: 1 note: 71 velocity 0 event ('note', 27648, 1, 71, 0)
	0,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((71 &0x7e)<<1)),	//# 910, ticks 27648, elapsed 0, voice: 1 note: 71 velocity 71 event ('note', 27648, 1, 71, 71)
	0,((( 0 &4)<<5)|( 61 &0x7f)), ((0 &3)|((58 &0x7e)<<1)),	//# 911, ticks 27648, elapsed 0, voice: 0 note: 61 velocity 58 event ('note', 27648, 1, 61, 58)
	// Note off skipped, note 50 not found in channels, probably interrupted
	0,((( 0 &4)<<5)|( 45 &0x7f)), ((0 &3)|((57 &0x7e)<<1)),	//# 913, ticks 27648, elapsed 0, voice: 0 note: 45 velocity 57 event ('note', 27648, 1, 45, 57)
	28,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 914, ticks 27776, elapsed 28, voice: 1 note: 71 velocity 0 event ('note', 27776, 1, 71, 0)
	0,((( 1 &4)<<5)|( 69 &0x7f)), ((1 &3)|((70 &0x7e)<<1)),	//# 915, ticks 27776, elapsed 0, voice: 1 note: 69 velocity 70 event ('note', 27776, 1, 69, 70)
	0,((( 0 &4)<<5)|( 45 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 916, ticks 27776, elapsed 0, voice: 0 note: 45 velocity 0 event ('note', 27776, 1, 45, 0)
	0,((( 0 &4)<<5)|( 52 &0x7f)), ((0 &3)|((65 &0x7e)<<1)),	//# 917, ticks 27776, elapsed 0, voice: 0 note: 52 velocity 65 event ('note', 27776, 1, 52, 65)
	// Note off skipped, note 61 not found in channels, probably interrupted
	28,((( 1 &4)<<5)|( 69 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 919, ticks 27904, elapsed 28, voice: 1 note: 69 velocity 0 event ('note', 27904, 1, 69, 0)
	0,((( 1 &4)<<5)|( 69 &0x7f)), ((1 &3)|((69 &0x7e)<<1)),	//# 920, ticks 27904, elapsed 0, voice: 1 note: 69 velocity 69 event ('note', 27904, 1, 69, 69)
	0,((( 0 &4)<<5)|( 61 &0x7f)), ((0 &3)|((61 &0x7e)<<1)),	//# 921, ticks 27904, elapsed 0, voice: 0 note: 61 velocity 61 event ('note', 27904, 1, 61, 61)
	// Note off skipped, note 52 not found in channels, probably interrupted
	0,((( 0 &4)<<5)|( 57 &0x7f)), ((0 &3)|((60 &0x7e)<<1)),	//# 923, ticks 27904, elapsed 0, voice: 0 note: 57 velocity 60 event ('note', 27904, 1, 57, 60)
	28,((( 1 &4)<<5)|( 69 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 924, ticks 28032, elapsed 28, voice: 1 note: 69 velocity 0 event ('note', 28032, 1, 69, 0)
	0,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((74 &0x7e)<<1)),	//# 925, ticks 28032, elapsed 0, voice: 1 note: 71 velocity 74 event ('note', 28032, 1, 71, 74)
	0,((( 0 &4)<<5)|( 57 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 926, ticks 28032, elapsed 0, voice: 0 note: 57 velocity 0 event ('note', 28032, 1, 57, 0)
	0,((( 0 &4)<<5)|( 52 &0x7f)), ((0 &3)|((59 &0x7e)<<1)),	//# 927, ticks 28032, elapsed 0, voice: 0 note: 52 velocity 59 event ('note', 28032, 1, 52, 59)
	// Note off skipped, note 61 not found in channels, probably interrupted
	28,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 929, ticks 28160, elapsed 28, voice: 1 note: 71 velocity 0 event ('note', 28160, 1, 71, 0)
	0,((( 1 &4)<<5)|( 69 &0x7f)), ((1 &3)|((69 &0x7e)<<1)),	//# 930, ticks 28160, elapsed 0, voice: 1 note: 69 velocity 69 event ('note', 28160, 1, 69, 69)
	0,((( 0 &4)<<5)|( 62 &0x7f)), ((0 &3)|((62 &0x7e)<<1)),	//# 931, ticks 28160, elapsed 0, voice: 0 note: 62 velocity 62 event ('note', 28160, 1, 62, 62)
	// Note off skipped, note 52 not found in channels, probably interrupted
	0,((( 0 &4)<<5)|( 50 &0x7f)), ((0 &3)|((60 &0x7e)<<1)),	//# 933, ticks 28160, elapsed 0, voice: 0 note: 50 velocity 60 event ('note', 28160, 1, 50, 60)
	28,((( 0 &4)<<5)|( 50 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 934, ticks 28288, elapsed 28, voice: 0 note: 50 velocity 0 event ('note', 28288, 1, 50, 0)
	0,((( 0 &4)<<5)|( 54 &0x7f)), ((0 &3)|((62 &0x7e)<<1)),	//# 935, ticks 28288, elapsed 0, voice: 0 note: 54 velocity 62 event ('note', 28288, 1, 54, 62)
	28,((( 1 &4)<<5)|( 69 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 936, ticks 28416, elapsed 28, voice: 1 note: 69 velocity 0 event ('note', 28416, 1, 69, 0)
	// Note off skipped, note 62 not found in channels, probably interrupted
	0,((( 1 &4)<<5)|( 74 &0x7f)), ((1 &3)|((76 &0x7e)<<1)),	//# 938, ticks 28416, elapsed 0, voice: 1 note: 74 velocity 76 event ('note', 28416, 1, 74, 76)
	0,((( 0 &4)<<5)|( 66 &0x7f)), ((0 &3)|((65 &0x7e)<<1)),	//# 939, ticks 28416, elapsed 0, voice: 0 note: 66 velocity 65 event ('note', 28416, 1, 66, 65)
	// Note off skipped, note 54 not found in channels, probably interrupted
	0,((( 0 &4)<<5)|( 57 &0x7f)), ((0 &3)|((64 &0x7e)<<1)),	//# 941, ticks 28416, elapsed 0, voice: 0 note: 57 velocity 64 event ('note', 28416, 1, 57, 64)
	28,((( 0 &4)<<5)|( 57 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 942, ticks 28544, elapsed 28, voice: 0 note: 57 velocity 0 event ('note', 28544, 1, 57, 0)
	0,((( 0 &4)<<5)|( 54 &0x7f)), ((0 &3)|((57 &0x7e)<<1)),	//# 943, ticks 28544, elapsed 0, voice: 0 note: 54 velocity 57 event ('note', 28544, 1, 54, 57)
	28,((( 1 &4)<<5)|( 74 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 944, ticks 28672, elapsed 28, voice: 1 note: 74 velocity 0 event ('note', 28672, 1, 74, 0)
	// Note off skipped, note 66 not found in channels, probably interrupted
	0,((( 1 &4)<<5)|( 67 &0x7f)), ((1 &3)|((70 &0x7e)<<1)),	//# 946, ticks 28672, elapsed 0, voice: 1 note: 67 velocity 70 event ('note', 28672, 1, 67, 70)
	0,((( 0 &4)<<5)|( 71 &0x7f)), ((0 &3)|((70 &0x7e)<<1)),	//# 947, ticks 28672, elapsed 0, voice: 0 note: 71 velocity 70 event ('note', 28672, 1, 71, 70)
	// Note off skipped, note 54 not found in channels, probably interrupted
	0,((( 0 &4)<<5)|( 43 &0x7f)), ((0 &3)|((59 &0x7e)<<1)),	//# 949, ticks 28672, elapsed 0, voice: 0 note: 43 velocity 59 event ('note', 28672, 1, 43, 59)
	28,((( 1 &4)<<5)|( 67 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 950, ticks 28800, elapsed 28, voice: 1 note: 67 velocity 0 event ('note', 28800, 1, 67, 0)
	// Note off skipped, note 71 not found in channels, probably interrupted
	0,((( 1 &4)<<5)|( 67 &0x7f)), ((1 &3)|((69 &0x7e)<<1)),	//# 952, ticks 28800, elapsed 0, voice: 1 note: 67 velocity 69 event ('note', 28800, 1, 67, 69)
	0,((( 0 &4)<<5)|( 71 &0x7f)), ((0 &3)|((69 &0x7e)<<1)),	//# 953, ticks 28800, elapsed 0, voice: 0 note: 71 velocity 69 event ('note', 28800, 1, 71, 69)
	28,((( 1 &4)<<5)|( 67 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 954, ticks 28928, elapsed 28, voice: 1 note: 67 velocity 0 event ('note', 28928, 1, 67, 0)
	0,((( 0 &4)<<5)|( 71 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 955, ticks 28928, elapsed 0, voice: 0 note: 71 velocity 0 event ('note', 28928, 1, 71, 0)
	0,((( 0 &4)<<5)|( 67 &0x7f)), ((0 &3)|((71 &0x7e)<<1)),	//# 956, ticks 28928, elapsed 0, voice: 0 note: 67 velocity 71 event ('note', 28928, 1, 67, 71)
	0,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((71 &0x7e)<<1)),	//# 957, ticks 28928, elapsed 0, voice: 1 note: 71 velocity 71 event ('note', 28928, 1, 71, 71)
	// Note off skipped, note 43 not found in channels, probably interrupted
	28,((( 0 &4)<<5)|( 50 &0x7f)), ((0 &3)|((64 &0x7e)<<1)),	//# 959, ticks 29056, elapsed 28, voice: 0 note: 50 velocity 64 event ('note', 29056, 1, 50, 64)
	// Note off skipped, note 67 not found in channels, probably interrupted
	28,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 961, ticks 29184, elapsed 28, voice: 1 note: 71 velocity 0 event ('note', 29184, 1, 71, 0)
	0,((( 1 &4)<<5)|( 67 &0x7f)), ((1 &3)|((73 &0x7e)<<1)),	//# 962, ticks 29184, elapsed 0, voice: 1 note: 67 velocity 73 event ('note', 29184, 1, 67, 73)
	0,((( 0 &4)<<5)|( 71 &0x7f)), ((0 &3)|((73 &0x7e)<<1)),	//# 963, ticks 29184, elapsed 0, voice: 0 note: 71 velocity 73 event ('note', 29184, 1, 71, 73)
	// Note off skipped, note 50 not found in channels, probably interrupted
	0,((( 0 &4)<<5)|( 55 &0x7f)), ((0 &3)|((63 &0x7e)<<1)),	//# 965, ticks 29184, elapsed 0, voice: 0 note: 55 velocity 63 event ('note', 29184, 1, 55, 63)
	28,((( 1 &4)<<5)|( 67 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 966, ticks 29312, elapsed 28, voice: 1 note: 67 velocity 0 event ('note', 29312, 1, 67, 0)
	// Note off skipped, note 71 not found in channels, probably interrupted
	0,((( 1 &4)<<5)|( 67 &0x7f)), ((1 &3)|((71 &0x7e)<<1)),	//# 968, ticks 29312, elapsed 0, voice: 1 note: 67 velocity 71 event ('note', 29312, 1, 67, 71)
	0,((( 0 &4)<<5)|( 71 &0x7f)), ((0 &3)|((71 &0x7e)<<1)),	//# 969, ticks 29312, elapsed 0, voice: 0 note: 71 velocity 71 event ('note', 29312, 1, 71, 71)
	28,((( 1 &4)<<5)|( 67 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 970, ticks 29440, elapsed 28, voice: 1 note: 67 velocity 0 event ('note', 29440, 1, 67, 0)
	0,((( 0 &4)<<5)|( 71 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 971, ticks 29440, elapsed 0, voice: 0 note: 71 velocity 0 event ('note', 29440, 1, 71, 0)
	0,((( 0 &4)<<5)|( 67 &0x7f)), ((0 &3)|((72 &0x7e)<<1)),	//# 972, ticks 29440, elapsed 0, voice: 0 note: 67 velocity 72 event ('note', 29440, 1, 67, 72)
	0,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((72 &0x7e)<<1)),	//# 973, ticks 29440, elapsed 0, voice: 1 note: 71 velocity 72 event ('note', 29440, 1, 71, 72)
	// Note off skipped, note 55 not found in channels, probably interrupted
	28,((( 0 &4)<<5)|( 50 &0x7f)), ((0 &3)|((58 &0x7e)<<1)),	//# 975, ticks 29568, elapsed 28, voice: 0 note: 50 velocity 58 event ('note', 29568, 1, 50, 58)
	// Note off skipped, note 67 not found in channels, probably interrupted
	28,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 977, ticks 29696, elapsed 28, voice: 1 note: 71 velocity 0 event ('note', 29696, 1, 71, 0)
	0,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((70 &0x7e)<<1)),	//# 978, ticks 29696, elapsed 0, voice: 1 note: 71 velocity 70 event ('note', 29696, 1, 71, 70)
	0,((( 0 &4)<<5)|( 67 &0x7f)), ((0 &3)|((65 &0x7e)<<1)),	//# 979, ticks 29696, elapsed 0, voice: 0 note: 67 velocity 65 event ('note', 29696, 1, 67, 65)
	// Note off skipped, note 50 not found in channels, probably interrupted
	0,((( 0 &4)<<5)|( 43 &0x7f)), ((0 &3)|((56 &0x7e)<<1)),	//# 981, ticks 29696, elapsed 0, voice: 0 note: 43 velocity 56 event ('note', 29696, 1, 43, 56)
	28,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 982, ticks 29824, elapsed 28, voice: 1 note: 71 velocity 0 event ('note', 29824, 1, 71, 0)
	0,((( 1 &4)<<5)|( 74 &0x7f)), ((1 &3)|((74 &0x7e)<<1)),	//# 983, ticks 29824, elapsed 0, voice: 1 note: 74 velocity 74 event ('note', 29824, 1, 74, 74)
	0,((( 0 &4)<<5)|( 43 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 984, ticks 29824, elapsed 0, voice: 0 note: 43 velocity 0 event ('note', 29824, 1, 43, 0)
	0,((( 0 &4)<<5)|( 50 &0x7f)), ((0 &3)|((64 &0x7e)<<1)),	//# 985, ticks 29824, elapsed 0, voice: 0 note: 50 velocity 64 event ('note', 29824, 1, 50, 64)
	// Note off skipped, note 67 not found in channels, probably interrupted
	28,((( 1 &4)<<5)|( 74 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 987, ticks 29952, elapsed 28, voice: 1 note: 74 velocity 0 event ('note', 29952, 1, 74, 0)
	0,((( 1 &4)<<5)|( 67 &0x7f)), ((1 &3)|((64 &0x7e)<<1)),	//# 988, ticks 29952, elapsed 0, voice: 1 note: 67 velocity 64 event ('note', 29952, 1, 67, 64)
	0,((( 0 &4)<<5)|( 64 &0x7f)), ((0 &3)|((59 &0x7e)<<1)),	//# 989, ticks 29952, elapsed 0, voice: 0 note: 64 velocity 59 event ('note', 29952, 1, 64, 59)
	// Note off skipped, note 50 not found in channels, probably interrupted
	0,((( 0 &4)<<5)|( 48 &0x7f)), ((0 &3)|((62 &0x7e)<<1)),	//# 991, ticks 29952, elapsed 0, voice: 0 note: 48 velocity 62 event ('note', 29952, 1, 48, 62)
	0,((( 0 &4)<<5)|( 52 &0x7f)), ((0 &3)|((62 &0x7e)<<1)),	//# 992, ticks 29952, elapsed 0, voice: 0 note: 52 velocity 62 event ('note', 29952, 1, 52, 62)
	42,((( 1 &4)<<5)|( 67 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 993, ticks 30144, elapsed 42, voice: 1 note: 67 velocity 0 event ('note', 30144, 1, 67, 0)
	0,((( 1 &4)<<5)|( 69 &0x7f)), ((1 &3)|((74 &0x7e)<<1)),	//# 994, ticks 30144, elapsed 0, voice: 1 note: 69 velocity 74 event ('note', 30144, 1, 69, 74)
	// Note off skipped, note 64 not found in channels, probably interrupted
	14,((( 1 &4)<<5)|( 69 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 996, ticks 30208, elapsed 14, voice: 1 note: 69 velocity 0 event ('note', 30208, 1, 69, 0)
	0,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((71 &0x7e)<<1)),	//# 997, ticks 30208, elapsed 0, voice: 1 note: 71 velocity 71 event ('note', 30208, 1, 71, 71)
	0,((( 0 &4)<<5)|( 62 &0x7f)), ((0 &3)|((59 &0x7e)<<1)),	//# 998, ticks 30208, elapsed 0, voice: 0 note: 62 velocity 59 event ('note', 30208, 1, 62, 59)
	// Note off skipped, note 48 not found in channels, probably interrupted
	// Note off skipped, note 52 not found in channels, probably interrupted
	0,((( 0 &4)<<5)|( 43 &0x7f)), ((0 &3)|((58 &0x7e)<<1)),	//# 1001, ticks 30208, elapsed 0, voice: 0 note: 43 velocity 58 event ('note', 30208, 1, 43, 58)
	28,((( 0 &4)<<5)|( 43 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 1002, ticks 30336, elapsed 28, voice: 0 note: 43 velocity 0 event ('note', 30336, 1, 43, 0)
	0,((( 0 &4)<<5)|( 50 &0x7f)), ((0 &3)|((63 &0x7e)<<1)),	//# 1003, ticks 30336, elapsed 0, voice: 0 note: 50 velocity 63 event ('note', 30336, 1, 50, 63)
	28,((( 0 &4)<<5)|( 50 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 1004, ticks 30464, elapsed 28, voice: 0 note: 50 velocity 0 event ('note', 30464, 1, 50, 0)
	0,((( 0 &4)<<5)|( 55 &0x7f)), ((0 &3)|((61 &0x7e)<<1)),	//# 1005, ticks 30464, elapsed 0, voice: 0 note: 55 velocity 61 event ('note', 30464, 1, 55, 61)
	57,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 1006, ticks 30720, elapsed 57, voice: 1 note: 71 velocity 0 event ('note', 30720, 1, 71, 0)
	// Note off skipped, note 62 not found in channels, probably interrupted
	0,((( 1 &4)<<5)|( 72 &0x7f)), ((1 &3)|((74 &0x7e)<<1)),	//# 1008, ticks 30720, elapsed 0, voice: 1 note: 72 velocity 74 event ('note', 30720, 1, 72, 74)
	0,((( 0 &4)<<5)|( 64 &0x7f)), ((0 &3)|((63 &0x7e)<<1)),	//# 1009, ticks 30720, elapsed 0, voice: 0 note: 64 velocity 63 event ('note', 30720, 1, 64, 63)
	// Note off skipped, note 55 not found in channels, probably interrupted
	0,((( 0 &4)<<5)|( 48 &0x7f)), ((0 &3)|((57 &0x7e)<<1)),	//# 1011, ticks 30720, elapsed 0, voice: 0 note: 48 velocity 57 event ('note', 30720, 1, 48, 57)
	28,((( 1 &4)<<5)|( 72 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 1012, ticks 30848, elapsed 28, voice: 1 note: 72 velocity 0 event ('note', 30848, 1, 72, 0)
	// Note off skipped, note 64 not found in channels, probably interrupted
	0,((( 1 &4)<<5)|( 72 &0x7f)), ((1 &3)|((69 &0x7e)<<1)),	//# 1014, ticks 30848, elapsed 0, voice: 1 note: 72 velocity 69 event ('note', 30848, 1, 72, 69)
	0,((( 0 &4)<<5)|( 64 &0x7f)), ((0 &3)|((62 &0x7e)<<1)),	//# 1015, ticks 30848, elapsed 0, voice: 0 note: 64 velocity 62 event ('note', 30848, 1, 64, 62)
	// Note off skipped, note 48 not found in channels, probably interrupted
	0,((( 0 &4)<<5)|( 52 &0x7f)), ((0 &3)|((64 &0x7e)<<1)),	//# 1017, ticks 30848, elapsed 0, voice: 0 note: 52 velocity 64 event ('note', 30848, 1, 52, 64)
	28,((( 1 &4)<<5)|( 72 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 1018, ticks 30976, elapsed 28, voice: 1 note: 72 velocity 0 event ('note', 30976, 1, 72, 0)
	// Note off skipped, note 64 not found in channels, probably interrupted
	0,((( 1 &4)<<5)|( 72 &0x7f)), ((1 &3)|((71 &0x7e)<<1)),	//# 1020, ticks 30976, elapsed 0, voice: 1 note: 72 velocity 71 event ('note', 30976, 1, 72, 71)
	0,((( 0 &4)<<5)|( 64 &0x7f)), ((0 &3)|((59 &0x7e)<<1)),	//# 1021, ticks 30976, elapsed 0, voice: 0 note: 64 velocity 59 event ('note', 30976, 1, 64, 59)
	// Note off skipped, note 52 not found in channels, probably interrupted
	0,((( 0 &4)<<5)|( 55 &0x7f)), ((0 &3)|((59 &0x7e)<<1)),	//# 1023, ticks 30976, elapsed 0, voice: 0 note: 55 velocity 59 event ('note', 30976, 1, 55, 59)
	28,((( 0 &4)<<5)|( 55 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 1024, ticks 31104, elapsed 28, voice: 0 note: 55 velocity 0 event ('note', 31104, 1, 55, 0)
	0,((( 0 &4)<<5)|( 52 &0x7f)), ((0 &3)|((62 &0x7e)<<1)),	//# 1025, ticks 31104, elapsed 0, voice: 0 note: 52 velocity 62 event ('note', 31104, 1, 52, 62)
	14,((( 1 &4)<<5)|( 72 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 1026, ticks 31168, elapsed 14, voice: 1 note: 72 velocity 0 event ('note', 31168, 1, 72, 0)
	0,((( 1 &4)<<5)|( 72 &0x7f)), ((1 &3)|((70 &0x7e)<<1)),	//# 1027, ticks 31168, elapsed 0, voice: 1 note: 72 velocity 70 event ('note', 31168, 1, 72, 70)
	// Note off skipped, note 64 not found in channels, probably interrupted
	14,((( 1 &4)<<5)|( 72 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 1029, ticks 31232, elapsed 14, voice: 1 note: 72 velocity 0 event ('note', 31232, 1, 72, 0)
	0,((( 1 &4)<<5)|( 72 &0x7f)), ((1 &3)|((72 &0x7e)<<1)),	//# 1030, ticks 31232, elapsed 0, voice: 1 note: 72 velocity 72 event ('note', 31232, 1, 72, 72)
	0,((( 0 &4)<<5)|( 62 &0x7f)), ((0 &3)|((59 &0x7e)<<1)),	//# 1031, ticks 31232, elapsed 0, voice: 0 note: 62 velocity 59 event ('note', 31232, 1, 62, 59)
	// Note off skipped, note 52 not found in channels, probably interrupted
	0,((( 0 &4)<<5)|( 47 &0x7f)), ((0 &3)|((58 &0x7e)<<1)),	//# 1033, ticks 31232, elapsed 0, voice: 0 note: 47 velocity 58 event ('note', 31232, 1, 47, 58)
	28,((( 1 &4)<<5)|( 72 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 1034, ticks 31360, elapsed 28, voice: 1 note: 72 velocity 0 event ('note', 31360, 1, 72, 0)
	0,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((69 &0x7e)<<1)),	//# 1035, ticks 31360, elapsed 0, voice: 1 note: 71 velocity 69 event ('note', 31360, 1, 71, 69)
	0,((( 0 &4)<<5)|( 47 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 1036, ticks 31360, elapsed 0, voice: 0 note: 47 velocity 0 event ('note', 31360, 1, 47, 0)
	0,((( 0 &4)<<5)|( 50 &0x7f)), ((0 &3)|((62 &0x7e)<<1)),	//# 1037, ticks 31360, elapsed 0, voice: 0 note: 50 velocity 62 event ('note', 31360, 1, 50, 62)
	// Note off skipped, note 62 not found in channels, probably interrupted
	28,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 1039, ticks 31488, elapsed 28, voice: 1 note: 71 velocity 0 event ('note', 31488, 1, 71, 0)
	0,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((69 &0x7e)<<1)),	//# 1040, ticks 31488, elapsed 0, voice: 1 note: 71 velocity 69 event ('note', 31488, 1, 71, 69)
	0,((( 0 &4)<<5)|( 62 &0x7f)), ((0 &3)|((60 &0x7e)<<1)),	//# 1041, ticks 31488, elapsed 0, voice: 0 note: 62 velocity 60 event ('note', 31488, 1, 62, 60)
	// Note off skipped, note 50 not found in channels, probably interrupted
	0,((( 0 &4)<<5)|( 55 &0x7f)), ((0 &3)|((60 &0x7e)<<1)),	//# 1043, ticks 31488, elapsed 0, voice: 0 note: 55 velocity 60 event ('note', 31488, 1, 55, 60)
	28,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 1044, ticks 31616, elapsed 28, voice: 1 note: 71 velocity 0 event ('note', 31616, 1, 71, 0)
	0,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((71 &0x7e)<<1)),	//# 1045, ticks 31616, elapsed 0, voice: 1 note: 71 velocity 71 event ('note', 31616, 1, 71, 71)
	0,((( 0 &4)<<5)|( 55 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 1046, ticks 31616, elapsed 0, voice: 0 note: 55 velocity 0 event ('note', 31616, 1, 55, 0)
	0,((( 0 &4)<<5)|( 50 &0x7f)), ((0 &3)|((59 &0x7e)<<1)),	//# 1047, ticks 31616, elapsed 0, voice: 0 note: 50 velocity 59 event ('note', 31616, 1, 50, 59)
	14,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 1048, ticks 31680, elapsed 14, voice: 1 note: 71 velocity 0 event ('note', 31680, 1, 71, 0)
	0,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((70 &0x7e)<<1)),	//# 1049, ticks 31680, elapsed 0, voice: 1 note: 71 velocity 70 event ('note', 31680, 1, 71, 70)
	// Note off skipped, note 62 not found in channels, probably interrupted
	14,((( 1 &4)<<5)|( 71 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 1051, ticks 31744, elapsed 14, voice: 1 note: 71 velocity 0 event ('note', 31744, 1, 71, 0)
	0,((( 1 &4)<<5)|( 74 &0x7f)), ((1 &3)|((72 &0x7e)<<1)),	//# 1052, ticks 31744, elapsed 0, voice: 1 note: 74 velocity 72 event ('note', 31744, 1, 74, 72)
	0,((( 0 &4)<<5)|( 66 &0x7f)), ((0 &3)|((65 &0x7e)<<1)),	//# 1053, ticks 31744, elapsed 0, voice: 0 note: 66 velocity 65 event ('note', 31744, 1, 66, 65)
	// Note off skipped, note 50 not found in channels, probably interrupted
	0,((( 0 &4)<<5)|( 45 &0x7f)), ((0 &3)|((59 &0x7e)<<1)),	//# 1055, ticks 31744, elapsed 0, voice: 0 note: 45 velocity 59 event ('note', 31744, 1, 45, 59)
	28,((( 1 &4)<<5)|( 74 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 1056, ticks 31872, elapsed 28, voice: 1 note: 74 velocity 0 event ('note', 31872, 1, 74, 0)
	0,((( 1 &4)<<5)|( 74 &0x7f)), ((1 &3)|((70 &0x7e)<<1)),	//# 1057, ticks 31872, elapsed 0, voice: 1 note: 74 velocity 70 event ('note', 31872, 1, 74, 70)
	0,((( 0 &4)<<5)|( 45 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 1058, ticks 31872, elapsed 0, voice: 0 note: 45 velocity 0 event ('note', 31872, 1, 45, 0)
	0,((( 0 &4)<<5)|( 50 &0x7f)), ((0 &3)|((65 &0x7e)<<1)),	//# 1059, ticks 31872, elapsed 0, voice: 0 note: 50 velocity 65 event ('note', 31872, 1, 50, 65)
	// Note off skipped, note 66 not found in channels, probably interrupted
	28,((( 1 &4)<<5)|( 74 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 1061, ticks 32000, elapsed 28, voice: 1 note: 74 velocity 0 event ('note', 32000, 1, 74, 0)
	0,((( 1 &4)<<5)|( 72 &0x7f)), ((1 &3)|((69 &0x7e)<<1)),	//# 1062, ticks 32000, elapsed 0, voice: 1 note: 72 velocity 69 event ('note', 32000, 1, 72, 69)
	0,((( 0 &4)<<5)|( 62 &0x7f)), ((0 &3)|((59 &0x7e)<<1)),	//# 1063, ticks 32000, elapsed 0, voice: 0 note: 62 velocity 59 event ('note', 32000, 1, 62, 59)
	// Note off skipped, note 50 not found in channels, probably interrupted
	0,((( 0 &4)<<5)|( 54 &0x7f)), ((0 &3)|((63 &0x7e)<<1)),	//# 1065, ticks 32000, elapsed 0, voice: 0 note: 54 velocity 63 event ('note', 32000, 1, 54, 63)
	28,((( 1 &4)<<5)|( 72 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 1066, ticks 32128, elapsed 28, voice: 1 note: 72 velocity 0 event ('note', 32128, 1, 72, 0)
	0,((( 1 &4)<<5)|( 69 &0x7f)), ((1 &3)|((67 &0x7e)<<1)),	//# 1067, ticks 32128, elapsed 0, voice: 1 note: 69 velocity 67 event ('note', 32128, 1, 69, 67)
	0,((( 0 &4)<<5)|( 54 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 1068, ticks 32128, elapsed 0, voice: 0 note: 54 velocity 0 event ('note', 32128, 1, 54, 0)
	0,((( 0 &4)<<5)|( 50 &0x7f)), ((0 &3)|((60 &0x7e)<<1)),	//# 1069, ticks 32128, elapsed 0, voice: 0 note: 50 velocity 60 event ('note', 32128, 1, 50, 60)
	// Note off skipped, note 62 not found in channels, probably interrupted
	28,((( 1 &4)<<5)|( 69 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 1071, ticks 32256, elapsed 28, voice: 1 note: 69 velocity 0 event ('note', 32256, 1, 69, 0)
	0,((( 1 &4)<<5)|( 67 &0x7f)), ((1 &3)|((69 &0x7e)<<1)),	//# 1072, ticks 32256, elapsed 0, voice: 1 note: 67 velocity 69 event ('note', 32256, 1, 67, 69)
	0,((( 0 &4)<<5)|( 59 &0x7f)), ((0 &3)|((63 &0x7e)<<1)),	//# 1073, ticks 32256, elapsed 0, voice: 0 note: 59 velocity 63 event ('note', 32256, 1, 59, 63)
	// Note off skipped, note 50 not found in channels, probably interrupted
	0,((( 0 &4)<<5)|( 43 &0x7f)), ((0 &3)|((60 &0x7e)<<1)),	//# 1075, ticks 32256, elapsed 0, voice: 0 note: 43 velocity 60 event ('note', 32256, 1, 43, 60)
	28,((( 0 &4)<<5)|( 43 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 1076, ticks 32384, elapsed 28, voice: 0 note: 43 velocity 0 event ('note', 32384, 1, 43, 0)
	0,((( 0 &4)<<5)|( 50 &0x7f)), ((0 &3)|((61 &0x7e)<<1)),	//# 1077, ticks 32384, elapsed 0, voice: 0 note: 50 velocity 61 event ('note', 32384, 1, 50, 61)
	28,((( 0 &4)<<5)|( 50 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 1078, ticks 32512, elapsed 28, voice: 0 note: 50 velocity 0 event ('note', 32512, 1, 50, 0)
	0,((( 0 &4)<<5)|( 55 &0x7f)), ((0 &3)|((63 &0x7e)<<1)),	//# 1079, ticks 32512, elapsed 0, voice: 0 note: 55 velocity 63 event ('note', 32512, 1, 55, 63)
	57,((( 1 &4)<<5)|( 67 &0x7f)), ((1 &3)|((0 &0x7e)<<1)),	//# 1080, ticks 32768, elapsed 57, voice: 1 note: 67 velocity 0 event ('note', 32768, 1, 67, 0)
	// Note off skipped, note 59 not found in channels, probably interrupted
	0,((( 0 &4)<<5)|( 55 &0x7f)), ((0 &3)|((0 &0x7e)<<1)),	//# 1082, ticks 32768, elapsed 0, voice: 0 note: 55 velocity 0 event ('note', 32768, 1, 55, 0)
0xff };

