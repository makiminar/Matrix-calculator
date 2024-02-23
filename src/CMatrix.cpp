/**
* @author Marketa Minarova <minarma5@fit.cvut.cz>
* @date 02.05.20
*/

#include "CMatrix.h"

using namespace std;

CMatrix::CMatrix( int x, int y)
   : m_Rows(x), m_Cols(y)
{ }

void CMatrix::Print(ostream & os) const
{
    for(int i = 0; i < m_Rows; ++i)
    {
        for(int j =0; j < m_Cols; ++j)
            os << GetVal(i, j) << " ";
        os<< endl;
    }
}

void CMatrix::GEM()
{
    LowerTriangular(m_Rows, m_Cols, m_Cols);
}

int CMatrix::GetCol() const {
    return m_Cols;
}

int CMatrix::GetRow() const {
    return m_Rows;
}

bool CMatrix::isSquare()
{
    return ( m_Rows == m_Cols );
}

double CMatrix::Determinant()
{
    if(m_Cols == 2)
        return ( GetVal(0, 0) * GetVal(1, 1) - GetVal(0, 1) * GetVal(1, 0) );
    return RecursiveDet(m_Cols, *this);

}

void CMatrix::LowerTriangular(int rows, int cols, int colMax)
{
    double c;
    int col = 0;
    for (int i = 0; i < rows; i++)
    {
        if(col >= colMax)
            return;
        //if element of current row and column is zero, find other row in which element is not zero and switch them
        if (GetVal(i, col) == 0)
        {
            for (int j = i + 1; j < rows; ++j)
            {
                if(GetVal(j, col) != 0)
                {
                    for (int k = 0; k < cols; ++k)
                    {
                        double tmp = GetVal(i, k);
                        PutElements(i, k, GetVal(j, k));
                        PutElements(j, k, tmp);
                    }
                    break;
                }
            }
        }
        // Make all columns below current column (and row) 0
        for (int p = i + 1; p < rows; p++)
        {
            if (GetVal(i, col) == 0)
            {
                c = 1;
            }
            else
            {
                c = -GetVal(p, col) / GetVal(i, col);
            }

            for (int j = i; j < cols; j++)
            {
                if (i == j)
                {
                    PutElements(p, j, 0);
                }
                else
                {
                    PutElements(p, j, GetVal(p, j) + c*GetVal(i, j));
                }
            }
        }
        col++;
    }
}

void CMatrix::UpperTriangular(int rows, int cols, int colMax)
{
    double c;
    int col = 0;
    for (int i = rows - 1; i >= 0; i--)
    {
        if(col >= colMax)
            return;

        if (GetVal(i, i) == 0)
        {
            for (int j = i - 1; j >= 0; j--)
            {
                if(GetVal(j, i) != 0)
                {
                    for (int k = 0; k < cols; ++k)
                    {
                        double tmp = GetVal(i, k);
                        PutElements(i, k, GetVal(j, k));
                        PutElements(j, k, tmp);
                    }
                    break;
                }
            }
        }
        // Make all rows below this row 0 in current column
        for (int p = i - 1; p >= 0; p--)
        {
            if (GetVal(i, i) == 0)
            {
                c = 1;
            }
            else
            {
                c = -GetVal(p, i) / GetVal(i, i);
            }

            for (int j = i; j < GetCol(); j++)
            {
                if (i == j)
                {
                    PutElements(p, j, 0);
                }
                else
                {
                    PutElements(p, j, GetVal(p, j) + c*GetVal(i, j));
                }
            }
        }
        col++;
    }
}

void CMatrix::Diagonal(int rows, int cols)
{
    double c;
    for (int i = 0; i < rows; ++i)
    {
        c = GetVal(i, i);
        PutElements(i, i, GetVal(i, i) / c);
        for(int j = rows; j < cols; ++j)
        {
            PutElements(i, j, GetVal(i, j) / c);
        }
    }
}

bool CMatrix::isSparse()
{
    int cnt = 0;
    for(int i =0; i < m_Rows; ++i)
    {
        for (int j = 0; j < m_Cols; ++j)
        {
            if(GetVal(i, j) != 0)
                cnt++;
        }
    }
    return cnt < SPARSE_CONSTANT * min(m_Rows, m_Cols);
}

