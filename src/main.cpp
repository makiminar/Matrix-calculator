#include <iostream>
#include "CApplication.h"

using namespace std;

/** inspired by @DavidBernhauer */

int main()
{
    try
    {
        CApplication app {CInterface {cin, cout} } ;
        return app.Launch();
    }
    catch ( ios::failure & failure )
    {
        if ( cin.eof() )
            return 0;
        cerr << failure.what() << endl;
        return 50;
    }

}
