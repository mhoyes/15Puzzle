
#include <list>
#include <string>
#include <stack>

using namespace std;

enum EMove { Up = 'w',
			 Down = 's',
			 Left = 'a',
			 Right = 'd' };

#ifndef BOARD_H
#define BOARD_H

// the number of rows and columns
static const int MAX_INDEX = 4;

struct Board2d
{
	char theBoard[MAX_INDEX][MAX_INDEX];

	bool operator ==(Board2d board)
	{
		bool equal = false;

		for (int row = 0; row < MAX_INDEX; ++row)
		{
			for (int col = 0; col < MAX_INDEX; ++col)
			{
				if(theBoard[row][col] == board.theBoard[row][col])
				{
					equal = true;
				}
				else
				{
					equal = false;
					break;
				}
			}

			if(!equal)
			{
				break;
			}
		}

		return equal;
	}
};

class Board
{
private:
	int movesMade;
	int depth;
	list<string> movesList;
	bool solved;
	
	stack<Board2d> boardStates;

	// initial board state, current board state, and the final board state
	Board2d initialBoard;
	Board2d currentBoard;
	Board2d finalBoard;

	// initializes the board.
	void InitializeBoard();

	// finds the location of the empty board space
	void LocateSpace(int&, int&, Board2d);
	list<int> LocateSpace(Board2d);
	void AssignCurrentBoard(Board2d);

	// moves the corresponding piece 
	void Move(Board2d, const EMove);
	list<Board2d> FindMoves(Board2d, list<int> space);
	bool DepthLimitedSearch(Board2d, int);
	bool RecursiveDLS(Board2d, int);

	// Heuristic: H1
	int CalculateMisplacedTiles(Board2d);

	// Heuristic: H2
	int CalculateManhattenDistance(Board2d);

	int FindDistance(Board2d, int, int);

	int Random(int, int);
	
public:
	Board();
	Board(bool testMode);
	void DisplayBoard();
	void PrintBoard(Board2d);
	void CreateTestBoard();
	void Randomize();
	void GetInput();
	bool IsComplete();
	int GetMoveCount();
	int GetDepth();
	string ConvertMoveToString(const EMove);
	void DisplayMoveList();
	void Solve();
	bool BoardsEqual(Board2d, Board2d);
	void IterativeDeepeningSearch();

	void Solve_ManhattenHeuristic();
	void Solve_MisplacedTileHeuristic();

	void DisplayBoardStates();
	
};

#endif