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
double totaltime=0;
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