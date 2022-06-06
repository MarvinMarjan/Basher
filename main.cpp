// g++ modules
#include <iostream>
#include <direct.h>
#include <map>

// program modules
#include "cli.hpp"
#include "local_dir.hpp"
#include "cd.hpp"
#include "exceptions_msgs.hpp"
#include "dir.hpp"

using namespace std;

/*

cmd[0] = command
args[0] = first argument of a command

__NULL__ = a empty string | a empty command: "" | literally void

clr = a dictionary that helps to color the console

*/


// a dictionary that contains formated colors for console std output
map<string, string> clr = { 
	{"STD", "\033[0m"},
	{"RED", "\033[0;31m"},
	{"GREEN", "\033[0;32m"},
	{"YELLOW", "\033[1;33m"}
};

// main process
int main(int argc, char *argv[])
{
	// the initial path (the path of the .exe )
	string path = get_local_dir();

	CD cd(path); // CD instantiation: path text handling (path text: "C:\")
	EXCP excp; // EXCP instantiation: contains the exceptions stuff
	DIRS dirs; // DIRS instantiation: directory handling

	while (true)
	{
		// path update
		path = cd.get_path();

		// path text
		cout << path << clr["GREEN"] << " $ " << clr["STD"];

		// splits the command in a vector
		vector<string> cmd = get_command();

		// if if there is no command: a empty string: ""
		if (cmd[0] == "__NULL__" && cmd.size() <= 1) { continue; }

		// cd command
		else if (cmd[0] == "cd") // join in a directory
		{
			// if you have fewer arguments than the minimum
			if (cmd.size() - 1 < cd.get_max_args())
			{
				// i don't remember the meaning of the acronym "isfct" :(
				excp._isfct_args(cmd.size() - 1, "== 1", clr);
				continue;
			}

			// splits all the arguments is a array
			vector<string> args = get_args(cmd);

			// if if you have more arguments than the limit
			if (args.size() > cd.get_max_args()) 
				excp._max_args_overload(cmd[0], args.size(), "== 1", clr);

			else
			{
				// back a directory
				if (args[0] == ".") { cd.cd_b_dir(); }

				else 
				{
					// if the specified path exists
					if (cd.path_exist(args[0]))
					{
						// cd "path"
						cd.cd_dir(args[0]);
					}

					// if path doesn't exists
					else { excp._path_not_found(args[0], clr); }
				}
			}
		}

		// dirs command
		else if (cmd[0] == "dirs")
		{
			vector<string> args = get_args(cmd);

			if (args.size() > dirs.get_max_args()) 
				excp._max_args_overload(cmd[0], args.size(), "== 0", clr);
			else
			{
				// dir_list[i] = [ buf_name, buf_type ]
				
				vector<vector<string>> dir_list = dirs.get_dir_list(path);

				for (int i = 0; i < dir_list.size(); i++)
				{
					cout << clr["GREEN"] << "[ " << dir_list[i][1] << " ]  " << clr["STD"] << dir_list[i][0] << endl;
				}
			}
		}

		// quit the program
		else if (cmd[0] == ".exit")
		{
			// return back to default console color
			cout << clr["STD"] << endl;
			break;
		}

		// if the command doesn't exists
		else
		{
			excp._cmd_not_found(cmd[0], clr);
		}
	}
}