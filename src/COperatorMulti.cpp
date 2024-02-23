/**
* @author Marketa Minarova <minarma5@fit.cvut.cz>
* @date 05.05.20
*/

#include "COperatorMulti.h"

using namespace std;

std::unique_ptr<CMatrix> COperatorMulti::Evaluate()
{
    unique_ptr<CMatrix> matrix{new CDenseMatrix(m_Left->GetRow(), m_Right->GetCol())};

    for(int i = 0; i < m_Left->GetRow(); ++i)
        for(int  j = 0; j < m_Right->GetCol(); ++j)
            for(int  k = 0; k < m_Left->GetCol(); ++k)
                matrix->PutElements(i, j, matrix->GetVal(i, j) + (m_Left->GetVal(i, k) * m_Right->GetVal(k, j )) );


    if(matrix->isSparse())
    {
        unique_ptr<CMatrix> sparse{new CSparseMatrix(*matrix)};
        return sparse;
    }
    return matrix;
}

COperatorMulti::COperatorMulti(const CMatrix & left, const CMatrix & right)
: COperator(left, right)
 { }

bool COperatorMulti::CorrectSize()
{
    return m_Left->GetCol() == m_Right->GetRow();
}