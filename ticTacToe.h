#include <iostream>
#include <vector>
#include <iomanip>
class TicTac
{
private:
    std::vector<double> board;

public:
    TicTac()
    {
        for (int i = 0; i < 9; i++)
        {
            board.push_back(0.01);
        }
    }
    void displayBoard()
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (this->at(i, j) == 1.0)
                    std::cout << "X";
                else if (this->at(i, j) == -1.0)
                    std::cout << "O";
                else
                    std::cout << "~";
                if (j != 2)
                    std::cout << std::setw(3) << "|" << std::setw(3);
            }

            if (i != 2)
                std::cout << "\n---------------";
            std::cout << std::endl;
        }
    }
    double evaluate()
    {

        if ((at(0, 0) == this->at(1, 1) && this->at(0, 0) == this->at(2, 2)) || (at(0, 2) == this->at(1, 1) && this->at(0, 2) == this->at(2, 0)) && this->at(1, 1) != 0.01)
            return this->at(1, 1);
        // checking horizontaly
        for (int i = 0; i < 3; i++)
        {
            if (at(i, 0) == this->at(i, 1) && at(i, 1) == this->at(i, 2) && this->at(i, 0) != 0.01)
            {
                return this->at(i, 1);
            }
            // checking vertically
            else if (at(0, i) == this->at(1, i) && this->at(0, i) == this->at(2, i) && this->at(1, i) != 0.01)
                return this->at(0, i);
        }
        return -101;
    }
    double &setBoard(int index)
    {
      return  board.at(index);
    }
    double at(int row, int col)
    {
        // As 1D vector is used instead of 2D so, 2D index are
        // converted in 1D by formula [row*rowSize+column]
        return board.at((row * 3) + col);
    }
    bool draw()
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
                if (this->at(i, j) == 0.01)
                    return false;
        }
        return true;
    }
    bool isEmpty(int x)
    {
        if (this->board.at(x) != 0.01)
            return true;
        else
            return false;
    }
};