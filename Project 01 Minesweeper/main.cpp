/*
	Project #1 : 1/8/2021 8 pm
	Make a simple Minesweeper game.
	Beginner     - 9 x 9 Board with 10 Mines
	Intermediate - 16 x 16 Board with 40 Mines
	Advanced     - 24 x 24 Board with 99 Mines
*/

#include <iostream>
#include <ctime>

#define BEGINNER 9
#define INTERMEDIATE 16
#define ADVANCED 24

#define BEGINNER_BOMB_COUNT 3
#define INTERMEDIATE_BOMB_COUNT 40
#define ADVANCED_BOMB_COUNT 99

using namespace std;

char Selection();
bool Difficulty(char input);
bool Reaffirm();
int SetSize(char input);
char** SetBoard(int size);
void PrintBoard(char** board, int size);
void SetBomb(char** board, int size);
void SelectSquare(int size, int& x, char& y);
void SetValues(char** board, int size);
bool CheckBomb(char** board, int x, char y);
char CheckValue(char** board, int x, int y, int size);
void PresetBoard(char** board, int size);
bool BoundaryCheck(int size, int x);
bool UserInput(char** Player_board, char** GM_board, int size);
int CheckInt();
void SquareCheck(char** Player_board, char** GM_board, int x, int y, int size);
bool WinCondition(char** Player_board, char** GM_board, int size);

int main()							
{					
	char input = ' ';
	do
	{
		input = Selection();
	} 
	while (!Difficulty(input));

	int size = SetSize(input);
	char** GM_board = SetBoard(size);
	
	PresetBoard(GM_board, size);

	char** Player_board = SetBoard(size);
	PrintBoard(Player_board, size);

	if (UserInput(Player_board, GM_board, size))
	{
		cout << "You Win" << endl;
	}
	else
	{
		cout << "You Lose" << endl;
	}
}

bool UserInput(char** Player_board, char** GM_board, int size)
{
	int x;
	char y;

	PrintBoard(GM_board, size);

	while (0 < 1)
	{
		SelectSquare(size, x, y);
		int yy = y - 65;
		while (Player_board[x][yy] != '-')
		{
			cout << "Please select a different location: " << endl;
			SelectSquare(size, x, y);
		}

		if (CheckBomb(GM_board, x, y))
		{
			PrintBoard(GM_board, size);
			return false;
		}

		int y_coord = y - 'A';
		SquareCheck(Player_board, GM_board, x, y_coord, size);
		PrintBoard(Player_board, size);
		if (WinCondition(Player_board, GM_board, size))
		{
			return true;
		}
	}
}

bool WinCondition(char** Player_board, char** GM_board, int size)
{
	int mines = 0;
	int counter = 0;
	switch (size)
	{
		case BEGINNER:
			mines = BEGINNER_BOMB_COUNT;
			break;
		case INTERMEDIATE:
			mines = INTERMEDIATE_BOMB_COUNT;
			break;
		case ADVANCED:
			mines = ADVANCED_BOMB_COUNT;
			break;
	}

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (Player_board[i][j] == '-')
			{
				counter++;
			}
		}
	}

	if (counter == mines)
	{
		return true;
	}
	else 
	{
		return false;
	}
}


void SquareCheck(char** Player_board, char** GM_board, int x, int y, int size)
{
	if (GM_board[y][x] > '0' && GM_board[y][x] != '*')
	{
		Player_board[y][x] = GM_board[y][x];
	}
	else
	{
		for (int i = x - 1; i <= x + 1; i++)
		{
			if (BoundaryCheck(size, i))
			{
				for (int j = y - 1; j <= y + 1; j++)
				{
					if (BoundaryCheck(size, j))
					{
						if (BoundaryCheck(size, i) && BoundaryCheck(size, j))
						{
							if (GM_board[j][i] == '0' && Player_board[j][i] == '-')
							{
								Player_board[j][i] = '0';
								SquareCheck(Player_board, GM_board, i, j, size);
							}

							if (GM_board[j][i] != '*' && Player_board[j][i] == '-')
							{
								Player_board[j][i] = GM_board[j][i];
							}
						}
					}
				}
			}
		}
	}
}


void SelectSquare(int size, int &x, char &y)
{
	cout << "Please select a square (x coordinate): ";
	x = CheckInt() - 1;
	while (x > size || x < 0)
	{
		cout << "Invalid input.  Try again: ";
		x = CheckInt() - 1;
		cout << endl;
	}

	cout << "Please select a square (y coordinate): ";
	cin >> y;

	while (y < 'A' || y >((size - 1) + 'A'))
	{
		cout << "Invalid input.  Try again: ";
		cin >> y;
		cout << endl;
	}

	cout << "x: " << x + 1 << " y: " << y << endl;
}

int CheckInt()
{
	int x;

	while (!(cin >> x))
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Invalid input.  Try again: ";
	}

	return x;
}

bool CheckBomb(char** board, int x, char y)
{
	int col = y - 65;
	if (board[col][x] == '*')
	{
		return true; 
	}

	return false;
}

void PresetBoard(char** board, int size)
{
	SetBomb(board, size);
	SetValues(board, size);
}

void SetBomb(char** board, int size)
{
	srand(time(NULL));
	int mines = 0;
	switch (size)
	{
	case BEGINNER:
		mines = BEGINNER_BOMB_COUNT;
		break;
	case INTERMEDIATE:
		mines = INTERMEDIATE_BOMB_COUNT;
		break;
	case ADVANCED:
		mines = ADVANCED_BOMB_COUNT;
		break;
	}

	for (int i = 0; i < mines; i++)
	{
		int x = rand() % size;
		int y = rand() % size;

		while (board[x][y] == '*')
		{
			x = rand() % size;
			y = rand() % size;
		}

		board[x][y] = '*';
	}
}

void SetValues(char** board, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (board[i][j] != '*')
			{
				board[i][j] = CheckValue(board, i, j, size);
			}
		}
	}
}

char CheckValue(char** board, int x, int y, int size)
{
	char counter = '0';
	// ===================================================
	//		Checks Surrounding Cells	(Func #005)
	// ===================================================
	for (int i = x - 1; i <= x + 1; i++)
	{
		if (BoundaryCheck(size, i))
		{
			for (int j = y - 1; j <= y + 1; j++)
			{
				if (BoundaryCheck(size, j))
				{
					if (BoundaryCheck(size, i) && BoundaryCheck(size, j))
					{
						if (board[i][j] == '*')
						{
							counter++;
						}
					}
				}
			}
		}
	}
	
	return counter;
}

bool BoundaryCheck(int size, int x)
{
	if (x < 0 || x > size - 1)
	{
		return false;
	}

	return true;
}

char Selection()
{
	char input = ' ';
	cout << "Please select difficulty: " << endl;
	cout << "A. Beginner     "			 << endl;
	cout << "B. Intermediate "			 << endl;
	cout << "C. Expert       "			 << endl;
	cout << "D. Quit         "			 << endl;
	cin >> input;

	return input;
}

bool Difficulty(char input)
{
	switch (input)
	{
	case 'A':
		cout << "You chose Beginner. Is this correct?" << endl;
		return Reaffirm();

	case 'B':
		cout << "You chose Intermediate. Is this correct?" << endl;
		return Reaffirm();

	case 'C':
		cout << "You chose Expert. Is this correct?" << endl;
		return Reaffirm();

	case 'D':
		cout << "Do you really want to quit?" << endl;
		return Reaffirm();

	default:
		cout << "Please enter a valid difficulty" << endl;
		return false;
	}
}

bool Reaffirm()
{
	char reaffirm = ' ';

	cout << "A. Yes                    B. No " << endl;
	cin >> reaffirm;

	if (reaffirm == 'A')
	{
		return true;
	}

	return false;
}

int SetSize(char input)
{
	switch (input)
	{
	case 'A':
		return BEGINNER;
	case 'B':
		return INTERMEDIATE;
	case 'C':
		return ADVANCED;
	default:
		return 0;
	}
}

char** SetBoard(int size)
{
	char** board = new char* [size];
	for (int i = 0; i < size; i++)
	{
		board[i] = new char[size];
	}

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			board[i][j] = '-';
		}
	}

	return board;
}

void PrintBoard(char** board, int size)
{	
	cout << ' ';

	for (int i = 0; i < size; i++)
	{
		cout << ' ' << i + 1;
	}

	cout << endl;

	for (int i = 0; i < size; i++)
	{
		cout << char(i + 65) << ' ';
		for (int j = 0; j < size; j++)
		{
			cout << board[i][j] << ' ';
		}

		cout << endl;
	}
} 