/**
* @author Marketa Minarova <minarma5@fit.cvut.cz>
* @date 02.05.20
*/

#include "CApplication.h"
#include "CDenseMatrix.h"
#include "CSparseMatrix.h"

using namespace std;

CApplication::CApplication(CInterface interface)
: m_Interface(interface)
{
    m_Commands.emplace(COMMAND_QUIT, CCommandQuit());
    m_Commands.emplace(COMMAND_HELP, CCommandHelp(m_Commands));
    m_Commands.emplace(COMMAND_PRINT, CCommandPrint());
    m_Commands.emplace(COMMAND_SCAN, CCommandScan());
    m_Commands.emplace(COMMAND_GEM, CCommandGem());
    m_Commands.emplace(COMMAND_MERGE, CCommandMerge());
    m_Commands.emplace(COMMAND_SPLIT, CCommandSplit());
    m_Commands.emplace(COMMAND_INV, CCommandInv());
    m_Commands.emplace(COMMAND_TRANS, CCommandTrans());
    m_Commands.emplace(COMMAND_DET, CCommandDet());
    m_Commands.emplace(COMMAND_OP, CCommandOperation());
    m_Commands.emplace(COMMAND_RANK, CCommandRank());
}

int CApplication::Launch()
{
    while( true )
    {
        string command = m_Interface.GetCommand( [ this ] ( const string & input )
                { return m_Commands.count(input) != 0; } ) ;
        auto it = m_Commands.find(command);
        if( !( it->second.Do(m_Interface) ) )
            return 1;
    }
}

CCommand CApplication::CCommandQuit()
{
    return CCommand (DESCRIPTION_QUIT, []( const CInterface & ){ return false; } );
}

CCommand CApplication::CCommandHelp(map<string, CCommand> & commands)
{
    return CCommand ( DESCRIPTION_HELP,[ &commands ] (const CInterface & interface )
            {
                for(auto i: commands)
                    interface.PrintHint(i.first, i.second.getDescription() );
                return true;
            }
    );
}

CCommand CApplication::CCommandPrint()
{
    return CCommand { DESCRIPTION_PRINT, [ this ] ( const CInterface & )
        {
            char tmp;
            if(! (m_Interface.FindName( [this] (const char &input) { return m_Matrices.count(input) != 0;}, tmp ) ) )
                return true;
            auto it = m_Matrices.find(tmp);
                m_Interface.PrintMatrix(it->second);
            return true;
        }
   };
}

CCommand CApplication::CCommandScan()
{
    return CCommand {DESCRIPTION_SCAN,[this] (const CInterface &)
        {
            char tmp = m_Interface.GetName ( [this] (const char &input) { return m_Matrices.count(input) != 0; } );
            int x, y;
            if(! m_Interface.ScanSize(x, y))
                return true;

            unique_ptr<CMatrix> mat{ new CDenseMatrix (x, y)};
            if( ! m_Interface.ScanMatrix(*mat))
                return true;

            if(mat->isSparse())
            {
                unique_ptr<CMatrix> sparse{new CSparseMatrix(*mat)};
                m_Matrices.emplace(tmp, sparse->Clone());
                return true;
            }

            m_Matrices.emplace(tmp, mat->Clone());
            return true;
        }
    };
}


CCommand CApplication::CCommandGem()
{
    return CCommand { DESCRIPTION_GEM,[ this ] ( const CInterface & )
        {
            char tmp;
            if(!( m_Interface.FindName([this] (const char &input) { return m_Matrices.count(input) != 0;}, tmp  ) ) )
                return true;
            auto it = m_Matrices.find(tmp);
            it->second->GEM();
            return true;
        }
    };
}

CCommand CApplication::CCommandMerge()
{
    return CCommand { DESCRIPTION_MERGE,[ this ] ( const CInterface & )
      {
          map<char, std::unique_ptr<CMatrix> >::iterator it1, it2;
          if( ! MergeFunction(it1, it2))
              it1->second->Merge(*it2->second);
          return true;
      }
   };
}

CCommand CApplication::CCommandTrans()
{
    return CCommand { DESCRIPTION_TRANS,[ this ] ( const CInterface & )
        {
            char tmp;
            if(!( m_Interface.FindName([this] (const char &input) { return m_Matrices.count(input) != 0;}, tmp  ) ) )
                return true;
            auto it = m_Matrices.find(tmp);
            it->second->Trans();
            return true;
        }
    };
}

CCommand CApplication::CCommandSplit()
{
    return CCommand { DESCRIPTION_SPLIT,[ this ] ( const CInterface & )
        {
            int x = 0, y = 0, o = 0, p = 0;
            char arg1;
            if(!( m_Interface.FindName([this] (const char &input) { return m_Matrices.count(input) != 0;}, arg1 ) ) )
                return true;
            auto it = m_Matrices.find(arg1);
            if(! m_Interface.ScanSize(x, y))
                return true;
            if(it->second->GetRow() < x || it->second->GetCol() < y || x < 0 || y < 0)
            {
                m_Interface.PrintMessage(MSG_INVALID_MATRIX_SIZE);
                return true;
            }
            if(! m_Interface.ScanIndexes(o, p))
                return true;
            if(it->second->GetRow() < o || it->second->GetCol() < p || o < 0 || p < 0 || (it->second->GetRow() - o ) < x || (it->second->GetCol() - p) < y )
            {
                m_Interface.PrintMessage(MSG_INVALID_INDEX);
                return true;
            }

            it->second->Split(x, y, o, p);
            return true;
        }
    };
}

CCommand CApplication::CCommandInv()
{
    return CCommand { DESCRIPTION_INV,[ this ] ( const CInterface & )
        {
            char tmp;
            if(!( m_Interface.FindName([this] (const char &input) { return m_Matrices.count(input) != 0;}, tmp  ) ) )
                return true;
            auto it = m_Matrices.find(tmp);
            if(! it->second->isSquare())
            {
                m_Interface.PrintMessage(MSG_NOT_SQUARE_MATRIX);
                return true;
            }
            if(it->second->Determinant() == 0)
            {
                m_Interface.PrintMessage(MSG_SINGULAR_MATRIX);
                return true;
            }
            it->second->Inv();
            return true;
        }
   };
}

CCommand CApplication::CCommandDet()
{
    return CCommand { DESCRIPTION_DET,[ this] ( const CInterface &)
        {
            char name1;
            if(!( m_Interface.FindName([this] (const char &input) { return m_Matrices.count(input) != 0;}, name1  ) ) )
                  return true;
            auto it = m_Matrices.find(name1);
            if(! it->second->isSquare())
            {
                  m_Interface.PrintMessage(MSG_NOT_SQUARE_MATRIX);
                  return true;
            }
            double determinant = it->second->Determinant();
            m_Interface.PrintMessage(DET_QUOTE);
            m_Interface.PrintResult(determinant);
            return true;
        }
    };
}

CCommand CApplication::CCommandOperation()
{
    return CCommand { DESCRIPTION_OP,[ this ] ( const CInterface &  )
    {
        char newName = m_Interface.GetName([this] (const char &input) { return m_Matrices.count(input) != 0; });

        if(! m_Interface.GetEqual() )
            return true;

        string op;
        if( ! m_Interface.FindName(op) )
            return true;

        if(op == "1")
        {
            int o, p;
            if(! m_Interface.ScanIndexes(o, p))
                return true;
            if(o != p)
            {
                m_Interface.PrintMessage(MSG_NOT_SQUARE_MATRIX);
                return true;
            }
            CSparseMatrix sp{};
            m_Matrices.emplace(newName, sp.IdentityM(o, p).Clone());
            return true;
        }
        else if(op == "MERGE")
        {
            auto it1 = m_Matrices.begin(), it2 = m_Matrices.begin();
            if ( ! MergeFunction(it1, it2) )
            {
                unique_ptr<CMatrix> mat { new CDenseMatrix (*it1->second)} ;
                mat->Merge(*it2->second);
                m_Matrices.emplace(newName, mat->Clone());
            }
            return true;
        }

        if(op.length() != 1)
        {
            m_Interface.PrintMessage(MSG_INVALID_INPUT);
            return true;
        }

        char name1;
        istringstream iss(op);
        iss >> name1;

          auto it = m_Matrices.find(name1);
          char operand;
          if( ! m_Interface.ScanOp( operand ) )
              return true;

          char name2;
          if(!( m_Interface.FindName([this] (const char &input) { return m_Matrices.count(input) != 0;}, name2  ) ) )
                return true;
          auto it2 = m_Matrices.find(name2);

          unique_ptr<COperator> operation;
           if(operand == '+' )
               operation = make_unique<COperatorPlus>(*it->second, *it2->second);
           else if(operand == '-')
               operation = make_unique<COperatorMinus>(*it->second, *it2->second);
           else if(operand == '*')
              operation = make_unique<COperatorMulti>(*it->second, *it2->second);
           else
           {
               m_Interface.PrintMessage(MSG_INVALID_INPUT);
               return true;
           }

            if( ! operation->CorrectSize())
            {
                m_Interface.PrintMessage(MSG_INVALID_MATRIX_SIZE);
                return true;
            }
            m_Matrices.emplace(newName, operation->Evaluate());
            return true;
        }
     };
}

CCommand CApplication::CCommandRank()
{
    return CCommand {DESCRIPTION_RANK, [this](const CInterface &)
    {
        char tmp;
        if (!(m_Interface.FindName([this](const char &input) { return m_Matrices.count(input) != 0; }, tmp)))
            return true;
        auto it = m_Matrices.find(tmp);
        int rank = it->second->Rank();
        m_Interface.PrintMessage(RANK_QUOTE);
        m_Interface.PrintResult(rank);
        return true;
    }
  };
}

bool CApplication::SplitFunction(std::map<char, std::unique_ptr<CMatrix> >::iterator & it ,int x, int y, int o, int p)
{
    char arg1;
    if(!( m_Interface.FindName([this] (const char &input) { return m_Matrices.count(input) != 0;}, arg1 ) ) )
        return true;
    it = m_Matrices.find(arg1);
    if(! m_Interface.ScanSize(x, y))
        return true;
    if(it->second->GetRow() < x || it->second->GetCol() < y || x < 0 || y < 0)
    {
        m_Interface.PrintMessage(MSG_INVALID_MATRIX_SIZE);
        return true;
    }
    if(! m_Interface.ScanIndexes(o, p))
        return true;
    if(it->second->GetRow() < o || it->second->GetCol() < p || o < 0 || p < 0 || (it->second->GetRow() - o ) < x || (it->second->GetCol() - p) < y )
    {
        m_Interface.PrintMessage(MSG_INVALID_INDEX);
        return true;
    }
    return false;
}

bool CApplication::MergeFunction(std::map<char, std::unique_ptr<CMatrix> >::iterator &it1, std::map<char, std::unique_ptr<CMatrix> >::iterator & it2)
{
    char tmp, tmp2;
    if(!( m_Interface.FindName([this] (const char &input) { return m_Matrices.count(input) != 0;}, tmp  ) ) )
        return true;
    it1 = m_Matrices.find(tmp);
    if(!( m_Interface.FindName([this] (const char &input) { return m_Matrices.count(input) != 0;}, tmp2  ) ) )
        return true;
    it2 = m_Matrices.find(tmp2);
    if(it1->second->GetRow() != it2->second->GetRow())
    {
        m_Interface.PrintMessage(MSG_INVALID_MATRIX_SIZE);
        return true;
    }
    return false;
}
