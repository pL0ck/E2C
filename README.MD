# E2C

## Overview

E2C is an console based EII Solver. Well it attempts to solve EII but so far has not been successful....yet. It is written in C++ and is fairly well optimised so runs pretty quick. Depending on which config options are chosen it can generate up to 200 million piece placements per second. It only needs a config file (explained later), a txt file with the board definition and a txt file with the piece definitions. It currently runs on Windows only but wouldn't take too much effort to port to Linux given it uses basic console commands for the display.

The main screen shows stats like runtime and pieces placed. In the center is the current placement of pieces on the board and the last section shows the current config settings.

![image-20220129120632629](C:\Users\Peter\AppData\Roaming\Typora\typora-user-images\image-20220129120632629.png)



`Run Time  :     (1) 1,014.64 [1,014.66]`

This shows the number of passes in () so far, in this case 1. The next is the run time for this pass in seconds and lastly the total run time for the program in [].

`Solve Proc:     173,425,347,569 (64,668,113,268)`

Here we see the number of times a piece has been placed on the board, and in () the number of backtracks the program has done. These figures are for the current pass.

`Max placed:     203 (203)`

This is the number of pieces so far placed for this pass and in () the max it has so far found through the life of the program.

`Chk/Sec   :     170,923,034`

This is just how many piece checks it is doing per second.



## The Board

The board display is showing all the pieces so far from the top left corner across and down. The pieces can be from 1-1024 as higher numbers represent rotations. So 1-256 will be all pieces without rotation, 257-512 will be a pieces rotated clockwise 90 degrees, 513-768 and pieces rotated clockwise 180 degrees and 769-1024 are rotated clockwise 270 degrees.

I did look at doing an OpenGL graphic to display but this tends to slow down the processing. Any sort of display, even the console one strips valuable processing time from the solver, so trying to keep that to a minimum. Just means some manual work at the end should it ever manage to solve it :-)



## Board Definition

The board definition file describes the layout of the board and what type of pieces go there. The fist line represents the board size. Only square boards can be done so in this case it is a 16x16 board. The fist 16 (or board size) entries are always 0 and help in the lookup with the top left corner and top row of edges. The numbers represent the type of piece that goes in that spot.

0=Corners

1=Edges

2=Internal

Any -ve numbers represent clue pieces. 

`16`
`0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,2,-976,2,2,2,2,2,2,2,2,2,2,-1023,2,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,-651,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,2,-949,2,2,2,2,2,2,2,2,2,2,-249,2,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0`



## Piece Definition

The piece definition file lists all the pieces in this format

Piece number,Piece type, Top pattern, Right pattern, Bottom pattern, Left pattern. So pieces are coded in a clockwise direction.

Piece type can be

0=Corner

1=Edge

2=Internal

3=Clue

`1,0,1,4,0,0`
`2,0,1,2,0,0`
`3,0,3,4,0,0`
`4,0,4,3,0,0`
`5,1,6,1,0,1`
`6,1,19,3,0,1`
`7,1,16,1,0,1`
`8,1,16,5,0,1`
`9,1,20,4,0,1`
`10,1,9,2,0,1`
`.`
`.`
`.`
`138,2,16,18,15,16`
`139,3,16,20,15,16`
`140,2,16,10,15,16`
`.`
`.`
`.`
`255,3,7,17,14,17`
`256,2,11,17,22,17`

The piece pattern is based on this table.

| **0**  | ![img](file:///C:/Users/Peter/AppData/Local/Temp/msohtmlclip1/01/clip_image002.png) | **00000** | **12** | ![img](file:///C:/Users/Peter/AppData/Local/Temp/msohtmlclip1/01/clip_image004.png) | **01100** |
| ------ | ------------------------------------------------------------ | --------- | ------ | ------------------------------------------------------------ | --------- |
| **1**  | ![img](file:///C:/Users/Peter/AppData/Local/Temp/msohtmlclip1/01/clip_image006.png)E | **00001** | **13** | ![img](file:///C:/Users/Peter/AppData/Local/Temp/msohtmlclip1/01/clip_image008.png) | **01101** |
| **2**  | ![img](file:///C:/Users/Peter/AppData/Local/Temp/msohtmlclip1/01/clip_image010.png)E | **00010** | **14** | ![img](file:///C:/Users/Peter/AppData/Local/Temp/msohtmlclip1/01/clip_image012.png) | **01110** |
| **3**  | ![img](file:///C:/Users/Peter/AppData/Local/Temp/msohtmlclip1/01/clip_image014.png)E | **00011** | **15** | ![img](file:///C:/Users/Peter/AppData/Local/Temp/msohtmlclip1/01/clip_image016.png) | **01111** |
| **4**  | ![img](file:///C:/Users/Peter/AppData/Local/Temp/msohtmlclip1/01/clip_image018.png)E | **00100** | **16** | ![img](file:///C:/Users/Peter/AppData/Local/Temp/msohtmlclip1/01/clip_image020.png) | **10000** |
| **5**  | ![img](file:///C:/Users/Peter/AppData/Local/Temp/msohtmlclip1/01/clip_image022.png)E | **00101** | **17** | ![img](file:///C:/Users/Peter/AppData/Local/Temp/msohtmlclip1/01/clip_image024.png) | **10001** |
| **6**  | ![img](file:///C:/Users/Peter/AppData/Local/Temp/msohtmlclip1/01/clip_image026.png) | **00110** | **18** | ![img](file:///C:/Users/Peter/AppData/Local/Temp/msohtmlclip1/01/clip_image028.png) | **10010** |
| **7**  | ![img](file:///C:/Users/Peter/AppData/Local/Temp/msohtmlclip1/01/clip_image030.png) | **00111** | **19** | ![img](file:///C:/Users/Peter/AppData/Local/Temp/msohtmlclip1/01/clip_image032.png) | **10011** |
| **8**  | ![img](file:///C:/Users/Peter/AppData/Local/Temp/msohtmlclip1/01/clip_image034.png) | **01000** | **20** | ![img](file:///C:/Users/Peter/AppData/Local/Temp/msohtmlclip1/01/clip_image036.png) | **10100** |
| **9**  | ![img](file:///C:/Users/Peter/AppData/Local/Temp/msohtmlclip1/01/clip_image038.png) | **01001** | **21** | ![img](file:///C:/Users/Peter/AppData/Local/Temp/msohtmlclip1/01/clip_image040.png) | **10101** |
| **10** | ![img](file:///C:/Users/Peter/AppData/Local/Temp/msohtmlclip1/01/clip_image042.png) | **01010** | **22** | ![img](file:///C:/Users/Peter/AppData/Local/Temp/msohtmlclip1/01/clip_image044.png) | **10110** |
| **11** | ![img](file:///C:/Users/Peter/AppData/Local/Temp/msohtmlclip1/01/clip_image046.png) | **01011** |        |                                                              |           |





## Config

There is a small config file (E2C.cfg) that allows you to set some parameters to run with. The config file is commented so reasonably obvious what each entry does.

`boardfile=board.txt`

This is the file that contains our board definition (see explanation later).

`piecefile=pieces.txt`

Likewise this is the file that has our piece definitions.

`displayafter=30`

How often to update the display in seconds. Note: if the solver finds a higher piece placement it will display regardless of this setting, assuming it has already reached the "*showafter*" value. The less time the solver spends updating the display the quicker it can do piece checks.

`resetafter=120`

If the solver hasn't found any higher piece placements after this many seconds, it will reset the board, randomise the pieces and start another pass.

`showafter=60`

Only show the board after this many pieces have been placed. Again the longer you leave the display the more processing time the solver has.

`initialrandomise=true`

This will initially randomise the pieces if set to true. The piece file will normally have the pieces in order. i.e 1,2,3,4,5,6,7...etc. With this setting to true the pieces and ultimately how they get chosen is randomised. So for example, instead of starting with piece 1 (rotated of course) in the top left corner it might pick piece 2 or 3 or 4, Same for edges and internals. I added this as an option to try and "jag" a solve or optionally speed things up but so far I don't think it has helped. There is possibility that it will randomise and make things worse rather than better but there isn't a way to tell without a solution.

`displaypartial=true`

Display the current board/piece placements, even if we haven't beaten the current max placements. 

`resetafterbacktrack=false`

Here's another option that I thought might help. If set to true, the moment a backtrack is detected it will reset the board, randomise the pieces and start another pass. 



## Solve File

If by some miracle it does manage to solve the puzzle then a file is written with the filename like *date-time-boardsize.E2O*. The format of the file is;

`8`
`769,10,14,23,9,24,28,4`
`785,568,546,47,826,319,292,271`
`780,52,35,53,566,830,562,269`
`779,316,51,296,800,313,48,264`
`786,571,64,549,46,297,799,278`
`784,285,807,30,811,556,289,277`
`794,45,823,829,554,49,550,262`
`515,531,537,539,517,519,532,258`

The first line is the boardsize and then the pieces for each row. 



## Comments

So this a rehash of an old program I had running ages ago. It didn't manage to find a solution (obviously) and ran fairly slow on my old laptop. I dug it out and made a few tweaks as I have some new hardware now. It manages to find a 6x6 generally in under a second, 8x8 after a few minutes and still have to try out the 10x10. Having the pieces randomise does change these times, and sometimes quite substantially so it is hit and miss.

Given there can only be 24 ways the corners can be placed I've looked at running 24 of these at the same time, each with different corner placements as clues. Doing it though does max out my CPU so end up only getting around 70-80 million piece placements, rather than 170 million or so. I might look at this method to try and gather some statistics on pieces placed for various corners.

Additionally I might add a checkpoint feature so it can run from a previously last saved maximum.



## Build

There shouldn't be anything special as it is a basic console app so should just load up into Visual Studio and compile. 



## License

Free to use anywhere, anytime or bits thereof.

