#include "trainNetwork.h"

#define X 1.0
#define O -1.0
#define _blank 0.01

void screenClear()
{
	// Function to print 50 new empty lines to clear the scree/console
	for (int i = 0; i < 50; i++)
		std::cout << std::endl;
}

int main()
{

	int choice;
	double prob;
	double min = RAND_MAX;
	int AImove;
	TicTac gameBoard;
	std::vector<double> test;
	std::vector<int> topology;
	topology.push_back(9);
	topology.push_back(18);
	topology.push_back(18);
	topology.push_back(1);

	Network net(topology, 0.05);
	/*passing the network to training funciton for feedforward
	back propogation*/
	train(net);

	while (true)
	{
		test.clear();
		test.resize(0);
		gameBoard.displayBoard();

		std::cout << "Enter your option: ";
		std::cin >> choice;
		while (gameBoard.isEmpty(choice - 1))
		{
			std::cout << "The cell is already filled\n";
			std::cout << "Enter your options: ";
			std::cin >> choice;
		}

		switch (choice)
		{
		case 1:
			gameBoard.setBoard(choice - 1) = X;
			break;
		case 2:
			gameBoard.setBoard(choice - 1) = X;
			break;
		case 3:
			gameBoard.setBoard(choice - 1) = X;
			break;
		case 4:
			gameBoard.setBoard(choice - 1) = X;
			break;
		case 5:
			gameBoard.setBoard(choice - 1) = X;
			break;
		case 6:
			gameBoard.setBoard(choice - 1) = X;
			break;
		case 7:
			gameBoard.setBoard(choice - 1) = X;
			break;
		case 8:
			gameBoard.setBoard(choice - 1) = X;
			break;
		case 9:
			gameBoard.setBoard(choice - 1) = X;
			break;
		}

		screenClear();
		gameBoard.displayBoard();

		//coping all the board values into a temporary test vector
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				test.push_back(gameBoard.at(i, j));
			}
		}

		// Checking for game win/loss/draw!

		if (gameBoard.evaluate() == X)
		{
			std::cout << "X won the game\n";
			break;
		}
		else if (gameBoard.evaluate() == O)
		{
			std::cout << "O won the game\n";
			break;
		}
		else if (gameBoard.draw())
		{
			std::cout << "\n------Game DRAW!------\n";
			break;
		}
		/**
		 * @brief
		 * cell left and calulate the probability at each step
		 * and then in the end make the best AImove possible
		 * A test vector is used for this purpose and then after testing
		 *changes are made to original boradGame vector
		 */

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (gameBoard.at(i, j) == _blank)
				{

					test.at((i * 3) + j) = O;
					net.feedForward(test);
					prob = net.valueMatrices.back().at(0, 0);
					test.at((i * 3) + j) = _blank;

					if (min > prob)
					{
						min = prob;
						AImove = (i * 3) + j;
					}
				}
			}
		}

		gameBoard.setBoard(AImove) = O;
		screenClear();
	}
}