/**
* @author Marketa Minarova <minarma5@fit.cvut.cz>
* @date 05.05.20
*/

#include "COperatorMinus.h"

using namespace std;

std::unique_ptr<CMatrix> COperatorMinus::Evaluate() {

    unique_ptr<CMatrix> matrix {new CDenseMatrix(m_Left->GetRow(), m_Left->GetCol())};
    for(int i =0; i < matrix->GetRow(); ++i)
        for(int j =0; j < matrix->GetCol(); ++j)
            matrix->PutElements(i, j,  m_Left->GetVal(i, j) - m_Right->GetVal(i, j));
    if(matrix->isSparse())
    {
        unique_ptr<CMatrix> sparsematrix {new CSparseMatrix(*matrix)};
        return sparsematrix;
    }
    return matrix;
}

COperatorMinus::COperatorMinus(const CMatrix & left, const CMatrix & right)
: COperator(left, right)
{ }

bool COperatorMinus::CorrectSize()
{
    return !(m_Right->GetRow() != m_Left->GetRow() || m_Right->GetCol() != m_Left->GetCol());
}
