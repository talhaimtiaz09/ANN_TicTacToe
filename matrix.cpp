#include <iostream>
#include <cmath>
#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;
template <typename x>
class Matrix
{
private:
    int _rows;
    int _cols;
    vector<vector<x> > matrix;

public:
    Matrix(int _rows = 0, int cols = 0)
    {
        this->_rows = _rows;
        this->_cols = cols;
        matrix.resize(_rows);
        for (int i = 0; i < _rows; i++)
            matrix[i].resize(cols);
        for (int i = 0; i < _rows; i++)
            for (int j = 0; j < _cols; j++)
                matrix[i][j] = 0;
    }

    void d_TANH()
    {
        for (int i = 0; i < _rows; i++)
            for (int j = 0; j < _cols; j++)
            {
                double temp = matrix[i][j];
                this->matrix[i][j] = 1.0 - (temp * temp);
            }
    }
    void _TANH()
    {
        for (int i = 0; i < _rows; i++)
            for (int j = 0; j < _cols; j++)
            {

                this->matrix[i][j] = tanh(matrix[i][j]);
            }
    }
    x &at(int row, int col)
    {
        if (col < 0 || row < 0)
        {
            cout << "Invalid index!\n";
        }

        return matrix[row][col];
    }

    Matrix negative()
    {
        Matrix output(_rows, _cols);
        for (int i = 0; i < _rows; i++)
            for (int j = 0; j < _cols; j++)
                output.matrix[i][j] = -1 * matrix[i][j];
        return output;
    }
    void display()
    {
        for (int i = 0; i < _rows; i++)
        {
            for (int j = 0; j < _cols; j++)
            {
                cout << matrix[i][j] << '\t';
            }
            cout << endl;
        }
    }
    Matrix multiply(Matrix mat)
    {
        if (this->_cols != mat._rows)
        {
            cout << "Columns of first matrix is not equal to rows of second matrix.";
        }
        Matrix product(_rows, mat._cols);
        for (int i = 0; i < product._rows; i++)
        {
            for (int j = 0; j < mat._cols; j++)
            {
                double res = 0.0;
                for (int k = 0; k < mat._rows; k++)
                {
                    res += matrix[i][k] * mat.matrix[k][j];
                }
                product.at(i, j) = res;
            }
        }

        return product;
    }
    Matrix multiplyElements(Matrix &mat)
    {
        if (_rows != mat._rows || _cols != mat._cols)
        {
            cout <<_rows<<"x"<<_cols <<" != "<<mat._rows<<"x"<<mat._cols<<endl;

        }
        Matrix output(_rows, _cols);
        for (int i = 0; i < _rows; i++)
            for (int j = 0; j < _cols; j++)
                output.matrix[i][j] = matrix[i][j] * mat.matrix[i][j];
        return output;
    }
    Matrix add(Matrix mat)
    {
        Matrix err(0, 0);
        if (_rows != mat._rows || _cols != mat._cols)
        {
            cout << "The number of _rows or the number of _cols are not equal.";
            return err;
        }
        else
        {
            Matrix sum(_rows, _cols);
            for (int i = 0; i < _rows; i++)
                for (int j = 0; j < _cols; j++)
                    sum.matrix[i][j] = matrix[i][j] + mat.matrix[i][j];
            return sum;
        }
    }
    Matrix multiplyScalar(x scaleFactor)
    {
        Matrix product(_rows, _cols);
        for (int i = 0; i < _rows; i++)
            for (int j = 0; j < _cols; j++)
                product.matrix[i][j] = scaleFactor * matrix[i][j];
        return product;
    }
    Matrix addScalar(x scaleFactor)
    {
        Matrix sum(_rows, _cols);
        for (int i = 0; i < _rows; i++)
            for (int j = 0; j < _cols; j++)
                sum.matrix[i][j] = matrix[i][j] + scaleFactor;
        return sum;
    }
    Matrix transpose()
    {
        Matrix output(_cols, _rows);
        for (int i = 0; i < _rows; i++)
            for (int j = 0; j < _cols; j++)
                output.matrix[j][i] = matrix[i][j];
        return output;
    }
    vector<x> & _atrow(int row){
     return matrix[row];
    }
    int get_rows() { return this->_rows; }

    int getCols() { return this->_cols; }
};

