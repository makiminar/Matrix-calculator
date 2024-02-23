/**
* @author Marketa Minarova <minarma5@fit.cvut.cz>
* @date 05.05.20
*/

#pragma once
#include "COperator.h"
#include "CSparseMatrix.h"
#include "CDenseMatrix.h"

/**
 * Derived class from COperator, COperatorMinus represents class which handles subtraction among matrices
 */

class COperatorMinus : public COperator
{
public:
    ~COperatorMinus  () override = default;

    COperatorMinus   ( const CMatrix & left, const CMatrix & right );

    /** method, which check if the operation of subtraction can be executed - only if matrices have same size */
    bool CorrectSize () override ;

    /** method which evaluates the subtraction of matrices, element by element*/
    std::unique_ptr<CMatrix> Evaluate() override;
};


