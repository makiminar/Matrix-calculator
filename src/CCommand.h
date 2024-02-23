/**
* @author Marketa Minarova <minarma5@fit.cvut.cz>
* @date 02.05.20
*/

#pragma once

#include <memory>
#include <functional>
#include "CInterface.h"

/**
 * class CCommand represents single command registered in our application, it has it's description and a function
 */

class CCommand
{
public:
    CCommand(std::string description, std::function< bool(const CInterface & )> ex);

    /** method returning description of a CCommand */
    const std::string & getDescription () const;

    /** method to call m_ExecuteCommand
     * @return boolean value, which m_ExecuteCommand returns - and only false when QUIT command is called */
    bool Do ( const CInterface & );

    ~CCommand() = default;

private:
    /** @var detailed description of the command, what it does and how to use it */
    std::string m_Description;
    /** @var  m_ExecuteCommand is a function, which says, what an instance of CCommand is supposed to do */
    std::function< bool ( const CInterface & ) > m_ExecuteCommand;
};


