#include <iostream>
#include <ctime>
#include "Board.h"

Board::Board()
{
	// no moves made
	movesMade = 0;
	depth = 0;
	solved = false;
	
	// Initialize the Initial Board, Current Board and Final Board.
	InitializeBoard();//currentBoard);

	// Randomize the board.
	Randomize();//currentBoard);
}

Board::Board(bool testMode)
{
	// no moves made
	movesMade = 0;
	depth = 0;
	solved = false;

	// Initialize the Initial Board, Current Board and Final Board.
	InitializeBoard();//currentBoard);

	if(testMode)
	{
		// Create the Test Board
		CreateTestBoard();
	}
	else
	{
		// Randomize the board.
		Randomize();//currentBoard);
	}

	//boardStates.push(currentBoard);
}

void Board::InitializeBoard()//Board2d currentBoard)
{
	const char InitialBoard[MAX_INDEX][MAX_INDEX] =
	{
			{'1', '2', '3', '4'},
			{'5', '6', '7', '8'},
			{'9', 'A', 'B', 'C'},
			{'D', 'E', 'F', ' '}
	};
	
	for (int row = 0; row < MAX_INDEX; ++row)
	{
		for (int col = 0; col < MAX_INDEX; ++col)
		{
			//initialBoard[row][col] = InitialBoard[row][col];

			currentBoard.theBoard[row][col] = InitialBoard[row][col];

			finalBoard.theBoard[row][col] = InitialBoard[row][col];
		}
	}
}

void Board::LocateSpace(int& Row, int& Col, Board2d currentBoard)
{
	bool spaceLocated = false;

	for (int row = 0; row < MAX_INDEX; ++row)
	{
		for (int col = 0; col < MAX_INDEX; ++col)
		{
			if (currentBoard.theBoard[row][col] == ' ')
			{
				Row = row;
				Col = col;
				spaceLocated = true;
				break;
			}
		}

		// if the space is found, quit searching
		if(spaceLocated)
		{
			break;
		}
	}
}

list<int> Board::LocateSpace(Board2d currentBoard)
{
	list<int> space;

	bool spaceLocated = false;

	for (int row = 0; row < MAX_INDEX; ++row)
	{
		for (int col = 0; col < MAX_INDEX; ++col)
		{
			// if the current location on the board is a space
			if (currentBoard.theBoard[row][col] == ' ')
			{
				// space found, store location
				space.push_back(row);
				space.push_back(col);
				spaceLocated = true;
				break;
			}
		}

		// if the space is found, quit searching
		if(spaceLocated)
		{
			break;
		}
	}

	return space;

}

void Board::CreateTestBoard()
{
	const char TestBoard[MAX_INDEX][MAX_INDEX] =
	{
		#pragma region SMALL TEST PUZZLE
		//{' ', '1', '3', '4'},
		//{'5', '2', '6', '8'},
		//{'9', 'A', '7', 'C'},
		//{'D', 'E', 'B', 'F'}
		#pragma endregion

		#pragma region BIGGER TEST PUZZLE
		{' ', '1', '2', '3'},
		{'6', '7', '8', '4'},
		{'5', '9', 'A', 'B'},
		{'D', 'E', 'F', 'C'}
		#pragma endregion
	};

	// go through all board locations and occupy each location with
	// cooresponding TestBoard locations value
	for (int row = 0; row < MAX_INDEX; ++row)
	{
		for (int col = 0; col < MAX_INDEX; ++col)
		{
			initialBoard.theBoard[row][col] = TestBoard[row][col];

			currentBoard.theBoard[row][col] = TestBoard[row][col];
		}
	}
}

void Board::Randomize()
{
	srand((unsigned int)time(0));

	list<int> nums;
	list<int> allNums;

	int max = (MAX_INDEX * MAX_INDEX) - 1;

	// make a list and occupy it with numbers 0 - max
	for (int i = 0; i <= max; i++)
	{
		allNums.push_back(i);
	}
	
	// continue until all numbers are gone
	while(!allNums.empty())
	{
		// find a number between 0 - # of elements in allNums list
		int num = Random(0, allNums.size());
		int count = 0;

		// iterate through the list and find the number
		for(list<int>::iterator number = allNums.begin(); number != allNums.end(); number++)
		{
			count++;

			if(count == num)
			{
				// store it in nums list
				nums.push_back(*number);

				// remove it from allNums list so the list shrinks
				// as you add to nums list
				allNums.remove(*number);
				
				break;
			}
		}
	}

	// when all numbers 0 - max are in list
	for (int row = 0; row < MAX_INDEX; ++row)
	{
		for (int col = 0; col < MAX_INDEX; ++col)
		{
			// grab the front number
			int number = nums.front();
			char character;

			// # 0 is the space
			if(number == 0)
			{
				character = ' ';
			}
			// convert number to ascii representation in char format
			else if(number < 10)
			{
				character = (char)(number + 48);
			}
			// if 10 or higher, convert number to ascii representation but
			// skipping ascii 58 - 64 to get alphabetical numbers 
			else
			{
				character = (char)(number + 55);
			}

			// store that char in the current location on the currentBoard
			currentBoard.theBoard[row][col] = character;

			// pop that number off the front of the list
			nums.pop_front();

			// store the current location on the currentBoard as the initialBoard as well
			initialBoard.theBoard[row][col] = currentBoard.theBoard[row][col];
		}
	}
}

void Board::PrintBoard(Board2d currentBoard)
{
	int askiOffset = 55;

	for (int row = 0; row < MAX_INDEX; ++row)
	{
		for (int col = 0; col < MAX_INDEX; ++col)
		{
			char A = 'A';

			// if the current locations value is the askii value of A or higher
			if((int)currentBoard.theBoard[row][col] >= (int)A)
			{
				// convert the character into the actual number but in char format
				int character = ((int)currentBoard.theBoard[row][col] - askiOffset);
				cout << character << "\t";
			}
			else
			{
				// display the current locations value
				cout << currentBoard.theBoard[row][col] << "\t";
			}
		}

		cout << endl;
	}
}

void Board::GetInput()
{
	//using namespace std;

	char cNextMove;
	
	cout << endl << "w = Up, s = Down, a = Left, d = Right" << endl;
	
	cin >> cNextMove;

	EMove eNextMove = (EMove)cNextMove;

	Move(currentBoard, eNextMove);

	cout << endl;
}

void Board::Move(Board2d currentBoard, const EMove keMove)
{
	int rowSpace;
	int colSpace;

	LocateSpace(rowSpace, colSpace, currentBoard);

	int rowMove(rowSpace);
	int colMove(colSpace);

	switch (keMove)
	{
		case Up:
			{
				rowMove = rowSpace + 1;
				break;
			}
		case Down:
			{
				rowMove = rowSpace - 1;
				break;
			}
		case Left:
			{
				colMove = colSpace + 1;
				break;
			}
		case Right:
			{
				colMove = colSpace - 1;
				break;
			}
	}

	// Make sure that the square to be moved is in bounds
	if (rowMove >= 0 && rowMove < MAX_INDEX && colMove >= 0 && colMove < MAX_INDEX)
	{
		currentBoard.theBoard[rowSpace][colSpace]	= currentBoard.theBoard[rowMove][colMove];
		currentBoard.theBoard[rowMove][colMove]	= ' ';
		movesMade++;

		string move = ConvertMoveToString(keMove);

		movesList.insert(movesList.end(), move);
	} 
}

void Board::DisplayBoard()
{
	cout << endl << "The Current Board:" << endl;

	PrintBoard(currentBoard);
}

bool Board::IsComplete()
{
	bool complete = false;

	for (int row = 0; row < MAX_INDEX; ++row)
	{
		for (int col = 0; col < MAX_INDEX; ++col)
		{
			// check each location to see if it matches
			if(currentBoard.theBoard[row][col] == finalBoard.theBoard[row][col])
			{
				complete = true;
			}
			else
			{
				// if not, break out since it's clearly not a match
				// no need to check anymore
				complete = false;
				break;
			}
		}
	}

	return complete;
}

int Board::GetMoveCount()
{
	return movesMade;
}

int Board::GetDepth()
{
	return depth;
}

string Board::ConvertMoveToString(const EMove keMove)
{
	string move;

	switch (keMove)
	{
		case Up:
			{
				move = "Up";
				break;
			}
		case Down:
			{
				move = "Down";
				break;
			}
		case Left:
			{
				move = "Left";
				break;
			}
		case Right:
			{
				move = "Right";
				break;
			}
	}

	return move;
}

void Board::DisplayMoveList()
{
	// create a string iterator
	list<string>::iterator iteration;

	cout << "\tMoves List:\n";
	cout << "\t___________\n\n";

	int count = 0;

	// display each move
	for(iteration = movesList.begin(); iteration != movesList.end(); iteration++)
	{
		count++;
		cout << count << ": " << *iteration << "\n\n";
	}
}

void Board::Solve()
{
	bool solved = false;

	depth = 0;
	int count = depth;

	list<Board2d> checkedStates;

	// continue until solved is true
	while(!solved)
	{
		// current board = initial board
		AssignCurrentBoard(initialBoard);

		// make sure states are clear
		while(!boardStates.empty())
		{
			boardStates.pop();
		}

		// for each depth 
		for(int i = 0; i <= depth; i++)
		{
			if(i == 6)
			{
				system("pause");
			}
			if(i == 0)
			{
				boardStates.push(currentBoard);
			
				if(!IsComplete())
				{
					checkedStates.push_back(currentBoard);
				}
				else
				{
					solved = true;
					break;
				}
			}
			else
			{
				while(count <= depth)
				{
					list<Board2d> states;
					list<Board2d> theCheckedStates;

					boardStates.push(currentBoard);
			
					if(!IsComplete())
					{
						checkedStates.push_back(currentBoard);
					}

					states = FindMoves(currentBoard, LocateSpace(currentBoard));

					// check if any board states have already been checked.
					for(list<Board2d>::iterator state = states.begin(); state != states.end(); state++)
					{
						for(list<Board2d>::iterator checkedState = checkedStates.begin(); checkedState != checkedStates.end(); checkedState++)
						{
							if(BoardsEqual(*state, *checkedState))
							{
								if(!states.empty())
								{
									theCheckedStates.push_back(*state);
								}
							}
						}
					}

					// since I can't remove from states list in a loop that uses states
					for(list<Board2d>::iterator checked = theCheckedStates.begin(); checked != theCheckedStates.end(); checked++)
					{
						// TODO: Find whats wrong here. Compiler error. Commenting out for now
						//states.remove(*checked);
					}

					// check each unchecked board state
					for(list<Board2d>::iterator currentState = states.begin(); currentState != states.end(); currentState++)
					{
						// push the board state onto the stack
						boardStates.push(*currentState);

						// assign the top board in the stack as the current board
						AssignCurrentBoard(boardStates.top());

						// check if the board state is the final board state
						if(BoardsEqual(*currentState, finalBoard))
						{
							solved = true;
							break;
						}
						else
						{
							if(count == depth)
							{
								// make sure the stack isn't empty
								if(!boardStates.empty())
								{
									// remove from the stack
									boardStates.pop();
								}

								if(!boardStates.empty())
								{
									Board2d board = boardStates.top();
									// reassign the top board in the stack as the current board
									AssignCurrentBoard(board);
								}
							}
							else
							{
								count++;
							}
						}
					}

					#pragma region CLEAR STACKS

					while(!boardStates.empty())
					{
						boardStates.pop();
					}

					while(!checkedStates.empty())
					{
						checkedStates.pop_back();
					}
				}
			}
			#pragma endregion
		}// end for

		if(!solved)
		{
			depth++;
		}
	}// end while
}

void Board::IterativeDeepeningSearch()
{
	bool solved = false;
	depth = -1;

	DisplayBoard();

	system("pause");

	while(!solved)
	{
		depth++;
		
		solved = DepthLimitedSearch(currentBoard, depth);
	}
}

bool Board::DepthLimitedSearch(Board2d board, int limit)
{
	return RecursiveDLS(board, limit);
}

bool Board::RecursiveDLS(Board2d board, int limit)
{
	if(!solved)
	{
		bool cutoffHasntOccurred = true;
		solved = false;
	
		movesMade++;
	
		system("CLS");

		cout << "Searching for solution...";

		if(BoardsEqual(board, finalBoard))
		{
			AssignCurrentBoard(board);
			solved = true;
			return true;
		}
		else if(limit == 0)
		{
			cutoffHasntOccurred = false;
			return cutoffHasntOccurred;
		}
		else
		{
			cutoffHasntOccurred = false;

			list<Board2d> states;

			states = FindMoves(board, LocateSpace(board));

			// check each unchecked board state
			for(list<Board2d>::iterator currentState = states.begin(); currentState != states.end(); currentState++)
			{
				if(!solved)
				{
					bool result = RecursiveDLS(*currentState, limit - 1);

					if(result == true)
					{
						cutoffHasntOccurred = true;
						break;
					}
				}
			}

			if(!cutoffHasntOccurred)
			{
				return cutoffHasntOccurred;
			}
		}
	}
}

list<Board2d> Board::FindMoves(Board2d theBoard, list<int> space)
{
	int row = space.front();
	
	int col = space.back();
	
	if(row < 0)
	{
		row = 0;
	}

	if(col < 0)
	{
		col = 0;
	}

	list<Board2d> moves;

	// iterate 4 times since there can only be 4 possible
	// moves at any given state
	for(int i = 0; i < 4; i++)
	{
		int r = 0;
		int c = 0;

		switch(i)
		{
		case 0:
			{
				r = row + 1;
				c = col;
				break;
			}
		case 1:
			{
				r = row - 1;
				c = col;
				break;
			}
		case 2:
			{
				c = col + 1;
				r = row;
				break;
			}
		case 3:
			{
				c = col - 1;
				r = row;
				break;
			}
		}

		// Make sure that the square to be moved is in bounds
		if (r >= 0 && r < MAX_INDEX && c >= 0 && c < MAX_INDEX)
		{
			Board2d board;
			
			for(int i = 0; i < MAX_INDEX; i++)
			{
				for(int j = 0; j < MAX_INDEX; j++)
				{
					board.theBoard[i][j] = theBoard.theBoard[i][j];
				}
			}
			
			char temp = board.theBoard[r][c];
			board.theBoard[r][c]	= board.theBoard[row][col];
			board.theBoard[row][col]	= temp;//' ';
			
			moves.push_back(board);
		} 
	}
	
	return moves;
}

bool Board::BoardsEqual(Board2d board1, Board2d board2)
{
	return (board1 == board2);
}

void Board::AssignCurrentBoard(Board2d board)
{
	for (int row = 0; row < MAX_INDEX; ++row)
	{
		for (int col = 0; col < MAX_INDEX; ++col)
		{
			currentBoard.theBoard[row][col] = board.theBoard[row][col];
		}
	}
}

// Heuristic: H1
int Board::CalculateMisplacedTiles(Board2d board)
{
	int numOfTiles = 0;

	for (int row = 0; row < MAX_INDEX; ++row)
	{
		for (int col = 0; col < MAX_INDEX; ++col)
		{
			// if the current locations value doesnt match the final boards location value
			if(board.theBoard[row][col] != finalBoard.theBoard[row][col])
			{
				numOfTiles++;
			}
		}
	}

	return numOfTiles;
}

// Heuristic: H2
int Board::CalculateManhattenDistance(Board2d board)
{
	int distance = 0;

	for (int row = 0; row < MAX_INDEX; ++row)
	{
		for (int col = 0; col < MAX_INDEX; ++col)
		{
			if(board.theBoard[row][col] == finalBoard.theBoard[MAX_INDEX - 1][MAX_INDEX - 1])
				continue;
			
			int tempDist = FindDistance(board, row, col);

			distance += tempDist;
			
		}
	}
	
	return distance;
}

int Board::FindDistance(Board2d board, int row, int column)
{
	int dist = 0;

	int finalRow = 0;
	int finalCol = 0;

	// find the char from the location
	char character = board.theBoard[row][column];

	for (int r = 0; r < MAX_INDEX; ++r)
	{
		// if the finalRow and finalColumn are found, jump out
		if(finalRow != 0 && finalCol != 0)
		{
			break;
		}
		
		for (int c = 0; c < MAX_INDEX; ++c)
		{
			// if we have found the character within the finalBoard
			if(finalBoard.theBoard[r][c] == character)
			{
				// store the location and jump out
				finalRow = r;
				finalCol = c;
				break;
			}
		}
	}

	// if the row of the board, and the final row differ
	// add the sum of both
	if(row != finalRow)
	{
		// always subtract the smaller number from the bigger one
		if(row > finalRow)
		{
			dist += (row - finalRow);
		}
		else
		{
			dist += (finalRow - row);
		}
	}

	// if the column of the board, and the final column differ
	// add the sum of both
	if(column != finalCol)
	{
		// always subtract the smaller number from the bigger one
		if(column > finalCol)
		{
			dist += (column - finalCol);
		}
		else
		{
			dist += (finalCol - column);
		}
	}

	return dist;
}

void Board::Solve_ManhattenHeuristic()
{
	AssignCurrentBoard(initialBoard);
	DisplayBoard();

	movesMade = 0;

	bool solved = false;

	while(!boardStates.empty())
	{
		boardStates.pop();
	}

	boardStates.push(currentBoard);

	if(BoardsEqual(currentBoard, finalBoard))
	{
		return;
	}
	
	while(!solved)
	{
		list<Board2d> states;

		states = FindMoves(currentBoard, LocateSpace(currentBoard));

		// make it huge from the beginning
		int lowestDistance = 99999;

		// check each unchecked board state
		for(list<Board2d>::iterator currentState = states.begin(); currentState != states.end(); currentState++)
		{
			int dist = CalculateManhattenDistance(*currentState);
			
			if(dist <= lowestDistance)
			{
				lowestDistance = dist;
				AssignCurrentBoard(*currentState);
			}
		}

		boardStates.push(currentBoard);

		movesMade++;

		if(BoardsEqual(currentBoard, finalBoard))
		{
			solved = true;
		}

	}
}

void Board::Solve_MisplacedTileHeuristic()
{
	AssignCurrentBoard(initialBoard);

	DisplayBoard();

	movesMade = 0;

	bool solved = false;
	
	while(!boardStates.empty())
	{
		boardStates.pop();
	}

	boardStates.push(currentBoard);

	if(BoardsEqual(currentBoard, finalBoard))
	{
		return;
	}
	
	while(!solved)
	{
		list<Board2d> states;

		states = FindMoves(currentBoard, LocateSpace(currentBoard));

		// make it huge from the beginning
		int lowestMisplaced = 99999;

		// check each unchecked board state
		for(list<Board2d>::iterator currentState = states.begin(); currentState != states.end(); currentState++)
		{
			int misplaced = CalculateMisplacedTiles(*currentState);
			
			if(misplaced <= lowestMisplaced)
			{
				lowestMisplaced = misplaced;
				AssignCurrentBoard(*currentState);
			}
		}

		boardStates.push(currentBoard);

		movesMade++;

		if(BoardsEqual(currentBoard, finalBoard))
		{
			solved = true;
		}

	}
}

void Board::DisplayBoardStates()
{
	if(boardStates.empty())
	{
		cout << "There are no board states to display.\n\n";
		return;
	}

	list<Board2d> states;

	while(!boardStates.empty())
	{
		//PrintBoard(boardStates.top());
		states.push_back(boardStates.top());
		boardStates.pop();

		//cout << "\n\n";
	}

	states.reverse();

	for(list<Board2d>::iterator currentState = states.begin(); currentState != states.end(); currentState++)
	{
		PrintBoard(*currentState);

		cout << "\n\n";
	}

}

int Board::Random(int lowerLimit, int upperLimit) {

	// returns a random number within the given boundary
	// using bit shifting, shifting left 5 bits, since 
	// rand() only returns up to 16 bits. This way, we
	// can get up to 32 bits of numbers (e.g: 1,000,000)
	return 1 + ((rand() << 5) + (rand() % 32)) % upperLimit;
}