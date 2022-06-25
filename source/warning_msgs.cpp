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

void WARN::_system_depedency_file_not_found(string file_path, map<string, string> clr)
{
	cout << clr["BLUE"] << "WARNING: " << clr["STD"] << "system dependency file: " << clr["GREEN"]
		<< '\"' << file_path << '\"' << clr["STD"] << " not found." << endl << "some commands may be unavailable" << endl << endl;
}

void WARN::_command_disabled(string cmd_name, string reason, map<string, string> clr)
{
	cout << clr["BLUE"] << "WARNING: " << clr["STD"] << "the command: " << clr["GREEN"] << '\"' << cmd_name << '\"'
		<< clr["STD"] << "has been disabled\n" << clr["YELLOW"] << "reason: " << '\"' << reason << '\"'
		<< clr["STD"] << endl << endl;
}

void WARN::_not_empty_dir(string d_name, map<string, string> clr)
{
	cout << clr["BLUE"] << "WARNING: " << clr["STD"] << "the directory: " << clr["GREEN"] << '\"' << d_name << '\"'
		<< clr["STD"] << " isn't empty" << clr["STD"] << endl << endl;
}