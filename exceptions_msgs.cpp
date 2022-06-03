#include <iostream>
#include <string>
#include <map>

#include "exceptions_msgs.hpp"

using namespace std;

void EXCP::_isfct_args(int args_c, string targ_args, map<string, string> clr)
{
	cout << clr["RED"] << "ERROR: " << clr["STD"] << "the arguments passed were less than expected: " <<
		    clr["YELLOW"] << "\n\nexpected: " << clr["STD"] << targ_args << 
		    clr["YELLOW"] << "\nreceived: " << clr["STD"] << args_c << endl;
}

void EXCP::_cmd_not_found(string cmd, map<string, string> clr)
{
	cout << clr["RED"] << "ERROR: " << clr["STD"] << "the command: " << clr["GREEN"] << '\"' << cmd << '\"' << clr["STD"] << " isn't a internal command" << endl << endl;
}