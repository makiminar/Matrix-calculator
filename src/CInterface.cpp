/**
* @author Marketa Minarova <minarma5@fit.cvut.cz>
* @date 02.05.20
*/

#include <limits>
#include "CInterface.h"

using namespace std;

CInterface::CInterface(istream &input, ostream &output)
: m_Input(input), m_Output(output)
{
    //setting exception masks, catching is in main.cpp
    m_Input.exceptions ( ios::badbit | ios::failbit );
    m_Output.exceptions ( ios::badbit | ios::failbit | ios::eofbit );
}

string CInterface::GetCommand(const function<bool(const string & input )> & isCommand) const
{
    string tmp;
    m_Output << ENTER_QUOTE << endl;
    while(true)
    {
        if (!(m_Input >> tmp))
        {
            m_Output << MSG_INVALID_INPUT << endl;
        }
        else
        {
            if( isCommand(tmp) )
                return tmp;
            m_Output << MSG_WRONG_COMMAND << endl;
        }
        Clear();
    }
}

void CInterface::PrintHint(const string &command, const string & hint) const
{
    m_Output << command << DELIMITER << hint << endl;
}

void CInterface::PrintMessage(const string & message) const
{
    m_Output << message << endl;
}

void CInterface::PrintMatrix(const std::unique_ptr<CMatrix> & matrix) const
{
    matrix->Print(m_Output);
}

char CInterface::GetName(const function<bool(const char & input )> & isName) const
{
    char tmp;
    while(true)
    {
        if( !(m_Input >> tmp) )
        {
            m_Output << MSG_INVALID_INPUT << endl;
        }
        else
        {
            if(!isName(tmp))
                return tmp;
            m_Output << MSG_EXISTING_MATRIX << endl;
        }
        Clear();
    }
}

bool CInterface::ScanMatrix(CMatrix & matrix) const
{
    CMatrix::value val;
    for(int i =0; i < matrix.GetRow(); ++i)
    {
        for(int j =0; j < matrix.GetCol(); ++j)
        {
                if(! ( m_Input >> val) )
                {
                    m_Output << MSG_INVALID_INPUT << endl;
                    Clear();
                    return false;
                }
             matrix.PutElements(i, j, val);
        }
    }
    return true;
}

void CInterface::Clear() const
{
    m_Input.clear();
    m_Input.ignore(numeric_limits<streamsize>::max(), '\n');
}

bool CInterface::FindName(const function<bool(const char & input )> & isName, char & name) const
{
    char tmp;
    if( !(m_Input >> tmp) )
    {
        m_Output << MSG_INVALID_INPUT << endl;
        return false;
    }

    if(isName(tmp))
    {
        name = tmp;
        return true;
    }

    m_Output << MSG_MATRIX_NOT_FOUND << endl;
    Clear();
    return false;
}

bool CInterface::ScanOp(char & op)
{
    char operand;
    if(! ( m_Input >> operand ) || ( operand != '+' && operand != '-' && operand != '*') )
    {
        m_Output << MSG_INVALID_INPUT << endl;
        Clear();
        return false;
    }
    op = operand;
    return true;
}

bool CInterface::GetEqual()
{
    char sign;
    if( !(m_Input >> sign) || sign != '=' )
    {
        m_Output << MSG_INVALID_INPUT << endl;
        Clear();
        return false;
    }
    return true;
}

bool CInterface::ScanSize(int &x, int &y) const
{
    char br1, br2, br3, br4;
    if( !( m_Input >> br1 >> x >> br2 >> br3 >> y >> br4 ) || ( br1 != '[' && br2 != ']' && br3 != '[' && br4 != ']' ) || x < 0 || y < 0 )
    {
        m_Output << MSG_INVALID_INPUT << endl;
        Clear();
        return false;
    }
    return true;
}

bool CInterface::FindName( string &name ) const
{
    string tmp;
    if( !(m_Input >> tmp) )
    {
        m_Output << MSG_INVALID_INPUT << endl;
        Clear();
        return false;
    }
    name = tmp;
    return true;
}

bool CInterface::ScanIndexes(int &x, int &t)
{
    char br1, br2, br4;
    if( !( m_Input >> br1 >> x >> br2  >> t >> br4 ) || ( br1 != '(' && br2 != ','  && br4 != ')' ) )
    {
        m_Output << MSG_INVALID_INPUT << endl;
        Clear();
        return false;
    }
    return true;
}

void CInterface::PrintResult(double result) const
{
    m_Output << result << endl;
}
