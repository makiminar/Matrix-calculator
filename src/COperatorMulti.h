/**
* @author Marketa Minarova <minarma5@fit.cvut.cz>
* @date 05.05.20
*/

#pragma once

#include "COperator.h"
#include "CSparseMatrix.h"
#include "CDenseMatrix.h"

/**
 * Derived class from COperator, COperatorMulti handles matrix multiplication
 */

class COperatorMulti : public COperator
{
public:
    ~COperatorMulti  () override = default;
    COperatorMulti   (const CMatrix & left, const CMatrix & right);

    /** method, which check if matrices have correct size for multiplication
     * left matrix's column size must be same as right's row size */
    bool CorrectSize () override ;

    /** method which evaluates the matrix multiplication
     * @return unique_ptr to a new matrix, which is the product of multiplication
     */
    std::unique_ptr<CMatrix> Evaluate( ) override ;
private:
    int num;
};


