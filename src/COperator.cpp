/**
* @author Marketa Minarova <minarma5@fit.cvut.cz>
* @date 05.05.20
*/

#include "COperator.h"

using namespace std;

COperator::COperator(const CMatrix & left,const CMatrix & right)
    :   m_Left(left.Clone()), m_Right(right.Clone())
{ }
