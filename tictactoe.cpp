#include "NueralNetwork.cpp"
#include "ticTacToe.h"

int main()
{
	// x,x,x,x,o,o,x,o,o,positive
	std::vector<std::vector<double> > data;
	ifstream file("test_data.data");
	if (file.is_open())
	{
		string s;
		while (getline(file, s))
		{
			std::vector<double> v;
			stringstream stream(s);
			string x;
			while (getline(stream, x, ','))
			{
				double temp = double(stoi(x));
				if (x == "2")
					v.push_back(0.01);
				else
					v.push_back(temp);
			}
			data.push_back(v);
		}
	}

	std::vector<int> topology;

	topology.push_back(9);
	topology.push_back(27);
	topology.push_back(3);
	topology.push_back(1);

	Network net(topology, 0.025);

	std::vector<double> res;

	for (int i = 0; i < data.size(); i++)
	{

		std::vector<double> target;
		target.push_back(data[i].back());
		data[i].pop_back();

		net.feedForward(data[i]);
		net.backPropogate(target);
		data[i].push_back(target.at(0));
		// cout << "error : " << net.m_recentAverageError << std::endl;

		// for (int k = 0; k < net.valueMatrices.back().get_rows(); k++)
		// {
		// 	for (int j = 0; j < net.valueMatrices.back().getCols(); j++)
		// 		cout << net.valueMatrices.back().at(k, j) << " ";
		// 	cout << std::endl;
		// }
	}

	//     net.feedForward(inp);
	std::cout<<"training complete\n";

	TicTac board;

	std::vector<double> test;

	int choice;

	while (true)
	{
		test.clear();
		test.resize(0);
		board.displayBoard();
	
		if(board.evaluate()==1.0){
			std::cout<<"X won the game\n";
			break;
		}
		else if(board.evaluate()==-1.0){
			std::cout<<"O won the game\n";
			break;
		}
	    else if(board.draw()){
			std::cout<<"\n------Game DRAW!------\n";
		}
		cout << "Enter your option: ";
		std::cin >> choice;
		board.setBoard()

		switch (choice)
		{
		case 1:
			board.setBoard(0, 0, 1);
			break;
		case 2:
			board.setBoard(0, 1, 1.0);
			break;
		case 3:
			board.setBoard(0, 2, 1.0);
			break;
		case 4:
			board.setBoard(1, 0, 1.0);
			break;
		case 5:
			board.setBoard(1, 1, 1.0);
			break;
		case 6:
			board.setBoard(1, 2, 1.0);
			break;
		case 7:
			board.setBoard(2, 0, 1.0);
			break;
		case 8:
			board.setBoard(2, 1, 1.0);
			break;
		case 9:
			board.setBoard(2, 2, 1.0);
			break;
		}
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				test.push_back(board.at(i, j));
			}
		}
		bool b = false;
		double prob;
		double min = RAND_MAX;
		int m_i, m_j;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (board.at(i, j) == 0.01)
				{

					test.at((i * 3) + j) = -1;
					net.feedForward(test);
					prob = net.valueMatrices.back().at(0, 0);
					test.at((i * 3) + j) = 0.01;
					cout << prob << std::endl;

					// min=prob;

					if (min > prob)
					{
						min = prob;
						m_i = i;
						m_j = j;
					}
				}
			}
		}

		board.setBoard(m_i, m_j, -1);
	}
}