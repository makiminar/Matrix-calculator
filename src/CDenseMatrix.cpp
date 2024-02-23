/**
* @author Marketa Minarova <minarma5@fit.cvut.cz>
* @date 15.05.20
*/

#include "CDenseMatrix.h"

using namespace std;

CDenseMatrix::CDenseMatrix()
 : CMatrix()
{ }

CDenseMatrix::CDenseMatrix(int x, int y)
    : CMatrix(x, y)
{
        m_Matrix.resize(m_Rows);
        for( int i = 0; i < m_Rows; ++i)
            m_Matrix[i].resize(m_Cols);
}

void CDenseMatrix::PutElements(int x, int y, CMatrix::value val)
{
    m_Matrix[x][y] = val;
}

CMatrix::value CDenseMatrix::GetVal(int x, int y) const
{
    return m_Matrix[x][y];
}

std::unique_ptr<CMatrix> CDenseMatrix::Clone() const
{
    return make_unique<CDenseMatrix>(*this);
}

void CDenseMatrix::Split(int rows, int cols, int x, int y)
{
    CDenseMatrix matrix(rows, cols);
    for (int i = x, o = 0; i < m_Rows && o < matrix.GetRow(); ++i, ++o)
        for (int j = y, p = 0; j < m_Cols && p < matrix.GetCol(); ++j, ++p)
            matrix.PutElements(o,p, GetVal(i, j));

    *this = matrix;
}

void CDenseMatrix::Merge(const CMatrix &other)
{
    CDenseMatrix tmp(m_Rows, m_Cols + other.GetCol());
    for(int i = 0; i < m_Rows; ++i)
    {
        for( int j =0; j < m_Cols; ++j)
            tmp.PutElements(i, j, GetVal(i, j));
        for( int k = 0, m = m_Cols; m < m_Cols + other.GetCol(); ++k, ++m)
            tmp.PutElements(i, m, other.GetVal(i, k));
    }
    *this = tmp;
}

int CDenseMatrix::Rank()
{
    int rank = m_Rows, tmp = 0;
    CDenseMatrix tmpMatrix(*this);
    tmpMatrix.GEM();
    for (int i = 0; i < tmpMatrix.GetRow(); ++i)
    {
        for (int j = 0; j < tmpMatrix.GetCol(); ++j)
        {
            if(tmpMatrix.GetVal(i, j) == 0)
            {
                tmp++;
                if(j == tmpMatrix.GetCol() - 1 && tmp == tmpMatrix.GetCol() )
                    rank--;
            }
        }
        tmp = 0;
    }
    return rank;
}

void CDenseMatrix::Inv()
{
    CDenseMatrix identity = CDenseMatrix{}.IdentityM(m_Rows, m_Cols);
    CDenseMatrix augmented = *this;
    augmented.Merge(identity);

    augmented.LowerTriangular(m_Rows, augmented.GetCol(), m_Rows);
    augmented.UpperTriangular(m_Rows, m_Rows, m_Rows);

    augmented.Diagonal(augmented.GetRow(), augmented.GetCol());
    augmented.Split(identity.GetRow(), identity.GetCol(), 0, identity.GetRow());
    *this = augmented;
}

void CDenseMatrix::Trans()
{
    CDenseMatrix tmp(m_Cols, m_Rows);
    for(int i =0; i < m_Rows; ++i)
        for( int j = 0; j < m_Cols; ++j)
            tmp.PutElements(j, i, GetVal(i, j));

    *this = tmp;
}

CDenseMatrix &CDenseMatrix::operator=(CDenseMatrix other)
{
    if(this == &other)
        return *this;
    swap(m_Rows, other.m_Rows);
    swap(m_Cols, other.m_Cols);
    swap(m_Matrix, other.m_Matrix);
    return *this;
}

double CDenseMatrix::RecursiveDet(int n, const CMatrix & matrix)
{
    double det = 0;
    CDenseMatrix mat(n, n);

    //the ending condition, determinant of matrix 1x1 is value at position A[0][0]
    if(n == 1)
        return matrix.GetVal(0,0);

    for(int i = 0; i < n; ++i )
    {
        int k = 0, j = 0;
        for (int row = 0; row < n; ++row)
        {
            for (int col = 0; col < n; ++col)
            {
                if(row != 0 && col != i)
                {
                    mat.PutElements(k, j++, matrix.GetVal(row, col));

                    if(j==n -1)
                    {
                        j = 0;
                        k++;
                    }
                }
            }
        }
        det = det + pow(-1, i)*matrix.GetVal(0, i)*RecursiveDet(n - 1, mat);
    }
    return det;
}

CDenseMatrix CDenseMatrix::IdentityM(int rows, int cols)
{
    CDenseMatrix dm (rows, cols);
    dm.m_Matrix.resize(rows);
    for(int i = 0; i < rows; ++i)
        dm.m_Matrix[i].resize(cols);
    for(int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
        {
            if(i == j)
                dm.PutElements(i, j, 1);
            else
                dm.PutElements(i,j,0);
        }
    return dm;
}

void CDenseMatrix::Print(std::ostream &os) const
{
    CMatrix::Print(os);
}

bool CDenseMatrix::isSparse()
{
    return CMatrix::isSparse();
}

CDenseMatrix::CDenseMatrix(const CMatrix &matrix)
{
    m_Rows = matrix.GetRow();
    m_Cols = matrix.GetCol();
    m_Matrix.resize(m_Rows);
    for( int i = 0; i < m_Rows; ++i)
        m_Matrix[i].resize(m_Cols);

    for (int i = 0; i < m_Rows; ++i)
    {
        for (int j = 0; j < m_Cols; ++j)
        {
                m_Matrix[i][j] = matrix.GetVal(i, j);
        }
    }
}
