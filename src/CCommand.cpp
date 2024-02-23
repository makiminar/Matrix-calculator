/**
* @author Marketa Minarova <minarma5@fit.cvut.cz>
* @date 02.05.20
*/

#include "CCommand.h"

using namespace std;

bool CCommand::Do(const CInterface & interface) {
    return m_ExecuteCommand(interface);
}

const string &CCommand::getDescription() const {
    return m_Description;
}

CCommand::CCommand(string description, function< bool(const CInterface &)> ex)
: m_Description(move(description)), m_ExecuteCommand(move(ex))
{ }
