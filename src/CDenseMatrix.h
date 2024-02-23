/**
* @author Marketa Minarova <minarma5@fit.cvut.cz>
* @date 15.05.20
*/

#pragma once

#include "CMatrix.h"

/**
 * Derived from CMatrix, CDenseMatrix represents class for dense matrix (aka "normal" matrices)
 */

class CDenseMatrix : public CMatrix
{
public:
    CDenseMatrix ( );
    CDenseMatrix ( int x, int y );
    CDenseMatrix & operator = ( CDenseMatrix other );
    CDenseMatrix ( const CMatrix & matrix );

    void                     Print ( std::ostream & os ) const override ;
    void                     PutElements ( int x, int y, value val ) override ;
    value                    GetVal ( int x, int y ) const override ;
    int                      Rank ( ) override ;
    void                     Inv ( ) override ;
    void                     Trans ( ) override ;
    double                   RecursiveDet ( int n, const CMatrix &) override ;
    bool                     isSparse ( ) override ;
    CDenseMatrix IdentityM(int rows, int cols) ;
    std::unique_ptr<CMatrix> Clone() const override ;
    void                     Merge ( const CMatrix & other ) override ;
    void                     Split( int rows, int cols, int x , int y ) override ;
private:

    /** @var m_Matrix is a storage for dense matrices, "classic" 2D array */
    std::vector<std::vector<value>> m_Matrix;
};


