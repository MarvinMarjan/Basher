#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "warning_msgs.hpp"

using namespace std;

void WARN::_file_already_exists(string file_name, map<string, string> clr)
{
	cout << clr["BLUE"] << "WARNING: " << clr["STD"] << "the file: " << clr["GREEN"]
		 << '\"' << file_name << '\"' << clr["STD"] << " already exists" << endl << endl;
}

void WARN::_shortcut_already_exists(pair<string, string> shortcut, map<string, string> clr)
{
	cout << clr["BLUE"] << "WARNING: " << clr["STD"] << "the shortcut: " << clr["GREEN"]
		<< '\"' << shortcut.first << '\"' << clr["STD"] << " already exists " 
		<< clr["GREEN"] << "(" << clr["YELLOW"] << shortcut.first << ": " << clr["GREEN"]
		<< shortcut.second << ")" << clr["STD"] << endl << endl;
}