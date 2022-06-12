#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "warning_msgs.hpp"

using namespace std;

void WARN::_file_already_exists(string file_name, map<string, string> clr)
{
	cout << clr["BLUE"] << "WARNING: " << clr["STD"] << "the file: " << clr["GREEN"]
		 << '\"' << file_name << '\"' << clr["STD"] << " already exists" << endl;
}