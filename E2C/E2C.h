#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <bitset>
#include "timer.h"
#include <stack>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <algorithm>
#include <random>
#include <functional>
#include <ratio>
#include <thread>

//Constants
//MAX_LOOKUP the maximum number of entries we expect to lookup
const int MAX_LOOKUP = 16;
const int MAX_STACK = 256;
//NUMBER_PIECE_ELEMENTS is the number of elements from the piece file used to represent a piece
const int NUMBER_PIECE_ELEMENTS = 6;

//Arrays
unsigned int stack[256];
unsigned int xpiece[1025];
unsigned int lookup[4096][MAX_LOOKUP];
unsigned int lookupcount[4096];
int placedpieces[280];
int board[512];
//inputpiece is the data read from the piece file
int inputpiece[6];

//Variables
unsigned int piecekey;
unsigned int index;
unsigned int foundcount;
unsigned int actualpiece;
unsigned long long backtracks;
unsigned int passes;
unsigned int finalposition;
unsigned int currentposition;
unsigned int boardsize;
unsigned long long solvecount;
double elapsed;
double prev_elapsed;
double totaltime = 0;
unsigned int maxplaced;
unsigned int original_maxplacedpieces = 0;
unsigned int clueisnext;
unsigned int clueahead;
int pieceindex;
unsigned int prevmax = 0;
bool abandon = false;
unsigned int maxever = 0;
std::string line;


double reset_after_secs = 30;
double display_after_secs = 5;
bool initial_randomise = false;
bool display_partial = false;
unsigned int show_after = 1;
bool resetafterbacktrack = false;
bool shuffle_TL = true;

//Functions
void loaddata();
void buildlookup(int[]);
void rotatepiece(int[]);
void displaydata(bool);
void solve2();
void randomisepieces();
void gotoxy(int, int, int);
void clearboard();
void savedata(unsigned int);






//********************************************************************************************************************
//New code
//********************************************************************************************************************
//#pragma once
//#include <iostream>
//#include <fstream>
//#include <sstream>
//#include <vector>
//#include <string>
//#include <stdlib.h>
//#include <bitset>
//#include "timer.h"
//#include <stack>
//#include <windows.h>
//#include <cstdlib>
//#include <ctime>
//#include <chrono>
//#include <algorithm>
//#include <random>
//#include <functional>
//#include <ratio>
//#include <thread>
//#include <unordered_map>
//
////Constants
////MAX_LOOKUP the maximum number of entries we expect to lookup
//const int MAX_LOOKUP = 16;
//const int MAX_STACK = 272;
////NUMBER_PIECE_ELEMENTS is the number of elements from the piece file used to represent a piece
//const int NUMBER_PIECE_ELEMENTS = 6;
//const int placedpieces_array_size = 288;
////Arrays
//unsigned int stack[MAX_STACK];
////unsigned int xpiece[1026];
//bool pieceinuse[257];
//
//unsigned int xpiecetop[1026];
//unsigned int xpieceright[1026];
//unsigned int xpiecebottom[1026];
//unsigned int xpieceleft[1026];
//
//
////unsigned int lookup[4096][MAX_LOOKUP];
////std::vector<std::vector<unsigned int>> xlookup;
//std::unordered_map<unsigned int, std::vector<unsigned int>> zlookup;
//unsigned int lookupcount[3][24][24][24][24];
//
//int placedpieces[placedpieces_array_size];
//int displaypiece;
//int board[512];
////inputpiece is the data read from the piece file
//int inputpiece[6];
//unsigned int vlookup[3][24][24][24][24][MAX_LOOKUP];
//unsigned int top;
//unsigned int right;
//unsigned int bottom;
//unsigned int left;
//unsigned int piecetype;
//unsigned int chktop;
//unsigned int chkright;
//unsigned int chkbottom;
//unsigned int chkleft;
//unsigned int chkpiecetype;
//
////Variables
//unsigned int piecekey;
//unsigned int index;
////unsigned int foundcount;
//unsigned int actualpiece;
//unsigned long long backtracks;
//unsigned int passes;
//unsigned int finalposition;
//unsigned int currentposition;
//unsigned int boardsize;
//unsigned long long solvecount;
//double elapsed;
//double prev_elapsed;
//double totaltime = 0;
//unsigned int maxplaced;
//unsigned int original_maxplacedpieces = 0;
//unsigned int piecesplacedonboard = 0;
//bool pieceok = false;
//bool chkpieceuse = false;
//
//unsigned int failedlookaheads = 0;
////unsigned int clueisnext;
////unsigned int clueahead;
//int pieceindex;
//unsigned int prevmax = 0;
//bool abandon = false;
//unsigned int maxever = 0;
//std::string line;
//
//
//double reset_after_secs = 30;
//double display_after_secs = 5;
//bool initial_randomise = false;
//bool display_partial = false;
//unsigned int show_after = 1;
//bool resetafterbacktrack = false;
//
////Functions
//void loaddata();
//void buildlookup(int[]);
//void rotatepiece(int[]);
//void displaydata(bool);
//void solve2();
//void randomisepieces();
//void gotoxy(int, int, int);
//void clearboard();
//void savedata(unsigned int);
////void analyse();