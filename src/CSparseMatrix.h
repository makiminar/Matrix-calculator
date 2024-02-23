/**
* @author Marketa Minarova <minarma5@fit.cvut.cz>
* @date 15.05.20
*/

#pragma once
#include <map>
#include "CMatrix.h"

/**
 * Derived from CMatrix, CSparseMatrix represents storage for sparse matrices
 */

class CSparseMatrix : public CMatrix
{
public:
    CSparseMatrix() = default;
    CSparseMatrix(int x, int y);
    CSparseMatrix(const CMatrix & matrix);
    CSparseMatrix &operator = (CSparseMatrix other);

    void                     Print (std::ostream & os ) const override ;
    void                     PutElements ( int x, int y, value val ) override ;
    value                    GetVal(int x, int y) const override ;
    int                      Rank () override ;
    void                     Inv ()override ;
    void                     Trans() override ;
    double                   RecursiveDet ( int n, const CMatrix &) override ;
    bool                     isSparse() override;
    std::unique_ptr<CMatrix> Clone() const override ;
    void                     Merge ( const CMatrix & other ) override ;
    void                     Split( int rows, int cols, int x , int y) override ;
    CSparseMatrix IdentityM(int rows, int cols) ;
private:

    /** @var m_Sparse is a storage for sparse matrices
     * represented as a map with key value as a pair - row, column index and value (set in CMatrix) as an element */
    std::map<std::pair<int, int>, value> m_Sparse;
};


