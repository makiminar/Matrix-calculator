/**
* @author Marketa Minarova <minarma5@fit.cvut.cz>
* @date 02.05.20
*/

#pragma once

#include <map>
#include <string>
#include "CCommand.h"
#include "COperatorPlus.h"
#include "COperatorMinus.h"
#include "COperatorMulti.h"

/**
 * class CApplication represents main class, which takes care of the whole program and its running
 * inspired by @DavidBernhauer and his @Minesweeper
 */

class CApplication {
public:

    CApplication ( CInterface interface);
    ~CApplication () = default;

    /**
     * copy constructor is forbidden, because there will be only one application running at time and therefore, there's
     * no need to make copy of it
     */

    CApplication ( const CApplication & ) = delete;

    /**
     * move operator is also forbidden, for the same reason as copy constructor
     */

    CApplication & operator = ( const CApplication & ) = delete;

    /**
     * method which starts up the application and keeps on running until command QUIT is typed
     * @return 1 when user types QUIT command, ending the program
     */

    int Launch ();

    /** function which creates QUIT command, which ends the program */

    CCommand CCommandQuit();

    /**
     * function which creates CCommand for command HELP, which prints out description of every registered command
     * @param commands takes the whole menu of commands, stored in CApplication
     */

    CCommand CCommandHelp(std::map<std::string, CCommand> & commands);

    /** function which creates CCommand for PRINT, which prints out given matrix */

    CCommand CCommandPrint();

    /** function which creates CCommand, which is used for scanning matrix from user input */

    CCommand CCommandScan();

    /** function creates CCommand for GEM command */

    CCommand CCommandGem();

    /** function creates CCommand for MERGE command, which merges 2 given matrices, if possible */

    CCommand CCommandMerge();

    /** function creates CCommand for TRANS command, which does transposition over given matrix*/

    CCommand CCommandTrans();

    /** function creates CCommand for SPLIT command, which splits one matrix by some parameters and creates new one */

    CCommand CCommandSplit();

    /** function creates CCommand for INV command, as to find an inverse of given matrix */

    CCommand CCommandInv();

    /** function creates CCommand for DET command, as to calculate determinant of a given matrix */

    CCommand CCommandDet();

    /** function creates CCommand for OP command, which does some operation in which a new matrix is created and stored */

    CCommand CCommandOperation();

    /** function creates CCommand for RANK command, which calculates rank of a given matrix */

    CCommand CCommandRank();

    bool SplitFunction(std::map<char, std::unique_ptr<CMatrix> >::iterator & it, int x, int y, int o, int p);
    bool MergeFunction(std::map<char, std::unique_ptr<CMatrix> >::iterator & it1, std::map<char, std::unique_ptr<CMatrix> >::iterator & it2);
private:
    CInterface m_Interface;

    /** @var m_Commands - menu of commands, that user can execute */
    std::map<std::string, CCommand> m_Commands;

    /** @var m_Matrices - storage of matrices used or created by user, their name and a unique pointer, so that
     * the polymorphism can take place */
    std::map<char, std::unique_ptr<CMatrix> > m_Matrices;
};


