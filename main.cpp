// g++ modules
#include <iostream>
#include <direct.h>
#include <map>
#include <csignal>

// program modules
#include "cli.hpp"
#include "local_dir.hpp"
#include "cd.hpp"
#include "exceptions_msgs.hpp"
#include "dir.hpp"
#include "path.hpp"

using namespace std;

/*

cmd[0] = command
args[0] = first argument of a command

__NULL__ = a empty string | a empty command: "" | literally void

clr = a dictionary that helps to color the console


// get the command args 
vector<string> args = get_args(cmd);

*/


// a dictionary that contains formated colors for console std output
map<string, string> clr = { 
	{"STD", "\033[0m"},
	{"RED", "\033[0;31m"},
	{"GREEN", "\033[0;32m"},
	{"YELLOW", "\033[1;33m"}
};

// ctrl + c interrupt handling
void signal_handling(int signum)
{
	cout.flush();
	cout << endl << clr["RED"] + "SIGNAL: " + clr["STD"] + to_string(signum) + " -> "
		+ clr["RED"] + ((signum == 2) ? "PROCESS_INTERRUPT" : "PROCESS_SIGNAL") + clr["STD"];

	exit(signum);
}

// main process
int main(int argc, char *argv[])
{
	signal(SIGINT, signal_handling);

	PATH path = { get_local_dir() }; // PATH instantiation: path object handling
	CD cd = { path.get_path() }; // CD instantiation: path text handling (path text: "C:\")
	EXCP excp; // EXCP instantiation: contains the exceptions stuff
	DIRS dirs; // DIRS instantiation: directory handling

	while (true)
	{
		// path update
		path.set_path(cd.get_path());

		// path text
		cout << path.get_path() << clr["GREEN"] << " $ " << clr["STD"];

		// contains the std::input of user, but splited in a array
		vector<string> cmd = get_command();

		// if if there is no command: a empty string: ""
		if (cmd[0] == "__NULL__" && cmd.size() <= 1) { continue; }

		// clear the console data
		else if (cmd[0] == "clear") { system("cls"); }

		// cd command
		else if (cmd[0] == "cd") // join in a directory
		{
			// a vector containing all command arguments
			vector<string> args = get_args(cmd);

			// if you have fewer arguments than the minimum
			if (args.size() < cd.get_max_args())	
				excp._isfct_args(args.size(), "== 1", clr); // isfct = "inssuficient"

			// if if you have more arguments than the limit
			else if (args.size() > cd.get_max_args()) 
				excp._max_args_overload(cmd[0], args.size(), "== 1", clr);

			else
			{
				// back a directory
				if (args[0] == ".") { cd.cd_b_dir(); }

				// root directory: C:/
				else if (args[0] == "/") { cd.cd_rt_dir(); }

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
			// a vector containing all command arguments
			vector<string> args = get_args(cmd);

			if (args.size() > dirs.get_max_args()) 
				excp._max_args_overload(cmd[0], args.size(), "== 0", clr);

			else
			{
				// dir_list[i] = [ buf_name, buf_type ]
				
				// a vector containing the bufs (files or directorys) [ [0]: buf_name, [1]: buf_type (FILE | DIRS) ]
				vector<vector<string>> dir_list = dirs.get_dir_list(path.get_path()); 

				for (int i = 0; i < dir_list.size(); i++)
				{
					// [ BUF_TYPE ]  BUF_NAME
					cout << clr["GREEN"] << "[ " << dir_list[i][1] << " ]  " << clr["STD"] << dir_list[i][0] << endl;
				}
			}
		}

		else if (cmd[0] == "mdir")
		{
			vector<string> args = get_args(cmd);

			if (args.size() > dirs.get_max_M_DIR_args())
				excp._max_args_overload(cmd[0], args.size(), "== 1", clr);
			

			else if (args.size() < dirs.get_max_M_DIR_args())
				excp._isfct_args(args.size(), "== 1", clr);
			

			else
				dirs.m_dir(args[0]);
			
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