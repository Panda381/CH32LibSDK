
// ****************************************************************************
//
//                                 Game levels
//
// ****************************************************************************

//   x = grass (empty)
//   # = wall
//   ! or | = next row
//   space or _ or - = floor
//   $ or b = box
//   * or B = box on mark
//   . = mark
//   @ or p = player
//   + or P = player on mark

#include "../include.h"

// selected level
int Level;		// current level 0..
const char* LevDef;	// current level definition
const char* LevSolve;	// current level solve

const char* const Levels[] = {

// ===== MiniCosmos collection, (c) Aymeric du Peloux

	// 1
	"xx#####x!"
	"###   #x!"
	"# $ # ##!"
	"# #  . #!"
	"#    # #!"
	"## #   #!"
	"x#@  ###!"
	"x#####xx",
	"",//"uuluuRldd3ruruullDDullddrRlddrruUluR",

	// 2
	"xx#####x!"
	"###   #x!"
	"# $ # ##!"
	"# #  . #!"
	"#    # #!"
	"##$#.  #!"
	"x#@  ###!"
	"x#####xx",
	"",//"rruu3luurlddrrurru2(ulldd)rru3rddlldlludrruuluullddrrurd",

	// 3
	"xx#####x!"
	"###   #x!"
	"# $ # ##!"
	"# #  . #!"
	"# .  # #!"
	"##$#.$ #!"
	"x#@  ###!"
	"x#####xx",
	"",//"rruu3luurldd3rddlludrr3urrddlruuluulldllddrddrruudd2(lluur)rdrdl",

	// 4
	"xxxx####!"
	"#####  #!"
	"#   $  #!"
	"#  .#  #!"
	"## ## ##!"
	"#      #!"
	"# @#   #!"
	"#  #####!"
	"####xxxx",
	"",//"4urRll3d3ruuruul3Duu3l3drrdrru3Lrr3u3lddDlddr3Ud3r3u4ldR",

	// 5
	"xxxx####!"
	"#####  #!"
	"#   $  #!"
	"# *.#  #!"
	"## ## ##!"
	"#      #!"
	"# @#   #!"
	"#  #####!"
	"####xxxx",
	"",//"3ururldldd3ruuruul3duulldllu3rll3drrdrru3lrruuruul3duu3l3dlddr3udrrdrru3lrr3u4ldrddlddr3u",

	// 6
	"xxxx####!"
	"#####  #!"
	"#   *  #!"
	"# *.#  #!"
	"## ## ##!"
	"# $    #!"
	"# @#   #!"
	"#  #####!"
	"####xxxx",
	"",//"luruururldlddrrdrru3lrruuruul3duulldllu3rll3dlddr3udrrdrru3lrruuruuld4ldrddlddr3ud3ruurul",

	// 7
	"x#####xx!"
	"x#   ##x!"
	"## #$ ##!"
	"# $    #!"
	"#. .#  #!"
	"### @ ##!"
	"xx# # #x!"
	"xx#   #x!"
	"xx#####x",
	"",//"lullu3rlluurrdrdllruullddldrurddrruru3lruullddrdlrdrrddlluu",

	// 8
	"x#####xx!"
	"x#   ##x!"
	"##.#$ ##!"
	"# $    #!"
	"#. .#$ #!"
	"### @ ##!"
	"xx# # #x!"
	"xx#   #x!"
	"xx#####x",
	"",//"luurrddllullu3rlluurrdrdllddrrurulluullddldr3urrddlruulldd3rddllddrr3uru3ldlu3r4dlluu",

	// 9
	"x#####xx!"
	"x#   #xx!"
	"##$# ###!"
	"#   $@ #!"
	"# #  # #!"
	"# #. . #!"
	"#   ####!"
	"#####xxx",
	"",//"rdd3luuruulldurr4drruulrdd3ldll3uruurr3durrddll4ullddrluurr3du3l3drruruuld",

	// 10
	"x#####xx!"
	"x#   #xx!"
	"##$# ###!"
	"#  .$@ #!"
	"# #  # #!"
	"# #..$ #!"
	"#   ####!"
	"#####xxx",
	"",//"rddllulur3l3drrur4ulldurr4drruulrdd3ldll3uruurr3d3ullddrll3drruuddll3uruu2(rrdd)llrruulld",

	// 11
	"x#####xxx!"
	"##   ###x!"
	"# . .  #x!"
	"# # ## ##!"
	"#    $$@#!"
	"### #   #!"
	"xx#   ###!"
	"xx#####xx",
	"",//"dlullrddll3udlluururrdrrdullulldrrlddrrdrru3lrddll3udlluururrdldd3ruul",

	// 12
	"x#####xxx!"
	"##   ###x!"
	"# . . .#x!"
	"# # ## ##!"
	"#    $$@#!"
	"### # $ #!"
	"xx#   ###!"
	"xx#####xx",
	"",//"dlu3lddrrudll4ullddrluu5rddlddll3udlluu3rl4drruulrddll3udlluururrdldd4rdl3ulrdd3lddrrudlluurrdruu",

	// 13
	"xxxx####x!"
	"x####  #x!"
	"## $   #x!"
	"#  # #$#x!"
	"#.@.   ##!"
	"## # #  #!"
	"x#      #!"
	"x#  #####!"
	"x####xxxx",
	"",//"rruurr3drd3luulluurr4dldl3urruulldld3ruurur4drd4ldluudrruulluu4rddll",

	// 14
	"xxxx####x!"
	"x####  #x!"
	"## $   #x!"
	"#  # #$#x!"
	"#.@..  ##!"
	"## # #  #!"
	"x#   $  #!"
	"x#  #####!"
	"x####xxxx",
	"",//"4rddll4urrdd4luurr4dldl3u4rdrd3l4ulldld3rddldl3urruulldldrrluu3rur4drd4ldluudrruulluu4rddllrruulld",

	// 15
	"xxx####x!"
	"####  #x!"
	"# $   #x!"
	"#  .# ##!"
	"## #.  #!"
	"# @  $ #!"
	"#   ####!"
	"#####xxx",
	"",//"uulurrl3drrurrd3ldl3urururddulldldd4ruluulldllu3rur3drd3ldluud3r3u4ldr",

	// 16
	"xxx####x!"
	"####  #x!"
	"# $ $ #x!"
	"#  .# ##!"
	"## #.  #!"
	"# @  $ #!"
	"#.  ####!"
	"#####xxx",
	"",//"rrurrd3ldlluru3(ur)3dldlrurrdllr3ulldldduulu3rur3dldldluudrruruu4ldrddrrurrd3ldl3ulu3rurddu3l3d4rul",

	// 17
	"xxxx#####x!"
	"xxx##   ##!"
	"xx## .#  #!"
	"x##   @  #!"
	"##    #  #!"
	"#  $ #####!"
	"# * ##xxxx!"
	"#  ##xxxxx!"
	"####xxxxxx",
	"",//"ld3ldlddrurudllururlddrurudllururrdluldrr3urrddlldldluldruurdru",

	// 18
	"xxxx#####x!"
	"xxx##   ##!"
	"xx## .#  #!"
	"x##   @  #!"
	"##  * #  #!"
	"#  $ #####!"
	"# * ##xxxx!"
	"#  ##xxxxx!"
	"####xxxxxx",
	"",//"3ldldldd3(ru)dldllururu3r3ldlddrurudllurur2(rdluld)u3r3urrdrddlulluldrdlr3urrdrdllruulldlddrulddllur",

	// 19
	"####xxxx!"
	"#  ####x!"
	"#     #x!"
	"#     #x!"
	"### ###x!"
	"# $$  ##!"
	"# . .@ #!"
	"####   #!"
	"xxx#####",
	"",//"ll3urul4dllurdr3ulluurdldrur3dldrrl3urrulldlluurdldrur3drdlrdrrul",

	// 20
	"####xxxx!"
	"#  ####x!"
	"#     #x!"
	"#     #x!"
	"### ###x!"
	"# $$$ ##!"
	"# ...@ #!"
	"####   #!"
	"xxx#####",
	"",//"ll3urul4dllurdr3ulluurdldrurdrrull3dldrrdrrululldllurdrrl3ulluurdldrurdrrull3drdl3ulluurdldrur3drddrrul",

	// 21
	"#####xx!"
	"#   ###!"
	"#     #!"
	"##    #!"
	"####$##!"
	"#  $ ##!"
	"# @   #!"
	"###. .#!"
	"xx#####",
	"",//"rr3uruldlluurdldrur3dldllurrddrrul3uruldlluurdldrur4dldruu3ldrurd",

	// 22
	"#####xx!"
	"#   ###!"
	"# .   #!"
	"## $  #!"
	"####$##!"
	"#  $ ##!"
	"# @   #!"
	"###. .#!"
	"xx#####",
	"",//"rr3urullulldrdrluurdr3dldllurrddrrul3urullulldrdrluurdr4dlr4ulldrur3dlddruu3ldrurdr3urull",

	// 23
	"xxxxxx####x!"
	"#######  #x!"
	"#        #x!"
	"#  $ #.# #x!"
	"#  $## # ##!"
	"###   @   #!"
	"xx###  #  #!"
	"xxxx##.  ##!"
	"xxxxx#####x",
	"",//"3ulldlullddrulu6rur4dllddrrurulddlluu3luulu5rur4dllddrrurullr3ull4d4u3l3drrdruu",

	// 24
	"xxxxxx####x!"
	"#######  #x!"
	"#        #x!"
	"#  $ #.# #x!"
	"# $$## # ##!"
	"### . @   #!"
	"xx###  #  #!"
	"xxxx##.  ##!"
	"xxxxx#####x",
	"",//"3ulldlu3r3d3lud3r3u5lddrulu3rdlru3rur4dllddrrurullrddlluu3lululu6rur4dllddrruruldd"
	//"lluu3luulu5rur4dllddrrurul3ull4d4u3l3drrdru3l3u5r3d3lru",

	// 25
	"xxxxx####!"
	"xxx###  #!"
	"x### .. #!"
	"x# $$#  #!"
	"## # #@##!"
	"#       #!"
	"#   #   #!"
	"######  #!"
	"xxxxx####",
	"",//"uulldduurr3d3ldlluruurldd3rdr3uruuldlldlldd4ruurul3d4luurrdulldd3rdr3u",

	// 26
	"xxxxx####!"
	"xxx###  #!"
	"x### .. #!"
	"x# $$#  #!"
	"## # #@##!"
	"#  *    #!"
	"#   #   #!"
	"######  #!"
	"xxxxx####",
	"",//"d3ldllu4rdr3uruuldlldduurr3drddluu3ldlluruurldd3rdrruluuruuldlldlldd3rdrr"
	//"uluurul3d3ldllu4rdru4luurrdulldd3rdrru3lrruu",

	// 27
	"x####xxx!"
	"x#  ####!"
	"x#     #!"
	"x# #.  #!"
	"##*##$##!"
	"#      #!"
	"# # @  #!"
	"#    ###!"
	"######xx",
	"",//"uruululldduurrdrddldd3luurrdrr3uru3lul3duu3r4dllurdruudldd3luurrl3u4rdl3dllurdr3uru3luldd",

	// 28
	"x####xxx!"
	"x#  ####!"
	"x#     #!"
	"x# #.  #!"
	"##*##$##!"
	"#    * #!"
	"# # @  #!"
	"#    ###!"
	"######xx",
	"",//"rruluululldduurrdr3dllurdd3luur3urrdrddrdlld3luu3rll3urrdrru3lul3duu3r3dldd3luurldd3r"
	//"uurrdl4u3l3drr3ldd3ruruuddld3luur3u4rdlu3l3drrdr3uru3lulddu3r3dlddludlluu3r",

	// 29
	"########!"
	"#   #  #!"
	"#      #!"
	"## #.  #!"
	"#    ###!"
	"# # . #x!"
	"# $$# #x!"
	"###  @#x!"
	"xx#####x",
	"",//"lluur3ullddlddrluurrdruuddrd2(dlluu)rrluurrddurruuldrdl",

	// 30
	"########!"
	"#   #  #!"
	"#      #!"
	"## #. .#!"
	"#    ###!"
	"# # * #x!"
	"# $$# #x!"
	"###  @#x!"
	"xx#####x",
	"",//"lluuddrruul3ullddrdrrddlluuruurullulldrddlddrluuruurrdrru3luldrr3drddllulluurrll"
	//"ddrruruurullulld3r3dldlluurrdruurruuldrdlullulld3rddlludrrurruuldrdlullulld4rurd",

	// 31
	"#####xx!"
	"#   ##x!"
	"# #  ##!"
	"#. #$ #!"
	"#  @  #!"
	"#.##$##!"
	"#    #x!"
	"######x",
	"",//"ll3ur3(rd)luulull5d3ruulluluur3(rd)ldd3l3u3d3ruulluld3ruululld",

	// 32
	"####xxx!"
	"#  ###x!"
	"#    ##!"
	"# .#$ #!"
	"## @  #!"
	"x#.#$##!"
	"x#   #x!"
	"x#####x",
	"",//"luurrdrdluull4drruulrddll3uluurdrrdrdlddll3ulur4drruulrddll3uluur3drruulrddlluluurd",

	// 33
	"x#######x!"
	"x#  #  ##!"
	"## **$. #!"
	"#   #   #!"
	"#   @ ###!"
	"#  ####xx!"
	"####xxxxx",
	"",//"ll3urdldd3ruruuldllulddlddrurudrruruuldllddrrudlluurrdd4lurd3ruulluld3rd2(dllu)rurlddru",

	// 34
	"x#######x!"
	"##  #  #x!"
	"#  **$.##!"
	"#   #   #!"
	"### @   #!"
	"xx####  #!"
	"xxxxx####",
	"",//"rr3uldrdd3luluurdrrurddrddluludlluluurdrrddlludrruulldd4ruld3luurrurddu3ldllurdrdrruruldrrddluu",

	// 35
	"xx####xx!"
	"###  ###!"
	"#   *$ #!"
	"# #  #@#!"
	"# # *. #!"
	"#   ####!"
	"#####xxx",
	"",//"dlluluurd3l3drru3ruu3l3rdd3lud3ruulldldr3uldrddldll3urrurddu3l3drruuddll3urr",

	// 36
	"#####xxx!"
	"#   ##xx!"
	"# #  ###!"
	"#   *$ #!"
	"###  #@#!"
	"xx# *. #!"
	"xx#  ###!"
	"xx####xx",
	"",//"dlldl3ulluurrdrdldd3ruulldldr3ulduullddrrdrddl3ulluurrdrdduulullddrr",

	// 37
	"xx####x!"
	"x##  #x!"
	"##   ##!"
	"#  *$ #!"
	"# # #@#!"
	"#  *. #!"
	"###  ##!"
	"xx#  #x!"
	"xx####x",
	"",//"dlluullddrluurrddrruullddlluururddurrddll4urdl3drruulrddlluuddrddluurruu4lddrrlluurrduruuld",

	// 38
	"xx####xx!"
	"xx#  ###!"
	"x## .  #!"
	"##@$$$ #!"
	"# . . ##!"
	"#   ###x!"
	"#  ##xxx!"
	"####xxxx",
	"",//"d3rurulldrdlldllururrdlr3ulddu3rdldlulldrllddru",

	// 39
	"xx#####x!"
	"###   #x!"
	"#     #x!"
	"#  #.###!"
	"##@$$$ #!"
	"x#.#.# #!"
	"x#     #!"
	"x#  ####!"
	"x####xxx",
	"",//"ddrr3u3dl2(luur)urrdlddlluururdll4d4ruu3l3rdd4lu2(urrd)d3ldlurruullulurrurrdlddlluururd",

	// 40
	"xx####x!"
	"x##  #x!"
	"## . ##!"
	"#@$$$ #!"
	"#. .# #!"
	"# #   #!"
	"#   ###!"
	"#####xx",
	"",//"drrudllururdll3drrurruulluld3rddllulrdrruulluurdlldrddrruulrddlluulldru3rddlldllu",
	
// ==== Boxxle 1 collection (part), (c) Thinking Rabbit

	// 41 ... 1
	"x#####xxx!"
	"x#   ####!"
	"x#   #  #!"
	"x##    .#!"
	"### ###.#!"
	"# $ #x#.#!"
	"# $$#x###!"
	"#@  #xxxx!"
	"#####xxxx!",
	"",//"rr4uruulldrurdl5dllurdr4u3rurddu3luulldrurdl4dllurdr3u3rurd3luulldrurdld3r",

	// 42 ... 2
	"xx#######x!"
	"xx#     #x!"
	"xx# $ @ #x!"
	"##### # #x!"
	"# $     #x!"
	"#  #$## ##!"
	"#..$  #  #!"
	"#..      #!"
	"##########!",
	"",//"u3ld3rur5drd6lrrullulu3rdurrluurr4drd5lrrull",

	// 43 ... 3
	"######!"
	"#..*.#!"
	"#.$  #!"
	"## $ #!"
	"##$ ##!"
	"#@$ #x!"
	"##  #x!"
	"x####x!",
	"",//"3(ru)ullrrddlulur3dluu4dr4u",

	// 44 ... 4
	"########!"
	"#.   $ #!"
	"#.$  # #!"
	"#.# #  #!"
	"### # ##!"
	"x# $  #x!"
	"x#@ ###x!"
	"x#####xx!",
	"",//"rurruuruulldlluld3rull4rddlddlluuddrruuruulldll",

	// 45 ... 5
	"x########x!"
	"##..#   #x!"
	"# ..# $ ##!"
	"# @ $  $ #!"
	"##$###   #!"
	"x#     ###!"
	"x#######xx!",
	"",//"3ruurrddldd4l3u3d4ruu3l3rdd4luulurdrud5rdlu5ldd4ruru4l3rdd4luulurd3ruurdrd4l3rdd4luu",

	// 46 ... 7
	"#########x!"
	"#.....  #x!"
	"### $ # ##!"
	"xx# $##  #!"
	"xx#$ $ $ #!"
	"xx#   #  #!"
	"xx##  # @#!"
	"xxx#######!",
	"",//"3uldlldll3u3drrurr3ulldlull5r3dlldll3urul4drruluulur3d4rddluru3ldl3u3dl3u",

	// 47 ... 8
	"xxxx#####x!"
	"#####   #x!"
	"#.. $ $ ##!"
	"#..$ $  @#!"
	"##. $## ##!"
	"x###    #x!"
	"xxx######x!",
	"",//"3lu3lrdurrd3l5rdd3luluurrdll4ru4l",

	// 48 ... 9
	"###########!"
	"#     # @ #!"
	"# $  $  $ #!"
	"## #...# ##!"
	"x# #...# #x!"
	"x#$ ### $#x!"
	"x#   $   #x!"
	"x#  ##   #x!"
	"x#########x!",
	"",//"ldldlluurdldrurrurrd3ldlluu3ldr3drd3rdrr4u4dllur4lul3ururdurdldrurrurrd3lrr3dld"
	//"dr4u3d5lul4u3rddurrurrd3lrr4d5lul4u3rd3l3drddl4u3d6r4u3lu4ldrrurd",

	// 49 ... 10
	"xxx####x!"
	"####  #x!"
	"# $...##!"
	"#@ $.. #!"
	"###$$$ #!"
	"xx#    #!"
	"xx######!",
	"",//"u3rdrrddlluululld3rddrruldludluu",

	// 50 ... 11
	"x##########x!"
	"##    # @ ##!"
	"#  $.... $ #!"
	"# $ ####$  #!"
	"##  #xx#   #!"
	"x####xx#####!",
	"",//"d3lu3ld3rllddlulu2(rrurrd)3l4rddluru3lrrddlurul",

	// 51 ... 12
	"xxxx########xxxxxxxx!"
	"xxxx#      #########!"
	"##### #### #@##  ..#!"
	"# $  $           ..#!"
	"#   # ### #####  ..#!"
	"### # ### #xxx######!"
	"xx#  $  $ #xxxxxxxxx!"
	"xx###  $###xxxxxxxxx!"
	"xxxx#$  #xxxxxxxxxxx!"
	"xxxx#   #xxxxxxxxxxx!"
	"xxxx#####xxxxxxxxxxx!",
	"",//"d3l3dlldllull3u12rdru13ldllu14rurrld7l3dlldll3uddll3u12rdrrlu7l3d3l3druull3uddll"
	//"3u12rurd7l3d3ldl3uddll3u14r8l2(3dll)5uddll3u13rldr",

	// 52 ... 13
	"xx#####x!"
	"xx#   ##!"
	"### *$ #!"
	"#  .$. #!"
	"#  $. ##!"
	"###  @#x!"
	"xx#####x!",
	"",//"ullulldrrdrruulluurrdull3dllur",

	// 53 ... 14
	"xx########xxxxxxxxxx!"
	"xx#      #xxx######x!"
	"xx#$ $ $ #xxx#  ..#x!"
	"###  $  $#####  ..##!"
	"#  $$$   $      ...#!"
	"# #  $ ####@##  ..##!"
	"# #  $ #xx####  ..#x!"
	"#    ###xxxxx######x!"
	"######xxxxxxxxxxxxxx!",
	"",//"u3lulld11r11l3urddld10r9l3urddld8r7l3u4l3d10rdruud12l3dll3u13ruu"
	//"rrdrddluuld12lddrulu13r12luurduullddrd11r7l3ullddld9rdrrlu9lddlul"
	//"u10rurrddlu9ld3lddrud3l3u14r9lddllulu11rurdldr",

	// 54 ... 15
	"########!"
	"#  @   #!"
	"#  #$$ #!"
	"## $  ##!"
	"x#  $.#x!"
	"x## .##x!"
	"xx#..#xx!"
	"xx####xx!",
	"",//"lddrrddull3urrdduurrdlu3lddrrdru3luurrddrdl3urddlldd",

	// 55 ... 17
	"xxx#######!"
	"xxx#  @  #!"
	"#### # $ #!"
	"#...$#$ ##!"
	"#... $   #!"
	"### $ ## #!"
	"xx# $    #!"
	"xx#    ###!"
	"xx######xx!",
	"",//"llddlddrluurdl3drruldl3udd5ruu6lrrullrruurrddrd4lddrruldluurulruu3rddldlldludd5ruu4l",

	// 56 ... 18
	"xxxxxx####!"
	"#######@ #!"
	"#   #    #!"
	"#   $  $ #!"
	"## ##$# ##!"
	"x#  $ #*.#!"
	"x##  $...#!"
	"xx#   #. #!"
	"xx########!",
	"",//"rddlddrddlulldllu4rdrul3uruuldll3d3urr4dlldllurlurd3r4ulldrur3duullddldru3luu4rurdd",

	// 57 ... 19
	"x########!"
	"x# @    #!"
	"##  ..$ #!"
	"#  #..###!"
	"# $$$##xx!"
	"#    #xxx!"
	"######xxx!",
	"",//"lddldd3ruurul3dllurdruuruurrdlulduldulldrrlldldrdrruuddllurdru",

	// 58 ... 20
	"########!"
	"#  #   #!"
	"# $..$ #!"
	"#@$.* ##!"
	"# $..$ #!"
	"#  #   #!"
	"########!",
	"",//"drluurdrrulrurrdll3drrululuurrdld4luurdldrrllddrulur",

	// 59 ... 21
	"xxx#####xx!"
	"#### @ ###!"
	"#    #   #!"
	"# $$  #$ #!"
	"#  $#$ $ #!"
	"###...$###!"
	"x#.... #xx!"
	"x#######xx!",
	"",//"lddrduluurrdrrddllrruullulldlldurrdlddrdrruldll4ulldrur3duulldrurdur"
	//"rddrdl3uluurrdrrddllrruullullddrddu3ruuldrdllruulullddrd",

	// 60 ... 23
	"#######!"
	"#  #@ #!"
	"# $$$ #!"
	"#  $  #!"
	"# $$$ #!"
	"#..#..#!"
	"#..$..#!"
	"#######!",
	"",//"rddldrdd3luluurddl4ur3drrduurdd4uldldulul3drrurduurdd",

	// 61 ... 25
	"xx######!"
	"xx#  @ #!"
	"xx# $  #!"
	"#### $ #!"
	"# .#$ ##!"
	"#..# $#x!"
	"#..$  ##!"
	"#.. $  #!"
	"####$  #!"
	"xxx#   #!"
	"xxx#####!",
	"",//"lldRdDuuurrddLdDDDulLLdlUrrrrdLLLrrrrddllUUruLLLrrdddrUruLuuulDrdLLdlUUdrrru"
	//"uuruulldDDDrdLLdlUrruuuuurDrdLulDDDrdLLrrdLL",

	// 62 ... 27
	"x########!"
	"x#  #  @#!"
	"x#$  $  #!"
	"x# ## $ #!"
	"##...$ ##!"
	"# ...# #x!"
	"# #$$  #x!"
	"#      #x!"
	"########x!",
	"",//"dlddlld3lddrrudrurr3uruulldllul3duu3rdrdlurru4luldd",

	// 63 ... 28
	"xx######xx!"
	"xx#....#xx!"
	"xx#  ..#xx!"
	"###$$#####!"
	"# $   $ @#!"
	"#   $ $  #!"
	"###   ####!"
	"xx#####xxx!",
	"",//"3lddlluuruulurrl3dlddr4ulur4d3lurrdruudluurrl3drruldluulurdd4rd3ldl4u",

	// 64 ... 31
	"xx############!"
	"xx#    #     #!"
	"xx# $  $ $ $ #!"
	"###### ##$ $ #!"
	"#..  # #  $ ##!"
	"#..    @ ##  #!"
	"#..  #$####  #!"
	"#..  # $  $  #!"
	"#..  #     ###!"
	"############xx!",
	"",//"rurr3urrddlddrddlld4luudd4rurruulu3ld6lul3duu5r3drruldluudd4rurruulu3ld6lulddu5r3d4ru3l"
	//"dluud6ruulu3ld6l4r4u3ldrrur4drru3ruruu4ldllulldrur3duurrurrd4lrru4rddldlludld5l3r4ulldru"
	//"r3duurrurrdlddld4luld5ruruu3lulldrur3duu3rddld4ldllru5ru3ruru6lulldrur3duu3rddld4lulldduu"
	//"rd5rurruru5lulldrur3duu3rddld5l5ru3rddrd4ldlluuddrru3r3u3ld4ldlu3r3drruldluud5r3u3ld4lul3drdl",

// ===== XSokoban collection, Original Levels & extras, (c) Thinking Rabbit

	// 65 ... 1
	"xxxx#####xxxxxxxxxx!"
	"xxxx#   #xxxxxxxxxx!"
	"xxxx#$  #xxxxxxxxxx!"
	"xx###  $##xxxxxxxxx!"
	"xx#  $ $ #xxxxxxxxx!"
	"### # ## #xxx######!"
	"#   # ## #####  ..#!"
	"# $  $          ..#!"
	"##### ### #@##  ..#!"
	"xxxx#     #########!"
	"xxxx#######xxxxxxxx!",
	"",//"u3l3ululldll3d11rurd12lulld13rdrrlu7l3ulull3duull3d11rurrld7l3ullul3duull3d11rdru7l3ull3urdduu"
	//"ll5duull3d13r8l3ullul3duull3d12rlur",

	// 66 ... 2
	"############xx!"
	"#..  #     ###!"
	"#..  # $  $  #!"
	"#..  #$####  #!"
	"#..    @ ##  #!"
	"#..  # #  $ ##!"
	"###### ##$ $ #!"
	"xx# $  $ $ $ #!"
	"xx#    #     #!"
	"xx############!",
	"",//"rdrr3drruuluuruullu4ldduu4rdrrddld3lu6ldl3udd5r3urrdluldduu4rdrrddld3lu6ldluud5r3u4rd3lulddu6rdd"
	//"ld3lu6l4r4d3lurrdr4urrd3rdrdd4lulldllurdr3uddrrdrru4lrrd4ruululldulu5l3r4dllurdr3uddrrdrruluulu4l"
	//"dlu5rdrdd3ldllurdr3udd3ruulu4lullrd5rd3rdrd6ldllurdr3udd3ruulu4ldlluuddru5rdrrdrd5ldllurdr3udd3ru"
	//"ulu5l5rd3ruuru4lulldduurrd3r3d3lu4luld3r3urrdlulddu5r3d3lu4ldl3urul",
/*
	// 67 ... 3
	"xxxxxxxx########x!"
	"xxxxxxxx#     @#x!"
	"xxxxxxxx# $#$ ##x!"
	"xxxxxxxx# $  $#xx!"
	"xxxxxxxx##$ $ #xx!"
	"######### $ # ###!"
	"#....  ## $  $  #!"
	"##...    $  $   #!"
	"#....  ##########!"
	"########xxxxxxxxx!",
	"",//"lddll4d8l8rurrdrrulld9l7r4urr3drd9l4ruurdrd5ldlu8r6u4lddr3drd5lu4l3rd5r3urdduurur3dld6ld4l3ru4ru"
	//"urrdrd6lu3lrrd4ru5rd8ld3lrru5r4uluur5drd5lullrd5r6urrddrdlul3drd6ldllru5r4uluur5drd5luldrdl",

	// 68 ... 6
	"######xx###x!"
	"#..  #x##@##!"
	"#..  ###   #!"
	"#..     $$ #!"
	"#..  # # $ #!"
	"#..### # $ #!"
	"#### $ #$  #!"
	"xxx#  $# $ #!"
	"xxx# $  $  #!"
	"xxx#  ##   #!"
	"xxx#########!",
	"",//"dr4dlDr3uLDr3ulD5LulD7rddlUru6LdLLrU6rddlUru6L7r4dll3Uru5LuLLDDulUdDrrU7r6dllUll4U4drr3Uruul"
	//"l5L7rddlUru6L3r4dllddrUluRdr4U4drrur3Ulul3LuLLrD5rurrd6LdLLUUrD3r4dlluRdr3U4drrdr5Ulul4L5rur"
	//"rd6LdLUruL",

	// 69 ... 38
	"xxxxxx####x!"
	"####### @#x!"
	"#     $  #x!"
	"#   $## $#x!"
	"##$#...# #x!"
	"x# $...  #x!"
	"x# #. .# ##!"
	"x#   # #$ #!"
	"x#$  $    #!"
	"x#  #######!"
	"x####xxxxxx!",
	"",//"ddlu3ldllddrrdru3l3urrddrddldll3u3drddl4urr3u3ldrrurddrdr3dllullddrulurluurrdru3rddrd5luudll"
	//"ddrulurluu3rl3u3rdr4drd5luudllddrulurl3udrr3u3ldrrurdu3rur6drd5luudllddrulurdru",

	// 70 ... 43
	"xxxxxxxx#######xxxx!"
	"xxxx#####  #  ####x!"
	"xxxx#   #   $    #x!"	
	"x#### #$$ ## ##  #x!"
	"##      # #  ## ###!"
	"#  ### $#$  $  $  #!"
	"#...    # ##  #   #!"
	"#...#    @ # ### ##!"
	"#...#  ###  $  $  #!"
	"########x##   #   #!"
	"xxxxxxxxxx#########!",
	"",//"rdrdrrurrdru3ldlluruurull4r3ulluld3l4d4u3rddldlrr3dllu4ldluru4l3rd4ruu3r3u3l4du3r3dllu4ldluru3l3ru"
	//"urdulluurrdrlulldd3lddulddru3rd4ruu3r3u3l4du3r3dllu4ldluruurd4ldlluurdd3u3ruurrddurr4d3ldluru3ldl"
	//"luurdldr3u5rdd3urru6r3d5lrr3dllu4ldluru4luld6r3urr3du6rdrru7lrr3dllu4ldluru4l5r3urr3du3r3d3rdrru4"
	//"ldl3uru3lrr3dllu4ldluru3l3ruu4ldd5r3urr3du3r3d4ruuru7lrr3dllu4ldluru3l4r3urr3du3r3dllu4ldlurull",
*/
};

// number of levels
const int LevNum = count_of(Levels)/2;
