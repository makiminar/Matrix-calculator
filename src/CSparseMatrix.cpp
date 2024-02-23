/**
* @author Marketa Minarova <minarma5@fit.cvut.cz>
* @date 15.05.20
*/

#include "CSparseMatrix.h"

using namespace std;

CSparseMatrix::CSparseMatrix(int x, int y) : CMatrix(x, y)
{ }

void CSparseMatrix::PutElements(int x, int y, CMatrix::value val)
{
    auto it = m_Sparse.find({x, y});
    if(it != m_Sparse.end())
        it->second = val;
    else
        m_Sparse.insert({{x, y}, val});
}

CMatrix::value CSparseMatrix::GetVal(int x, int y) const
{
    auto it = m_Sparse.find({x, y});
    if(it != m_Sparse.end())
        return it->second;
    else
        return 0;
}

std::unique_ptr<CMatrix> CSparseMatrix::Clone() const
{
    return make_unique<CSparseMatrix>(*this);
}

void CSparseMatrix::Merge(const CMatrix &other)
{
    CSparseMatrix tmp(m_Rows, m_Cols + other.GetCol());
    for(int i = 0; i < m_Rows; ++i)
    {
        for( int j =0; j < m_Cols; ++j)
            tmp.PutElements(i, j, GetVal(i, j));
        for( int k = 0, m = m_Cols; m < m_Cols + other.GetCol(); ++k, ++m)
            tmp.PutElements(i, m, other.GetVal(i, k));
    }
    *this = tmp;
}

void CSparseMatrix::Split(int rows, int cols, int x, int y)
{
    CSparseMatrix matrix(rows, cols);
    for (int i = x, o = 0; i < m_Rows && o < matrix.GetRow() ; ++i, ++o)
        for (int j = y, p = 0; j < m_Cols && p < matrix.GetCol(); ++j, ++p)
        {
            matrix.PutElements(o,p, this->GetVal(i, j));
        }
    *this = matrix;
}

int CSparseMatrix::Rank()
{
    int rank = m_Rows, tmp = 0;
    CSparseMatrix tmpMatrix(*this);
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

void CSparseMatrix::Inv()
{
    CSparseMatrix identity = CSparseMatrix{}.IdentityM(m_Rows, m_Cols);
    CSparseMatrix augmented = *this;
    augmented.Merge(identity);

    augmented.LowerTriangular(m_Rows, augmented.GetCol(), m_Rows);
    augmented.UpperTriangular(m_Rows, m_Rows, m_Rows);

    augmented.Diagonal(augmented.GetRow(), augmented.GetCol());
    augmented.Split(identity.GetRow(), identity.GetCol(), 0, identity.GetRow());
    *this = augmented;
}

void CSparseMatrix::Trans()
{
    CSparseMatrix tmp(m_Cols, m_Rows);
    for(int i =0; i < m_Rows; ++i)
        for( int j = 0; j < m_Cols; ++j)
            tmp.PutElements(j, i, GetVal(i, j));

    *this = tmp;
}

CSparseMatrix &CSparseMatrix::operator=(CSparseMatrix other)
{
    if(this == &other)
        return *this;
    swap(m_Rows, other.m_Rows);
    swap(m_Cols, other.m_Cols);
    swap(m_Sparse, other.m_Sparse);
    return *this;
}

double CSparseMatrix::RecursiveDet(int n, const CMatrix & matrix)
{
    double det = 0;
    CSparseMatrix mat(n, n);

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

CSparseMatrix CSparseMatrix::IdentityM(int rows, int cols)
{
    CSparseMatrix sp(rows, cols);
    for(int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
        {
            if(i == j)
            {
                sp.PutElements(i,j, 1);
            }
        }
    return sp;
}

void CSparseMatrix::Print(std::ostream &os) const {
    CMatrix::Print(os);

}

bool CSparseMatrix::isSparse() {
    return CMatrix::isSparse();
}

CSparseMatrix::CSparseMatrix(const CMatrix & matrix)
{
    m_Rows = matrix.GetRow();
    m_Cols = matrix.GetCol();
    for (int i = 0; i < m_Rows; ++i)
    {
        for (int j = 0; j < m_Cols; ++j)
        {
            if(matrix.GetVal(i, j) != 0)
                m_Sparse.insert({{i, j}, matrix.GetVal(i, j)});
        }
    }
}
