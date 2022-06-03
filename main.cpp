// g++ modules
#include <iostream>
#include <direct.h>
#include <map>

// program modules
#include "cli.hpp"
#include "local_dir.hpp"
#include "cd.hpp"
#include "exceptions_msgs.hpp"

#define STD "\033[0m"
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"

using namespace std;

map<string, string> clr = { 
	{"STD", "\033[0m"},
	{"RED", "\033[0;31m"},
	{"GREEN", "\033[0;32m"},
	{"YELLOW", "\033[1;33m"}
};

// main process
int main(int argc, char *argv[])
{
	string path;

	EXCP excp;

	while (true)
	{
		path = get_local_dir();
		CD cd(path);

		cout << path << clr["GREEN"] << " $ " << clr["STD"];

		vector<string> cmd = get_command();

		if (cmd[0] == "__NULL__" && cmd.size() <= 1) { continue; }

		else if (cmd[0] == "cd")
		{
			if (cmd.size() < 2)
			{
				excp._isfct_args(cmd.size() - 1, ">= 2", clr);
				continue;
			}

			vector<string> args = get_args(cmd);

			for (int i = 0; i < args.size(); i++)
			{
				cout << args[i] << endl;
			}
		}

		else if (cmd[0] == ".exit") { break; }

		else
		{ 
			excp._cmd_not_found(cmd[0], clr);
		}
	}
}