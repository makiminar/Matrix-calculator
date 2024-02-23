/**
* @author Marketa Minarova <minarma5@fit.cvut.cz>
* @date 05.05.20
*/

#pragma once
#include "COperator.h"
#include "CSparseMatrix.h"
#include "CDenseMatrix.h"

/**
 * Derived class from COperator, COperatorPlus takes care of matrix addition
 */

class COperatorPlus : public COperator
{
public:
    ~COperatorPlus   ( ) override = default;
    COperatorPlus    ( const CMatrix & left, const CMatrix & right);

    /** @return true, if matrices have same row and column size*/
    bool CorrectSize ( ) override ;

    /** method evaluates the operation of addition, element by element */
    std::unique_ptr<CMatrix> Evaluate() override;
};


