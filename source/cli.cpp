// c++ modules
#include <iostream>
#include <string>
#include <vector>
#include <map>

//program modules
#include "utilities.hpp"
#include "shortcut.hpp"
#include "cli.hpp"

using namespace std;

vector<string> get_command()
{
	UTILS utils;

	string cmd;
	getline(cin, cmd);

	return utils.split_string(cmd);
}

vector<string> get_args(vector<string> cmd, map<string, string> shortcut)
{
	vector<string> args;
	string full_arg = "";

	// jump index 0 because it's a command
	for (int o = 1; o < cmd.size(); o++)
	{
		if (cmd[o][0] == '\"')
		{
			for (int i = o; i < cmd.size(); i++)
			{
				full_arg += cmd[i] + ((i == cmd.size() - 1) ? "" : " ");

				if (cmd[i][cmd[i].size() - 1] == '\"') 
					break;

				else 
					o++;

			}

			full_arg.erase(0, 1);
			full_arg.erase(full_arg.size() - 1);

			args.push_back(full_arg);
			continue;
		}

		else if (cmd[o][0] == '$')
		{
			for (int i = 1; i < cmd[o].size(); i++)
				full_arg += cmd[o][i];

			args.push_back(shortcut[full_arg]);
		}

		else if (cmd[o] == "+")
		{
			args[args.size() - 1] = args[args.size() - 1] + cmd[o + 1];
			o++;
		}

		else
			args.push_back(cmd[o]);
	}

	return args;
}

vector<string> get_program_args(char* argv[], int argc)
{
	vector<string> args;

	for (int i = 0; i < argc; i++)	
		args.push_back(argv[i]);
	
	return args;
}

vector<string> get_program_flags(char* argv[], int argc)
{
	vector<string> flags;

	for (int i = 0; i < argc; i++)
		if (argv[i][0] == '-')
			flags.push_back(argv[i]);
		
	return flags;
}

vector<string> get_cmd_flags(vector<string> cmd)
{
	vector<string> flags;
	
	for (string i : cmd)
		if (i[0] == '-')
			flags.push_back(i);

	return flags;
}

map<string, bool> set_cmd_modes(vector<string> args)
{
	map<string, bool> modes = {
		{"details_mode", false},
		{"debug_path_mode", false}
	};

	for (string i : args)
	{
		if (i == "-d")
			modes["details_mode"] = true;

		else if (i == "-p")
			modes["debug_path_mode"] = true;
	}

	return modes;
}