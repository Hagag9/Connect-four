#include <iostream>
#include <stdlib.h>
#include<windows.h>
using namespace std;

// connect four
const HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
int GetNumber(string message)
{
	int number;
	do {
		cout << message;
		cin >> number;
	} while (number < 1 || number > 7);
	return number;
}
void DrawBoard(char boardArr[6][7])
{
	for (int i = 1; i <= 7; i++)
		cout << "  " << i << " ";

	cout << endl;
	for (int i = 0; i <= 6; i++)
	{
		int x = i - 1;
		int y = -1;
		for (int j = 0; j <= 28; j++)
		{
			if (i == 0)
			{
				cout << "=";
			}
			else
			{
				if (j % 4 == 0)
				{
					cout << "|";
					y++;
				}
				else if (boardArr[x][y] != ' '
					&& (j == 2 || j == 6 || j == 10 || j == 14 || j == 18 || j == 22 || j == 26))
				{

					if (boardArr[x][y] == '#')
					{
						SetConsoleTextAttribute(h, 4);
						cout << boardArr[x][y];
						SetConsoleTextAttribute(h, 7);
					}
					else
					{
						SetConsoleTextAttribute(h, 1);
						cout << boardArr[x][y];
						SetConsoleTextAttribute(h, 7);
					}

				}
				else
					cout << "_";
			}
		}
		cout << endl;
	}
}
void ClearBoard(char boardArr[6][7])
{
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			boardArr[i][j] = ' ';
		}
	}
}
char CheckWinner(char boardArr[6][7])
{
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (boardArr[i][j] != ' ' && boardArr[i][j] == boardArr[i][j + 1]        //Check rows
				&& boardArr[i][j + 1] == boardArr[i][j + 2]
				&& boardArr[i][j + 2] == boardArr[i][j + 3])
				return boardArr[i][j];
		}
	}
	for (int j = 0; j < 7; j++)
	{
		for (int i = 0; i < 3; i++)
		{
			if (boardArr[i][j] != ' '
				&& boardArr[i][j] == boardArr[i + 1][j]								 //Check cols
				&& boardArr[i + 1][j] == boardArr[i + 2][j]
				&& boardArr[i + 2][j] == boardArr[i + 3][j])
				return boardArr[i][j];
		}
	}
	for (int i = 0; i < 6; i++)                     // check right diagonals
	{
		for (int j = 3; j < 7; j++)
		{
			if (boardArr[i][j] != ' '
				&& boardArr[i][j] == boardArr[i + 1][j - 1]
				&& boardArr[i + 1][j - 1] == boardArr[i + 2][j - 2]
				&& boardArr[i + 2][j - 2] == boardArr[i + 3][j - 3]
				)
				return boardArr[i][j];
		}
	}
	for (int i = 5; i >= 0; i--)	                     // check left diagonals
	{
		for (int j = 3; j < 7; j++)
		{
			if (boardArr[i][j] != ' '
				&& boardArr[i][j] == boardArr[i - 1][j - 1]
				&& boardArr[i - 1][j - 1] == boardArr[i - 2][j - 2]
				&& boardArr[i - 2][j - 2] == boardArr[i - 3][j - 3]
				)
				return boardArr[i][j];
		}
	}
}
void SetPosition(int y, char ColNum, char boardArr[6][7])
{
	for (int i = 5; i >= 0; i--)
	{
		if (boardArr[i][y - 1] == ' ')
		{
			boardArr[i][y - 1] = ColNum;
			return;
		}
	}
}
bool WhoWin(char Winner)
{
	if (Winner == '#')
	{
		SetConsoleTextAttribute(h, 4);
		cout << "\n\t\t\t****** RED PLAYER IS WINNER  ******\n";
		SetConsoleTextAttribute(h, 7);
		return true;
	}
	else if (Winner == '$')
	{
		SetConsoleTextAttribute(h, 1);
		cout << "\n\t\t\t****** BLUE PLAYER IS WINNER ******  \n";
		SetConsoleTextAttribute(h, 7);
		return true;
	}
	return false;
}
void ConnectFourGame()
{
	char boardArr[6][7];
	ClearBoard(boardArr);
	DrawBoard(boardArr);
	int choice = 0;
	bool IsRed = true;
	while (choice < 42)
	{

		if (IsRed)
		{
			SetConsoleTextAttribute(h, 4);
			cout << "\n Red player round >>> \n";
			SetConsoleTextAttribute(h, 7);
		}
		else
		{
			SetConsoleTextAttribute(h, 1);
			cout << "\n Blue player round >>>\n";
			SetConsoleTextAttribute(h, 7);
		}
		int y = GetNumber("\nPlease select number of col: ");
		while (boardArr[0][y - 1] != ' ')
		{
			SetConsoleTextAttribute(h, 3);
			cout << "Coulmn Filled ! Please try to input again: ";
			SetConsoleTextAttribute(h, 7);
			cin >> y;
		}
		if (IsRed)
			SetPosition(y, '#', boardArr);
		else
			SetPosition(y, '$', boardArr);

		IsRed = !IsRed;
		system("cls");
		DrawBoard(boardArr);
		if (WhoWin(CheckWinner(boardArr)))
			return;
		choice++;
	}
	cout << "\n\n\t\tGAME OVER !!!!" << endl;
	system("color 4F");
	cout << "\a";
}
int main()
{

	ConnectFourGame();

	return 0;
}



