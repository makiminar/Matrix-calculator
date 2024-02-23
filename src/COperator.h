/**
* @author Marketa Minarova <minarma5@fit.cvut.cz>
* @date 05.05.20
*/

#pragma once

#include <memory>
#include "CMatrix.h"

/** COperator is an abstract class for each operation - addition, subtraction, multiplication...this way we can easily
 * add more operations in the future */

class COperator
{
public:
               COperator ( const CMatrix & left, const CMatrix & right );
    virtual   ~COperator() = default;

    /** abstract method to check size of matrices */
    virtual bool CorrectSize() = 0;

    /** abstract method to do the operation that is meant to do */
    virtual std::unique_ptr<CMatrix> Evaluate() = 0;

protected:
    std::unique_ptr<CMatrix> m_Left;
    std::unique_ptr<CMatrix>  m_Right;
};


