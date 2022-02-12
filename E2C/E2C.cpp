//#include "E2C.h"
//
//timer displaytime;
//timer passtime;
//timer runtime;
//COORD coord;
//
//void gotoxy(int x, int y, int color = FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED)
//{
//	coord.X = x;
//	coord.Y = y;
//	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
//	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
//}
//
//void randomisepieces()
//{
//	// To obtain a time-based seed
//	//unsigned seed = 0;
//
//	for (int x = shuffle_TL ? 0 : 1; x < 4096; x++)
//	{
//		if (lookupcount[x] > 1)
//		{
//			int n = sizeof(lookup[x]) / sizeof(lookup[x][0]);
//			// Shuffling our array
//			for (int i = lookupcount[x] - 1; i > 0; i--)
//			{
//				std::swap(lookup[x][rand() % (i + 1)], lookup[x][i]);
//			}
//		}
//	}
//}
//
//void clearboard()
//{
//	std::string divider = "|    ";
//
//	for (unsigned int r = 4; r < boardsize + 4; r++)
//	{
//		for (unsigned int c = 0; c < boardsize * 5; c += 5)
//		{
//			gotoxy(c, r, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
//			std::cout << divider;
//		}
//		gotoxy((boardsize * 5), r, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
//		std::cout << "|";
//	}
//	gotoxy(16, 1);
//	std::cout << "                                 ";
//	gotoxy(16, 3);
//	std::cout << "                                 ";
//}
//
//int main()
//{
//	std::srand(unsigned(std::time(0)));
//
//	loaddata();
//
//	if (initial_randomise)
//		randomisepieces();
//
//	//static display
//	std::cout.imbue(std::locale(""));
//	gotoxy(0, 0);
//	std::cout << "Run Time  : ";
//	gotoxy(0, 1);
//	std::cout << "Solve Proc: ";
//	gotoxy(0, 2);
//	std::cout << "Max placed: ";
//	gotoxy(0, 3);
//	std::cout << "Chk/Sec   : ";
//
//
//
//	passes = 1;
//	do
//	{
//		clearboard();
//		solvecount = 0;
//		totaltime = runtime.get_elapsed_time();
//		passtime.reset();
//		displaytime.reset();
//		currentposition = boardsize;
//		prevmax = 0;
//		maxplaced = original_maxplacedpieces;
//		prev_elapsed = 0;
//		for (int x = 0; x < 1025; x++)
//		{
//			//clear in use flag
//			//don't clear clue pieces
//			if ((xpiece[x] & 0x40000000) != 0x40000000)
//				xpiece[x] &= 0x7FFFFFFF;
//		}
//
//		for (int x = 0; x < 280; x++)
//		{
//			//clear placed pieces
//			if (board[x] != 0xC00)
//				placedpieces[x] = 0;
//		}
//
//		randomisepieces();
//		solve2();
//		passes++;
//		displaydata(false);
//
//		if (abandon)
//		{
//			original_maxplacedpieces = 0;
//			randomisepieces();
//		}
//	} while (currentposition != finalposition);
//
//	displaydata(true);
//	gotoxy(0, boardsize + 5);
//	if (currentposition == finalposition)
//	{
//		std::cout << "SOLVED....";
//		//Save the data
//		//create the filename
//		std::string filename = passtime.CurrentDateTime() + "-" + std::to_string(boardsize) + ".E2O";
//		std::ofstream solvefile(filename);
//		if (solvefile.is_open())
//		{
//			//write out the board
//			solvefile << boardsize << "\n";
//			for (unsigned int r = 0; r < boardsize; r++)
//			{
//				for (unsigned int c = 0; c < boardsize; c++)
//				{
//					solvefile << (placedpieces[((r + 1) * boardsize) + c]);
//					if (c < boardsize - 1)
//						solvefile << ",";
//				}
//				solvefile << "\n";
//			}
//			solvefile.close();
//		}
//
//
//
//		//Do we want the 2D graphics.
//
//	}
//	else
//		std::cout << "NO SOLUTION...press any key";
//
//	char gc = getchar();
//}
//
//void loaddata()
//{
//	std::string pfile = "pieces.txt";
//	std::string bfile = "board.txt";
//	std::string cfile = "E2C.cfg";
//
//	int idx;  //index for array
//	int piecenumber;
//	int bpt;  //board piece type 0=corner, 1=edge, 2=internal, any other is a clue piece
//	int sbpt; //temp save of the board piece type
//
//	//Read our config file
//	std::ifstream cFile(cfile);
//	if (cFile.is_open())
//	{
//		std::string line;
//		while (getline(cFile, line))
//		{
//			line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
//			if (line[0] == '#' || line.empty()) continue;
//
//			auto delimiterPos = line.find("=");
//			auto name = line.substr(0, delimiterPos);
//			auto value = line.substr(delimiterPos + 1);
//
//			//Custom coding
//			if (name == "boardfile") bfile = value;
//			else if (name == "piecefile") pfile = value;
//			else if (name == "displayafter") display_after_secs = std::stod(value);
//			else if (name == "resetafter") reset_after_secs = std::stod(value);
//			else if (name == "showafter") show_after = std::stoi(value);
//			else if (name == "initialrandomise")
//			{
//				if (value == "true")
//					initial_randomise = true;
//				else
//					initial_randomise = false;
//			}
//			else if (name == "displaypartial")
//			{
//				if (value == "true")
//					display_partial = true;
//				else
//					display_partial = false;
//			}
//			else if (name == "resetafterbacktrack")
//			{
//				if (value == "true")
//					resetafterbacktrack = true;
//				else
//					resetafterbacktrack = false;
//			}
//			else if (name == "shuffleTL")
//			{
//				if (value == "true")
//					shuffle_TL = true;
//				else
//					shuffle_TL = false;
//			}
//		}
//	}
//	else
//	{
//		std::cerr << "Couldn't open config file for reading.\n";
//		reset_after_secs = 30;
//		display_after_secs = 5;
//		show_after = 1;
//
//	}
//
//	//display the config data
//	gotoxy(0, 21);
//	std::cout << "Update Board Every: " << display_after_secs << " secs";
//	gotoxy(0, 22);
//	std::cout << "Reset Board After : " << reset_after_secs << " secs";
//	gotoxy(0, 23);
//	std::cout << "Show Result After : " << show_after << " pieces placed";
//	gotoxy(0, 24);
//	std::cout << "Initial Randomise : " << (initial_randomise ? "Yes" : "No");
//	gotoxy(0, 25);
//	std::cout << "Partial Display   : " << (display_partial ? "Yes" : "No");
//	gotoxy(0, 26);
//	std::cout << "Reset w Backtrack : " << (resetafterbacktrack ? "Yes" : "No");
//	gotoxy(0, 27);
//	std::cout << "Board File        : " << bfile;
//	gotoxy(0, 28);
//	std::cout << "Piece File        : " << pfile;
//	//Read in our piece data from file
//	std::ifstream pdata(pfile);
//	if (pdata.is_open())
//	{
//
//		while (!pdata.eof())
//		{
//			//We need to get a whole line first
//			getline(pdata, line);
//			std::stringstream st(line);
//
//			idx = 0;
//
//			//Now read each piece of data seperated by commas
//			//0=piece number
//			//1=piece type (0=corner,1=edge,2=internal,>2=clue)
//			//2=top
//			//3=right
//			//4=bottom
//			//5=left
//			while (getline(st, line, ','))
//			{
//				//Build and array with all 5 bits
//				inputpiece[idx] = std::stoi(line);
//				idx += 1;
//				if (idx == NUMBER_PIECE_ELEMENTS)
//				{
//					//We now have our array with the data for this piece
//					idx = 0;
//
//					//Get our piece number from the first entry
//					piecenumber = inputpiece[0];
//
//					//Build our xpiece array from the data we've read
//					buildlookup(inputpiece);
//
//					//Rotate 90 degrees right and save this xpiece. Then do 2 more times
//					//we then end up with an xpiece array with all rotated combinations of the piece
//					//a total of 1024 pieces.
//					rotatepiece(inputpiece);
//					inputpiece[0] = piecenumber + 256;
//					buildlookup(inputpiece);
//
//
//					rotatepiece(inputpiece);
//					inputpiece[0] = piecenumber + 512;
//					buildlookup(inputpiece);
//
//
//					rotatepiece(inputpiece);
//					inputpiece[0] = piecenumber + 768;
//					buildlookup(inputpiece);
//				}
//			}
//		}
//		pdata.close();
//	}
//
//	//Read in our board data that tells us what piece type goes in each square.
//	std::ifstream bdata(bfile);
//	if (bdata.is_open())
//	{
//		//file open so read
//		getline(bdata, line);
//
//		//First line of file contains the size of the board
//		boardsize = std::stoi(line);
//
//		//The final size is boardsize x boardsize plus allow boardsize more for the 0's at the beginning
//		//finalposition = (boardsize * boardsize) + boardsize;
//		finalposition = (boardsize * boardsize) + boardsize;
//
//		//Start at board position 0
//		idx = 0;
//
//		//Read each entry seperated by commas
//		while (getline(bdata, line, ','))
//		{
//			bpt = std::stoi(line);
//
//			//Entries are either 0 for corners, 1 for edges and 2 for internal
//			//If we find an entry > 2 then it's a clue piece so has a fixed position
//			//Note-means we can't have pieces 1 & 2 as clues
//			if (bpt < 0)
//			{
//				//We have a clue piece. bpt is the piece number. > 255 and it's rotated.
//				//Change the sign to make positive
//				bpt = bpt * -1;
//
//				//First change rotated piece to find the actual piece number 0-255 in array (1-256)
//				sbpt = bpt & 0xFF;
//
//				//Set the top 2 bits set this piece in use
//				//Bit 31 sets it in use
//				//Bit 30 is a clue piece
//				//Set each piece including the rotated ones
//				xpiece[sbpt] = xpiece[sbpt] | 0xC0000000;
//				xpiece[sbpt + 256] |= 0xC0000000;
//				xpiece[sbpt + 512] |= 0xC0000000;
//				xpiece[sbpt + 768] |= 0xC0000000;
//
//				//we now need to set the placed piece
//				//we set bit 30 to show it's a clue...no we don't
//				//placedpieces[idx] = (bpt | 0x40000000);
//				placedpieces[idx] = bpt;
//				original_maxplacedpieces++;
//
//				//set the board piece type to 3 (clue)
//				bpt = 3;
//			}
//
//			//The board holds the type in bit 10 & 11
//			// 0=0, 1=1024(0x400), 2=2048(0x800), 3=3072(0xc00)
//			board[idx] = bpt << 10;
//
//			//Increment to next board position
//			idx += 1;
//		}
//		bdata.close();
//	}
//}
//
//void buildlookup(int piece[])
//{
//	//piece is the piece data 
//	//piece[0]=piece number
//	//piece[1]=piece type From file 0=corner, 1=edge, 2=internal >2=clue
//	//piece[2]=top
//	//piece[3]=right
//	//piece[4]=bottom
//	//piece[5]=left
//
//	//-----------------------------------------------------------------------------------------------
//	// Bit layout for 32 bit integer holding piece info
//	//  31     30     22-29     17-21    12-16    10-11    5-9   0-4
//	//   0      0    00000000   00000    00000      00    00000 00000
//	// InUse  Clue   PieceId    Bottom   Right    Type     Top   Left 
//	//-----------------------------------------------------------------------------------------------
//	xpiece[piece[0]] = piece[5] | (piece[2] << 5) | (piece[1] << 10) | (piece[3] << 12) | (piece[4] << 17);
//	//populate array for top,left & type
//
//	//The lookup array stores all the pieces that match top & left
//	//We use this to match bottom of piece above and right of piece to the left and type of piece when checking
//	//Using the 3 values (top,left,type) we get an integervalue that represents the index into the array
//	//Then we populate for multiple enries the same
//	//The value stored there is the piece number piece[0]
//	//To get just the top,left & type we AND with 4095 (0xFFF) to clear out the top bits
//
//	//Set a temp value representing the top,left,type
//	unsigned int piecelookupvalue = xpiece[piece[0]] & 0xFFF;
//
//	//Now put it into the lookup array after the last one.
//	//The lookupcount stores how many of these we have in each lookup array
//	lookup[piecelookupvalue][lookupcount[piecelookupvalue]] = piece[0];
//
//	//Then increment the number of these pieces we have
//	lookupcount[piecelookupvalue]++;
//}
//
//void rotatepiece(int piece[])
//{
//	int tempstore;
//	tempstore = piece[5];
//	piece[5] = piece[4];
//	piece[4] = piece[3];
//	piece[3] = piece[2];
//	piece[2] = tempstore;
//}
//
//void displaydata(bool force)
//{
//	displaytime.reset();
//
//	if (maxplaced > maxever)
//		maxever = maxplaced;
//
//	elapsed = passtime.get_elapsed_time();
//	totaltime = runtime.get_elapsed_time();
//
//	if (reset_after_secs > 0 && (elapsed - prev_elapsed) > reset_after_secs)
//		abandon = true;
//
//	std::cout.imbue(std::locale(""));
//	gotoxy(16, 0);
//	std::cout << "                         ";
//	gotoxy(16, 0, FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
//	std::cout << "(" << passes << ") " << elapsed << " [" << totaltime << "]";
//	gotoxy(16, 1);
//	std::cout << "                         ";
//	gotoxy(16, 1, FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
//	std::cout << solvecount << " (" << backtracks << ")";
//	gotoxy(16, 2);
//	std::cout << "                         ";
//	gotoxy(16, 2, FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
//	std::cout << maxplaced;
//	gotoxy(19, 2, FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_RED);
//	std::cout << " (" << maxever << ")";
//	gotoxy(16, 3);
//	std::cout << "                         ";
//	gotoxy(16, 3, FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
//	std::cout << (unsigned int)(solvecount / elapsed);
//	std::cout.imbue(std::locale("C"));
//
//	if (((maxplaced > prevmax || display_partial) && maxplaced >= show_after) || force)
//	{
//		//reset clock for elapsed only if not partial display
//		if (!display_partial)
//			prev_elapsed = elapsed;
//
//		prevmax = maxplaced;
//		for (unsigned int r = 4; r < boardsize + 4; r++)
//		{
//			for (unsigned int c = 1; c < boardsize * 5; c += 5)
//			{
//				gotoxy(c, r);
//				std::cout.width(4);
//				if (placedpieces[((r - 4) * boardsize) + (c - 1) / 5 + boardsize] == 0)
//					std::cout << " ";
//				else
//					std::cout << (placedpieces[((r - 4) * boardsize) + (c - 1) / 5 + boardsize]);
//			}
//		}
//	}
//}
//
//
//void solve2()
//{
//	abandon = false;
//	index = 0;
//	solvecount = 0;
//	backtracks = 0;
//
//	do
//	{
//		if (displaytime.get_elapsed_time() > display_after_secs)
//			displaydata(false);
//
//		//if we have a placed piece (clue) at this location then just skip over and exit
//		//skip over edges only do internal
//		if (board[currentposition] == 0xC00)
//		{
//			currentposition++;
//		}
//		else
//		{
//			//PIECETYPE | BOTTOM OF PIECE IN PREV ROW | RH OF PIECE TO THE LEFT	
//			piecekey = (board[currentposition] | ((xpiece[placedpieces[currentposition - boardsize]] >> 12) & 0x3E0) | ((xpiece[placedpieces[currentposition - 1]] >> 12) & 0x1F));
//			//foundcount = lookupcount[piecekey];
//
//			//we need to check if there are any clue pieces on the next square and get the left edge for a check
//			//Note: could be faster if we just get a 3 way array with the rh piece (left edge) anyway.
//			//This would mean changing lookup to bigger than 4096
//			//see if the next piece is a clue. if so get the left of that otherwise 0x1f000
//
//			clueisnext = xpiece[placedpieces[currentposition + 1]] & 0x1F;
//			clueahead = (xpiece[placedpieces[currentposition + boardsize]] >> 5) & 0x1F;
//
//			//loop through all the matching pieces to see if one fits
//			while (index < lookupcount[piecekey] && !abandon)
//			{
//				solvecount++;
//				//2147483648 = 0x80000000 If set then piece is in use
//				actualpiece = lookup[piecekey][index];
//				if ((xpiece[(actualpiece & 0xFF)] & 0x80000000) == 0)
//				{
//					if ((clueisnext + clueahead == 0) || (((xpiece[actualpiece] >> 12) & 0x1F) == clueisnext) || (((xpiece[actualpiece] >> 17) & 0x1F) == clueahead))
//					{
//						//store the piece we've found
//						placedpieces[currentposition] = actualpiece;
//
//						//set that piece in use
//						//Note we only need to set the base piece
//						xpiece[(actualpiece & 0xFF)] |= 0x80000000;
//
//						index++;
//						stack[currentposition] = index;
//
//						currentposition++;
//						if ((currentposition - boardsize) > maxplaced)
//						{
//							maxplaced = currentposition - boardsize;
//							displaydata(false);
//						}
//						index = 0;
//						break;
//					}
//				}
//				index++;
//			}
//
//			if (index >= lookupcount[piecekey])
//			{
//				if (resetafterbacktrack)
//					abandon = true;
//				else
//				{
//					//run out of pieces so go back and check next
//					currentposition--;
//					backtracks++;
//
//					while (board[currentposition] == 0xC00)
//						currentposition--;
//
//					//clear piece in use
//					xpiece[(placedpieces[currentposition] & 0xFF)] &= 0x7FFFFFFF;
//
//					placedpieces[currentposition] = 0;
//					index = stack[currentposition];
//				}
//			}
//		}
//	} while (currentposition != finalposition && !abandon);
//}












//********************************************************************************************************************
//New code
//********************************************************************************************************************
#include "E2C.h"

timer displaytime;
timer passtime;
timer runtime;
COORD coord;

void gotoxy(int x, int y, int color = FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED)
{
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void randomisepieces()
{
	for (int y = 0; y < 3; y++)
	{
		for (int t = 0; t < 24; t++)
		{
			for (int r = 0; r < 24; r++)
			{
				for (int b = 0; b < 24; b++)
				{
					for (int l = 0; l < 24; l++)
					{
						if (lookupcount[y][t][r][b][l] > 1)
						{
							for (int i = lookupcount[y][t][r][b][l] - 1; i > 0; i--)
							{
								std::swap(vlookup[y][t][r][b][l][rand() % (i + 1)], vlookup[y][t][r][b][l][i]);
							}
						}
					}
				}
			}
		}
	}

}

void clearboard()
{
	std::string divider = "|    ";

	for (unsigned int r = 4; r < boardsize + 4; r++)
	{
		for (unsigned int c = 0; c < boardsize * 5; c += 5)
		{
			gotoxy(c, r, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
			std::cout << divider;
		}
		gotoxy((boardsize * 5), r, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
		std::cout << "|";
	}
	gotoxy(16, 1);
	std::cout << "                                 ";
	gotoxy(16, 3);
	std::cout << "                                 ";
}

int main()
{
	std::srand(unsigned(std::time(0)));

	loaddata();


	//analyse();


	if (initial_randomise)
		randomisepieces();

	//static display
	std::cout.imbue(std::locale(""));
	gotoxy(0, 0);
	std::cout << "Run Time  : ";
	gotoxy(0, 1);
	std::cout << "Solve Proc: ";
	gotoxy(0, 2);
	std::cout << "Max placed: ";
	gotoxy(0, 3);
	std::cout << "Chk/Sec   : ";


	passes = 1;
	do
	{
		clearboard();
		solvecount = 0;
		totaltime = runtime.get_elapsed_time();
		passtime.reset();
		displaytime.reset();
		currentposition = boardsize;
		prevmax = 0;
		piecesplacedonboard = original_maxplacedpieces;
		maxplaced = piecesplacedonboard;

		prev_elapsed = 0;
		for (int x = 0; x < 257; x++)
		{
			pieceinuse[x] = false;
			////clear in use flag
			////don't clear clue pieces
			//if ((xpiece[x] & 0x40000000) != 0x40000000)
			//	xpiece[x] &= 0x7FFFFFFF;
		}

		//initialise the placed pieces array
		for (unsigned int x = 0; x < placedpieces_array_size; x++)
		{
			//clear placed pieces
			if (board[x] != 0xC00)
				if (x < boardsize || x >= (boardsize * boardsize) + boardsize)
					placedpieces[x] = 0;
				else
					placedpieces[x] = 1025;
		}

		randomisepieces();
		solve2();
		passes++;
		displaydata(false);

		if (abandon)
			randomisepieces();

	} while (currentposition != finalposition);

	displaydata(true);
	gotoxy(0, boardsize + 5);
	if (currentposition == finalposition)
	{
		std::cout << "SOLVED....";
		savedata(256);



		//Do we want the 2D graphics.

	}
	else
		std::cout << "NO SOLUTION...press any key";

	char gc = getchar();
}

void savedata(unsigned int pcount)
{
	//Save the data
	//create the filename
	std::string filename = passtime.CurrentDateTime() + "-" + std::to_string(boardsize) + "-" + std::to_string(pcount) + ".E2O";
	std::ofstream solvefile(filename);
	if (solvefile.is_open())
	{
		//write out the board
		solvefile << boardsize << "\n";
		for (unsigned int r = 0; r < boardsize; r++)
		{
			for (unsigned int c = 0; c < boardsize; c++)
			{
				solvefile << (placedpieces[((r + 1) * boardsize) + c]);
				if (c < boardsize - 1)
					solvefile << ",";
			}
			solvefile << "\n";
		}
		solvefile.close();
	}
}

void loaddata()
{
	std::string pfile = "pieces.txt";
	std::string bfile = "board.txt";
	std::string cfile = "E2C.cfg";

	unsigned int idx;  //index for array
	int piecenumber;
	int bpt;  //board piece type 0=corner, 1=edge, 2=internal, any other is a clue piece
	int sbpt; //temp save of the board piece type

	//Read our config file
	std::ifstream cFile(cfile);
	if (cFile.is_open())
	{
		std::string line;
		while (getline(cFile, line))
		{
			line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
			if (line[0] == '#' || line.empty()) continue;

			auto delimiterPos = line.find("=");
			auto name = line.substr(0, delimiterPos);
			auto value = line.substr(delimiterPos + 1);

			//Custom coding
			if (name == "boardfile") bfile = value;
			else if (name == "piecefile") pfile = value;
			else if (name == "displayafter") display_after_secs = std::stod(value);
			else if (name == "resetafter") reset_after_secs = std::stod(value);
			else if (name == "showafter") show_after = std::stoi(value);
			else if (name == "initialrandomise")
			{
				if (value == "true")
					initial_randomise = true;
				else
					initial_randomise = false;
			}
			else if (name == "displaypartial")
			{
				if (value == "true")
					display_partial = true;
				else
					display_partial = false;
			}
			else if (name == "resetafterbacktrack")
			{
				if (value == "true")
					resetafterbacktrack = true;
				else
					resetafterbacktrack = false;
			}
		}
	}
	else
	{
		std::cerr << "Couldn't open config file for reading.\n";
		reset_after_secs = 30;
		display_after_secs = 5;
		show_after = 1;

	}

	//display the config data
	gotoxy(0, 21);
	std::cout << "Update Board Every: " << display_after_secs << " secs";
	gotoxy(0, 22);
	std::cout << "Reset Board After : " << reset_after_secs << " secs";
	gotoxy(0, 23);
	std::cout << "Show Result After : " << show_after << " pieces placed";
	gotoxy(0, 24);
	std::cout << "Initial Randomise : " << (initial_randomise ? "Yes" : "No");
	gotoxy(0, 25);
	std::cout << "Partial Display   : " << (display_partial ? "Yes" : "No");
	gotoxy(0, 26);
	std::cout << "Reset w Backtrack : " << (resetafterbacktrack ? "Yes" : "No");
	gotoxy(0, 27);
	std::cout << "Board File        : " << bfile;
	gotoxy(0, 28);
	std::cout << "Piece File        : " << pfile;
	//Read in our piece data from file
	std::ifstream pdata(pfile);
	if (pdata.is_open())
	{

		while (!pdata.eof())
		{
			//We need to get a whole line first
			getline(pdata, line);
			std::stringstream st(line);

			idx = 0;

			//Now read each piece of data seperated by commas
			//0=piece number
			//1=piece type (0=corner,1=edge,2=internal,>2=clue)
			//2=top
			//3=right
			//4=bottom
			//5=left
			while (getline(st, line, ','))
			{
				//Build and array with all 5 bits
				inputpiece[idx] = std::stoi(line);
				idx += 1;
				if (idx == NUMBER_PIECE_ELEMENTS)
				{
					//We now have our array with the data for this piece
					idx = 0;

					//Get our piece number from the first entry
					piecenumber = inputpiece[0];

					//Build our xpiece array from the data we've read
					buildlookup(inputpiece);

					//Rotate 90 degrees right and save this xpiece. Then do 2 more times
					//we then end up with an xpiece array with all rotated combinations of the piece
					//a total of 1024 pieces.
					rotatepiece(inputpiece);
					inputpiece[0] = piecenumber + 256;
					buildlookup(inputpiece);


					rotatepiece(inputpiece);
					inputpiece[0] = piecenumber + 512;
					buildlookup(inputpiece);


					rotatepiece(inputpiece);
					inputpiece[0] = piecenumber + 768;
					buildlookup(inputpiece);
				}
			}
		}

		//piece 0 is special as it is empty so has 10111 on all sides.
		xpiecetop[1025] = 23;
		xpieceright[1025] = 23;
		xpiecebottom[1025] = 23;
		xpieceleft[1025] = 23;
		pdata.close();
	}

	//Read in our board data that tells us what piece type goes in each square.
	std::ifstream bdata(bfile);
	if (bdata.is_open())
	{
		//file open so read
		getline(bdata, line);

		//First line of file contains the size of the board
		boardsize = std::stoi(line);

		//The final size is boardsize x boardsize plus allow boardsize more for the 0's at the beginning
		//finalposition = (boardsize * boardsize) + boardsize;
		finalposition = (boardsize * boardsize) + boardsize;

		//Start at board position 0
		idx = 0;

		//Read each entry seperated by commas
		while (getline(bdata, line, ','))
		{
			bpt = std::stoi(line);

			//Entries are either 0 for corners, 1 for edges and 2 for internal
			//If we find an entry > 2 then it's a clue piece so has a fixed position
			//Note-means we can't have pieces 1 & 2 as clues
			if (bpt < 0)
			{
				//We have a clue piece. bpt is the piece number. > 255 and it's rotated.
				//Change the sign to make positive
				bpt = bpt * -1;

				//First change rotated piece to find the actual piece number 0-255 in array (1-256)
				sbpt = bpt & 0xFF;

				//Set the top 2 bits set this piece in use
				//Bit 31 sets it in use
				//Bit 30 is a clue piece
				//Set each piece including the rotated ones
				//xpiece[sbpt] = xpiece[sbpt] | 0xC0000000;
				//xpiece[sbpt + 256] |= 0xC0000000;
				//xpiece[sbpt + 512] |= 0xC0000000;
				//xpiece[sbpt + 768] |= 0xC0000000;

				//we now need to set the placed piece
				//we set bit 30 to show it's a clue...no we don't
				//placedpieces[idx] = (bpt | 0x40000000);
				placedpieces[idx] = bpt;
				original_maxplacedpieces++;

				//set the board piece type to 3 (clue)
				bpt = 3;
			}

			//The board holds the type in bit 10 & 11
			// 0=0, 1=1024(0x400), 2=2048(0x800), 3=3072(0xc00)
			board[idx] = bpt << 10;

			//Increment to next board position
			idx += 1;
		}
		bdata.close();
	}
}

void buildlookup(int piece[])
{
	//piece is the piece data 
	//piece[0]=piece number
	//piece[1]=piece type From file 0=corner, 1=edge, 2=internal >2=clue
	//piece[2]=top
	//piece[3]=right
	//piece[4]=bottom
	//piece[5]=left

	//-----------------------------------------------------------------------------------------------
	// Bit layout for 32 bit integer holding piece info
	//  31     30     22-29     17-21    12-16    10-11    5-9   0-4
	//   0      0    00000000   00000    00000      00    00000 00000
	// InUse  Clue   PieceId    Bottom   Right    Type     Top   Left 
	//-----------------------------------------------------------------------------------------------
	//xpiece[piece[0]] = piece[5] | (piece[2] << 5) | (piece[1] << 10) | (piece[3] << 12) | (piece[4] << 17);
	//populate array for top,left & type

	xpiecetop[piece[0]] = piece[2];
	xpieceright[piece[0]] = piece[3];
	xpiecebottom[piece[0]] = piece[4];
	xpieceleft[piece[0]] = piece[5];


	//The lookup array stores all the pieces that match top & left
	//We use this to match bottom of piece above and right of piece to the left and type of piece when checking
	//Using the 3 values (top,left,type) we get an integervalue that represents the index into the array
	//Then we populate for multiple enries the same
	//The value stored there is the piece number piece[0]
	//To get just the top,left & type we AND with 4095 (0xFFF) to clear out the top bits

	//Set a temp value representing the top,left,type
	//unsigned int piecelookupvalue = xpiece[piece[0]] & 0xFFF;

	//we populate our lookup vector based on the xpiece value
	//replace bottom with empty

	//We need to have entries for right empty, bottom empty and right and bottom empty
	//right empty

	//we only need right empty, bottom empty and righ+bottom empty

	//only add pieces thata re not clues to the lookup

	if (piece[1] < 3)
	{

		vlookup[piece[1]][piece[2]][23][piece[4]][piece[5]][lookupcount[piece[1]][piece[2]][23][piece[4]][piece[5]]] = piece[0];
		lookupcount[piece[1]][piece[2]][23][piece[4]][piece[5]]++;

		vlookup[piece[1]][piece[2]][piece[3]][23][piece[5]][lookupcount[piece[1]][piece[2]][piece[3]][23][piece[5]]] = piece[0];
		lookupcount[piece[1]][piece[2]][piece[3]][23][piece[5]]++;

		vlookup[piece[1]][piece[2]][23][23][piece[5]][lookupcount[piece[1]][piece[2]][23][23][piece[5]]] = piece[0];
		lookupcount[piece[1]][piece[2]][23][23][piece[5]]++;

		vlookup[piece[1]][piece[2]][23][23][23][lookupcount[piece[1]][piece[2]][23][23][23]] = piece[0];
		lookupcount[piece[1]][piece[2]][23][23][23]++;

		vlookup[piece[1]][piece[2]][piece[3]][piece[4]][23][lookupcount[piece[1]][piece[2]][piece[3]][piece[4]][23]] = piece[0];
		lookupcount[piece[1]][piece[2]][piece[3]][piece[4]][23]++;

		vlookup[piece[1]][piece[2]][piece[3]][23][23][lookupcount[piece[1]][piece[2]][piece[3]][23][23]] = piece[0];
		lookupcount[piece[1]][piece[2]][piece[3]][23][23]++;

		vlookup[piece[1]][piece[2]][23][piece[4]][23][lookupcount[piece[1]][piece[2]][23][piece[4]][23]] = piece[0];
		lookupcount[piece[1]][piece[2]][23][piece[4]][23]++;


	}




	//zlookup[(xpiece[piece[0]] & 0x1FFFF) | 0x2E0000].push_back(piece[0]);

	////replace right with empty
	//zlookup[(xpiece[piece[0]] & 0x3E0FFF) | 0x17000].push_back(piece[0]);

	////replace bottom and right with empty
	//zlookup[(xpiece[piece[0]] & 0xFFF) | 0x2F7000].push_back(piece[0]);

	//we also populate where right is empty, bottom is empty and both right and bottom is empty
	//the value 10111 is used to signify empty

	//Now put it into the lookup array after the last one.
	//The lookupcount stores how many of these we have in each lookup array
	//lookup[piecelookupvalue][lookupcount[piecelookupvalue]] = piece[0];

	//Then increment the number of these pieces we have
	//lookupcount[piece[2]][piece[3]][piece[4]][piece[5]]++;
	//lookupcount[piecelookupvalue]++;
}

void rotatepiece(int piece[])
{
	int tempstore;
	tempstore = piece[5];
	piece[5] = piece[4];
	piece[4] = piece[3];
	piece[3] = piece[2];
	piece[2] = tempstore;
}

void displaydata(bool force)
{
	displaytime.reset();

	if (maxplaced > maxever)
		maxever = maxplaced;

	elapsed = passtime.get_elapsed_time();
	totaltime = runtime.get_elapsed_time();

	if (reset_after_secs > 0 && (elapsed - prev_elapsed) > reset_after_secs)
		abandon = true;

	std::cout.imbue(std::locale(""));
	gotoxy(16, 0);
	std::cout << "                         ";
	gotoxy(16, 0, FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout << "(" << passes << ") " << elapsed << " [" << totaltime << "]";
	gotoxy(16, 1);
	std::cout << "                         ";
	gotoxy(16, 1, FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout << solvecount << " (" << backtracks << ")";
	gotoxy(16, 2);
	std::cout << "                         ";
	gotoxy(16, 2, FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout << maxplaced;
	gotoxy(19, 2, FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_RED);
	std::cout << " (" << maxever << ")";
	gotoxy(16, 3);
	std::cout << "                         ";
	gotoxy(16, 3, FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout << (unsigned int)(solvecount / elapsed);
	gotoxy(30, 3, FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_RED);
	std::cout << " [" << failedlookaheads << "]";
	std::cout.imbue(std::locale("C"));

	if (((maxplaced > prevmax || display_partial) && maxplaced >= show_after) || force)
	{
		//reset clock for elapsed only if not partial display
		if (!display_partial)
		{
			prev_elapsed = elapsed;
			savedata(maxplaced);
		}


		prevmax = maxplaced;
		for (unsigned int r = 4; r < boardsize + 4; r++)
		{
			for (unsigned int c = 1; c < boardsize * 5; c += 5)
			{
				gotoxy(c, r);
				std::cout.width(4);
				displaypiece = placedpieces[((r - 4) * boardsize) + (c - 1) / 5 + boardsize];
				if (displaypiece == 0 || displaypiece == 1025)
					std::cout << " ";
				else
					std::cout << (placedpieces[((r - 4) * boardsize) + (c - 1) / 5 + boardsize]);
			}
		}
	}
}


void solve2()
{
	abandon = false;
	index = 0;
	solvecount = 0;
	backtracks = 0;
	failedlookaheads = 0;

	do
	{
		if (displaytime.get_elapsed_time() > display_after_secs)
			displaydata(false);

		//if we have a placed piece (clue) at this location then just skip over and exit
		//skip over edges only do internal
		if (board[currentposition] == 0xC00)
			currentposition++;

		else
		{
			//PIECETYPE | BOTTOM OF PIECE IN PREV ROW | RH OF PIECE TO THE LEFT	| LH OF PIECE TO RIGHT | TOP OF PIECE IN NEXT ROW
			//piecekey = (board[currentposition] | ((xpiece[placedpieces[currentposition - boardsize]] >> 12) & 0x3E0) | ((xpiece[placedpieces[currentposition - 1]] >> 12) & 0x1F)) | ((xpiece[placedpieces[currentposition + 1]] & 0x1F) <<12) | ((xpiece[placedpieces[currentposition + boardsize]] & 0x3E0) << 12);
			top = xpiecebottom[placedpieces[currentposition - boardsize]];
			right = xpieceleft[placedpieces[currentposition + 1]];
			bottom = xpiecetop[placedpieces[currentposition + boardsize]];
			left = xpieceright[placedpieces[currentposition - 1]];
			piecetype = board[currentposition] >>10;

			//loop through all the matching pieces to see if one fits
			while (index < lookupcount[piecetype][top][right][bottom][left] && !abandon)
			{
				solvecount++;
			
				actualpiece = vlookup[piecetype][top][right][bottom][left][index];

				if (!pieceinuse[(actualpiece & 0xFF)])
				{
					//store the piece we've found
					placedpieces[currentposition] = actualpiece;

					//set that piece in use
					//Note we only need to set the base piece
					pieceinuse[(actualpiece & 0xFF)] = true;

					pieceok = false;

					//now look ahead and if we cant place anything then go back
					//skip if the next row has a clue piece
					if (board[currentposition+boardsize] != 0xC00)
					{
						//get a list of what pieces can be placed
						//if we can't palce a piece then we try another

						//top will be the bottom of the current piece
						chktop = xpiecebottom[actualpiece];

						//right will be left of the next row +1
						chkright = xpieceleft[placedpieces[currentposition + 1 + boardsize]];

						//bottom will be the top of the piece 2 rows ahead
						chkbottom = xpiecetop[placedpieces[currentposition + boardsize + boardsize]];

						//left will be the right of the piece in the next row -1
						chkleft = xpieceright[placedpieces[currentposition - 1 + boardsize]];

						//type will be the piece in the next row
						chkpiecetype = board[currentposition+boardsize] >> 10;

						if (lookupcount[chkpiecetype][chktop][chkright][chkbottom][chkleft] > 0)
						{
							//loop through the pieces and make sure they are no in use
							for (unsigned int x = 0; x < lookupcount[chkpiecetype][chktop][chkright][chkbottom][chkleft]; x++)
							{
								if (!pieceinuse[vlookup[chkpiecetype][chktop][chkright][chkbottom][chkleft][x] & 0xFF])
								{
									pieceok = true;
									break;
								}
							}
						}

					}
					else
					{
						pieceok = true;
					}


					if (pieceok)
					{
						piecesplacedonboard++;

						index++;
						stack[currentposition] = index;

						currentposition++;
						if (piecesplacedonboard > maxplaced)
						{
							maxplaced = piecesplacedonboard;
							displaydata(false);
						}
						index = 0;
						break;
					}
					else
					{
						//we need to remove the piece and mark it unused and continue
						pieceinuse[(placedpieces[currentposition] & 0xFF)] = false;
						placedpieces[currentposition] = 1025;
						failedlookaheads++;
					}
				}
				index++;
			}

			if (index >= lookupcount[piecetype][top][right][bottom][left])
			{
				if (resetafterbacktrack)
					abandon = true;
				else
				{
					//run out of pieces so go back and check next
					currentposition--;
					backtracks++;

					while (board[currentposition] == 0xC00)
						currentposition--;

					//clear piece in use
					pieceinuse[(placedpieces[currentposition] & 0xFF)] = false;
					piecesplacedonboard--;

					placedpieces[currentposition] = 1025;
					index = stack[currentposition];
				}
			}
		}
	} while (currentposition != finalposition && !abandon);
}

//void analyse()
//{
//
//	unsigned int atop[16];
//	unsigned int aright[16];
//	unsigned int abottom[16];
//	unsigned int aleft[16];
//
//	currentposition = boardsize;
//
//	for (int x = 0; x < 257; x++)
//	{
//		pieceinuse[x] = false;
//		////clear in use flag
//		////don't clear clue pieces
//		//if ((xpiece[x] & 0x40000000) != 0x40000000)
//		//	xpiece[x] &= 0x7FFFFFFF;
//	}
//
//	//initialise the placed pieces array
//	for (unsigned int x = 0; x < placedpieces_array_size; x++)
//	{
//		//clear placed pieces
//		if (board[x] != 0xC00)
//			if (x < boardsize || x >= (boardsize * boardsize) + boardsize)
//				placedpieces[x] = 0;
//			else
//				placedpieces[x] = 1025;
//	}
//
//
//	std::ofstream analysefile("257-Analyse.txt");
//
//
//
//
//
//
//
////this is our start corner (1)
//	placedpieces[currentposition] = 257;
//	currentposition++;
//
//	//now we loop through all possible patterns for top row
//	atop[0] = xpiecebottom[placedpieces[currentposition - boardsize]];
//	aright[0] = xpieceleft[placedpieces[currentposition + 1]];
//	abottom[0] = xpiecetop[placedpieces[currentposition + boardsize]];
//	aleft[0] = xpieceright[placedpieces[currentposition - 1]];
//
//
//	for (unsigned int p1 = 0; p1 < lookupcount[1][atop[0]][aright[0]][abottom[0]][aleft[0]]; p1++)
//	{
//		//place a piece and go to the next square (2)
//		actualpiece = vlookup[1][atop[0]][aright[0]][abottom[0]][aleft[0]][p1];
//		if (!pieceinuse[(actualpiece & 0xFF)])
//		{ 
//			
//			placedpieces[currentposition] = actualpiece;
//			pieceinuse[(actualpiece & 0xFF)] = true;
//			currentposition++;
//
//			//next square etc
//			atop[1] = xpiecebottom[placedpieces[currentposition - boardsize]];
//			aright[1] = xpieceleft[placedpieces[currentposition + 1]];
//			abottom[1] = xpiecetop[placedpieces[currentposition + boardsize]];
//			aleft[1] = xpieceright[placedpieces[currentposition - 1]];
//			for (unsigned int p2 = 0; p2 < lookupcount[1][atop[1]][aright[1]][abottom[1]][aleft[1]]; p2++)
//			{
//				//place a piece and go to the next square (3)
//				actualpiece = vlookup[1][atop[1]][aright[1]][abottom[1]][aleft[1]][p2];
//				if (!pieceinuse[(actualpiece & 0xFF)])
//				{
//					
//					placedpieces[currentposition] = actualpiece;
//					pieceinuse[(actualpiece & 0xFF)] = true;
//					currentposition++;
//
//					//next square etc
//					atop[2] = xpiecebottom[placedpieces[currentposition - boardsize]];
//					aright[2] = xpieceleft[placedpieces[currentposition + 1]];
//					abottom[2] = xpiecetop[placedpieces[currentposition + boardsize]];
//					aleft[2] = xpieceright[placedpieces[currentposition - 1]];
//					for (unsigned int p3 = 0; p3 < lookupcount[1][atop[2]][aright[2]][abottom[2]][aleft[2]]; p3++)
//					{
//						//place a piece and go to the next square (4)
//						actualpiece = vlookup[1][atop[2]][aright[2]][abottom[2]][aleft[2]][p3];
//						if (!pieceinuse[(actualpiece & 0xFF)])
//						{
//							
//							placedpieces[currentposition] = actualpiece;
//							pieceinuse[(actualpiece & 0xFF)] = true;
//							currentposition++;
//
//							//next square etc
//							atop[3] = xpiecebottom[placedpieces[currentposition - boardsize]];
//							aright[3] = xpieceleft[placedpieces[currentposition + 1]];
//							abottom[3] = xpiecetop[placedpieces[currentposition + boardsize]];
//							aleft[3] = xpieceright[placedpieces[currentposition - 1]];
//							for (unsigned int p4 = 0; p4 < lookupcount[1][atop[3]][aright[3]][abottom[3]][aleft[3]]; p4++)
//							{
//								//place a piece and go to the next square (5)
//								actualpiece = vlookup[1][atop[3]][aright[3]][abottom[3]][aleft[3]][p4];
//								if (!pieceinuse[(actualpiece & 0xFF)])
//								{
//									
//									placedpieces[currentposition] = actualpiece;
//									pieceinuse[(actualpiece & 0xFF)] = true;
//									currentposition++;
//
//									//next square etc
//									atop[4] = xpiecebottom[placedpieces[currentposition - boardsize]];
//									aright[4] = xpieceleft[placedpieces[currentposition + 1]];
//									abottom[4] = xpiecetop[placedpieces[currentposition + boardsize]];
//									aleft[4] = xpieceright[placedpieces[currentposition - 1]];
//									for (unsigned int p5 = 0; p5 < lookupcount[1][atop[4]][aright[4]][abottom[4]][aleft[4]]; p5++)
//									{
//										//place a piece and go to the next square (6)
//										actualpiece = vlookup[1][atop[4]][aright[4]][abottom[4]][aleft[4]][p5];
//										if (!pieceinuse[(actualpiece & 0xFF)])
//										{
//											
//											placedpieces[currentposition] = actualpiece;
//											pieceinuse[(actualpiece & 0xFF)] = true;
//											currentposition++;
//
//											//next square etc
//											atop[5] = xpiecebottom[placedpieces[currentposition - boardsize]];
//											aright[5] = xpieceleft[placedpieces[currentposition + 1]];
//											abottom[5] = xpiecetop[placedpieces[currentposition + boardsize]];
//											aleft[5] = xpieceright[placedpieces[currentposition - 1]];
//											for (unsigned int p6 = 0; p6 < lookupcount[1][atop[5]][aright[5]][abottom[5]][aleft[5]]; p6++)
//											{
//												//place a piece and go to the next square (7)
//												actualpiece = vlookup[1][atop[5]][aright[5]][abottom[5]][aleft[5]][p6];
//												if (!pieceinuse[(actualpiece & 0xFF)])
//												{
//													
//													placedpieces[currentposition] = actualpiece;
//													pieceinuse[(actualpiece & 0xFF)] = true;
//													currentposition++;
//
//													//next square etc
//													atop[6] = xpiecebottom[placedpieces[currentposition - boardsize]];
//													aright[6] = xpieceleft[placedpieces[currentposition + 1]];
//													abottom[6] = xpiecetop[placedpieces[currentposition + boardsize]];
//													aleft[6] = xpieceright[placedpieces[currentposition - 1]];
//													for (unsigned int p7 = 0; p7 < lookupcount[1][atop[6]][aright[6]][abottom[6]][aleft[6]]; p7++)
//													{
//														//place a piece and go to the next square (8)
//														actualpiece = vlookup[1][atop[6]][aright[6]][abottom[6]][aleft[6]][p7];
//														if (!pieceinuse[(actualpiece & 0xFF)])
//														{
//															
//															placedpieces[currentposition] = actualpiece;
//															pieceinuse[(actualpiece & 0xFF)] = true;
//															currentposition++;
//
//															//next square etc
//															atop[7] = xpiecebottom[placedpieces[currentposition - boardsize]];
//															aright[7] = xpieceleft[placedpieces[currentposition + 1]];
//															abottom[7] = xpiecetop[placedpieces[currentposition + boardsize]];
//															aleft[7] = xpieceright[placedpieces[currentposition - 1]];
//															for (unsigned int p8 = 0; p8 < lookupcount[1][atop[7]][aright[7]][abottom[7]][aleft[7]]; p8++)
//															{
//																//place a piece and go to the next square (9)
//																actualpiece = vlookup[1][atop[7]][aright[7]][abottom[7]][aleft[7]][p8];
//																if (!pieceinuse[(actualpiece & 0xFF)])
//																{
//																	
//																	placedpieces[currentposition] = actualpiece;
//																	pieceinuse[(actualpiece & 0xFF)] = true;
//																	currentposition++;
//
//																	//next square etc
//																	atop[8] = xpiecebottom[placedpieces[currentposition - boardsize]];
//																	aright[8] = xpieceleft[placedpieces[currentposition + 1]];
//																	abottom[8] = xpiecetop[placedpieces[currentposition + boardsize]];
//																	aleft[8] = xpieceright[placedpieces[currentposition - 1]];
//																	for (unsigned int p9 = 0; p9 < lookupcount[1][atop[8]][aright[8]][abottom[8]][aleft[8]]; p9++)
//																	{
//																		//place a piece and go to the next square (10)
//																		actualpiece = vlookup[1][atop[8]][aright[8]][abottom[8]][aleft[8]][p9];
//																		if (!pieceinuse[(actualpiece & 0xFF)])
//																		{
//																			
//																			placedpieces[currentposition] = actualpiece;
//																			pieceinuse[(actualpiece & 0xFF)] = true;
//																			currentposition++;
//
//																			//next square etc
//																			atop[9] = xpiecebottom[placedpieces[currentposition - boardsize]];
//																			aright[9] = xpieceleft[placedpieces[currentposition + 1]];
//																			abottom[9] = xpiecetop[placedpieces[currentposition + boardsize]];
//																			aleft[9] = xpieceright[placedpieces[currentposition - 1]];
//																			for (unsigned int p10 = 0; p10 < lookupcount[1][atop[9]][aright[9]][abottom[9]][aleft[9]]; p10++)
//																			{
//																				//place a piece and go to the next square (11)
//																				actualpiece = vlookup[1][atop[9]][aright[9]][abottom[9]][aleft[9]][p10];
//																				if (!pieceinuse[(actualpiece & 0xFF)])
//																				{
//																					
//																					placedpieces[currentposition] = actualpiece;
//																					pieceinuse[(actualpiece & 0xFF)] = true;
//																					currentposition++;
//
//																					//next square etc
//																					atop[10] = xpiecebottom[placedpieces[currentposition - boardsize]];
//																					aright[10] = xpieceleft[placedpieces[currentposition + 1]];
//																					abottom[10] = xpiecetop[placedpieces[currentposition + boardsize]];
//																					aleft[10] = xpieceright[placedpieces[currentposition - 1]];
//																					for (unsigned int p11 = 0; p11 < lookupcount[1][atop[10]][aright[10]][abottom[10]][aleft[10]]; p11++)
//																					{
//																						//place a piece and go to the next square (12)
//																						actualpiece = vlookup[1][atop[10]][aright[10]][abottom[10]][aleft[10]][p11];
//																						if (!pieceinuse[(actualpiece & 0xFF)])
//																						{
//																							
//																							placedpieces[currentposition] = actualpiece;
//																							pieceinuse[(actualpiece & 0xFF)] = true;
//																							currentposition++;
//
//																							//next square etc
//																							atop[11] = xpiecebottom[placedpieces[currentposition - boardsize]];
//																							aright[11] = xpieceleft[placedpieces[currentposition + 1]];
//																							abottom[11] = xpiecetop[placedpieces[currentposition + boardsize]];
//																							aleft[11] = xpieceright[placedpieces[currentposition - 1]];
//																							for (unsigned int p12 = 0; p12 < lookupcount[1][atop[11]][aright[11]][abottom[11]][aleft[11]]; p12++)
//																							{
//																								//place a piece and go to the next square (13)
//																								actualpiece = vlookup[1][atop[11]][aright[11]][abottom[11]][aleft[11]][p12];
//																								if (!pieceinuse[(actualpiece & 0xFF)])
//																								{
//																									
//																									placedpieces[currentposition] = actualpiece;
//																									pieceinuse[(actualpiece & 0xFF)] = true;
//																									currentposition++;
//
//																									//next square etc
//																									atop[12] = xpiecebottom[placedpieces[currentposition - boardsize]];
//																									aright[12] = xpieceleft[placedpieces[currentposition + 1]];
//																									abottom[12] = xpiecetop[placedpieces[currentposition + boardsize]];
//																									aleft[12] = xpieceright[placedpieces[currentposition - 1]];
//																									for (unsigned int p13 = 0; p13 < lookupcount[1][atop[12]][aright[12]][abottom[12]][aleft[12]]; p13++)
//																									{
//																										//place a piece and go to the next square (14)
//																										actualpiece = vlookup[1][atop[12]][aright[12]][abottom[12]][aleft[12]][p13];
//																										if (!pieceinuse[(actualpiece & 0xFF)])
//																										{
//																											
//																											placedpieces[currentposition] = actualpiece;
//																											pieceinuse[(actualpiece & 0xFF)] = true;
//																											currentposition++;
//
//																											//next square etc
//																											atop[13] = xpiecebottom[placedpieces[currentposition - boardsize]];
//																											aright[13] = xpieceleft[placedpieces[currentposition + 1]];
//																											abottom[13] = xpiecetop[placedpieces[currentposition + boardsize]];
//																											aleft[13] = xpieceright[placedpieces[currentposition - 1]];
//																											for (unsigned int p14 = 0; p14 < lookupcount[1][atop[13]][aright[13]][abottom[13]][aleft[13]]; p14++)
//																											{
//																												//place a piece and go to the next square (14)
//																												actualpiece = vlookup[1][atop[13]][aright[13]][abottom[13]][aleft[13]][p14];
//																												if (!pieceinuse[(actualpiece & 0xFF)])
//																												{
//																													
//																													placedpieces[currentposition] = actualpiece;
//																													pieceinuse[(actualpiece & 0xFF)] = true;
//																													currentposition++;
//
//																													//next square etc
//																													atop[14] = xpiecebottom[placedpieces[currentposition - boardsize]];
//																													aright[14] = xpieceleft[placedpieces[currentposition + 1]];
//																													abottom[14] = xpiecetop[placedpieces[currentposition + boardsize]];
//																													aleft[14] = xpieceright[placedpieces[currentposition - 1]];
//																													for (unsigned int p15 = 0; p15 < lookupcount[0][atop[14]][aright[14]][abottom[14]][aleft[14]]; p15++)
//																													{
//																														//OK this should be the top right corner
//																														//loop through these and write out the piece placements
//																														//place a piece and go to the next square (14)
//																														actualpiece = vlookup[0][atop[14]][aright[14]][abottom[14]][aleft[14]][p15];
//																														if (!pieceinuse[(actualpiece & 0xFF)])
//																														{
//																															
//																															placedpieces[currentposition] = actualpiece;
//																															//now write these out
//																															std::string data = "";
//																															for (unsigned int x = 16; x < 32; x++)
//																															{
//																																data = data + std::to_string(placedpieces[x]) + ",";
//																															}
//																															
//																															std::cout << data << "\n";
//																															analysefile << data << "\n";
//
//
//																														}
//																													}
//																													currentposition--;
//																													pieceinuse[(placedpieces[currentposition] & 0xFF)] = false;
//																													placedpieces[currentposition] = 1025;
//																												}
//																											}
//																											currentposition--;
//																											pieceinuse[(placedpieces[currentposition] & 0xFF)] = false;
//																											placedpieces[currentposition] = 1025;
//																										}
//																									}
//																									currentposition--;
//																									pieceinuse[(placedpieces[currentposition] & 0xFF)] = false;
//																									placedpieces[currentposition] = 1025;
//																								}
//																							}
//																							currentposition--;
//																							pieceinuse[(placedpieces[currentposition] & 0xFF)] = false;
//																							placedpieces[currentposition] = 1025;
//																						}
//																					}
//																					currentposition--;
//																					pieceinuse[(placedpieces[currentposition] & 0xFF)] = false;
//																					placedpieces[currentposition] = 1025;
//																				}
//																			}
//																			currentposition--;
//																			pieceinuse[(placedpieces[currentposition] & 0xFF)] = false;
//																			placedpieces[currentposition] = 1025;
//																		}
//																	}
//																	currentposition--;
//																	pieceinuse[(placedpieces[currentposition] & 0xFF)] = false;
//																	placedpieces[currentposition] = 1025;
//																}
//															}
//															currentposition--;
//															pieceinuse[(placedpieces[currentposition] & 0xFF)] = false;
//															placedpieces[currentposition] = 1025;
//														}
//													}
//													currentposition--;
//													pieceinuse[(placedpieces[currentposition] & 0xFF)] = false;
//													placedpieces[currentposition] = 1025;
//												}
//											}
//											currentposition--;
//											pieceinuse[(placedpieces[currentposition] & 0xFF)] = false;
//											placedpieces[currentposition] = 1025;
//										}
//									}
//									currentposition--;
//									pieceinuse[(placedpieces[currentposition] & 0xFF)] = false;
//									placedpieces[currentposition] = 1025;
//								}
//							}
//							currentposition--;
//							pieceinuse[(placedpieces[currentposition] & 0xFF)] = false;
//							placedpieces[currentposition] = 1025;
//						}
//					}
//					currentposition--;
//					pieceinuse[(placedpieces[currentposition] & 0xFF)] = false;
//					placedpieces[currentposition] = 1025;
//				}
//			}
//			currentposition--;
//			pieceinuse[(placedpieces[currentposition] & 0xFF)] = false;
//			placedpieces[currentposition] = 1025;
//		}
//
//	}
//
//	//finished
//	analysefile.close();
//	std::cout << "Finished..\n";
//	std::getchar();
//}