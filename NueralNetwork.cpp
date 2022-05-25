#include "matrix.cpp"
#include <fstream>
#include <sstream>
#include<time.h>
#include<cstdlib>


class Network
{
public:
    std::vector<Matrix<double> > weightMatrices;
    std::vector<Matrix<double> > biasMatrices;
    std::vector<Matrix<double> > valueMatrices;
    std::vector<int> topology;
    float learningRate;

public:
    Network(std::vector<int> _topology, float l_Rate);
    void feedForward(std::vector<double> inputs);
    void backPropogate(std::vector<double> target);
    std::vector<std::vector<float> > getPredictions();
      double m_error;
    double m_recentAverageError;
    static double m_recentAverageSmoothingFactor;
};
double Network::m_recentAverageSmoothingFactor=100.0;

double randomValueGenerator()
{
    srand(time(0));
    return rand() / double(RAND_MAX);
}

Network::Network(std::vector<int> _topology, float l_Rate)
{

    this->learningRate = l_Rate;
    valueMatrices.resize(topology.size());
    for (int i = 0; i < _topology.size(); i++)
        this->topology.push_back(_topology.at(i));
    for (int i = 0; i < topology.size() - 1; i++)
    {
        //matrix tempWeight(2,3);
        //matrix tempBias(2,3);

        
        Matrix<double> tempWeightMatrix(this->topology[i], topology[i + 1]);
        for (int j = 0; j < tempWeightMatrix.get_rows(); j++)
        {
            for (int k = 0; k < tempWeightMatrix.getCols(); k++)
            {
                tempWeightMatrix.at(j, k) = randomValueGenerator();
            }
        }

        Matrix<double> tempBiasMatrix(1, this->topology[i + 1]);

        for (int j = 0; j < tempBiasMatrix.getCols(); j++)
            tempBiasMatrix.at(0, j) = randomValueGenerator();

        weightMatrices.push_back(tempWeightMatrix);
        biasMatrices.push_back(tempBiasMatrix);
    }
    valueMatrices.resize(topology.size());
}
void Network::feedForward(std::vector<double> inputs)
{
    if (inputs.size() != this->topology.at(0))
    {
        std::cout << "Invalid no. of inputs\n";
        std::cout << "There are currently " << this->topology.at(0) << " Neurons in input layer\n";
        std::cout << "input is: " << inputs.size() << std::endl;
    }
    Matrix<double> inputLayer(1, inputs.size());
    for (int i = 0; i < inputs.size(); i++)
    {
        inputLayer.at(0, i) = inputs[i];
    }

    for (int i = 0; i <= weightMatrices.size(); i++)
    {

       if (i == weightMatrices.size())
           valueMatrices[i] = inputLayer;
       else
        {
            valueMatrices[i] = inputLayer;
            // 1x9  9x6 1x6
            inputLayer = inputLayer.multiply(weightMatrices[i]);
            inputLayer = inputLayer.add(biasMatrices[i]);
            inputLayer.sigmoid();
        }
    }
}

void Network::backPropogate(std::vector<double> target)
{
    if (target.size() != this->topology.back())
    {
        std::cout << "Invalid no. of inputs\n";
        std::cout << "There are currently " << this->topology.back() << " Neurons in output layer\n";
    }

        m_error=0.0;
        double delta = target[0] - valueMatrices.back().at(0,0);
        m_error = (delta * delta);
    m_error = sqrt(m_error); // RMS

    m_recentAverageError =
            (m_recentAverageError * m_recentAverageSmoothingFactor + m_error)
            / (m_recentAverageSmoothingFactor + 1.0);


    Matrix<double> errorLayer(1, target.size());
    errorLayer._atrow(0) = target;
    errorLayer = errorLayer.add(valueMatrices.back().negative());

    for (int i = weightMatrices.size() - 1; i >= 0; i--)
    {

        Matrix<double> previousErrors = errorLayer.multiply(weightMatrices[i].transpose());
        // calculating output derivatice;
        valueMatrices[i + 1].derivatedSigmoid();
        Matrix<double> derivatedOutput = valueMatrices[i + 1];
        Matrix<double> gradient = errorLayer.multiplyElements(derivatedOutput);
        gradient = gradient.multiplyScalar(this->learningRate);
        Matrix<double> weightGradient = valueMatrices[i].transpose().multiply(gradient);
        biasMatrices[i] = biasMatrices[i].add(gradient);
        weightMatrices[i] = weightMatrices[i].add(weightGradient);
        errorLayer = previousErrors;
    }
}


