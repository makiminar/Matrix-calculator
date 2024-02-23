/**
* @author Marketa Minarova <minarma5@fit.cvut.cz>
* @date 02.05.20
*/

#pragma once

#include <vector>
#include <memory>
#include <cmath>
#include <iostream>
#include <algorithm>


/**
 * CMatrix is and abstract class for matrices - it only stores their size (rows and collumns) and offers many abstract
 * functions that can be used polymorphically
 */

class CMatrix
{
public:
    /** value is a data type that matrices will store as elements */
    typedef double value;

    /** SPARSE_CONSTANT is a constant which helps decide whether given matrix is sparse or dense */
    const double SPARSE_CONSTANT = 2.5;

             CMatrix() = default;
             CMatrix( int x, int y);
    virtual ~CMatrix() = default;

    /** abstract method which creates unique pointer to an instance of CMatrix
     * @return unique_ptr to an instance of CMatrix
     */
    virtual std::unique_ptr<CMatrix> Clone() const = 0;

    /** abstract method which prints matrix to the ostream */
    virtual void                     Print ( std::ostream & os ) const = 0;

    /** abstract method which performs matrix transposition */
    virtual void                     Trans ( ) = 0;

    /**
     * abstract method which merges current CMatrix with CMatrix in parameter
     * @param other is CMatrix with which we want this matrix to merge
     */
    virtual void Merge ( const CMatrix & other ) = 0;

    /**
     * abstract method which splits matrix into a new one
     * @param rows is the row size of a new matrix
     * @param cols is the column size of a new matrix
     * @param x is row position of current matrix, from which we'll split it
     * @param y is column position of current matrix, from which we'll split it
     */
    virtual void Split( int rows, int cols, int x , int y ) = 0;

    /** method which evaluates Gauss Elimination Method over matrix */
    virtual void                     GEM ();

    /** abstract method which finds the inverse of a matrix */
    virtual void Inv () = 0;

    /** abstract method which calculated the rank of a matrix */
    virtual int                      Rank () = 0;

    /** method which calculates determinant of a matrix */
    virtual double                   Determinant();

    /** method which determines whether matrix is sparse or not */
    virtual bool                     isSparse();

    /** method which determines whether matrix is square or not */
            bool                     isSquare();

            int                      GetRow() const;
            int                      GetCol() const;

    virtual value                    GetVal(int x, int y) const = 0;
    virtual void                     PutElements ( int x, int y, value val ) = 0;

    /** method which finds the upper triangular form of matrix */
    virtual void                     UpperTriangular(int rows, int cols, int colMax);

    /** method which finds the lower triangular form of matrix */
    virtual void                     LowerTriangular(int rows, int cols, int colMax);

    /** method which makes elements on a diagonal of matrix 1 (first half) and then the second half divides by value
     * which was on the diagonal element ( help function for finding inverse matrix) */
    virtual void                     Diagonal(int rows, int cols);

    /** abstract method which helps to find the determinant of matrix, using recursive algorithm
     * algorithm inspired by an article on geekforgeeks.org:
     * cofactor = matrix created by removing current row and column
     * for each element of first row get cofactor of those elements
     * then multiply the element with the determinant of the corresponding cofactor
     * and add them with alternate signs
      */
    virtual double                   RecursiveDet ( int n, const CMatrix &) = 0;
protected:
    /**
     * @var m_Rows represents number of rows in a matrix
     * @var m_Cols represents number of columns in a matrix
     */
    int m_Rows = 0, m_Cols = 0;
};

