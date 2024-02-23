/**
* @author Marketa Minarova <minarma5@fit.cvut.cz>
* @date 02.05.20
*/

#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <functional>
#include <map>
#include <memory>
#include "CConstants.h"
#include "CMatrix.h"

/**
 * CInterface represents class which handles communication with user, handles input and output and such
 * inspired (not completely, but quite a lot) by @DavidBernhauer
 */

class CInterface
{
public:
                CInterface(std::istream & input, std::ostream & output);

    /**
     * method asks for a command from user input
     * @param isCommand is a function, which determines, if given user input is a registered command
     * (used as a lambda function) in CApplication.cpp
     * @return string, which is name of a command
    */
    std::string GetCommand ( const std::function < bool ( const std::string & input ) > & isCommand ) const;

    /** method prints name of command and then its description */
    void        PrintHint (const std::string & command, const std::string & hint) const;
    void        PrintMessage (const std::string & message) const;
    void        PrintResult ( double ) const;

    /** method to print out instance of CMatrix */
    void        PrintMatrix ( const std::unique_ptr<CMatrix> & matrix ) const;

    /**
     * method asks for a unique name from user input, if the name is already used, user must give another
     * @return char, which is a unique name of CMatrix to be registered
     */
    char        GetName ( const std::function < bool ( const char & input ) > & ) const;

    /** overloading function - first version takes char as a name of Matrix and searches through the storage to find it */
    bool        FindName ( const std::function < bool ( const char & input ) > & isName, char & name ) const;

    /** overloading function - second version only gets a string (for a case when there's OP X = MERGE, 1..) */
    bool        FindName ( std::string & name ) const;
    bool        ScanMatrix ( CMatrix & matrix ) const;
    bool        ScanOp ( char & op );

    /** @return true if operator '=' was found from user input */
    bool        GetEqual ( );
    bool        ScanSize ( int & x, int & t ) const;
    bool        ScanIndexes ( int & x, int & t );
private:

    /** here are stored references of istream and ostream, because doesn't exist copy constructor for them */
    std::istream & m_Input;
    std::ostream & m_Output;

    /** method which clears the input and ignores all new lines */
    void        Clear() const;
};


