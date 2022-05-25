#include <iostream>
#include <cmath>
#include <iostream>
#include <vector>
#include <cstdlib>

template <typename x>
class Matrix
{
private:
    int _rows;
    int _cols;
    std::vector<std::vector<x> > matrix;

public:
    //constructor to maek matrix of desired size filled intially with 0
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
    //fucniton to calculate dervated sigmoid on each element of matrix
    void derivatedSigmoid()
    {
        for (int i = 0; i < _rows; i++)
            for (int j = 0; j < _cols; j++)
            {
                double temp = matrix[i][j];
                this->matrix[i][j] = temp*(1-temp);
            }
    }
    //funciton to cacluate the sigmoid function on each element of matrix
    void sigmoid()
    {
        for (int i = 0; i < _rows; i++)
            for (int j = 0; j < _cols; j++)
            {
                double temp=1.0/(1+exp(-1*matrix[i][j]));
                this->matrix[i][j] = temp;
            }
    }
    //return reference of element of matrix at particular (row,column) of template type
    x &at(int row, int col)
    {
        if (col < 0 || row < 0)
        {
            cout << "Invalid index!\n";
        }

        return matrix[row][col];
    }
    //fucntion to take negative of each element of matrix
    Matrix negative()
    {
        Matrix output(_rows, _cols);
        for (int i = 0; i < _rows; i++)
            for (int j = 0; j < _cols; j++)
                output.matrix[i][j] = -1 * matrix[i][j];
        return output;
    }
    
    //funtin to perform matrix multiplication between two matrices
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
    /*function to multiply each element of one matrix 
     *with coresponding element of other matrix*/
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
    //function to add coresponding enteries of two matrices
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
    /*function to multiply a provide scalar with each element of matrix*/
    Matrix multiplyScalar(x scaleFactor)
    {
        Matrix product(_rows, _cols);
        for (int i = 0; i < _rows; i++)
            for (int j = 0; j < _cols; j++)
                product.matrix[i][j] = scaleFactor * matrix[i][j];
        return product;
    }
    /*funciton to add a scalar to each element of matrix*/
    Matrix addScalar(x scaleFactor)
    {
        Matrix sum(_rows, _cols);
        for (int i = 0; i < _rows; i++)
            for (int j = 0; j < _cols; j++)
                sum.matrix[i][j] = matrix[i][j] + scaleFactor;
        return sum;
    }
    /*Transpose fucntions returns a new matrix of columns x rows
    order of current matrix and copy all the corresponding values into
    new matrix*/
    Matrix transpose()
    {
        Matrix output(_cols, _rows);
        for (int i = 0; i < _rows; i++)
            for (int j = 0; j < _cols; j++)
                output.matrix[j][i] = matrix[i][j];
        return output;
    }

    /*returns reference of row of matrix at provided row index*/
    std::vector<x> & _atrow(int row){
     return matrix[row];
    }

    /*returns number of rows in matrix(row size)*/
    int get_rows() { return this->_rows; }
    /*returns number of columns in matrix(column size)*/
    int getCols() { return this->_cols; }
};

