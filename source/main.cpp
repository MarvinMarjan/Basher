// Copyright � Marvin Marjan

#define _VERSION "0.1.0 - (BETA)"

// c++ modules
#include <Windows.h>
#include <iostream>
#include <direct.h>
#include <csignal>
#include <cstdlib>
#include <iomanip>
#include <string>
#include <vector>
#include <map>

// program modules
#include "exceptions_msgs.hpp"
#include "maiky_system.hpp"
#include "warning_msgs.hpp"
#include "flags_arg.hpp"
#include "local_dir.hpp"
#include "utilities.hpp"
#include "shortcut.hpp"
#include "flags.hpp"
#include "boot.hpp"
#include "data.hpp"
#include "file.hpp"
#include "func.hpp"
#include "path.hpp"
#include "cli.hpp"
#include "dir.hpp"
#include "cd.hpp"

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
	{"YELLOW", "\033[1;33m"},
	{"BLUE", "\033[0;34m"},
	{"CYAN", "\033[0;36m"}
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
	UTILS utils; // some util stuff
	BOOT boot; // BOOT instantiation: takes care of startup processes

	const string app_path = (boot.check_app_path() == "NULL") ? "" : boot.check_app_path();

	vector<string> program_args = get_program_args(argv, argc); // contain the program args
	vector<string> flags_array = get_program_flags(argv, argc); // return the boot program args: exmaple: basher [-dc || -rf]

	map<string, bool> modes = boot.set_program_modes(flags_array);
	
	bool read_file_mode = modes["read_file_mode"];
	bool no_clr_mode = modes["no_clr_mode"];
	bool inline_cmd_mode = modes["inline_cmd_mode"];
	bool stay_mode = modes["stay_mode"];

	if (no_clr_mode)
		clr = {
			{"STD", ""},
			{"RED", ""},
			{"GREEN", ""},
			{"YELLOW", ""},
			{"BLUE", ""},
			{"CYAN", ""}
		};

	PATH path = ((read_file_mode) ? "C:/" : get_local_dir()); // PATH instantiation: path object handling
	CD cd = path.get_path(); // CD instantiation: path text handling (path text: "C:\")
	EXCP excp; // EXCP instantiation: contains the exceptions stuff
	WARN warn; // WARN instantiation: contains warning messages
	DIRS dirs; // DIRS instantiation: directory handling
	FILE_HAND file; // FILE instantiation: file system handling
	FUNC func; // FUNC instantiation: in-program-app handling
	SHORTCUT shortcut(app_path, clr); // SHORTCUT instantiation: shortcut handling
	MAIKY_SYSTEM maiky(app_path);

	if (shortcut.can_run)
		shortcut.update("read");

	FLAG_ARG flags_args; // FLAG_ARG instantiation: program flags handling

	FLAGS::READ_FILE_FLAG rf_flag( ((read_file_mode) ? true : false), 0, utils.find_item(program_args, "-rf") + 1);
	FLAGS::INLINE_COMMAND_FLAG inline_cmd_flag( ((inline_cmd_mode) ? true : false), program_args, -1);

	signal(SIGINT, signal_handling);

	while (true)
	{
		map<string, string> shortcut_val = shortcut.get_shortcuts();

		if (read_file_mode && inline_cmd_mode)
		{
			excp._incompatible_flags({ "-rf", "-c" }, clr);
			break;
		}

		if (read_file_mode)
			rf_flag.iterator++; // line

		if (inline_cmd_mode)
			inline_cmd_flag.current++;

		// path update
		path = cd.get_path();

		// if current line > max lines of file
		if (read_file_mode)
		{
			if (rf_flag.iterator > file.get_file_lines(program_args[rf_flag.rf_index], clr))
			{
				if (!stay_mode)
					break;

				else
				{
					read_file_mode = false;
					continue;
				}
			}
		}

		// path text
		cout << path.get_path() << clr["GREEN"] << " $ " << clr["STD"];

		// contains the std::input of user, but splited in a array
		vector<string> cmd = ((read_file_mode) ? flags_args.get_rf_commands(program_args[rf_flag.rf_index], rf_flag.iterator, clr) :
							  (inline_cmd_mode) ? inline_cmd_flag.cmds[inline_cmd_flag.current] : get_command());

		if (inline_cmd_mode)
		{
			for (string i : cmd)
				cout << i << " ";

			cout << endl;
		}

		if (read_file_mode)
		{
			for (string i : cmd) // prints the command
				cout << i << " ";
			
			cout << endl;
		}

		// if if there is no command: a empty string: ""
		if (cmd[0] == "__NULL__" && cmd.size() <= 1) 
			continue;

		else if (cmd[0] == "version" || cmd[0] == "-v" || cmd[0] == "vers")
			cout << clr["CYAN"] << "Basher: " << clr["GREEN"] << _VERSION << clr["STD"] << endl << endl;
		

		else if (cmd[0] == "help")
		{
			cout << clr["RED"] << "--> " << clr["BLUE"] << "tips: " << clr["STD"] << endl << endl;

			cout << clr["YELLOW"] << "1" << clr["STD"] << " - " << "if your argument has spaces, for example: "
				<< clr["GREEN"] << "file name.txt" << clr["STD"] << ",\n      enclose the argument in quotes:" << clr["CYAN"]
				<< " \"" << clr["GREEN"] << "file name.txt" << clr["CYAN"] << "\"" << clr["STD"] << ", so there will be no problems" << endl << endl;

			cout << clr["YELLOW"] << "2" << clr["STD"] << " - " << "you can run basher anywhere in the operating system you want, \n" << 
				"just add an environment variable inside the PATH containing the absolute path of the basher, \n" << 
				"after you do that you also need to add an environment variable \nwith the name of " << clr["GREEN"] << "\"BSH_APP_LOCAL\"" 
				<< clr["STD"] << " and assign the absolute path to the basher, \nand that's it. " << endl << endl;



			cout << clr["RED"] << "-->" << clr["BLUE"] << "commands: " << clr["STD"] << endl << endl;

			cout << clr["YELLOW"] << "clear" << clr["STD"] << " - " << "clean the console" << endl 
				<< "\t\tsyntax: " << clr["YELLOW"] << "clear" << endl << endl;
			
			cout << clr["YELLOW"] << "cd" << clr["STD"] << " - " << "navigate between paths" << endl
				<< "\t\tsyntax: " << clr["YELLOW"] << "cd" << clr["CYAN"] << " [ path ]" << clr["STD"] << endl << endl;

			cout << clr["YELLOW"] << "dirs" << clr["STD"] << " - " << "show all [files|directories] in the current directory" << endl
				<< "\t\tsyntax: " << clr["YELLOW"] << "dirs" << clr["CYAN"] << " [-detail (-d) ? | -path_debug (-p) ?]" << clr["STD"] << endl << endl;

			cout << clr["YELLOW"] << "mdir" << clr["STD"] << " - " << "create a directory" << endl
				<< "\t\tsyntax: " << clr["YELLOW"] << "mdir" << clr["CYAN"] << " [ dir_name ]" << clr["STD"] << endl << endl;

			cout << clr["YELLOW"] << "mdir" << clr["STD"] << " - " << "remove a directory" << endl
				<< "\t\tsyntax: " << clr["YELLOW"] << "rmdir" << clr["CYAN"] << " [ dir_name ]" << clr["STD"] << endl << endl;

			cout << clr["YELLOW"] << "mfile" << clr["STD"] << " - " << "create a file" << endl
				<< "\t\tsyntax: " << clr["YELLOW"] << "mfile" << clr["CYAN"] << " [ file_name ]" << clr["STD"] << endl << endl;

			cout << clr["YELLOW"] << "rmfile" << clr["STD"] << " - " << "remove a file" << endl
				<< "\t\tsyntax: " << clr["YELLOW"] << "rmfile" << clr["CYAN"] << " [ file_name ]" << clr["STD"] << endl << endl;

			cout << clr["YELLOW"] << "write" << clr["STD"] << " - " << "write something to a file" << endl
				<< "\t\tsyntax: " << clr["YELLOW"] << "write" << clr["CYAN"] << " [ file_name ] [ content ]" << clr["STD"] << endl << endl;

			cout << clr["YELLOW"] << "read" << clr["STD"] << " - " << "read the contents of a file" << endl
				<< "\t\tsyntax: " << clr["YELLOW"] << "read" << clr["CYAN"] << " [ file_name ]" << clr["STD"] << endl << endl;

			cout << clr["YELLOW"] << "copy" << clr["STD"] << " - " << "copy a file to another path" << endl
				<< "\t\tsyntax: " << clr["YELLOW"] << "copy" << clr["CYAN"] << " [ file_to_copy_name ] [ target_path ]" << clr["STD"] << endl << endl;

			cout << clr["YELLOW"] << "sys" << clr["STD"] << " - " << "execute an operating system command" << endl
				<< "\t\tsyntax: " << clr["YELLOW"] << "sys" << clr["CYAN"] << " \"[ command ]\"" << clr["STD"] << endl << endl;

			cout << clr["YELLOW"] << "shortcut" << clr["STD"] << " - " << "path shortcuts. path shortcuts - use the $shortcut_name operator \nto access the value of a shortcut. Example: " << "\"cd $desktop\"" << endl
				<< "\t\tsyntax: " << clr["YELLOW"] << "shortcut" << clr["CYAN"] << " [ add ] [ shortcut_name ] [ shortcut_path ]" << clr["STD"] << endl <<
									 clr["YELLOW"] << "\t\t\tshortcut" << clr["CYAN"] << " [ rmv (remove) ] [ shortcut_name ]" << endl <<
				                     clr["YELLOW"] << "\t\t\tshortcut" << clr["CYAN"] << " [ edit ] [ shortcut_name ] [ new_shortcut_path ]" << endl <<
									 clr["YELLOW"] << "\t\t\tshortcut" << clr["CYAN"] << " [ list ] " << clr["STD"] << clr["STD"] << endl << endl;

			cout << clr["YELLOW"] << "repeat" << clr["STD"] << " - " << "repeats a block of code a number of times. (use \".run\" to run de block of code)" << endl
				<< "\t\tsyntax: " << clr["YELLOW"] << "repeat" << clr["CYAN"] << " [ times ]" << clr["STD"] << endl << endl;

			cout << clr["YELLOW"] << ".exit" << clr["STD"] << " - " << "quit the program" << endl
				<< "\t\tsyntax: " << clr["YELLOW"] << ".exit" << clr["STD"] << endl << endl;
		}

		// clear the console data
		else if (cmd[0] == "clear") 
			system("cls");

		// cd command
		else if (cmd[0] == "cd") // join in a directory
		{
			// a vector containing all command arguments
			vector<string> args = get_args(cmd, shortcut_val);

			int max_args = cd.get_max_args();

			// if you have fewer arguments than the minimum
			if (args.size() < max_args)
				excp._isfct_args(args.size(), "== 1", clr); // isfct = "inssuficient"

			// if if you have more arguments than the limit
			else if (args.size() > max_args)
				excp._max_args_overload(cmd[0], args.size(), "== 1", clr);

			else
			{
				// back a directory
				if (args[0] == "." || args[0] == "..")
					cd.cd_b_dir();

				// root directory: C:/
				else if (args[0] == "/") 
					cd.cd_rt_dir();

				else if (!PATH::is_same_path(args[0]))
				{
					// if the specified path exists
					if (cd.path_exist(PATH::check(args[0], path.get_path()))) 
						cd.cd_dir(PATH::check(args[0], path.get_path())); // cd [ path ]

					// if path doesn't exists
					else 
						excp._path_not_found(args[0], clr);
				}
			}
		}

		// dirs command
		else if (cmd[0] == "dirs")
		{
			// a vector containing all command arguments
			vector<string> args = get_args(cmd, shortcut_val);

			int max_args = dirs.get_max_args();

			if (args.size() > max_args) 
				excp._max_args_overload(cmd[0], args.size(), "<= 2", clr);

			else
			{
				// dir_list[i] = [ buf_name, buf_type ]
				
				// a vector containing the bufs (files or directorys) [ [0]: buf_name, [1]: buf_type (FILE | DIRS) ]

				vector<string> cmd_flags = get_cmd_flags(args);
				map<string, bool> cmd_modes = set_cmd_modes(cmd_flags);

				vector<vector<string>> dir_list = dirs.get_dir_list(path.get_path(), cmd_modes["details_mode"], true, cmd_modes["debug_path_mode"], clr);

				/*
				dir_list = [
					[ BUF_NAME, BUF_TYPE, BUF_SIZE ?, BUF_PATH ? ], 
					[ BUF_NAME, BUF_TYPE, BUF_SIZE ?, BUF_PATH ? ]
				]
				*/

				for (int i = 0; i < dir_list.size(); i++)
				{
					if (args.size() >= 1)
					{

						if (cmd_modes["details_mode"])
						{
							float buf_size = stoi(dir_list[i][2]);

							cout << clr["GREEN"] << "[ " << dir_list[i][1] << " ]  ";

							cout << clr["CYAN"] << "[ " << setw(5);

							cout << fixed;

							if (buf_size == -1)
								cout << right << "NULL";

							else
							{
								cout.precision(1);
								cout << right << ((buf_size < 1000)
									? buf_size : (buf_size >= 1000 && buf_size < 1000000)
									? buf_size / 1000 : (buf_size >= 1000000 && buf_size < 1000000000)
									? buf_size / 1000000 : (buf_size >= 1000000000)
									? buf_size / 1000000000 : -1);

								cout << " " << ((buf_size < 1000)
									? "BT" : (buf_size >= 1000 && buf_size < 1000000)
									? "KB" : (buf_size >= 1000000 && buf_size < 1000000000)
									? "MB" : (buf_size >= 1000000000)
									? "GB" : "BIG");
							}

							cout << " ] " << clr["STD"];
							cout << dir_list[i][0] << endl;
						}
					}

					else
						cout << clr["GREEN"] << "[ " << dir_list[i][1] << " ]  " << clr["STD"] << dir_list[i][0] << endl;
				}
			}
		}

		else if (cmd[0] == "mdir")
		{
			vector<string> args = get_args(cmd, shortcut_val);

			int max_args = dirs.get_max_M_DIR_args();

			if (args.size() > max_args)
				excp._max_args_overload(cmd[0], args.size(), "== 1", clr);
			
			else if (args.size() < max_args)
				excp._isfct_args(args.size(), "== 1", clr);

			else
			{
				if (cd.path_exist(PATH::check(args[0], path.get_path())))
					excp._dir_already_exists(args[0], clr);

				else	
					dirs.m_dir(PATH::check(args[0], path.get_path()));
			}
		}

		else if (cmd[0] == "rmdir")
		{
			vector<string> args = get_args(cmd, shortcut_val);

			int max_args = dirs.get_max_RM_DIR_args();

			if (args.size() > max_args)
				excp._max_args_overload(cmd[0], args.size(), "<= 2", clr);

			else if (args.size() < max_args - 1)
				excp._isfct_args(args.size(), "<= 2", clr);

			else
			{
				if (cd.path_exist(PATH::check(args[0], path.get_path())))
				{
					vector<vector<string>> d_list = dirs.get_dir_list(args[0]);

					if (!d_list.size())
						dirs.rm_dir(PATH::check(args[0], path.get_path()));

					else
					{
						vector<string> cmd_flags = get_cmd_flags(args);
						map<string, bool> cmd_modes = set_cmd_modes(cmd_flags);

						warn._not_empty_dir(args[0], clr);
						string inp;

						cout << "would you like to delete it anyway? Y/N: ";
						getline(cin, inp);

						inp = utils.to_lower_case(inp);

						if (inp == "y" || inp == "yes")
							dirs.rm_all_dir(args[0], cmd_modes["debug_path_mode"], clr);
					}
				}

				else
					excp._path_not_found(args[0], clr);
			}
		}

		else if (cmd[0] == "mfile")
		{
			vector<string> args = get_args(cmd, shortcut_val);

			int max_args = file.get_M_FILE_max_args();

			if (args.size() > max_args)
				excp._max_args_overload(cmd[0], args.size(), "== 1", clr);

			else if (args.size() < max_args)
				excp._isfct_args(args.size(), "== 1", clr);
			
			else
			{
				if (cd.file_exist(PATH::check(args[0], path.get_path())))
				{
					string input;

					warn._file_already_exists(args[0], clr);
					cout << "would you like to replace it? Y/N: ";

					getline(cin, input);

					input = utils.to_lower_case(input);

					if (input == "y" || input == "yes")
						file.m_file(cd.format_path(path.get_path()) + args[0]);

					else if (input == "n" || input == "no")
					{
						vector<vector<string>> buf_list = dirs.get_dir_list(path.get_path(), false, true, false, clr);

						string file_i_name;
						int file_i = 1;


						for (int i = 0; i < buf_list.size(); i++)
						{
							if (buf_list[i][0] == to_string(file_i) + "_" + args[0])
								file_i++;
						}

						file_i_name = to_string(file_i) + "_" + args[0];

						file.m_file(cd.format_path(path.get_path()) + file_i_name);
					}
				}

				else
					file.m_file(PATH::check(args[0], path.get_path()));
			}

			cout << endl;
		}

		else if (cmd[0] == "rmfile")
		{
			vector<string> args = get_args(cmd, shortcut_val);

			int max_args = file.get_RM_FILE_max_args();
			
			if (args.size() > max_args)
				excp._max_args_overload(cmd[0], args.size(), "== 1", clr);

			else if (args.size() < max_args)
				excp._isfct_args(args.size(), "== 1", clr);

			else
			{
				if (cd.file_exist(PATH::check(args[0], path.get_path())))
					file.rm_file(PATH::check(args[0], path.get_path()));

				else
					excp._file_not_found(args[0], clr);
			}
		}

		else if (cmd[0] == "read")
		{
			vector<string> args = get_args(cmd, shortcut_val);

			int max_args = file.get_READ_FILE_max_args();

			if (args.size() > max_args)
				excp._max_args_overload(cmd[0], args.size(), "== 1", clr);

			else if (args.size() < max_args)
				excp._isfct_args(args.size(), "== 1", clr);

			else
			{
				if (cd.file_exist(PATH::check(args[0], path.get_path())))
				{
					cout << clr["GREEN"] << '\"' << args[0] << '\"' << clr["STD"] << " content:" << endl << endl;

					vector<string> buffer = file.read_file(cd.format_path(path.get_path()) + args[0]);

					for (int i = 0; i < buffer.size(); i++)
						cout << buffer[i] << endl;
				}

				else
					excp._file_not_found(args[0], clr);
			}
		}

		else if (cmd[0] == "write")
		{
			vector<string> args = get_args(cmd, shortcut_val);

			int max_args = file.get_WRITE_FILE_max_args();

			if (args.size() > max_args)
				excp._max_args_overload(cmd[0], args.size(), "== 2", clr);

			else if (args.size() < max_args)
				excp._isfct_args(args.size(), "== 2", clr);
			
			else
			{
				if (cd.file_exist(PATH::check(args[0], path.get_path())))
					file.write_file(PATH::check(args[0], path.get_path()), args[1], false);

				else
					excp._file_not_found(args[0], clr);
			}
		}

		else if (cmd[0] == "copy")
		{
			vector<string> args = get_args(cmd, shortcut_val);

			int max_args = file.get_COPY_FILE_max_args();

			if (args.size() > max_args)
				excp._max_args_overload(cmd[0], args.size(), "== 2", clr);

			else if (args.size() < max_args - 1)
				excp._isfct_args(args.size(), "== 2", clr);

			else
			{
				if (dirs.get_buf_type(PATH::check(args[0], path.get_path())) == "FILE")
				{
					if (cd.file_exist(PATH::check(args[0], path.get_path())))
					{
						if (cd.path_exist(PATH::check(args[1], path.get_path())))
							file.copy_file(PATH::check(args[0], path.get_path()), cd.format_path(args[1]) + args[0]);

						else
							excp._path_not_found(args[1], clr);
					}


					else
						excp._file_not_found(args[0], clr);
				}

				else
				{
					vector<string> cmd_flags = get_cmd_flags(args);
					map<string, bool> cmd_modes = set_cmd_modes(cmd_flags);

					if (cd.path_exist(PATH::check(args[0], path.get_path())))
					{
						if (cd.path_exist(PATH::check(args[1], path.get_path())))
							dirs.copy_dir(PATH::check(args[0], path.get_path()), cd.format_path(args[1]) + args[0], cmd_modes["debug_path_mode"], clr);

						else
							excp._path_not_found(args[1], clr);
					}

					else
						excp._path_not_found(args[0], clr);
				}
			}
		}

		else if (cmd[0] == "sys")
		{
			vector<string> args = get_args(cmd, shortcut_val);

			if (args.size() > 1)
				excp._max_args_overload(cmd[0], args.size(), "== 1", clr);

			else if (args.size() < 1)
				excp._isfct_args(args.size(), "== 1", clr);

			else
				system(args[0].c_str());
		}

		else if (cmd[0] == "shortcut")
		{
			if (shortcut.can_run)
			{
				shortcut.update("read");
				vector<string> args = get_args(cmd, shortcut_val);

				int max_ADD_args = shortcut.get_max_ADD_args();
				int max_RMV_args = shortcut.get_max_RMV_args();
				int max_EDIT_args = shortcut.get_max_EDIT_args();
				int max_LIST_args = shortcut.get_max_LIST_args();

				if (args[0] == "add")
				{
					if (args.size() > max_ADD_args)
						excp._max_args_overload(cmd[0], args.size(), "== 3", clr);

					else if (args.size() < max_ADD_args)
						excp._isfct_args(args.size(), "== 3", clr);

					else
					{
						bool exist = shortcut.exist(args[1]);

						if (exist)
						{
							string input;

							warn._shortcut_already_exists({ args[1], shortcut.get_shortcuts()[args[1]] }, clr);

							cout << "would you like to replace it? Y/N: ";
							cin >> input;

							input = utils.to_lower_case(input);

							if (input == "y" || input == "yes")
							{
								string new_value;

								getline(cin, new_value);

								shortcut.edit_shortcut(args[1], new_value);
							}
						}

						else
							shortcut.add_shortcut({ args[1], args[2] });
					}
				}

				else if (args[0] == "rmv")
				{
					if (args.size() > max_RMV_args)
						excp._max_args_overload(cmd[0], args.size(), "== 2", clr);

					else if (args.size() < max_RMV_args)
						excp._isfct_args(args.size(), "== 2", clr);

					else if (shortcut.exist(args[1]))
						shortcut.rmv_shortcut(args[1]);

					else
						excp._shortcut_not_found(args[1], clr);
				}

				else if (args[0] == "edit")
				{
					if (args.size() > max_EDIT_args)
						excp._max_args_overload(cmd[0], args.size(), "== 3", clr);

					else if (args.size() < max_EDIT_args)
						excp._isfct_args(args.size(), "== 3", clr);

					else if (shortcut.exist(args[1]))
						shortcut.edit_shortcut(args[1], args[2]);

					else
						excp._shortcut_not_found(args[1], clr);
				}

				else if (args[0] == "list")
				{
					if (args.size() > max_LIST_args)
						excp._max_args_overload(cmd[0], args.size(), "== 1", clr);

					else if (args.size() < max_LIST_args)
						excp._isfct_args(args.size(), "== 1", clr);

					else
					{
						for (auto i : shortcut.get_shortcuts())
							cout << clr["YELLOW"] << i.first << ": " << clr["GREEN"] << i.second << clr["STD"] << endl;

						cout << endl;
					}
				}

				shortcut.update("write");
			}

			else
				warn._command_disabled(cmd[0], "ERROR: _system_depedency_file_not_found", clr);
		}

		else if (cmd[0] == "repeat")
		{
			vector<string> args = get_args(cmd, shortcut_val);

			int max_args = func.get_REPEAT_max_args();
			
			if (args.size() > max_args)
				excp._max_args_overload(cmd[0], args.size(), "== 1", clr);

			else if (args.size() < max_args)
				excp._isfct_args(args.size(), "== 1", clr);

			else
			{
				vector<string> cmds;
				string buffer;

				do
				{
					cout << path.get_path() << clr["GREEN"] << " $" << clr["STD"] << " ---> ";
					getline(cin, buffer);

					if (buffer != ".run")
						cmds.push_back(buffer);

				} while (buffer != ".run");

				func.repeat(stoi(args[0]), cmds, flags_array);
			}
		}

		else if (cmd[0] == "func")
		{
			vector<string> args = get_args(cmd, shortcut_val);

			int max_ADD_args = maiky.get_ADD_MAX_ARGS();
			int max_RMV_args = maiky.get_RMV_MAX_ARGS();

			if (args[0] == "add")
			{
				if (args.size() > max_ADD_args)
					excp._max_args_overload(cmd[0], args.size(), "== 3", clr);

				else if (args.size() < max_ADD_args)
					excp._isfct_args(args.size(), "== 3", clr);

				else
				{
					if (cd.file_exist(args[2]))
						maiky.add_func({ args[1], args[2] });

					else
						excp._path_not_found(args[2], clr);
				}
			}

			else if (args[0] == "rmv")
			{
				if (args.size() > max_RMV_args)
					excp._max_args_overload(cmd[0], args.size(), "== 2", clr);

				else if (args.size() < max_RMV_args)
					excp._isfct_args(args.size(), "== 2", clr);

				else
					maiky.rmv_func(args[1]);
			}

			else if (args[0] == "list")
			{
				if (args.size() > 1)
					excp._max_args_overload(cmd[0], args.size(), "== 1", clr);

				else
					for (auto itr : maiky.get_all_funcs())
						cout << clr["YELLOW"] << itr.first << ": " << clr["GREEN"] << itr.second << clr["STD"] << endl;

				cout << endl;
			}

			maiky.update();
		}

		else if (maiky.exist(cmd[0]))
			maiky.run_func(cmd[0], get_args(cmd, shortcut_val), clr);
		
		// quit the program
		else if (cmd[0] == ".exit")
		{
			// return back to default console color
			if (shortcut.can_run)
				shortcut.update("write");

			cout << clr["STD"] << endl;
			break;
		}

		// if the command doesn't exists
		else
			excp._cmd_not_found(cmd[0], clr);

		if (inline_cmd_mode)
			if (inline_cmd_flag.current + 1 >= inline_cmd_flag.count)
			{
				if (!stay_mode)
					break;

				else
					inline_cmd_mode = false;
			}
	}
}