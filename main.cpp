
#include <iostream>
#include <ctime>

#include "Board.h"

#include <stack>

int main()
{
	using namespace std;
	
	cout << "\nWelcome to Matthew's 15-Puzzle program.\n";
	cout << "---------------------------------------------------\n";
	cout << "Solve the puzzle by sliding numbers into the empty space.\n";
	cout << "Only tiles adjacent to the empty space are movable.\n";
	cout << "---------------------------------------------------\n\n";

	cout << "Which mode would you like to start in?\n\n";
	cout << "1.\tTest Mode\n";
	cout << "2.\tRandom Mode\n\n";
	cout << "3.\tQuit Application\n\n";

	cout << "Choice: ";

	int choice = 0;
	bool testMode = false;

	cin >> choice;

	while(choice < 1 || choice > 3)
	{
		cout << "Invalid choice. Please pick again\n\n";
		cout << "Choice: ";
		cin >> choice;
	}

	switch(choice)
	{
	case 1:
		testMode = true;
		break;

	case 2:
		testMode = false;
		break;

	case 3:
		system("cls");

		cout << "\n\nQuitting now...\n\n";
			
		system("pause");

		break;
	}

	if(choice == 3)
		return EXIT_SUCCESS;

	system("CLS");

	cout << "\nCreating board now...\n";
	
	Board board(testMode);
	
	system("CLS");
	
	#pragma region USER INTERACTION
	/*
	do
	{
		// Display the Board
		board.DisplayBoard();
		
		// Check if the board is Completed
		if(board.IsComplete())
		{
			cout << "\n\nThe 15-puzzle is solved! Congratulations.\n\n";
			cout << "Moves Made: " << board.GetMoveCount() << "\n\n";

			// Display all the moves it took to solve the puzzle.
			board.DisplayMoveList();

			system("pause");
			break;
		}
		
		// if it's not complete, get input and move the pieces
		board.GetInput();

		system("CLS");
	}
	while (true);
	*/

	#pragma endregion

	bool repeat = true;

	while(repeat)
	{
		system("cls");

		cout << "Which type of algorithm would you like to solve with?\n\n";
		cout << "1.\tIterative Deepening Search\n";
		cout << "2.\tA* - Manhatten Distance\n";
		cout << "3.\tA* - Misplaced Tiles\n\n";
		cout << "4.\tQuit Application\n\n";

		cout << "Choice: ";

		int option = 0;
		cin >> option;

		while(option < 1 || option > 4)
		{
			cout << "Invalid choice. Please pick again\n\n";
			cout << "Choice: ";
			cin >> option;
		}

		switch(option)
		{
	
		#pragma region Iterative Deepening Search
	
		case 1:

			/* not working */
			//board.
			//;

			board.IterativeDeepeningSearch();
	
			break;

		#pragma endregion
	
		#pragma region A*

		case 2:
		
			board.Solve_ManhattenHeuristic();
		
			break;

		case 3:

			board.Solve_MisplacedTileHeuristic();
		
			break;
	
		#pragma endregion

		case 4:
			system("cls");

			cout << "\n\nQuitting now...\n\n";
			
			system("pause");
			repeat = false;
			break;
		}
	
		if(repeat)
		{
			// Check if the board is Completed
			if(board.IsComplete())
			{
				//system("CLS");

				cout << "\n\nThe 15-puzzle is solved! Congratulations.\n\n";

				cout << "Moves Made: " << board.GetMoveCount() << "\n\n";

				board.DisplayBoardStates();

				// Display all the moves it took to solve the puzzle.
			//	board.DisplayMoveList();

				system("pause");
			}
		}
	}
	return EXIT_SUCCESS;
}
