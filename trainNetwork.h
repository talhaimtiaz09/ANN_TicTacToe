#include "NueralNetwork.cpp"
#include "ticTacToe.h"

void train(Network &net){

    std::vector<std::vector<double> > data;
	std::ifstream file("test_data.data");
	if (file.is_open())
	{
		std::string s;
		while (std::getline(file, s))
		{
			std::vector<double> v;
			std::stringstream stream(s);
			std::string x;
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




	std::vector<double> res;
    std::vector<std::string> trainingFlickering;
	trainingFlickering.push_back("Training^*****");
	trainingFlickering.push_back("Training*^****");
	trainingFlickering.push_back("Training**^***");
	trainingFlickering.push_back("Training***^**");
	trainingFlickering.push_back("Training****^*");
	trainingFlickering.push_back("Training*****^");

		for (int i = 0; i < data.size(); i++)
		{

			std::vector<double> target;
			target.push_back(data[i].back());
			data[i].pop_back();

			net.feedForward(data[i]);
			net.backPropogate(target);
			data[i].push_back(target.at(0));
			std::cout <<trainingFlickering.at(i%trainingFlickering.size())<<std::endl;
		}


	std::cout << "\n------Training complete------\n";


}