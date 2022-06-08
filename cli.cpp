// c++ modules
#include <iostream>
#include <vector>
#include <string>

//program modules
#include "cli.hpp"

using namespace std;

vector<string> get_command()
{
	string cmd;
	getline(cin, cmd);

	return split_string(cmd);
}

vector<string> split_string(string str)
{
	vector<string> split_str;
	string aux_str = "";

	for (int i = 0; i < str.size(); i++)
	{
		aux_str = "";

		while (str[i] != ' ')
		{
			aux_str += str[i];
			i++;

			if (i >= str.size())
				break;
		}

		split_str.push_back(aux_str);
	}

	if (split_str.size() < 1)
		split_str.push_back("__NULL__");

	return split_str;
}

vector<string> get_args(vector<string> cmd)
{
	vector<string> args;
	string full_arg = "";

	bool in_quote = false;

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
			
			//full_arg[full_arg.size() - ((full_arg[full_arg.size() - 1] == '\"') ? 1 : 2)] = (char*)"";

			args.push_back(full_arg);
			continue;
		}

		else //if (cmd[o][cmd[o].size() - 1] != '\"')
			args.push_back(cmd[o]);
		
	}

	return args;
}